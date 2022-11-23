https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
//=================================================================
// Implementation for DLL module.
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"
#include "globals.h"

LLNode* create_llnode(void* data) {
    // complete this function (see doubly_linked_list.h for documentation)
    LLNode* newNode;
    return newNode;
}

DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

void insertHead(DLinkedList* dLinkedList, void* data){
  LLNode* newNode = create_llnode(data);
  // complete this function
}

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){
  // complete this function
}

void destroyList(DLinkedList* dLinkedList){
  LLNode* Node = dLinkedList->head;
  LLNode* Next;
  while(Node){
    free(Node->data);
    Next = Node->next;
    free(Node);
    Node = Next;
    }
  free(dLinkedList);
}

int getSize(DLinkedList* dLinkedList){
  return dLinkedList->size;
}

// Check for common errors and ASSERT_P to raise the error code.
void testDLL(void){
  int n = 4;
  LLItem* m[n];
  DLinkedList* myList = create_dlinkedlist();
  while (n--)
    m[n] = (LLItem*) malloc(sizeof(LLItem));
  for(n = 0; n<3; n++){
    insertHead(myList, m[n]);
    if ((myList->head->data != m[n]) || (getSize(myList) != n+1))
      uLCD.printf("Complete and debug DLL to get rid of this error\n");
    ASSERT_P(myList->head->data == m[n], ERROR_DLL_INSERT_HEAD);
    ASSERT_P(getSize(myList) == n+1, ERROR_DLL_INSERT_HEAD);
  }
  // [2 1 0]
  LLNode* current = myList->head;
  for (n = 2; n>=0; n--){
    if (current->data != m[n])
      uLCD.printf("Complete and debug DLL to get rid of this error\n");
    ASSERT_P(current->data == m[n], ERROR_DLL_INSERT_HEAD);
    current = current->next;
  }
  pc.printf("OK DLL 3 x insertHead: [2 1 0]\n");
  uLCD.printf("OK DLL 3 inserts:\n    [2 1 0]\n");
  deleteNode(myList, myList->head->next);  // delete middle node
  if (getSize(myList) != 2) 
    uLCD.printf("Complete and debug DLL to get rid of this error\n");
  ASSERT_P(getSize(myList) == 2, ERROR_DLL_DELETE);
  // [2 0]
  current = myList->head;
  for (n = 2; n>=0; n=n-2){
    if (current->data != m[n]) 
      uLCD.printf("Complete and debug DLL to get rid of this error\n");
    ASSERT_P(current->data == m[n], ERROR_DLL_DELETE);
    current = current->next;
  }
  pc.printf("OK DLL deleteNode middle: [2 0]\n");
  uLCD.printf("OK DLL del mid:\n    [2 0]\n");
  insertHead(myList, m[3]); // 3 2 0
  if (getSize(myList) != 3) 
    uLCD.printf("Complete and debug DLL to get rid of this error\n");
  ASSERT_P(getSize(myList) == 3, ERROR_DLL_INSERT_HEAD);
  pc.printf("OK DLL insertHead: [3 2 0]\n");
  uLCD.printf("OK DLL 1 ins:\n    [3 2 0]\n");
  deleteNode(myList, myList->head);  // delete head
  if (getSize(myList) != 2)
    uLCD.printf("Complete and debug DLL to get rid of this error\n");
  ASSERT_P(getSize(myList) == 2, ERROR_DLL_DELETE);
  current = myList->head;
  // [2 0]
  for (n = 2; n>=0; n=n-2){
    if (current->data != m[n]) 
      uLCD.printf("Complete and debug DLL to get rid of this error\n");
    ASSERT_P(current->data == m[n], ERROR_DLL_DELETE);
    current = current->next;
  }
  pc.printf("OK DLL deleteNode head: [2 0]\n");
  uLCD.printf("OK DLL del head:\n    [2 0]\n");
  destroyList(myList);
}
