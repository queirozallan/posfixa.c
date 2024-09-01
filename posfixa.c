
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int topo;
    char itens[MAX];
} Pilha;

// Funções para manipular a pilha
void inicializarPilha(Pilha* p) {
    p->topo = -1;
}

int pilhaVazia(Pilha* p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha* p) {
    return p->topo == MAX - 1;
}

void empilhar(Pilha* p, char c) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia!\n");
        return;
    }
    p->itens[++(p->topo)] = c;
}

char desempilhar(Pilha* p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return '\0';
    }
    return p->itens[(p->topo)--];
}

char topoPilha(Pilha* p) {
    if (pilhaVazia(p)) {
        return '\0';
    }
    return p->itens[p->topo];
}

// Funções auxiliares
int precedencia(char operador) {
    switch (operador) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

void infixaParaPosfixa(char* infixa, char* posfixa) {
    Pilha p;
    inicializarPilha(&p);
    int i = 0, j = 0;
    
    while (infixa[i] != '\0') {
        if (isalnum(infixa[i])) {
            posfixa[j++] = infixa[i];
        } else if (infixa[i] == '(') {
            empilhar(&p, infixa[i]);
        } else if (infixa[i] == ')') {
            while (!pilhaVazia(&p) && topoPilha(&p) != '(') {
                posfixa[j++] = desempilhar(&p);
            }
            desempilhar(&p);  // Remove '('
        } else {
            while (!pilhaVazia(&p) && precedencia(topoPilha(&p)) >= precedencia(infixa[i])) {
                posfixa[j++] = desempilhar(&p);
            }
            empilhar(&p, infixa[i]);
        }
        i++;
    }
    
    while (!pilhaVazia(&p)) {
        posfixa[j++] = desempilhar(&p);
    }
    
    posfixa[j] = '\0';
}

// Função para avaliar expressão posfixa
int avaliarPosfixa(char* posfixa, int* valores) {
    Pilha p;
    inicializarPilha(&p);
    int i = 0;
    
    while (posfixa[i] != '\0') {
        if (isalnum(posfixa[i])) {
            empilhar(&p, posfixa[i]);
        } else {
            int op2 = topoPilha(&p) - '0';
            desempilhar(&p);
            int op1 = topoPilha(&p) - '0';
            desempilhar(&p);
            
            switch (posfixa[i]) {
                case '+': empilhar(&p, op1 + op2 + '0'); break;
                case '-': empilhar(&p, op1 - op2 + '0'); break;
                case '*': empilhar(&p, op1 * op2 + '0'); break;
                case '/': empilhar(&p, op1 / op2 + '0'); break;
            }
        }
        i++;
    }
    
    return topoPilha(&p) - '0';
}

int main() {
    char infixa[MAX], posfixa[MAX];
    int valores[26];
    
    printf("Digite a expressão infixa: ");
    fgets(infixa, MAX, stdin);
    infixa[strcspn(infixa, "\n")] = '\0';  // Remove newline
    
    infixaParaPosfixa(infixa, posfixa);
    printf("Expressão em notação posfixa: %s\n", posfixa);
    
    for (char c = 'A'; c <= 'Z'; c++) {
        if (strchr(infixa, c)) {
            printf("Digite o valor para %c: ", c);
            scanf("%d", &valores[c - 'A']);
        }
    }
    
    printf("Resultado da avaliação: %d\n", avaliarPosfixa(posfixa, valores));
    
    return 0;
}
