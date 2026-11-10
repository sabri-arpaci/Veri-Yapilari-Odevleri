
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int height(Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;

    return rightHeight + 1;
}

int balanceFactor(Node* root) {
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

Node* insertBST(Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertBST(root->left, data);

    else if (data > root->data)
        root->right = insertBST(root->right, data);

    return root;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

Node* insertAVL(Node* root, int data) {

    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertAVL(root->left, data);

    else if (data > root->data)
        root->right = insertAVL(root->right, data);

    else
        return root;

    int bf = balanceFactor(root);

    if (bf > 1 && data < root->left->data)
        return rotateRight(root);

    if (bf < -1 && data > root->right->data)
        return rotateLeft(root);

    if (bf > 1 && data > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (bf < -1 && data < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void runTest(char name[], int values[], int size) {

    Node* root = NULL;

    for (int i = 0; i < size; i++) {
        root = insertAVL(root, values[i]);
    }

    printf("\n%s\n", name);
    printf("Kok: %d\n", root->data);

    printf("Preorder: ");
    preorder(root);

    printf("\n");
}

int main() {

    printf("SORU 1 - AVL EKLEME\n");

    Node* root = NULL;

    int numbers[] = {10, 20, 30};

    for (int i = 0; i < 3; i++) {
        root = insertBST(root, numbers[i]);

        printf("%d eklendi. BF(kok) = %d\n",
               numbers[i], balanceFactor(root));
    }

    if (balanceFactor(root) < -1) {
        printf("RR dengesizligi: Sol rotasyon!\n");
        root = rotateLeft(root);
    }

    printf("Kok: %d\n", root->data);

    printf("Inorder: ");
    inorder(root);

    printf("\nPreorder: ");
    preorder(root);

    printf("\n\n");


    int A[] = {30, 20, 10};
    int B[] = {10, 20, 30};
    int C[] = {30, 10, 20};
    int D[] = {10, 30, 20};

    runTest("A (LL)", A, 3);
    runTest("B (RR)", B, 3);
    runTest("C (LR)", C, 3);
    runTest("D (RL)", D, 3);

    return 0;
}
