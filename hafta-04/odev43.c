/*Bu uygulama bir yazıcının işlem sırasını taklit edecek.
Her eklenen dosya kuyruğa alınır, “Yazdır” komutuyla sıradaki iş çıkarılır.
Yapılacaklar:
 enqueuePrintJob(Queue* q, char* dosyaAdı)
 processNextJob(Queue* q)
 showQueue(Queue q)
 Menü: 1) Yeni dosya ekle, 2) Yazdır, 3) Kuyruğu göster
İpucu:
 Kuyruk boşken yazdırma işlemi yapılmamalı.
 FIFO mantığına dikkat edin.
*/
#include <stdio.h>
#include <string.h>

#define MAX_QUEUE 100
#define MAX_NAME_LEN 50

typedef struct {
    char files[MAX_QUEUE][MAX_NAME_LEN];
    int front;
    int rear;
    int count;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

int isEmpty(const Queue *q) {
    return q->count == 0;
}

int isFull(const Queue *q) {
    return q->count == MAX_QUEUE;
}

void enqueuePrintJob(Queue *q, char *dosyaAdi) {
    if (isFull(q)) {
        printf("Hata: Yazici kuyrugu dolu!\n");
        return;
    }
    strncpy(q->files[q->rear], dosyaAdi, MAX_NAME_LEN - 1);
    q->files[q->rear][MAX_NAME_LEN - 1] = '\0';
    q->rear = (q->rear + 1) % MAX_QUEUE;
    q->count++;
    printf("'%s' kuyruga eklendi.\n", dosyaAdi);
}

void processNextJob(Queue *q) {
    if (isEmpty(q)) {
        printf("Uyari: Kuyruk bos! Yazdirilacak dosya yok.\n");
        return;
    }
    printf("Yazdiriliyor -> %s\n", q->files[q->front]);
    q->front = (q->front + 1) % MAX_QUEUE;
    q->count--;
}

void showQueue(Queue q) {
    if (q.count == 0) {
        printf("Kuyrukta bekleyen dosya yok (bos).\n");
        return;
    }
    printf("\n--- Bekleyen Yazdirma Isleri (FIFO) ---\n");
    int idx = q.front;
    for (int i = 0; i < q.count; i++) {
        printf("%d. %s\n", i + 1, q.files[idx]);
        idx = (idx + 1) % MAX_QUEUE;
    }
    printf("---------------------------------------\n");
}

int main() {
    Queue printerQueue;
    initQueue(&printerQueue);

    int choice;
    char dosyaAdi[MAX_NAME_LEN];

    while (1) {
        printf("\n--- YAZICI SISTEMI ---\n");
        printf("1) Yeni dosya ekle\n");
        printf("2) Yazdir\n");
        printf("3) Kuyrugu goster\n");
        printf("4) Cikis\n");
        printf("Seciminiz: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            printf("Gecersiz secim!\n");
            continue;
        }

        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                printf("Dosya adi: ");
                if (fgets(dosyaAdi, sizeof(dosyaAdi), stdin)) {
                    dosyaAdi[strcspn(dosyaAdi, "\n")] = '\0';
                    if (strlen(dosyaAdi) > 0) {
                        enqueuePrintJob(&printerQueue, dosyaAdi);
                    } else {
                        printf("Dosya adi bos olamaz!\n");
                    }
                }
                break;
            case 2:
                processNextJob(&printerQueue);
                break;
            case 3:
                showQueue(printerQueue);
                break;
            case 4:
                printf("Cikis yapiliyor...\n");
                return 0;
            default:
                printf("Gecersiz secim! Lutfen 1-4 arasi bir secim yapin.\n");
        }
    }

    return 0;
}