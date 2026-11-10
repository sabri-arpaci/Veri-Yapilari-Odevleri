# Veri Yapıları – 9. Hafta Ödevi
## AVL Tree (Dengeli İkili Arama Ağacı)

### 1. Projenin Amacı

Bu çalışmada AVL ağaçlarının çalışma mantığı, denge faktörü ve rotasyon işlemleri incelenmiştir. C dili kullanılarak AVL ağacına eleman ekleme ve ağacı dengeleme işlemleri gerçekleştirilmiştir.

### 2. AVL Tree Nedir?

AVL Tree, kendi kendini dengeleyen bir Binary Search Tree türüdür.

Her düğüm için denge faktörü şu şekilde hesaplanır:

`BF = Sol Alt Ağacın Yüksekliği - Sağ Alt Ağacın Yüksekliği`

Denge faktörü -1, 0 veya 1 olmalıdır. Bu değerlerin dışına çıkıldığında gerekli rotasyon işlemi uygulanır.

### 3. Soru 1 – RR Rotasyonu

Ekleme sırası: `10, 20, 30`

30 eklendiğinde kök düğümün denge faktörü -2 olur ve RR dengesizliği oluşur.

**Rotasyon öncesi:**

```text
10
  \
   20
     \
      30
```

**Uygulanan işlem:** Sola rotasyon.

**Rotasyon sonrası:**

```text
    20
   /  \
  10  30
```

Beklenen sonuç:

- Kök: 20
- Inorder: 10 20 30
- Preorder: 20 10 30

### 4. Soru 2 – Dört Rotasyon Durumu

| Test | Ekleme Sırası | Rotasyon |
|---|---|---|
| A (LL) | 30, 20, 10 | Sağa rotasyon |
| B (RR) | 10, 20, 30 | Sola rotasyon |
| C (LR) | 30, 10, 20 | Çift rotasyon |
| D (RL) | 10, 30, 20 | Çift rotasyon |

**LL Rotasyonu:** Tek sağ rotasyon uygulanır.

**RR Rotasyonu:** Tek sol rotasyon uygulanır.

**LR Rotasyonu:** Önce sol çocuğa sola, ardından köke sağa rotasyon uygulanır.

**RL Rotasyonu:** Önce sağ çocuğa sağa, ardından köke sola rotasyon uygulanır.

Dört testin de dengeleme sonrasındaki ağacı:

```text
    20
   /  \
  10  30
```

Dört testin de Preorder sonucu:

`20 10 30`

### 5. Ek Çalışma – Inorder Dolaşma

Binary Search Tree yapısında sol alt ağaçtaki değerler kökten küçük, sağ alt ağaçtaki değerler kökten büyüktür.

Inorder dolaşma Sol-Kök-Sağ sırasıyla gerçekleştirildiği için elemanlar küçükten büyüğe sıralanır.

### 6. Ek Çalışma – 2-3 Tree

Boş bir 2-3 ağacına 10, 20 ve 30 sayıları eklendiğinde düğüm bölünür. Ortanca değer olan 20 köke yükselir.

```text
     [20]
     /  \
   [10] [30]
```

### 7. AVL Tree ve Red-Black Tree Karşılaştırması

- AVL Tree, her düğümün sol ve sağ alt ağaç yükseklikleri arasındaki farkı en fazla 1 tutar.
- Red-Black Tree, renk kurallarına dayanarak daha esnek bir dengeleme sağlar.
- Her iki ağaçta da arama, ekleme ve silme işlemlerinin en kötü durum karmaşıklığı O(log n)'dir.

### 8. Dosyalar

- `odev91.c`: C dilinde AVL Tree uygulaması.
- `README.md`: Ödev açıklamaları ve teorik cevaplar.

### 9. Derleme ve Çalıştırma

Windows (GCC):

```bash
gcc -std=c11 -Wall -Wextra -pedantic odev91.c -o avl.exe
.\avl.exe
```

Linux:

```bash
gcc -std=c11 -Wall -Wextra -pedantic odev91.c -o avl
./avl
```

### 10. Kullanılan Teknolojiler

- C Programming Language
- GCC Compiler
- Visual Studio Code