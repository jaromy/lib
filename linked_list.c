// Implement a linked list
//  Append - add node to end of list
//  printList - print the data field from the entire linked list
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node* next;
};

// create new node
// if existing list empty, point to newly created node
// otherwise, append new node to existing list
// NOTE: node will be read-only, except in the case where we pass in NULL.
//    In this case appendNode will create first item in linked list.
void appendNode(struct Node** node, int data) {
  struct Node* p = malloc(sizeof(struct Node));
  if (p == NULL) {
    return;
  } else {
    p->data = data;
    p->next = NULL;
  }

  if (*node == NULL) {        // existing linked list is empty; this is 1st element
    *node = p;                //  so assign it as such
    return;
  }

  // else, append to end of list; i.e. find last element
  // set temp variable while traversing list so we don't
  // change passed in variable; we need node to point to head!

  // traverse list to get to last element
  struct Node* xp = *node;
  while (xp->next != NULL) {
    xp = xp->next;
  }

  xp->next = p;   // append newly created Node
}

void printList(struct Node* node) {
  while (node != NULL) {
    printf("%i\n", node->data);
    node = node->next;
  }
}




int main(int argc, char* argv[]){

  struct Node* head = NULL;
  appendNode(&head, 1);
  appendNode(&head, 2);
  appendNode(&head, 3);

  printf("hello world\n");
  printList(head);
  return 0;
}
