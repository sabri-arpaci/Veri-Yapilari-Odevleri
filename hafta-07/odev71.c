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

int hazineAra(Node* root, int hedef) {
    if (root == NULL) {
        return 0;
    }

    printf("Ziyaret edilen dugum: %d\n", root->data);

    if (root->data == hedef) {
        return 1;
    }

    if (hedef < root->data) {
        return hazineAra(root->left, hedef);
    } else {
        return hazineAra(root->right, hedef);
    }
}

int agacYuksekligi(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int sol = agacYuksekligi(root->left);
    int sag = agacYuksekligi(root->right);

    return (sol > sag ? sol : sag) + 1;
}

int main() {
    Node* root = NULL;
    int hazineler[] = {50, 30, 70, 20, 40, 60, 80, 10, 35};
    int n = sizeof(hazineler) / sizeof(hazineler[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, hazineler[i]);
    }

    int aranan;
    printf("Aramak istediginiz hazine degerini girin: ");
    scanf("%d", &aranan);

    printf("\n--- Arama Adimlari ---\n");
    if (hazineAra(root, aranan)) {
        printf("\nHazine bulundu!\n");
    } else {
        printf("\nBosuna kazdin!\n");
    }

    printf("En kotu durumda gereken maksimum adim sayisi (Agac Yuksekligi): %d\n", agacYuksekligi(root));

    return 0;
}