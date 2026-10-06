/*Öğrenci Kayıt Sistemi
Numaraya göre sıralı öğrenci ekleyen, listeyi hem baştan hem sondan yazdıran çift bağlı liste
uygulamasını c koduyla yazınız.
İstenilenler:
 Node yapısı: numara, isim, next, prev
 insertOrdered() → numaraya göre sıralı ekleme
 displayForward() → baştan sona yazdır
 displayBackward() → sondan başa yazdır*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

// Düğüm (Node) Yapısı
typedef struct Node {
    int numara;
    char isim[MAX_NAME_LEN];
    struct Node *prev;
    struct Node *next;
} Node;

// Yeni düğüm oluşturan yardımcı fonksiyon
Node* createNode(int numara, const char *isim) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Bellek yetersiz!\n");
        exit(1);
    }
    newNode->numara = numara;
    strncpy(newNode->isim, isim, MAX_NAME_LEN - 1);
    newNode->isim[MAX_NAME_LEN - 1] = '\0';
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Numaraya göre küçükten büyüğe sıralı ekleme
void insertOrdered(Node **head, int numara, const char *isim) {
    Node *newNode = createNode(numara, isim);

    // Durum 1: Liste boşsa
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Durum 2: Eklenecek numara ilk elemandan küçükse (başa ekleme)
    if (numara < (*head)->numara) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
        return;
    }

    // Durum 3: Araya veya sona ekleme
    Node *current = *head;
    while (current->next != NULL && current->next->numara < numara) {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != NULL) {
        current->next->prev = newNode; // Araya eklendiyse sonraki düğümün prev bağını güncelle
    }
    current->next = newNode;
}

// Baştan sona doğru listeleme
void displayForward(Node *head) {
    if (head == NULL) {
        printf("Liste bos.\n");
        return;
    }
    printf("\n--- Ogrenci Listesi (Bastan Sona) ---\n");
    Node *current = head;
    while (current != NULL) {
        printf("No: %-5d | Isim: %s\n", current->numara, current->isim);
        current = current->next;
    }
    printf("------------------------------------\n");
}

// Sondan başa doğru listeleme
void displayBackward(Node *head) {
    if (head == NULL) {
        printf("Liste bos.\n");
        return;
    }

    // Önce son düğüme (tail) gidilir
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    printf("\n--- Ogrenci Listesi (Sondan Basa) ---\n");
    // 'prev' işaretçileri üzerinden başa doğru geri yürünür
    while (current != NULL) {
        printf("No: %-5d | Isim: %s\n", current->numara, current->isim);
        current = current->prev;
    }
    printf("------------------------------------\n");
}

// Belleği serbest bırakma
void freeList(Node **head) {
    Node *current = *head;
    Node *temp;
    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }
    *head = NULL;
}

int main() {
    Node *head = NULL;

    // Karışık sırada ekleme (otomatik sıralanacak)
    insertOrdered(&head, 105, "Ali");
    insertOrdered(&head, 101, "Ayse");
    insertOrdered(&head, 108, "Mehmet");
    insertOrdered(&head, 103, "Zeynep");
    insertOrdered(&head, 110, "Burak");

    // Listeyi ileri ve geri yazdırma
    displayForward(head);