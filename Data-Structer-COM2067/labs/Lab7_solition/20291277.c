#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* sol;
    struct Node* sag;
    int uzunluk;
};

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->sol = node->sag = NULL;
    node->uzunluk = 1;
    return node;
}

int uzunluk(struct Node* N) {
    if (N == NULL)
        return 0;
    return N->uzunluk;
}

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* sagDon(struct Node* y) {
    struct Node* x = y->sol;
    struct Node* T2 = x->sag;

    x->sag = y;
    y->sol = T2;

    y->uzunluk = maximum(uzunluk(y->sol), uzunluk(y->sag)) + 1;
    x->uzunluk = maximum(uzunluk(x->sol), uzunluk(x->sag)) + 1;

    return x;
}

struct Node* solDon(struct Node* x) {
    struct Node* y = x->sag;
    struct Node* T2 = y->sol;

    y->sol = x;
    x->sag = T2;

    x->uzunluk = maximum(uzunluk(x->sol), uzunluk(x->sag)) + 1;
    y->uzunluk = maximum(uzunluk(y->sol), uzunluk(y->sag)) + 1;

    return y;
}

int getBalance(struct Node* N) {
    if (N == NULL)
        return 0;
    return uzunluk(N->sol) - uzunluk(N->sag);
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->sol = insert(node->sol, key);
    else if (key > node->key)
        node->sag = insert(node->sag, key);
    else
        return node;

    node->uzunluk = 1 + maximum(uzunluk(node->sol), uzunluk(node->sag));

    int balance = getBalance(node);

    if (balance > 1 && key < node->sol->key)
        return sagDon(node);

    if (balance < -1 && key > node->sag->key)
        return solDon(node);

    if (balance > 1 && key > node->sol->key) {
        node->sol = solDon(node->sol);
        return sagDon(node);
    }

    if (balance < -1 && key < node->sag->key) {
        node->sag = sagDon(node->sag);
        return solDon(node);
    }

    return node;
}

void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->sol);
        printf("%d\n", root->key);
        inOrder(root->sag);
    }
}

void printCurrentLevel(struct Node* root, int level) {
    if (root == NULL)
        return;
    if (level == 1) {
        if (root->sol && root->sag) {
            printf("%d (%d L) (%d B) %d (%d R) (%d B) ", root->sol->key, root->key, getBalance(root->sol), root->sag->key, root->key, getBalance(root->sag));
        } else if (root->sol) {
            printf("%d (%d L) (%d B) ", root->sol->key, root->key, getBalance(root->sol));
        } else if (root->sag) {
            printf("%d (%d R) (%d B) ", root->sag->key, root->key, getBalance(root->sag));
        }
    } else if (level > 1) {
        printCurrentLevel(root->sol, level - 1);
        printCurrentLevel(root->sag, level - 1);
    }
}

int uzunlukBul(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + maximum(uzunlukBul(root->sol), uzunlukBul(root->sag));
}

void printLevelOrder(struct Node* root) {
    int h = uzunlukBul(root);
    int i;
    for (i = 1; i <= h; i++) {
        printCurrentLevel(root, i);
        printf("\n");
    }
}

int main() {
    struct Node* root = NULL;
    int key;

    while (1) {
        scanf("%d", &key);
        if (key == -1)
            break;
        root = insert(root, key);
    }

    inOrder(root);

    printf("\n");
    printf("%d (-1 B)\n", root->key);
    printLevelOrder(root);

    return 0;
}
