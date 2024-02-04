#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "coolCFuncs.h"
#define newline printf("\n")
#define DEBUG_NULL 0xcdcdcdcdcdcdcdcd

typedef struct Node {
    char c;
    int f; //frequencies
    struct Node* left;
    struct Node* right;
} Node;

void ppn(Node node, int nth) {
    printf("Node %d:\n", nth);
    printf("  Character: %c\n", node.c);
    printf("  Frequency: %d\n", node.f);
    if (node.left != NULL && node.left != DEBUG_NULL) { // 0xcdcdcdcdcdcdcdcd
        printf("  Left Child:\n");
        printf("    Character: %c\n", node.left->c);
        printf("    Frequency: %d\n", node.left->f);
    }
    if (node.right != NULL && node.right != DEBUG_NULL) { // 0xcdcdcdcdcdcdcdcd
        printf("  Right Child:\n");
        printf("    Character: %c\n", node.right->c);
        printf("    Frequency: %d\n", node.right->f);
    }
    newline;
}

void ppq(Node* priQuene, int size) { // print priority quene
    for (int i = 0; i < size; i++) {
        ppn(priQuene[i], i + 1);
    }
}

void asf(Node* pMain) { // Node* l, Node* r
    pMain->f = pMain->right->f + pMain->left->f; // pMain->f = l->f + r->f;
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
    /*
    for (int i = 0; i < aa.size; i++) {
        priQuene[i] = *newnode(aa.freqs[i].character, aa.freqs[i].frequency);
    }
    */
    Node main = { 0 };

    for (int i = 0; i < aa.size; i += 2) {
        Node* new = newnode('\0', 0);
        if (i + 1 < aa.size) {
            asl(new, &aa.freqs[i]);
            asr(new, &aa.freqs[i + 1]);
            asf(new);
        }
        else {
            new->c = aa.freqs[i].character;
            new->f = aa.freqs[i].frequency;
        }
        priQuene[j] = *new;
        j++;
    }
    /*
    while (j > 1) {
        for (int i = 0; i < j; i += 2) {
            Node* new = newnode('\0', 0);
            if (i + 1 < j) {
                asl(new, &priQuene[0]);
                asr(new, &priQuene[1]);
                asf(new, &priQuene[0], &priQuene[1]);
            }
            else {
                new->c = priQuene[0].c;
                new->f = priQuene[0].f;
            }
            priQuene[0] = *new;
            for (int i = 1; i < j - 1; i++) {
                priQuene[i] = priQuene[i + 1];
            }
        }
        j--;
        sortnodes(priQuene, j);
    }
    */
    /*
    for (int i = j; i > 0; i--) {
        priQuene[i] = priQuene[i - 1];
        ppn(priQuene[i], i);
    }
    */
    while (j > 1) {
        sortnodes(priQuene, j);
        Node* new = newnode('\0', 0);
        asl(new, &priQuene[0]);
        // if (&priQuene[2] != NULL) else get 0 and 1 of priquene element
        asr(new, &priQuene[1]);
        asf(new);
        /*
        ppn(priQuene[0], 0);
        ppn(priQuene[1], 1);
        ppn(priQuene[2], 2);
        */
        //ppn(priQuene[3], j);
        main = *new;
        for (int i = 1; i < j - 1; i++) {
            priQuene[i] = priQuene[i + 1];
        }
        //ppn(main, 0);
        //printf("%d\n", j);
        j--;
    }
    sortnodes(priQuene, j);
    ppn((main.left != NULL && main.right != NULL) ? main : priQuene[0], 1);
    free(priQuene);
}
