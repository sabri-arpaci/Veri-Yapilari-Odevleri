#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* yeniDugum(int veri) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) {
        return NULL;
    }
    n->data = veri;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* insert(Node* root, int veri) {
    if (root == NULL) {
        return yeniDugum(veri);
    }

    if (veri < root->data) {
        root->left = insert(root->left, veri);
    } else if (veri > root->data) {
        root->right = insert(root->right, veri);
    }

    return root;
}

void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int search(Node* root, int hedef) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == hedef) {
        return 1;
    }
    if (hedef < root->data) {
        return search(root->left, hedef);
    } else {
        return search(root->right, hedef);
    }
}

int findMin(Node* root) {
    Node* curr = root;
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr->data;
}

int main() {
    Node* root = NULL;
    int numbers[] = {40, 20, 60, 10, 30, 50, 70};

    for (int i = 0; i < 7; i++) {
        root = insert(root, numbers[i]);
    }

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    if (search(root, 30))
        printf("30 agacta bulundu.\n");
    else
        printf("30 agacta bulunamadi.\n");

    if (search(root, 90))
        printf("90 agacta bulundu.\n");
    else
        printf("90 agacta bulunamadi.\n");

    if (root != NULL)
        printf("En kucuk eleman: %d\n", findMin(root));

    return 0;
}