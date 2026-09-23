#include<stdio.h>
//Kullanıcıdan bir tam sayı alın ve bu sayının bir Palindrom Sayı olup olmadığını bulan C
//programını yazın.
int main(){
int sayi;
printf("bir sayi giriniz:\n");
scanf("%d", &sayi);
int temp = 0;
    for (int k = sayi; k != 0; k /= 10) {
        int kalan = k % 10;
        temp = (temp * 10) + kalan;
    }

    if (sayi == temp) {
        printf("%d bir palindrom sayidir.\n", sayi);
    } else {
        printf("%d bir palindrom sayi degildir.\n", sayi);
    }
    return 0;
}