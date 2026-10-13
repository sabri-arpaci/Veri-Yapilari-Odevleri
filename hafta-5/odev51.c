#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hasta {
    int id;
    char ad[50];
    char durum[20];
    struct Hasta* next;
} Hasta;

typedef struct {
    Hasta* front;
    Hasta* rear;
} Queue;

typedef struct {
    Hasta* top;
} Stack;

Hasta* yeniHasta(int id, const char* ad) {
    Hasta* h = (Hasta*)malloc(sizeof(Hasta));
    if (!h) {
        return NULL;
    }
    h->id = id;
    strcpy(h->ad, ad);
    strcpy(h->durum, "bekliyor");
    h->next = NULL;
    return h;
}

Queue* kuyrukOlustur() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

Stack* yiginOlustur() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

void enqueue(Queue* q, int id, const char* ad) {
    Hasta* h = yeniHasta(id, ad);
    if (!h) return;

    if (q->rear == NULL) {
        q->front = h;
        q->rear = h;
    } else {
        q->rear->next = h;
        q->rear = h;
    }
    printf("[KAYIT] %s (ID: %d) sisteme eklendi. Durum: %s\n", h->ad, h->id, h->durum);
}

Hasta* dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("[HATA] Kuyruk bos, cikarilacak hasta yok.\n");
        return NULL;
    }

    Hasta* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    temp->next = NULL;
    return temp;
}

void push(Stack* s, Hasta* h) {
    if (h == NULL) return;

    strcpy(h->durum, "muayenede");
    h->next = s->top;
    s->top = h;

    printf("[MUAYENE] %s (ID: %d) odaya alindi. Durum: %s\n", h->ad, h->id, h->durum);
}

Hasta* pop(Stack* s) {
    if (s->top == NULL) {
        printf("[HATA] Yigin bos, muayenede hasta yok.\n");
        return NULL;
    }

    Hasta* temp = s->top;
    s->top = s->top->next;
    temp->next = NULL;
    return temp;
}

void gecmisEkle(Hasta** head, Hasta* h) {
    if (h == NULL) return;

    strcpy(h->durum, "tamamlandi");
    h->next = NULL;

    if (*head == NULL) {
        *head = h;
    } else {
        Hasta* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = h;
    }
    printf("[TAMAMLANDI] %s (ID: %d) taburcu edildi. Durum: %s\n", h->ad, h->id, h->durum);
}

void bekleyenleriListele(Queue* q) {
    printf("\n--- BEKLEYEN HASTALAR (KUYRUK) ---\n");
    if (q->front == NULL) {
        printf("Kuyrukta bekleyen hasta yok.\n");
        return;
    }
    Hasta* temp = q->front;
    int sira = 1;
    while (temp != NULL) {
        printf("%d. [ID: %d] %-10s | Durum: %s\n", sira++, temp->id, temp->ad, temp->durum);
        temp = temp->next;
    }
}

void muayenedekileriListele(Stack* s) {
    printf("\n--- MUAYENE ODASINDAKI HASTALAR (YIGIN) ---\n");
    if (s->top == NULL) {
        printf("Muayene odasinda hasta yok.\n");
        return;
    }
    Hasta* temp = s->top;
    while (temp != NULL) {
        printf("[ID: %d] %-10s | Durum: %s\n", temp->id, temp->ad, temp->durum);
        temp = temp->next;
    }
}

void gecmisListele(Hasta* head) {
    printf("\n--- GECMIS HASTA KAYITLARI (BAGLI LISTE) ---\n");
    if (head == NULL) {
        printf("Gecmis hasta kaydi bulunmuyor.\n");
        return;
    }
    Hasta* temp = head;
    int sira = 1;
    while (temp != NULL) {
        printf("%d. [ID: %d] %-10s | Durum: %s\n", sira++, temp->id, temp->ad, temp->durum);
        temp = temp->next;
    }
}

int main() {
    Queue* beklemeKuyrugu = kuyrukOlustur();
    Stack* muayeneOdasi = yiginOlustur();
    Hasta* gecmisListesi = NULL;

    printf("==========================================\n");
    printf("   HASTANE TAKIP SISTEMI BASLATILDI       \n");
    printf("==========================================\n\n");

    enqueue(beklemeKuyrugu, 1, "Ahmet");
    enqueue(beklemeKuyrugu, 2, "Mehmet");
    enqueue(beklemeKuyrugu, 3, "Ayse");

    bekleyenleriListele(beklemeKuyrugu);
    muayenedekileriListele(muayeneOdasi);
    gecmisListele(gecmisListesi);

    printf("\n------------------------------------------\n");
    Hasta* hasta1 = dequeue(beklemeKuyrugu);
    push(muayeneOdasi, hasta1);

    bekleyenleriListele(beklemeKuyrugu);
    muayenedekileriListele(muayeneOdasi);

    printf("\n------------------------------------------\n");
    Hasta* muayenesiBiten = pop(muayeneOdasi);
    gecmisEkle(&gecmisListesi, muayenesiBiten);

    printf("\n==========================================\n");
    printf("               SON DURUM                  \n");
    printf("==========================================\n");
    bekleyenleriListele(beklemeKuyrugu);
    muayenedekileriListele(muayeneOdasi);
    gecmisListele(gecmisListesi);

    return 0;
}