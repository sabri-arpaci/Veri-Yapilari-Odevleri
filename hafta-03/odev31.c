/*Örnek-1:
Yapılacaklar:
Bir tek yönlü bağlı liste kullanarak aşağıdaki fonksiyonları C dilinde yazınız:
● void addOrdered(Node** head, int value);
Bağlı listeye sıralı şekilde yeni bir düğüm ekler. Liste boşsa yeni düğüm baş olur.
Bu fonksiyonun sıralı sonuç üretmesi için mevcut liste sıralı olmalıdır; fonksiyon
önceki düğümleri yeniden sıralamaz.
Örneğin: Boş listeye sırasıyla 23, 11, 5, 9, 6, 4, 12, 24 sayıları bu fonksiyonla
eklendiğinde
listenin içeriği 4 → 5 → 6 → 9 → 11 → 12 → 23 → 24 şeklinde olmalıdır.
● void removeNode(Node** head, int value);
Bağlı listede verilen değere sahip ilk düğümü siler.
● int count(Node* head);
Listedeki düğüm sayısını döndürür.
● void printList(Node* head);
Listenin elemanlarını baştan sona ekrana yazdırır.
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

// 1) Listeye sıralı eleman ekleme
void addOrdered(Node **head, int value) {
    Node *newNode = createNode(value);

    // Durum 1: Liste boşsa veya eklenecek değer baştaki elemandan küçükse
    if (*head == NULL || value < (*head)->value) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // Durum 2: Araya veya sona ekleme
    Node *current = *head;
    while (current->next != NULL && current->next->value < value) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// 2) Verilen değere sahip ilk düğümü silme
void removeNode(Node **head, int value) {
    if (*head == NULL) {
        printf("Hata: Liste bos, silme islemi yapilamadi.\n");
        return;
    }

    // Durum 1: Silinecek düğüm başta ise
    if ((*head)->value == value) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("%d degeri listeden silindi.\n", value);
        return;
    }

    // Durum 2: Silinecek düğüm aradaysa veya sondaysa
    Node *current = *head;
    while (current->next != NULL && current->next->value != value) {
        current = current->next;
    }

    if (current->next != NULL) {
        Node *temp = current->next;
        current->next = current->next->next;
        free(temp);
        printf("%d degeri listeden silindi.\n", value);
    } else {
        printf("%d degeri listede bulunamadi.\n", value);
    }
}

// 3) Listedeki toplam düğüm sayısını bulma
int count(Node *head) {
    int total = 0;
    Node *current = head;
    while (current != NULL) {
        total++;
        current = current->next;
    }
    return total;
}

// 4) Listenin elemanlarını ekrana yazdırma
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

// 5) Listedeki tüm düğümleri serbest bırakma ve listeyi boşaltma
void clear(Node **head) {
    Node *current = *head;
    Node *temp;

    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }

    *head = NULL;
    printf("Liste temizlendi ve tum bellek serbest birakildi.\n");
}

int main() {
    Node *head = NULL;

    // Örnekteki sayıların sırayla eklenmesi: 23, 11, 5, 9, 6, 4, 12, 24
    int elements[] = {23, 11, 5, 9, 6, 4, 12, 24};
    int n = sizeof(elements) / sizeof(elements[0]);

    printf("Elemanlar sirayla ekleniyor...\n");
    for (int i = 0; i < n; i++) {
        addOrdered(&head, elements[i]);
    }

    // Beklenen çıktı: 4 -> 5 -> 6 -> 9 -> 11 -> 12 -> 23 -> 24
    printf("Liste: ");
    printList(head);
    printf("Dugum sayisi: %d\n\n", count(head));

    // Silme işlemleri
    removeNode(&head, 9);   // Aradaki elemanı silme
    removeNode(&head, 4);   // Baştaki elemanı silme
    removeNode(&head, 100); // Listede olmayan elemanı silme denemesi

    printf("\nGuncel Liste: ");
    printList(head);
    printf("Guncel Dugum sayisi: %d\n\n", count(head));

    // Listeyi tamamen temizleme
    clear(&head);
    printf("Temizleme sonrasi: ");
    printList(head);

    return 0;
}