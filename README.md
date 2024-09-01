# posfixa.c
Situação 3: Considere operações infixas compostas exclusivamente por letras maiúsculas e operadores
aritméticos.
Exemplos:
A+B-C
A-B+C*D
A/(B-C)+D*(E/F)
A/(B+C)
Para se obter a notação posfixa, um dos algoritmos é apresentado a seguir:
• Copiamos os números/letras diretamente na saída
• Quando aparece um operador (+,-,/,*)
✓ Enquanto o operador no topo da pilha tem precedência maior ou igual ao operador na
entrada: desempilhamos e copiamos na saída
✓ Empilhamos o operador novo

• Abre parênteses é sempre empilhado
• Fecha parênteses nunca é empilhado (menor precedência). Todos os operadores são desempilhados
até encontrar um ‘(‘.
• No final, desempilhamos todos os elementos da pilha, copiando para a saída
Seja s uma string que representa uma destas expressões. Crie um programa que receba s e devolve como






# Conversão e Avaliação de Expressões Infixas

Este projeto em C realiza a conversão de expressões infixas para notação posfixa (notação polonesa reversa) e avalia a expressão posfixa resultante. A conversão é feita usando uma pilha para gerenciar operadores e parênteses, enquanto a avaliação da notação posfixa é feita com outra pilha.

## Funcionalidades

- **Conversão de Expressão**: Converte expressões infixas (ex: `A+B-C`) para notação posfixa (ex: `AB+C-`).
- **Avaliação**: Avalia a expressão posfixa usando valores fornecidos pelo usuário para cada letra da expressão.

## Algoritmos Utilizados

### Conversão para Notação Posfixa
1. **Copiar Letras/Números**: Letras e números são copiados diretamente para a saída.
2. **Gerenciar Operadores**:
   - Enquanto o operador no topo da pilha tem precedência maior ou igual ao operador atual, desempilhar e copiar para a saída.
   - Empilhar o operador atual.
3. **Gerenciar Parênteses**:
   - Abre parênteses são empilhados.
   - Fecha parênteses resultam na remoção dos operadores da pilha até encontrar um abre parênteses.
4. **Desempilhar Restantes**: Todos os operadores restantes na pilha são desempilhados e copiados para a saída.

### Avaliação da Expressão Posfixa
1. **Gerenciar Operandos**: Empilhar operandos (valores).
2. **Gerenciar Operadores**:
   - Desempilhar os operandos necessários.
   - Aplicar o operador.
   - Empilhar o resultado.

## Código

```c
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


**Instruções de Compilação e Execução**
**Compilar o Código:**
gcc -o posfixa posfixa.c

**Executar o Programa:**
./posfixa

Uso:

Digite a expressão infixa: Insira a expressão no formato infixo, como A+B-C.
Informe os valores para cada letra: Forneça valores inteiros para cada letra na expressão.
Resultado: O programa exibirá a expressão na notação posfixa e o resultado da avaliação.

