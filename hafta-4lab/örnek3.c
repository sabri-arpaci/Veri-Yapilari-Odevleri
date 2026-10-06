/*İstenilenler:
 Node: müşteriNumarası, next
 Fonksiyonlar:
o enqueue(), dequeue(), display()
Kullanıcı “müşteri geldi” dediğinde kuyruğa eklenir.
“işlem tamamlandı” dediğinde sıradaki müşteri çıkar.
display() ile bekleyen müşteri sırası gösterilir.
Beklenen çıktı:
Müşteri #1 geldi.
Müşteri #2 geldi.
Sıradaki müşteri: #1
Müşteri #1 işlemi tamamladı.
Yeni sıradaki müşteri: #2 */
#include <stdio.h>
#include <stdlib.h>

// Düğüm (Node) Yapısı
typedef struct Node {
    int musteriNumarasi;
    struct Node *next;
} Node;

// Kuyruk (Queue) Yapısı: Başı (front) ve sonu (rear) takip eder
typedef struct {
    Node *front;
    Node *rear;
} Queue;

void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(const Queue *q) {
    return q->front == NULL;
}

// 1) Yeni müşteri ekleme (Enqueue)
void enqueue(Queue *q, int musteriNumarasi) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Hata: Bellek yetersiz!\n");
        return;
    }
    newNode->musteriNumarasi = musteriNumarasi;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Müşteri #%d geldi.\n", musteriNumarasi);
}

// 2) Sıradaki müşterinin işlemini tamamlama ve çıkarma (Dequeue)
void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Kuyrukta bekleyen müşteri yok!\n");
        return;
    }

    Node *temp = q->front;
    int tamamlananNo = temp->musteriNumarasi;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);

    printf("Müşteri #%d işlemi tamamladı.\n", tamamlananNo);

    if (!isEmpty(q)) {
        printf("Yeni sıradaki müşteri: #%d\n", q->front->musteriNumarasi);
    } else {
        printf("Kuyrukta bekleyen başka müşteri kalmadı.\n");
    }
}

// 3) Bekleyen müşteri sırasını ve ilk sıradakini gösterme
void display(const Queue *q) {
    if (isEmpty(q)) {
        printf("Kuyruk boş (bekleyen müşteri yok).\n");
        return;
    }

    printf("Sıradaki müşteri: #%d\n", q->front->musteriNumarasi);
    printf("Kuyruk Durumu: ");
    Node *current = q->front;
    while (current != NULL) {
        printf("#%d%s", current->musteriNumarasi, (current->next != NULL) ? " -> " : "");
        current = current->next;
    }
    printf("\n");
}

// Belleği temizleme
void freeQueue(Queue *q) {
    while (!isEmpty(q)) {
        Node *temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}

int main() {
    Queue bankaKuyrugu;
    initQueue(&bankaKuyrugu);

    int musteriSayaci = 1;
    int secim;

    printf("--- MÜŞTERİ KUYRUK SİSTEMİ ---\n");
    printf("1) Müşteri geldi\n");
    printf("2) İşlem tamamlandı\n");
    printf("3) Sırayı göster (display)\n");
    printf("4) Çıkış\n");

    while (1) {
        printf("\nSeçiminiz: ");
        if (scanf("%d", &secim) != 1) {
            while (getchar() != '\n'); // Hatalı girdi temizleme
            printf("Geçersiz giriş!\n");
            continue;
        }

        switch (secim) {
            case 1:
                enqueue(&bankaKuyrugu, musteriSayaci++);
                break;
            case 2:
                dequeue(&bankaKuyrugu);
                break;
            case 3:
                display(&bankaKuyrugu);
                break;
            case 4:
                printf("Program sonlandırılıyor...\n");
                freeQueue(&bankaKuyrugu);
                return 0;
            default:
                printf("Lütfen 1-4 arasında bir seçim yapın.\n");
        }
    }

    return 0;
}