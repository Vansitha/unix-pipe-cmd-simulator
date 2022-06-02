/*
 * FILE: linkedList.h
 * AUTHOR: Vansitha Induja Ratnayake
 * UNIT: Unix Systems Programming COMP2002
 * PURPOSE: Contains function declarations and constants to create a generic linked list
 * REFERENCE: This file was previously submitted for COMP1000 Unix and C Programming Incremental task 2
 *            Final Examination, and Unix Systems Programming COMP2002 Mid Semester Examination. Modifed
 *            the file to meet current programs requirements.
 *            (REFERENCES ARE LISTED BELOW IN ORDER OF RECENT TO EARLIEST.)
 *            Ratnayake. Vansitha, Induja. 2022. USP COMP2002 Mid Semester Examination.
 *            Ratnayake. Vansitha, Induja. 2021. UCP COMP1000 Final Examination.
 *            Ratnayake. Vansitha, Induja. 2021. UCP COMP1000 Incremental Task 2.
 *            Liang, Antoni. 2021. "Practical 06-Structs Unix and C Programming".
 *            https://echo360.net.au/section/a5467870-5383-4267-bb2f-13c2cd3a1e6c/home
 * COMMENTS: removed insertFirst() function and added an insertlast() function
 * LAST MOD: 29/05/2022
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define PAGE_SIZE 4096 // 40096 bytes -> 4kb

/* List node */
typedef struct ListNode
{
    void *data;
    struct ListNode *next;

} ListNode;

/* head node */
typedef struct
{
    ListNode *head;

} LinkedList;

/* insert the data through this */
typedef void (*funcPtr)(void *data);

/*LinkedList *createLinkedList();*/
LinkedList *createLinkedList();
void insertFirst(LinkedList *list, void *data);
void insertLast(LinkedList *list, void *data);
void freeData(void *data);
void freeLinkedList(LinkedList *list, void (*fp)(void *));

#endif