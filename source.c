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

void as(Node* pMain, Node* l, Node* r){
    pMain->left = l;
    pMain->right = r;
    asf(pMain, l, r);
} //assign left & right

void sortnodes(Node* nodes, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (nodes[j].f > nodes[i].f) {
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
    //Node* nodes = malloc(aa.size * sizeof(Node*));
    Node* priQuene = malloc(aa.size * sizeof(Node)); //priority quene
    Node main = { 0 };

    /*
    for (int i = 0; i < aa.size; i++) { // aa.size + ceil(aa.size / 2) == amount of nodes
        printf("%c\n", aa.freqs[i].character);
        Node* new = newnode(aa.freqs[i].character, aa.freqs[i].frequency);
        nodes[i] = *new;
    }
    */

    for (int i = 0; i < aa.size - (aa.size % 2); i += 2) {
        //printf("%c\n", aa.freqs[i].character);
        //printf("%c\n", aa.freqs[i + 1].character);
        Node* new = newnode('\0', 0);
        Node* new1 = newnode(aa.freqs[i].character, aa.freqs[i].frequency);
        Node* new2 = newnode(aa.freqs[i + 1].character, aa.freqs[i + 1].frequency);
        as(new, new1, new2);
        priQuene[j] = *new;
        j++;
    }

   /*
    while (sizeEx > 0) {
        for (int i = 0; i < sizeEx - (sizeEx % 2); i += 2) {
            printf("%c\n", aa.freqs[i].character);
            printf("%c\n", aa.freqs[i + 1].character);
            Node* new = newnode('\0', 0);
            Node* new1 = newnode(aa.freqs[i].character, aa.freqs[i].frequency);
            Node* new2 = newnode(aa.freqs[i + 1].character, aa.freqs[i + 1].frequency);
            as(new, new1, new2);
            priQuene[j] = *new;
            j++;
            printf("%c, %c, %d\n", aa.freqs[i].character, aa.freqs[i + 1].character, i);
        }
        sizeEx = sizeEx - (sizeEx % 2);
        sizeEx = sizeEx / 2;
        //j = 0;
        //f++;
    }
   */
    if (aa.size % 2) { // if odd number of nodes - aa.size
        priQuene[j] = *newnode(aa.freqs[aa.size - 1].character, aa.freqs[aa.size - 1].frequency); // + (aa.size > 1)
        j++;
    }

    //printf("%d\n", j);

    sortnodes(priQuene, j);

    ppq(priQuene, j);

    /*
    newline;
    newline;
    newline;
    for (int i = 0; i < aa.size; i++) {
        printf("%c\n%d\n\n", aa.freqs[i].character, aa.freqs[i].frequency);
    }
    */
    free(priQuene);
}
