/*Bu uygulama bir müzik çalar gibi çalışacak.
Kullanıcı şarkı ekleyip silebilecek, ileri/geri şarkı geçişi yapabilecek.
Buradaki amaç, prev ve next pointer’larının dinamik şekilde yönetimini kavratmak.
Yapılacaklar:
 addSongToEnd(Node** head, char* isim)
 removeSong(Node** head, char* isim)
 playNext() ve playPrevious() fonksiyonları.
 Menü: Kullanıcı seçimleriyle listeyi yönetsin.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SONG_NAME 100

typedef struct Node {
	char isim[MAX_SONG_NAME];
	struct Node *prev;
	struct Node *next;
} Node;

static Node *currentSong = NULL;

void addSongToEnd(Node **head, char *isim);
void removeSong(Node **head, char *isim);
void playNext(void);
void playPrevious(void);
void showPlaylist(Node *head);
int readLine(char *buffer, size_t size);
void freePlaylist(Node **head);

void addSongToEnd(Node **head, char *isim) {
	Node *newSong = malloc(sizeof(Node));
	if (newSong == NULL) {
		printf("Bellek ayrilamadi.\n");
		return;
	}

	snprintf(newSong->isim, sizeof(newSong->isim), "%s", isim);
	newSong->next = NULL;

	if (*head == NULL) {
		newSong->prev = NULL;
		*head = newSong;
		currentSong = newSong;
	} else {
		Node *lastSong = *head;
		while (lastSong->next != NULL) {
			lastSong = lastSong->next;
		}
		lastSong->next = newSong;
		newSong->prev = lastSong;
	}

	printf("'%.99s' listeye eklendi.\n", newSong->isim);
}

void removeSong(Node **head, char *isim) {
	Node *song = *head;
	while (song != NULL && strcmp(song->isim, isim) != 0) {
		song = song->next;
	}

	if (song == NULL) {
		printf("Bu isimde bir sarki bulunamadi.\n");
		return;
	}

	if (song->prev != NULL) {
		song->prev->next = song->next;
	} else {
		*head = song->next;
	}
	if (song->next != NULL) {
		song->next->prev = song->prev;
	}

	if (currentSong == song) {
		currentSong = song->next != NULL ? song->next : song->prev;
	}

	printf("'%.99s' listeden silindi.\n", song->isim);
	free(song);
}

void playNext(void) {
	if (currentSong == NULL) {
		printf("Calma listesinde sarki yok.\n");
	} else if (currentSong->next == NULL) {
		printf("Son sarkidasiniz; ileri sarki yok.\n");
	} else {
		currentSong = currentSong->next;
		printf("Simdi caliyor: %s\n", currentSong->isim);
	}
}

void playPrevious(void) {
	if (currentSong == NULL) {
		printf("Calma listesinde sarki yok.\n");
	} else if (currentSong->prev == NULL) {
		printf("Ilk sarkidasiniz; onceki sarki yok.\n");
	} else {
		currentSong = currentSong->prev;
		printf("Simdi caliyor: %s\n", currentSong->isim);
	}
}

void showPlaylist(Node *head) {
	if (head == NULL) {
		printf("Calma listesi bos.\n");
		return;
	}

	printf("\nCalma listesi:\n");
	while (head != NULL) {
		printf("%s %s\n", head == currentSong ? ">" : " ", head->isim);
		head = head->next;
	}
}

int readLine(char *buffer, size_t size) {
	if (fgets(buffer, (int)size, stdin) == NULL) {
		return 0;
	}

	size_t length = strcspn(buffer, "\n");
	if (buffer[length] == '\n') {
		buffer[length] = '\0';
	} else {
		int character;
		while ((character = getchar()) != '\n' && character != EOF) {
		}
	}
	return 1;
}

void freePlaylist(Node **head) {
	Node *song = *head;
	while (song != NULL) {
		Node *nextSong = song->next;
		free(song);
		song = nextSong;
	}
	*head = NULL;
	currentSong = NULL;
}

int main(void) {
	Node *head = NULL;
	char input[32];
	char songName[MAX_SONG_NAME];
	int choice;

	do {
		printf("\n--- Muzik Calar ---\n");
		printf("1. Sarki ekle\n");
		printf("2. Sarki sil\n");
		printf("3. Sonraki sarki\n");
		printf("4. Onceki sarki\n");
		printf("5. Listeyi goster\n");
		printf("6. Calan sarkiyi goster\n");
		printf("0. Cikis\n");
		printf("Seciminiz: ");

		if (!readLine(input, sizeof(input))) {
			break;
		}
		choice = atoi(input);

		switch (choice) {
			case 1:
				printf("Eklenecek sarki adi: ");
				if (readLine(songName, sizeof(songName)) && songName[0] != '\0') {
					addSongToEnd(&head, songName);
				} else {
					printf("Sarki adi bos olamaz.\n");
				}
				break;
			case 2:
				printf("Silinecek sarki adi: ");
				if (readLine(songName, sizeof(songName)) && songName[0] != '\0') {
					removeSong(&head, songName);
				} else {
					printf("Sarki adi bos olamaz.\n");
				}
				break;
			case 3:
				playNext();
				break;
			case 4:
				playPrevious();
				break;
			case 5:
				showPlaylist(head);
				break;
			case 6:
				if (currentSong == NULL) {
					printf("Calma listesinde sarki yok.\n");
				} else {
					printf("Simdi caliyor: %s\n", currentSong->isim);
				}
				break;
			case 0:
				break;
			default:
				printf("Gecersiz secim.\n");
		}
	} while (choice != 0);

	freePlaylist(&head);
	return 0;
}