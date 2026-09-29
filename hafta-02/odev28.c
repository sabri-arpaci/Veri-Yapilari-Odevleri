//10 20 30 NULL listesinin başına 5 ekleyin. Sonuç 5 10 20 30 NULL olmalıdır.
#include <stdio.h>
#include <stdlib.h>

// Definition of a singly linked list node
struct Node {
    int data;
    struct Node *next;
};

int main() {
    struct Node *first = (struct Node *)malloc(sizeof(struct Node));
    struct Node *second = (struct Node *)malloc(sizeof(struct Node));
    struct Node *third = (struct Node *)malloc(sizeof(struct Node));

    if (first == NULL || second == NULL || third == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    first->data = 10;
    first->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = NULL;

    struct Node *head = first; 

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    newNode->data = 5;
    newNode->next = head; // 5 points to 10
    head = newNode;       // New head is now 5

    struct Node *current = head;
    printf("Updated Linked List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    free(newNode); // Frees node 5
    free(first);   // Frees node 10
    free(second);  // Frees node 20
    free(third);   // Frees node 30

    return 0;
}