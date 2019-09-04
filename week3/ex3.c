#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode ListNode;

typedef struct ListNode {
    int element;
    ListNode* next;
} ListNode;


typedef struct LinkedList {
    ListNode* first;
} LinkedList;


void insert_node(LinkedList* list, ListNode* node, int element) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return;
    }
    newNode->element = element;

    if (node == NULL) {
      newNode->next = NULL;
      list->first = newNode;
    } else {
      newNode->next = node->next;
      node->next = newNode;
    }
}


void delete_node(ListNode* node) {
    if (node->next == NULL) {
      return;
    }
    ListNode* toFree = node->next;
    node->next = node->next->next;
    free(toFree);
}


void print_list(LinkedList* list) {
    ListNode* curr = list->first;
    printf("[");
    while (curr != NULL && curr->next != NULL) {
        printf("%d, ", curr->element);
        curr = curr->next;
    }
    if (curr != NULL) {
        printf("%d", curr->element);
    }
    printf("]\n");
}


int main() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->first = NULL;

    print_list(list);
    insert_node(list, list->first, 5);
    print_list(list);
    insert_node(list, list->first, 2);
    print_list(list);
    insert_node(list, list->first->next, 3);
    print_list(list);
    delete_node(list->first);
    print_list(list);
}
