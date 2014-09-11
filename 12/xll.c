#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#define GET_PTR(link, node) ((XNode*) (((unsigned) (link)) ^ ((unsigned) (node))))

typedef struct XNode {
    int           data;
    struct XNode *link;
} XNode;

typedef struct XList {
    XNode *head;
    XNode *tail;
} XList;

typedef int (*XListTraversalFunc) (XNode *node, void *context);

int InsertBefore (XList *list, XNode *nodeToInsert, XNode *refnode)
{
    XNode *prev;
    XNode *curr;
    XNode *next;
    XNode *t;

    // First insertion
    if (list->head == NULL) {
        assert (list->tail == NULL);
        assert (refnode == NULL);

        nodeToInsert->link = NULL;
        list->head = list->tail = nodeToInsert;
        return 1;
    }

    assert (list->tail != NULL);

    // Insert as first
    if (refnode == NULL || refnode == list->head) {
        nodeToInsert->link = list->head;
        list->head->link = GET_PTR (nodeToInsert, list->head->link);
        list->head = nodeToInsert;
        return 1;
    }


    curr = list->head;
    prev = NULL;
    while (curr && curr != refnode) {
        next = GET_PTR (curr->link, prev);
        prev = curr;
        curr = next;
    }

    if (curr != refnode) return 0;


    nodeToInsert->link = GET_PTR(prev, curr);
    // Update prev's link
    t = GET_PTR(prev->link, curr);
    prev->link = GET_PTR (t, nodeToInsert);

    // Update curr's link
    t = GET_PTR (curr->link, prev);
    curr->link = GET_PTR (nodeToInsert, t);
    return 1;
}

void Traverse (XList *list, XListTraversalFunc callback, void *context)
{
    XNode *curr = list->head;
    XNode *prev = NULL;
    XNode *next;

    while (curr) {
        if (callback (curr, context) == 0) break;
        next = GET_PTR (curr->link, prev);
        prev = curr;
        curr = next;
    }
}

void TraverseBack (XList *list, XListTraversalFunc callback, void *context)
{
    XNode *curr = list->tail;
    XNode *prev;
    XNode *next = NULL;

    while (curr) {
        if (callback (curr, context) == 0) break;
        prev = GET_PTR (curr->link, next);
        next = curr;
        curr = prev;
    }
}

int Delete (XList *list, XNode *node)
{
    XNode *curr = list->head;
    XNode *next;
    XNode *prev = NULL;
    XNode *t;
    XNode *t1;

    if (list->head == NULL) return 0;

    assert (list->tail != NULL);

    while (curr && curr != node) {
        next = GET_PTR (curr->link, prev);
        prev = curr;
        curr = next;
    }

    if (curr != node) return 0;

    next = GET_PTR (curr->link, prev);
    // Update prev
    if (prev) {
        t = GET_PTR (prev->link, curr);
        prev->link = GET_PTR (t, next);
    } else {
        list->head = next;
    }

    // Update next
    if (next) {
        t = GET_PTR (next->link, curr);
        next->link = GET_PTR (prev, t);
    } else {
        list->tail = prev;
    }

    return 1;
}

int PrintData (XNode *node, void* p)
{
    printf ("%ld ", node->data);
    return 1;
}

void PrintListBackAndForward (XList *list)
{
    printf ("Forward: ");
    Traverse (list, PrintData, NULL);
    printf ("\n");

    printf ("Backward: ");
    TraverseBack (list, PrintData, NULL);
    printf ("\n");
}

XNode* GetNode (int data)
{
    XNode *n;
    n = (XNode*) malloc(sizeof(XNode));
    n->data = data;
    return n;
}

int main()
{
    XList lst;
    XNode *n;
    XNode *n1;
    lst.head = lst.tail = NULL;


    n = GetNode (100);
    InsertBefore (&lst, n, NULL);

    n1 = GetNode(200);
    InsertBefore (&lst, n1, NULL);
    InsertBefore (&lst, GetNode(150), n);
    InsertBefore (&lst, GetNode(180), n);

    PrintListBackAndForward (&lst);

    Delete (&lst, n1);
    PrintListBackAndForward (&lst);

    Delete (&lst, n);
    PrintListBackAndForward (&lst);
    return 0;
}
