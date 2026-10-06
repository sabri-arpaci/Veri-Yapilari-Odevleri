/*Örnek-2:
Bir tek yönlü bağlı liste üzerinde pozisyona göre ekleme ve silme işlemlerini gerçekleştiren
C programını yazınız.
Aşağıdaki fonksiyonları oluşturmanız beklenmektedir:
● void insertAt(Node** head, int value, int position);

Verilen value değerini, bağlı listenin position (indis) numaralı pozisyonuna
ekler.
0 veya negatif pozisyona ekleme yapıldığında, yeni düğüm listenin başına
eklenmiş olur.
Eğer verilen pozisyon, listedeki eleman sayısından büyükse, yeni düğüm
listenin sonuna eklenir.

● void deleteAt(Node** head, int position);
Verilen pozisyondaki düğümü listeden siler.
0. pozisyondaki düğüm silinirse, baş düğüm bir sonraki düğümle güncellenir.
Geçersiz bir pozisyon girilirse işlem yapılmaz.

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

// 1) Pozisyona göre düğüm ekleme
void insertAt(Node **head, int value, int position) {
    Node *newNode = createNode(value);

    // Durum 1: Pozisyon 0 veya negatifse ya da liste boşsa -> Başa ekle
    if (position <= 0 || *head == NULL) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // Durum 2: Araya veya pozisyon liste uzunluğundan büyükse sona ekle
    Node *current = *head;
    int currentPos = 0;

    // Hedef pozisyondan bir önceki düğüme veya listenin son düğümüne kadar ilerle
    while (current->next != NULL && currentPos < position - 1) {
        current = current->next;
        currentPos++;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// 2) Pozisyona göre düğüm silme
void deleteAt(Node **head, int position) {
    // Liste boşsa veya pozisyon negatifse işlem yapma
    if (*head == NULL || position < 0) {
        return;
    }

    // Durum 1: 0. pozisyondaki düğümü silme (Baştan silme)
    if (position == 0) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    // Durum 2: Belirtilen pozisyondaki düğümü bulma
    Node *current = *head;
    int currentPos = 0;

    // Silinecek düğümden hemen önceki düğüme git
    while (current->next != NULL && currentPos < position - 1) {
        current = current->next;
        currentPos++;
    }

    // Eğer hedef pozisyon liste boyutundan büyük veya eşitse işlem yapma
    if (current->next == NULL) {
        return;
    }

    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
}

// 3) Listenin elemanlarını baştan sona yazdırma
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

// 4) Listedeki tüm düğümleri serbest bırakma ve listeyi boşaltma
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

    printf("--- EKLEME TESTLERI ---\n");
    insertAt(&head, 10, 0);   // Başa ekleme: [10]
    insertAt(&head, 20, 1);   // Sona ekleme: [10 -> 20]
    insertAt(&head, 30, 2);   // Sona ekleme: [10 -> 20 -> 30]
    insertAt(&head, 5, -2);   // Negatif pozisyon (başa eklenmeli): [5 -> 10 -> 20 -> 30]
    insertAt(&head, 15, 2);   // Araya ekleme: [5 -> 10 -> 15 -> 20 -> 30]
    insertAt(&head, 99, 100); // Sınırı aşan pozisyon (sona eklenmeli): [5 -> 10 -> 15 -> 20 -> 30 -> 99]

    printf("Liste: ");
    printList(head);

    printf("\n--- SILME TESTLERI ---\n");
    deleteAt(&head, 0);       // Baştaki 5 silinir
    printf("0. pozisyon silindi: ");
    printList(head);

    deleteAt(&head, 2);       // 2. indisteki 20 silinir
    printf("2. pozisyon silindi: ");
    printList(head);

    deleteAt(&head, -1);      // Negatif pozisyon (islem yapilmaz)
    deleteAt(&head, 50);      // Boyuttan buyuk pozisyon (islem yapilmaz)
    printf("Gecersiz pozisyonlar denendi (degismez): ");
    printList(head);

    printf("\n--- TEMIZLEME ---\n");
    clear(&head);
    printf("Temizlendikten sonra: ");
    printList(head);

    return 0;
}