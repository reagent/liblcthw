#ifndef _tests_h
#define _tests_h

#include <dlfcn.h>

typedef int (*lib_function)(const char *data);
char *lib_file = "build/libsample.so";
void *lib = NULL;

int check_function(const char *func_to_run, const char *data, int expected)
{
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

    int rc = func(data);
    check(rc == expected, "Function %s returned %d for data: %s", func_to_run, rc, data);

    return 1;
error:
    return 0;
}

#endif