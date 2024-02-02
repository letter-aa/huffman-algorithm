#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "coolCFuncs.h"
#define newline printf("\n")

typedef struct Node {
    char c;
    int f; //frequencies
    struct Node* left;
    struct Node* right;
} Node;

void ppq(Node* priQuene, int size) { // print priority quene
    for (int i = 0; i < size; i++) {
        printf("Node %d:\n", i + 1);
        printf("  Character: %c\n", priQuene[i].c);
        printf("  Frequency: %d\n", priQuene[i].f);
        if (priQuene[i].left != NULL && priQuene[i].left != 0xcdcdcdcdcdcdcdcd) {
            printf("  Left Child:\n");
            printf("    Character: %c\n", priQuene[i].left->c);
            printf("    Frequency: %d\n", priQuene[i].left->f);
        }
        if (priQuene[i].right != NULL && priQuene[i].right != 0xcdcdcdcdcdcdcdcd) {
            printf("  Right Child:\n");
            printf("    Character: %c\n", priQuene[i].right->c);
            printf("    Frequency: %d\n", priQuene[i].right->f);
        }
        newline;
    }
}

void asf(Node* pMain, Node* l, Node* r) {
    pMain->f = pMain->right->f + pMain->left->f;
}

void asl(Node* pMain, Node* l) {
    pMain->left = l;
}

void asr(Node* pMain, Node* r) {
    pMain->right = r;
} //assign left & right

void sortnodes(Node* nodes, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (nodes[j].f < nodes[i].f) { // > if least to greatest, < if vice versa
                Node old = nodes[j];
                nodes[j] = nodes[i];
                nodes[i] = old;
            }
        }
    }
}

Node* newnode(char c, int f) {
    Node* new = malloc(sizeof(Node));
    new->c = c;
    new->f = f;
    new->left = NULL;
    new->right = NULL;
    return new;
}

int main() {
    int f = 0;
    char* ipt = input();
    frequencies aa = getfrequencies(ipt);
    newline;
    sortfrequencies(&aa);
    int j = 0;
    for (int i = 0; i < aa.size; i++) {
        printf("%c: %d\n", aa.freqs[i].character, aa.freqs[i].frequency);
    }
    newline;
    Node* priQuene = malloc(aa.size * sizeof(Node)); //priority quene
    Node main = { 0 };

    for (int i = 0; i < aa.size; i += 2) {
        Node* new = newnode('\0', 0);
        if (i + 1 < aa.size) {
            asl(new, &aa.freqs[i]);
            asr(new, &aa.freqs[i + 1]);
            asf(new, &aa.freqs[i], &aa.freqs[i + 1]);
        }
        else {
            new->c = aa.freqs[i].character;
            new->f = aa.freqs[i].frequency;
        }
        priQuene[j] = *new;
        j++;
    }
    sortnodes(priQuene, j);
    ppq(priQuene, j);
    free(priQuene);
}
