#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>
#include "dbg.h"

struct ListNode;

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

#define List_count(A) ((A)->count)
#define List_value(N) ((N) != NULL ? (N)->value : NULL)
#define List_first(A) (List_value((A)->first))
#define List_last(A) (List_value((A)->last))

#define List_check(L) \
    check(L != NULL, "List is NULL.");\
    check(L->count >= 0, "List count is less than 0.");\
    check(L->count == 0 || L->first != NULL, "First item in list is NULL, but should not be.");

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);
List *List_copy(List *source);

void *List_remove(List *list, ListNode *node);

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif