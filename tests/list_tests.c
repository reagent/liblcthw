#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

char *str1 = "test1 data";
char *str2 = "test2 data";
char *str3 = "test3 data";

char *test_create()
{
    List *list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    List_destroy(list);
    return NULL;
}

char *test_destroy()
{
    List *list = List_create();

    List_clear_destroy(list);

    return NULL;
}

char *test_push_pop()
{
    List *list = List_create();

    char *test1 = strdup(str1);
    char *test2 = strdup(str2);
    char *test3 = strdup(str3);

    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value.");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");
    free(val);

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");
    free(val);

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    free(val);

    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    List_clear_destroy(list);

    return NULL;
}

char *test_unshift()
{
    List *list = List_create();

    char *test1 = strdup(str1);
    char *test2 = strdup(str2);
    char *test3 = strdup(str3);

    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value.");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong first value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    List_clear_destroy(list);

    return NULL;
}

char *test_remove()
{
    List *list = List_create();

    char *test1 = strdup(str1);
    char *test2 = strdup(str2);
    char *test3 = strdup(str3);

    List_unshift(list, test1);
    List_unshift(list, test2);
    List_unshift(list, test3);

    char *val = List_remove(list, list->first->next);
    free(val);

    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    List_clear_destroy(list);

    return NULL;
}

char *test_shift()
{
    List *list = List_create();

    char *test1 = strdup(str1);
    char *test3 = strdup(str3);

    List_unshift(list, test1);
    List_unshift(list, test3);

    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");
    free(val);

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    free(val);

    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    List_clear_destroy(list);

    return NULL;
}

char *test_copy()
{
    List *list = List_create();

    char *test1 = strdup(str1);
    char *test2 = strdup(str2);
    char *test3 = strdup(str3);

    List *copy1 = List_copy(list);

    mu_assert(List_count(copy1) == 0, "Wrong count on copying empty list.");

    List_push(list, test1);
    List_push(list, test2);
    List_push(list, test3);

    mu_assert(List_count(list) == 3, "Wrong count after push.");

    List *copy2 = List_copy(list);

    mu_assert(List_count(copy2) == 3, "Wrong count after copy.");

    mu_assert(copy2->first != NULL, "First element null after copy.");
    mu_assert(copy2->last != NULL,  "Last element null after copy.");

    mu_assert(copy2->first != list->first, "First element points to source node.");
    mu_assert(copy2->first != list->last,  "Last element points to source node.");

    mu_assert(List_first(copy2) == test1, "Wrong first element value.");
    mu_assert(List_last(copy2)  == test3, "Wrong last element value.");

    ListNode *prev = NULL;
    ListNode *node = copy2->first;

    mu_assert(node->prev == NULL, "Previous element is not NULL.");
    mu_assert(node->next != NULL, "Next element is NULL.");

    prev = node;
    node = node->next;

    mu_assert(node != NULL, "Next element is NULL.");
    mu_assert(node->prev == prev, "Next element points to wrong previous node.");
    mu_assert(node->next == copy2->last, "Next element points at wrong next node.");
    mu_assert(List_value(node) == test2, "Wrong value for next node.");

    prev = node;
    node = node->next;

    mu_assert(node != NULL, "Next element is NULL.");
    mu_assert(node->prev == prev, "Next element points to wrong previous node.");
    mu_assert(node->next == NULL, "Next element points at non-NULL node.");
    mu_assert(copy2->last == node, "Last element points at wrong node.");

    List_destroy(copy1);
    List_destroy(copy2);
    List_clear_destroy(list);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_destroy);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_copy);

    return NULL;
}

RUN_TESTS(all_tests);