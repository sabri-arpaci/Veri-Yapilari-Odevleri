#include<stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;           // Yolcu / Sayı
    struct Node* next;  // Bir sonraki vagona takılan kanca
} Node;
//typedef  struct Node { ... }   Node  ;
//───────  ───────────────────   ────  ─
//Komut       Eski Uzun Adı     Yeni    Bitiş
//                              Kısa
//                              Adı
//typedef, C dilinde bir veri tipine yeni bir isim vermek için kullanılır. Bu sayede, uzun ve karmaşık yapı tanımlarını daha kısa ve okunabilir hale getirebiliriz. Örneğin, `struct Node` yerine sadece `Node` kullanabiliriz.

//yeni bir vagon üretip içine veri koyan fonksiyon
Node* yenidugum(int veri){
    Node *yeni = (Node*)malloc(sizeof(Node));  // 1. RAM'den boş bir vagon yeri al
    yeni->data = veri;                        // 2. İçine yolcuyu/sayıyı koy
    yeni->next = NULL;                   // 3. Kancayı şimdilik boşa (NULL) bağla[cite: 4]
    return yeni;                        // 4. Hazır vagonun adresini teslim et[cite: 4]

};
/*1. Marangoz / Fabrika (yeniDugum)
Bu elemanın tek bir uzmanlığı vardır: Sıfırdan boş bir vagon üretmek.   
Gidip işletim sisteminden sıfır kilometre bir vagon alanı ister (malloc).   
Vagonun içine yolcuyu (veri) oturtur.   
Arkasındaki kancayı şimdilik boş bırakır (yeni->next = NULL).   
Vagonu teslim eder: "Al kardeşim, vagon hazır, nereye bağlarsan bağla" der ve adresi eline verir.   
Önemli detay: Bu fonksiyon vagonu trene bağlamaz. Vagon hala hangarda tek başına beklemektedir.
*/

void basaEkle(Node** head, int veri) {
    Node* yeni = yeniDugum(veri); // 1. Fabrikadan yeni vagonu al[cite: 4]
    yeni->next = *head;          // 2. Yeni vagonun kancasını eski 1. vagona tak[cite: 4]
    *head = yeni;                // 3. Masadaki "1. vagon kim?" kağıdına yeni vagonu yaz[cite: 4]
};
/*
2. Ray Ustası / İstasyon Şefi (basaEkle)
Bu eleman bizzat rayların başındadır; hangardaki vagonu getirip trenin en önüne kilitler.   
Yaptığı üç hamle şudur:
Marangozu arar: "Bana içine şu yolcuyu koyduğun yeni bir vagon yolla" (Node* yeni = yeniDugum(veri);).  
Yeni vagonun arkasındaki kancayı alır, trenin eski ilk vagonuna kilitler (yeni->next = *head;).   
İstasyonun tabelasındaki yazıyı siler: "Artık trenin ilk vagonu bu yeni vagon oldu!" der (*head = yeni;).   
İşi biter, tren artık 1 vagon daha uzundur.
*/
void yazdir(Node* head) {
    Node* temp = head; // Feneri alıp 1. vagona geç
    while (temp != NULL) {
        printf("%d -> ", temp->data); // Yolcuyu oku
        temp = temp->next;           // Bir sonraki vagona adım at
    }
    printf("NULL\n"); // Tren bitti
}
/*
3. Kondüktör / Bilet Kontrolcüsü (yazdir)
Bu eleman trene ne vagon ekler, ne de vagondan bir şey söker.   
Elinde fenerle trenin en başından içeri girer (Node* temp = head;).   
Vagonun içindeki yolcunun numarasını megafonla anons eder (printf("%d -> ", temp->data);).   
Kancayı takip edip bir sonraki vagona zıplar (temp = temp->next;).   
Rayların bittiği boşluğa (NULL) gelene kadar bütün vagonları tek tek anons edip durur.
*/

// 4. İSTASYON MEYDANI: Seferin başladığı yer
int main() {
    // Başlangıçta raylarda hiç tren yok, istasyon boş
    Node* head = NULL;

    // Trene sırayla önden vagon ekliyoruz
    basaEkle(&head, 10); // Tren: 10 -> NULL
    basaEkle(&head, 20); // Tren: 20 -> 10 -> NULL
    basaEkle(&head, 30); // Tren: 30 -> 20 -> 10 -> NULL

    // Kondüktörü çağırıp treni kontrol ettiriyoruz
    printf("Trenin guncel hali: ");
    yazdir(head);

    return 0;
}