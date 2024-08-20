#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 60

typedef struct Node {
    char isim[MAX_STR];
    struct Node* next;
} Node;

typedef struct {
    Node* bas;
    Node* son;
} Queue;

Queue* createQuery() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->bas = queue->son = NULL;
    return queue;
}

void endQuery(Queue* queue, const char* isim) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->isim, isim);
    newNode->next = NULL;

    if (queue->son == NULL) {
        queue->bas = queue->son = newNode;
        return;
    }

    queue->son->next = newNode;
    queue->son = newNode;
}

char* deq(Queue* queue) {
    if (queue->bas == NULL) {
        return NULL;
    }

    Node* temp = queue->bas;
    char* isim = (char*)malloc(MAX_STR);
    strcpy(isim, temp->isim);

    queue->bas = queue->bas->next;
    if (queue->bas == NULL) {
        queue->son = NULL;
    }

    free(temp);
    return isim;
}

void freeQ(Queue* queue) {
    while (queue->bas != NULL) {
        Node* temp = queue->bas;
        queue->bas = queue->bas->next;
        free(temp);
    }
    free(queue);
}

int oncelik(const char *isim) {
    if (strcmp(isim, "Annem") == 0 || strcmp(isim, "Babam") == 0 || strcmp(isim, "Kardesim") == 0)
        return 1;
    else if (strcmp(isim, "Amcam") == 0 || strcmp(isim, "Halam") == 0 || strcmp(isim, "Teyzem") == 0 || strcmp(isim, "Dayim") == 0)
        return 2;
    else if (strcmp(isim, "Isyeri") == 0 || strcmp(isim, "Okul") == 0)
        return 3;
    else if (strcmp(isim, "Arkadasim1") == 0 || strcmp(isim, "Arkadasim2") == 0 || strcmp(isim, "Arkadasim3") == 0 || strcmp(isim, "Arkadasim4") == 0 || strcmp(isim, "Arkadasim5") == 0)
        return 4;
    else if (strcmp(isim, "Banka") == 0 || strcmp(isim, "Kargo") == 0)
        return 5;
    else if (strcmp(isim, "Reklam") == 0)
        return 6;
    else
        return 7; 
}

void sortQuery(Queue* queue) {
    int n = 0;
    Node* temp = queue->bas;
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }

    char** isimler = (char**)malloc(n * sizeof(char*));
    temp = queue->bas;
    for (int i = 0; i < n; i++) {
        isimler[i] = (char*)malloc(MAX_STR);
        strcpy(isimler[i], temp->isim);
        temp = temp->next;
    }

    // Sıralama
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (oncelik(isimler[i]) > oncelik(isimler[j]) || (oncelik(isimler[i]) == oncelik(isimler[j]) && strcmp(isimler[i], isimler[j]) > 0)) {
                char* tempName = isimler[i];
                isimler[i] = isimler[j];
                isimler[j] = tempName;
            }
        }
    }

    temp = queue->bas;
    for (int i = 0; i < n; i++) {
        strcpy(temp->isim, isimler[i]);
        temp = temp->next;
    }

    for (int i = 0; i < n; i++) {
        free(isimler[i]);
    }
    free(isimler);
}

int main() {
    Queue* queue = createQuery();
    char input[MAX_STR];

    while (1) {
        fgets(input, MAX_STR, stdin);
        input[strcspn(input, "\n")] = '\0'; 

        if (strcmp(input, "-1") == 0) {
            break;
        }

        endQuery(queue, input);
    }

    sortQuery(queue);

    char* isim;
    while ((isim = deq(queue)) != NULL) {
        printf("%s\n", isim);
        free(isim);
    }

    freeQ(queue);
    return 0;
}
