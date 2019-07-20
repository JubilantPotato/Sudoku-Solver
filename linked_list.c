/*
 * Author: Tristan Lynass-Margetic
 * Student ID: 19132484
 * Last modified: 27/10/2017
 * Purpose: A collection of functions and structs that together allow the use
 *          of the abstract data type, 'linked list'. This implimentation has
 *          been written to so that it is a doublely-ended and linked list.
 */

#include <stdlib.h>
#include "linked_list.h"

/*
 * Purpose: Allocates all required memory for LinkedList and initialises
 *          struct members.
 * Algorithm: n/a
 * Relations: This stores a chain of references to LinkedListNodes to,
 *            and is designed to be modifed by the other functions in 
 *            linked_list.c.
 */ 
LinkedList* createList()
{
    LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;

    return newList;
}

/* Destroyer */
void destroyList(LinkedList* list)
{
    LinkedListNode* nextNode = list->head;
    
    while(nextNode != NULL)
    {
        LinkedListNode* prev = nextNode;
        nextNode = nextNode->next;
        free(prev);
    }

    free(list);
}

LinkedListNode* createNode(int newData)
{
    LinkedListNode* newNd = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNd->data = newData;
    newNd->next = NULL;
    newNd->prev = NULL;

    return newNd;
}

/* Setters */
void insertFirst(LinkedList* list, int newData)
{
    LinkedListNode* newNd = createNode(newData); 

    if (isEmpty(list))
    {
        list->tail = newNd;
    }
    else
    {
        newNd->next = list->head;
        list->head->prev = newNd;
    }

    list->head = newNd;
    list->size++;
}

void insertLast(LinkedList* list, int newData)
{
    LinkedListNode* newNd = createNode(newData);

    if (isEmpty(list))
    {
        list->head = newNd;
    }
    else
    {
        newNd->prev = list->tail;
        list->tail->next = newNd;
    }

    list->tail = newNd;
    list->size++;
}

/* Getters */
int removeFirst(LinkedList* list)
{
    int nodeValue = -1;
    
    if (!isEmpty(list))
    {
        LinkedListNode* delNd = list->head;
        nodeValue = delNd->data;
        
        /* One node in list */
        if (list->head == list->tail)
        {
            list->head = NULL;
            list->tail = NULL;
        }
        /* Mutli-node list */
        else
        {
            list->head = delNd->next;
        }
        
        free(delNd);
        list->size--;
    }

    return nodeValue;
}

int removeLast(LinkedList* list)
{
    int nodeValue = -1;
    
    if (!isEmpty(list))
    {
        LinkedListNode* delNd = list->tail;
        nodeValue = delNd->data;
        
        /* One node in list */
        if (list->head == list->tail)
        {
            list->head = NULL;
            list->tail = NULL;
        }
        /* Mutli-node list */
        else
        {
            list->tail = delNd->prev;
        }
        
        free(delNd);
        list->size--;
    }

    return nodeValue;
}

int peekFirst(LinkedList* list)
{
    int nodeValue = -1;

    if (list->head != NULL)
    {
        nodeValue = list->head->data;
    }

    return nodeValue;
}

int peekLast(LinkedList* list)
{
    int nodeValue = -1;

    if (list->tail != NULL)
    {
        nodeValue = list->tail->data;
    }

    return nodeValue;
}

/* Misc. Functions */
int isEmpty(LinkedList* list)
{
    return list->size == 0;
}
    
