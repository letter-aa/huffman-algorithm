#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "coolCFuncs.h"
#define newline printf("\n")
#define DEBUG_NULL 0xcdcdcdcdcdcdcdcd

typedef struct Node {
    char c; //characters
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

Node* fton(frequency freq) { // frequency to node
    return newnode(freq.character, freq.frequency);
}

Node build(frequencies freq) {
    int j = 0;
    Node* priQuene = malloc(freq.size * sizeof(Node)); //priority quene
    /*
    for (int i = 0; i < aa.size; i++) {
        priQuene[i] = *newnode(aa.freqs[i].character, aa.freqs[i].frequency);
    }
    */
    Node main = { 0 };

    for (int i = 0; i < freq.size; i += 2) {
        Node* new = newnode('\0', 0);
        if (i + 1 < freq.size) {
            asl(new, fton(freq.freqs[i]));
            asr(new, fton(freq.freqs[i + 1]));
            asf(new);
        }
        else {
            new = fton(freq.freqs[i]);
        }
        priQuene[j] = *new;
        j++;
    }

    while (j > 1) {
        sortnodes(priQuene, j);
        Node* new = newnode('\0', 0);
        ppn(priQuene[0], 0);
        ppn(priQuene[1], 1);
        Node* ex = newnode(priQuene[0].c, priQuene[0].f);
        Node* ex1 = newnode(priQuene[1].c, priQuene[1].f);
        asl(ex, priQuene[0].left);
        asr(ex, priQuene[0].right);
        asl(ex1, priQuene[1].left);
        asr(ex1, priQuene[1].right);
        asl(new, ex);
        asr(new, ex1);
        asf(new);
        priQuene[0] = *new;
        for (int i = 1; i < j - 1; i++) {
            priQuene[i] = priQuene[i + 1];
        }
        j--;
    }
    sortnodes(priQuene, j);
    return priQuene[0];
}

int main() {
    char* ipt = input();
    frequencies aa = getfrequencies(ipt);
    newline;
    sortfrequencies(&aa);
    for (int i = 0; i < aa.size; i++) {
        printf("%c: %d\n", aa.freqs[i].character, aa.freqs[i].frequency);
    }
    newline;
    ppn(build(aa), 0);
}
