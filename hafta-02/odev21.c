//Bir Node yapısı oluşturun. Node içerisinde 10 değerini saklayın ve ekrana yazdırın.#include <stdio.h>
// 1. Vagonun Taslağını Çiziyoruz (Struct)
#include <stdio.h>
/*
struct Vagon {
    int yuk;                 // Vagonun taşıdığı sayı (data)
    struct Vagon *sonraki;   // Bir sonraki vagonun adresi (next pointer)
};

int main() {
    // 2. Üç Tane Bağımsız Vagon Üretiyoruz
    struct Vagon v1;
    struct Vagon v2;
    struct Vagon v3;

    // 3. Vagonların İçine Yüklerini Koyuyoruz
    v1.yuk = 100;
    v2.yuk = 200;
    v3.yuk = 300;

    // 4. Kancaları Takıyoruz (Birbirine Bağlama)
    v1.sonraki = &v2;   // 1. vagon 2. vagonun adresini tutuyor[cite: 12]
    v2.sonraki = &v3;   // 2. vagon 3. vagonun adresini tutuyor[cite: 12]
    v3.sonraki = NULL;  // Son vagonun arkasında kimse yok (NULL)[cite: 12]

    // 5. Trenin Başı: Lokomotif[cite: 12, 13]
    struct Vagon *lokomotif = &v1; // İlk vagonu işaret eder[cite: 12]

    // 6. Treni Baştan Sona Gezen Kondüktör Döngüsü[cite: 12, 13]
    struct Vagon *konduktor = lokomotif; // Kontrole en baştan başla[cite: 12]

    while (konduktor != NULL) {
        printf("Vagondaki Yuk: %d\n", konduktor->yuk); // Yükü ekrana yazdır[cite: 12]
        konduktor = konduktor->sonraki; // Kancayı takip edip sonraki vagona geç[cite: 12]
    }

    return 0;
}
    */
   struct Node{
    int data;
    struct Node *next;
   };
   int main(){
struct Node node1.data =10;
node1.next = NULL;
printf("Node data: %d\n", node1.data);

    return 0;
   }

