/*Undo (Geri Alma) Özelliği Simülasyonu
İstenilenler:
 Kullanıcı “metin ekle” diyerek bir kelime girer → stack’e eklenir.
 “undo” seçerse son eklenen kelime geri alınır (pop edilir).
 “show” seçerse şu ana kadar eklenen kelimeleri gösterir.
Beklenen örnek kullanım:
 &gt; add Merhaba
 &gt; add Dünya
 &gt; show -&gt; Merhaba Dünya
 &gt; undo
 &gt; show -&gt; Merhaba
*/
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LEN 50

typedef struct {
    char data[MAX_WORDS][MAX_LEN];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX_WORDS - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, const char *word) {
    if (isFull(s)) {
        printf("Hata: Yigin dolu!\n");
        return;
    }
    s->top++;
    strncpy(s->data[s->top], word, MAX_LEN - 1);
    s->data[s->top][MAX_LEN - 1] = '\0';
}

void pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Hata: Geri alinacak kelime yok!\n");
        return;
    }
    s->top--;
}

void show(Stack *s) {
    if (isEmpty(s)) {
        printf("show -> (bos)\n");
        return;
    }
    printf("show -> ");
    for (int i = 0; i <= s->top; i++) {
        printf("%s%s", s->data[i], (i == s->top) ? "" : " ");
    }
    printf("\n");
}

int main() {
    Stack textStack;
    initStack(&textStack);

    char line[128];
    char command[20];
    char word[MAX_LEN];

    printf("Komutlar: add <kelime>, undo, show, exit\n");

    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if (sscanf(line, "%s", command) != 1) {
            continue;
        }

        if (strcmp(command, "add") == 0) {
            if (sscanf(line, "%*s %s", word) == 1) {
                push(&textStack, word);
            } else {
                printf("Kullanim: add <kelime>\n");
            }
        } else if (strcmp(command, "undo") == 0) {
            pop(&textStack);
        } else if (strcmp(command, "show") == 0) {
            show(&textStack);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Bilinmeyen komut! (add, undo, show, exit)\n");
        }
    }

    return 0;
}