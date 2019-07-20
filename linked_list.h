#ifndef LL_H
#define LL_H
#include "util.h"

/*
 * Purpose: Stores the data and pointers for an individual node in the list.
 * Algorithm: n/a
 * Relations: This is stored though a chain of references within the 
 *            LinkedList struct.
 */ 
typedef struct LinkedListNode
{
    int data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode;

/*
 * Purpose: Stores head and tail pointers, that act as the starting points
 *          for accessing, inserting, deleting, etc, in a linked list.
 * Algorithm: n/a
 * Relations: This stores a chain of references to LinkedListNodes to,
 *            and is designed to be modifed by the other functions in 
 *            linked_list.c.
 */ 
typedef struct
{
    LinkedListNode* head;
    LinkedListNode* tail;
    int size;
} LinkedList;

LinkedList* createList();
void destroyList(LinkedList* list);
LinkedListNode* createNode(int newData);
void insertFirst(LinkedList* list, int newData);
void insertLast(LinkedList* list, int newData);
int removeFirst(LinkedList* list);
int removeLast(LinkedList* list);
int peekFirst(LinkedList* list);
int peekLast(LinkedList* list);
int isEmpty(LinkedList* list);

#endif
