/*Parantez Dengesi Kontrolü
İstenilenler:
 Kullanıcıdan bir ifade alınır (örnek: {[()()]})
 Stack kullanarak parantezlerin dengede olup olmadığı kontrol edilir.
 Her ( için push, her ) için pop yapılır.
Beklenen Çıktı:
 İfade: {[()()]}
 Sonuç: Parantezler dengede!*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 256

// Yığın (Stack) Yapısı
typedef struct {
    char items[MAX_LEN];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

bool isEmpty(const Stack *s) {
    return s->top == -1;
}

bool isFull(const Stack *s) {
    return s->top == MAX_LEN - 1;
}

void push(Stack *s, char c) {
    if (!isFull(s)) {
        s->items[++(s->top)] = c;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

// Parantezlerin birbirini kapatıp kapatmadığını kontrol etme
bool isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '{' && close == '}') return true;
    if (open == '[' && close == ']') return true;
    return false;
}

// Parantez dengesini doğrulayan fonksiyon
bool isBalanced(const char *expr) {
    Stack s;
    initStack(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        // Açılış parantezi ise yığına ekle (push)
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        }
        // Kapanış parantezi ise kontrol et ve çıkar (pop)
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&s)) {
                return false; // Kapatılacak açılış parantezi yok
            }
            char topChar = pop(&s);
            if (!isMatchingPair(topChar, ch)) {
                return false; // Eşleşmeyen türde parantez (örn. [} veya (])
            }
        }
    }

    // İfade bittiğinde yığın tamamen boş olmalı
    return isEmpty(&s);
}

int main() {
    char expr[MAX_LEN];

    printf("Parantez iceren bir ifade girin: ");
    if (fgets(expr, sizeof(expr), stdin)) {
        // Satır sonu karakterini temizle
        expr[strcspn(expr, "\n")] = '\0';

        printf("İfade: %s\n", expr);

        if (isBalanced(expr)) {
            printf("Sonuç: Parantezler dengede!\n");
        } else {
            printf("Sonuç: Parantezler dengede DEĞİL!\n");
        }
    }

    return 0;
}