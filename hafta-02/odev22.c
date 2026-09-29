//10 ve 20 değerlerini içeren iki Node oluşturun ve 10  20 NULL listesini oluşturun.
#include<stdio.h>
struct Node{
    int data;
    struct Node *next;
};
int main(){
struct Node node1, node2;
node1.data =10;
node2.data = 20;
node1.next = &node2;
node2.next = NULL;

printf("first node data: %d\n", node1.data);
printf("second node data: %d\n", node2.data);

    return 0;
}