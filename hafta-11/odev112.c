#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 6
#define INF 99999

char dugumIsmi(int index) {
    return 'A' + index;
}

int dugumIndeksi(char harf) {
    if (harf >= 'a' && harf <= 'f') return harf - 'a';
    return harf - 'A';
}

void kenarEkle(int graf[V][V], char u, char v, int agirlik) {
    int i = dugumIndeksi(u);
    int j = dugumIndeksi(v);
    graf[i][j] = agirlik;
    graf[j][i] = agirlik;
}

void tabloYazdir(int adim, bool known[], int dist[], int path[]) {
    printf("\n--- Adim %d ---\n", adim);
    printf("Dugum | Known | Distance | Path\n");
    printf("------|-------|----------|-----\n");
    for (int i = 0; i < V; i++) {
        printf("  %c   |   %d   |   ", dugumIsmi(i), known[i]);
        if (dist[i] == INF) printf("INF    | ");
        else printf("%-6d | ", dist[i]);

        if (path[i] == -1) printf("-\n");
        else printf("%c\n", dugumIsmi(path[i]));
    }
}

void rotaYazdir(int hedef, int path[]) {
    if (path[hedef] == -1) {
        printf("%c", dugumIsmi(hedef));
        return;
    }
    rotaYazdir(path[hedef], path);
    printf("->%c", dugumIsmi(hedef));
}

int dijkstra(int graf[V][V], int kok, bool detayYazdir, int outDist[], int outPath[]) {
    bool known[V];
    int dist[V];
    int path[V];

    for (int i = 0; i < V; i++) {
        known[i] = false;
        dist[i] = INF;
        path[i] = -1;
    }

    dist[kok] = 0;

    for (int adim = 0; adim < V; adim++) {
        int minDist = INF;
        int u = -1;

        for (int i = 0; i < V; i++) {
            if (!known[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        known[u] = true;

        for (int v = 0; v < V; v++) {
            if (!known[v] && graf[u][v] > 0 && dist[u] + graf[u][v] < dist[v]) {
                dist[v] = dist[u] + graf[u][v];
                path[v] = u;
            }
        }

        if (detayYazdir) {
            tabloYazdir(adim + 1, known, dist, path);
        }
    }

    int toplamMaliyet = 0;
    for (int i = 0; i < V; i++) {
        if (outDist != NULL) outDist[i] = dist[i];
        if (outPath != NULL) outPath[i] = path[i];
        if (dist[i] != INF) toplamMaliyet += dist[i];
    }
    return toplamMaliyet;
}

int main() {
    int graf[V][V] = {0};

    // Tablodaki kenarlar
    kenarEkle(graf, 'A', 'B', 7);
    kenarEkle(graf, 'A', 'C', 5);
    kenarEkle(graf, 'A', 'F', 1);
    kenarEkle(graf, 'B', 'C', 1);
    kenarEkle(graf, 'B', 'D', 1);
    kenarEkle(graf, 'B', 'E', 3);
    kenarEkle(graf, 'C', 'D', 2);
    kenarEkle(graf, 'C', 'E', 1);
    kenarEkle(graf, 'D', 'F', 7);
    kenarEkle(graf, 'E', 'F', 2);

    char secim;
    printf("1. Gorev icin kok dugumu giriniz (Orn: A): ");
    scanf(" %c", &secim);
    int kok = dugumIndeksi(secim);

    int dist[V], path[V];
    printf("\n=== DIJKSTRA ADIM TABLOSU (Kok: %c) ===\n", dugumIsmi(kok));
    dijkstra(graf, kok, true, dist, path);

    // 2. Gorev: A dugumunden B ve D'ye en kisa yollar
    printf("\n=== 2. GOREV: A DUGUMUNDEN ROTA CIKTILARI ===\n");
    int distA[V], pathA[V];
    dijkstra(graf, dugumIndeksi('A'), false, distA, pathA);

    printf("A -> B En Dusuk Maliyet: %d | Rota: ", distA[dugumIndeksi('B')]);
    rotaYazdir(dugumIndeksi('B'), pathA);
    printf("\n");

    printf("A -> D En Dusuk Maliyet: %d | Rota: ", distA[dugumIndeksi('D')]);
    rotaYazdir(dugumIndeksi('D'), pathA);
    printf("\n");

    // 3. Gorev: Merkezi Dugum Tespiti
    printf("\n=== 3. GOREV: MERKEZI DUGUM ANALIZI ===\n");
    int minToplam = INF;
    int merkeziDugum = -1;

    for (int i = 0; i < V; i++) {
        int toplam = dijkstra(graf, i, false, NULL, NULL);
        printf("Kok Dugum %c -> En Kisa Yol Agaci Toplam Maliyeti: %d\n", dugumIsmi(i), toplam);
        if (toplam < minToplam) {
            minToplam = toplam;
            merkeziDugum = i;
        }
    }

    printf("\nEN MERKEZI DUGUM (Ana Aktarma Merkezi): %c (Toplam Maliyet: %d)\n", 
           dugumIsmi(merkeziDugum), minToplam);

    return 0;
}