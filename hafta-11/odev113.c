#include <stdio.h>
#include <stdbool.h>

#define DERS_SAYISI 6
#define OGRENCI_SAYISI 4

void cakismaMatrisiOlustur(int kayitlar[OGRENCI_SAYISI][DERS_SAYISI], int matris[DERS_SAYISI][DERS_SAYISI]) {
    for (int i = 0; i < DERS_SAYISI; i++)
        for (int j = 0; j < DERS_SAYISI; j++)
            matris[i][j] = 0;

    for (int o = 0; o < OGRENCI_SAYISI; o++) {
        for (int i = 0; i < DERS_SAYISI; i++) {
            for (int j = i + 1; j < DERS_SAYISI; j++) {
                if (kayitlar[o][i] == 1 && kayitlar[o][j] == 1) {
                    matris[i][j] = 1;
                    matris[j][i] = 1;
                }
            }
        }
    }
}

void welchPowellCalistir(int matris[DERS_SAYISI][DERS_SAYISI]) {
    int derece[DERS_SAYISI] = {0};
    int siraliDugumler[DERS_SAYISI];
    int renk[DERS_SAYISI];

    printf("Cakisma Komsuluk Matrisi:\n    ");
    for (int i = 0; i < DERS_SAYISI; i++) printf("d%d ", i);
    printf("\n");

    for (int i = 0; i < DERS_SAYISI; i++) {
        siraliDugumler[i] = i;
        renk[i] = 0; // 0: Henuz oturum atanmadi
        printf("d%d: ", i);
        for (int j = 0; j < DERS_SAYISI; j++) {
            printf(" %d ", matris[i][j]);
            derece[i] += matris[i][j];
        }
        printf(" (Derece: %d)\n", derece[i]);
    }

    // Derecelere gore buyukten kucuge siralama (Bubble Sort)
    for (int i = 0; i < DERS_SAYISI - 1; i++) {
        for (int j = 0; j < DERS_SAYISI - i - 1; j++) {
            int u = siraliDugumler[j];
            int v = siraliDugumler[j + 1];
            if (derece[u] < derece[v]) {
                siraliDugumler[j] = v;
                siraliDugumler[j + 1] = u;
            }
        }
    }

    // Welch-Powell Renklendirme
    int oturumSayisi = 0;
    int boyananSayisi = 0;

    while (boyananSayisi < DERS_SAYISI) {
        oturumSayisi++;
        for (int i = 0; i < DERS_SAYISI; i++) {
            int aday = siraliDugumler[i];
            if (renk[aday] == 0) {
                bool cakismaVar = false;
                for (int j = 0; j < DERS_SAYISI; j++) {
                    if (matris[aday][j] == 1 && renk[j] == oturumSayisi) {
                        cakismaVar = true;
                        break;
                    }
                }
                if (!cakismaVar) {
                    renk[aday] = oturumSayisi;
                    boyananSayisi++;
                }
            }
        }
    }

    // Raporlama
    printf("\nGerekli Minimum Sinav Oturumu Sayisi (Kromatik Sayi): %d\n", oturumSayisi);
    for (int s = 1; s <= oturumSayisi; s++) {
        printf("Oturum %d: ", s);
        for (int i = 0; i < DERS_SAYISI; i++) {
            if (renk[i] == s) {
                printf("d%d ", i);
            }
        }
        printf("\n");
    }
}

int main() {
    // Satirlar: Ogrenci-1..4, Sutunlar: d0..d5 (1: Dersi aliyor, 0: Almiyor)
    int kayitlar[OGRENCI_SAYISI][DERS_SAYISI] = {
        {1, 1, 0, 0, 1, 0}, // Ogrenci-1: d0, d1, d4
        {1, 0, 1, 0, 1, 0}, // Ogrenci-2: d0, d2, d4
        {0, 0, 1, 1, 0, 1}, // Ogrenci-3: d2, d3, d5
        {0, 0, 0, 1, 1, 1}  // Ogrenci-4: d3, d4, d5
    };

    int cakismaMatrisi[DERS_SAYISI][DERS_SAYISI];

    printf("=== 1. MEVCUT KAYIT LISTESI ILE SINAV TAKVIMI ===\n");
    cakismaMatrisiOlustur(kayitlar, cakismaMatrisi);
    welchPowellCalistir(cakismaMatrisi);

    printf("\n==================================================\n");
    printf("=== 2. DINAMIK GUNCELLEME: OGRENCI-4 d4 DERSINI BIRAKTI ===\n");
    kayitlar[3][4] = 0; // Ogrenci-4 (indeks 3), d4 (indeks 4) silindi
    cakismaMatrisiOlustur(kayitlar, cakismaMatrisi);
    welchPowellCalistir(cakismaMatrisi);

    return 0;
}