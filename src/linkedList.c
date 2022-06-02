/*
 * FILE: linkedList.c
 * AUTHOR: Vansitha Induja Ratnayake
 * UNIT: Unix Systems Programming COMP2002
 * PURPOSE: Contains function implementations to create a generic linked list
 * REFERENCE: This file was previously submitted for COMP1000 Unix and C Programming Incremental task 2
 *            Final Examination, and Unix Systems Programming COMP2002 Mid Semester Examination. Modifed
 *            the file to meet current programs requirements.
 *            (REFERENCES ARE LISTED BELOW IN ORDER OF RECENT TO EARLIEST.)
 *            Ratnayake. Vansitha, Induja. 2022. USP COMP2002 Mid Semester Examination.
 *            Ratnayake. Vansitha, Induja. 2021. UCP COMP1000 Final Examination.
 *            Ratnayake. Vansitha, Induja. 2021. UCP COMP1000 Incremental Task 2.
 *            Liang, Antoni. 2021. "Practical 06-Structs Unix and C Programming".
 *            https://echo360.net.au/section/a5467870-5383-4267-bb2f-13c2cd3a1e6c/home
 *            (converted pseudocode from practical supplementary video)
 * COMMENTS: removed insertFirst() function and added an insertlast() function
 * LAST MOD: 29/05/2022
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "linkedList.h"


/* 
 * NAME: createLinkedList
 * PURPOSE: Creates an empty linkedlist pointing to the head node
 * IMPORTS: none
 * EXPORTS: linkedlist (ll)
 * ASSERTIONS:
 *      PRE: None
 *      POST: Creates empty linked list
*/
LinkedList *createLinkedList()
{

    // increase the size of the heap  (program break)
    void *newBrk = sbrk(PAGE_SIZE);

    LinkedList *ll = (LinkedList *)newBrk;
    ll->head = NULL;

    return ll;
}

/*
 * NAME: insertLast
 * PURPOSE: Inserts a new node to end of the list
 * IMPORTS: linkedlist, data
 * EXPORTS: None
 * ASSERTIONS:
 *      PRE: linked list must be intitalized first
 *      POST: Adds a new node to the end of the list
 * REMARKS: None
 */
void insertLast(LinkedList *list, void *data)
{
    ListNode *newNode;
    void *newBrk = sbrk(PAGE_SIZE); //returns the previously program break
    newNode = (ListNode *)newBrk;

    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL)
    {
        list->head = newNode;
    }
    else
    {
        ListNode *lastNode = list->head;
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}

/* 
 *  NAME: freeLinkedList
 *  PURPOSE: Free allocated memory for the linked list in heap memory
 *  IMPORTS: linkedlist, function pointer
 *  EXPORTS: None
 *  ASSERTIONS:
 *      PRE: Any operations with the linked list my be dealt with before function is called
 *      POST: Linked list does not exist in memory
*/
void freeLinkedList(LinkedList *list, void (*fp)(void *))
{

    ListNode *currNode;
    ListNode *nextNode;

    currNode = list->head;

    while (currNode != NULL)
    {
        nextNode = currNode->next;
        (*fp)(currNode->data);
        currNode = nextNode;
    }
}

/* 
 *  NAME: freeData
 *  PURPOSE: Special function to free the coordinate data stores in the linked list
 *           required for the undo feature
 *  IMPORTS: data
 *  EXPORTS: None
 *  ASSERTIONS:
 *      PRE: At least one node should contain coordinate data in linked list
 *      POST: Coordinate data cannot be used for futher operations
*/
void freeData(void *data)
{
    char *value = (char *)data;
    free(value);
    data = NULL;
}