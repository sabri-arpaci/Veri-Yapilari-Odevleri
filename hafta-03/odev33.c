/*Örnek-3:
Bir tek yönlü bağlı liste içindeki ortadaki düğümün değerini bulan bir C programı yazınız.
Aşağıdaki fonksiyonları oluşturmanız beklenmektedir:
● Node* findMiddle(Node* head);

Bağlı listedeki ortadaki düğümü döndürür.
Eğer listedeki eleman sayısı tek ise, ortadaki düğüm döndürülür.
Eğer eleman sayısı çift ise, iki ortadan ikincisini döndürür.
Boş liste durumunda NULL döndürülür.
Bu işlem için slow ve fast göstericileri (iki pointer) kullanabilirsiniz:
o slow → her adımda bir düğüm ilerler
o fast → her adımda iki düğüm ilerler
fast sona ulaştığında slow ortadadır.

● void printList(Node* head);

Listenin elemanlarını baştan sona yazdırır.

● void clear(Node** head);

Listedeki tüm düğümleri serbest bırakır (free eder) ve listeyi boşaltır.*/
#include <stdio.h>
#include <stdlib.h>

// Düğüm (Node) Yapısı
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Yeni düğüm oluşturan yardımcı fonksiyon
Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Hata: Bellek yetersiz!\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Test amacıyla listenin sonuna eleman ekleme fonksiyonu
void appendNode(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// 1) Ortadaki düğümü bulan fonksiyon (Slow & Fast Pointer)
Node* findMiddle(Node *head) {
    // Liste boşsa NULL döndür
    if (head == NULL) {
        return NULL;
    }

    Node *slow = head; // Her adımda 1 birim ilerler
    Node *fast = head; // Her adımda 2 birim ilerler

    // fast listenin sonuna veya son düğüme ulaşana kadar devam et
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // fast sona ulaştığında, slow tam ortadaki (çift sayıda ise 2. ortadaki) düğümdedir
    return slow;
}

// 2) Listenin elemanlarını baştan sona yazdırma
void printList(Node *head) {
    if (head == NULL) {
        printf("Liste bos.\n");
        return;
    }

    Node *current = head;
    while (current != NULL) {
        printf("%d", current->value);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

// 3) Listedeki tüm düğümleri serbest bırakma ve listeyi boşaltma
void clear(Node **head) {
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

    // Test 1: Tek sayıda eleman içeren liste (1 -> 2 -> 3 -> 4 -> 5)
    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);
    appendNode(&head, 4);
    appendNode(&head, 5);

    printf("--- Test 1 (Tek sayida eleman: 5 adet) ---\n");
    printf("Liste: ");
    printList(head);

    Node *middle1 = findMiddle(head);
    if (middle1 != NULL) {
        printf("Ortadaki dugumun degeri: %d\n\n", middle1->value); // Beklenen: 3
    }

    // Test 2: Çift sayıda eleman içeren liste (1 -> 2 -> 3 -> 4 -> 5 -> 6)
    appendNode(&head, 6);

    printf("--- Test 2 (Cift sayida eleman: 6 adet) ---\n");
    printf("Liste: ");
    printList(head);

    Node *middle2 = findMiddle(head);
    if (middle2 != NULL) {
        printf("Ortadaki dugumun degeri (ikinci orta): %d\n\n", middle2->value); // Beklenen: 4
    }

    // Belleği temizleme
    clear(&head);

    // Test 3: Boş liste testi
    printf("--- Test 3 (Bos liste) ---\n");
    Node *middle3 = findMiddle(head);
    if (middle3 == NULL) {
        printf("Bos liste: Ortadaki dugum bulunamadi (NULL).\n");
    }

    return 0;
}