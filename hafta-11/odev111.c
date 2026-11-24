#include <stdio.h>
#include <stdbool.h>

#define N 6

void kenarEkle(int matris[N][N], int u, int v) {
    matris[u - 1][v - 1] = 1;
    matris[v - 1][u - 1] = 1;
}

void matrisYazdir(int matris[N][N]) {
    printf("Komsuluk Matrisi:\n   ");
    for (int i = 0; i < N; i++) printf("%d ", i + 1);
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < N; j++) {
            printf("%d ", matris[i][j]);
        }
        printf("\n");
    }
}

void dereceHesapla(int matris[N][N]) {
    int toplamDerece = 0;
    printf("\nDugum Dereceleri:\n");
    for (int i = 0; i < N; i++) {
        int derece = 0;
        for (int j = 0; j < N; j++) {
            derece += matris[i][j];
        }
        toplamDerece += derece;
        printf("Dugum %d derecesi: %d\n", i + 1, derece);
    }
    printf("Grafin Genel (Toplam) Derecesi: %d\n", toplamDerece);
}

void bipartiteKontrol(int matris[N][N], int baslangic) {
    int renk[N];
    for (int i = 0; i < N; i++) renk[i] = -1; // -1: Renksiz

    int kuyruk[N];
    int on = 0, arka = 0;

    int startIdx = baslangic - 1;
    renk[startIdx] = 0; // 0: Mavi (Cift), 1: Kirmizi (Tek)
    kuyruk[arka++] = startIdx;

    bool bipartiteMi = true;

    while (on < arka) {
        int u = kuyruk[on++];
        for (int v = 0; v < N; v++) {
            if (matris[u][v] == 1) {
                if (renk[v] == -1) {
                    renk[v] = 1 - renk[u];
                    kuyruk[arka++] = v;
                } else if (renk[v] == renk[u]) {
                    bipartiteMi = false;
                }
            }
        }
    }

    printf("\nRenklendirme (Parite) Sonuclari (Baslangic: %d):\n", baslangic);
    for (int i = 0; i < N; i++) {
        printf("Dugum %d -> Renk/Parite: %d (%s)\n", 
               i + 1, renk[i], renk[i] == 0 ? "Mavi / Cift" : "Kirmizi / Tek");
    }

    if (bipartiteMi) {
        printf("SONUC: Graf Iki Parcalidir (Bipartite). Guvenlik politikasina uygundur.\n");
    } else {
        printf("SONUC: Graf Iki Parcali DEGILDIR (Bipartite Degil). Ayni kume ici baglanti tespit edildi!\n");
    }
}

int main() {
    int graf[N][N] = {0};

    // Baslangic kenarlari: E = {(1, 2), (1, 4), (2, 3), (3, 4), (3, 6), (4, 5), (5, 6)}
    kenarEkle(graf, 1, 2);
    kenarEkle(graf, 1, 4);
    kenarEkle(graf, 2, 3);
    kenarEkle(graf, 3, 4);
    kenarEkle(graf, 3, 6);
    kenarEkle(graf, 4, 5);
    kenarEkle(graf, 5, 6);

    printf("=== ILK DURUM ANALIZI ===\n");
    matrisYazdir(graf);
    dereceHesapla(graf);
    bipartiteKontrol(graf, 1);

    printf("\n==================================================\n");
    printf("=== DINAMIK TEST: (2, 4) KENARI EKLENDIKTEN SONRA ===\n");
    kenarEkle(graf, 2, 4);
    matrisYazdir(graf);
    dereceHesapla(graf);
    bipartiteKontrol(graf, 1);

    return 0;
}