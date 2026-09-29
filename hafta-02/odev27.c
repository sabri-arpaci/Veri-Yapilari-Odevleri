//Kullanıcının girdiği sayının 10 20 30 40 NULL listesinde olup olmadığını bulun.
#include <stdio.h>
#include <stdlib.h>
struct Node{
    int data;
    struct Node *next;
};

int main(){
    struct Node *head=(struct Node*)malloc(sizeof(struct Node));
    struct Node *second=(struct Node*)malloc(sizeof(struct Node));
    struct Node *third=(struct Node*)malloc(sizeof(struct Node));
    struct Node *fourth=(struct Node*)malloc(sizeof(struct Node));

    if (head == NULL || second == NULL || third == NULL || fourth == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    head->data = 10;
    head->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = fourth;

    fourth->data = 40;
    fourth->next = NULL;

    int searchValue;
    printf("Enter the value to search for: ");
    scanf("%d", &searchValue);

    int found = 0;
    struct Node *current = head;
    while (current != NULL) {
        if (current->data == searchValue) {
            found = 1;
            break;
        }
        current = current->next;
    }

    if (found) {
        printf("The value %d is in the linked list.\n", searchValue);
    } else {
        printf("The value %d is not in the linked list.\n", searchValue);
    }

    free(head);
    free(second);
    free(third);
    free(fourth);

    return 0;
}