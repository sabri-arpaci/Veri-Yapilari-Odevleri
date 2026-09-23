#include <stdio.h>
/*C programlama dilinde 10 elemanlı bir tamsayı dizisi tanımlayınız. Kullanıcıdan dizinin 10
elemanını alınız ve daha sonra bu elemanları ekrana yazdırınız.*/
int main() {
  int dizi[10];
  printf("dizinin 10 elemanini giriniz:\n");
  for(int i=0; i<10; i++){
    scanf("%d", &dizi[i]);
  }

printf("Dizinin elemanlari:\n");
for(int i=0; i<10; i++){
  printf("%d ", dizi[i]);
}
return 0;
}

//Diğer soruların cevapları;
// 2. T(n) Zaman Maliyeti: T(n) = a*n + b (Dogrusal Maliyet)
// (Donguler n defa calistigi icin girdi boyutuyla orantili islem yapilir)
//3. O(n) Zaman Karmasikligi: O(n)
//4. S(n) Alan Karmasikligi: O(n) (n elemanli dizi hafizada tutulur)
