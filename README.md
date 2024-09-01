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






Conversão de Expressão Infixa para Posfixa e Avaliação
Este projeto em C realiza a conversão de uma expressão infixa (usando letras maiúsculas e operadores aritméticos) para a notação posfixa (notação polonesa reversa) e avalia a expressão com base em valores fornecidos para cada letra.

Funcionalidades
Conversão de Expressão: Converte uma expressão infixa para a notação posfixa usando o algoritmo de Shunting Yard.
Avaliação: Avalia a expressão posfixa com valores fornecidos para cada letra.
Interface de Usuário: Permite ao usuário inserir a expressão e fornecer os valores para as letras.
Exemplos
Expressão Infixa
A+B-C
A-B+C*D
A/(B-C)+D*(E/F)
A/(B+C)
Notação Posfixa
Para A+B-C, a notação posfixa seria AB+C-.
Para A-B+C*D, a notação posfixa seria AB-CD*+.
Para A/(B-C)+D*(E/F), a notação posfixa seria ABC-/DE/F*+.
Como Usar
Compilação: Compile o código usando o compilador gcc.


gcc -o posfixa posfixa.c
Execução: Execute o programa.
./posfixa
Entrada:

Digite a expressão infixa: Insira a expressão que deseja converter.
Digite o valor para cada letra: Forneça valores para cada letra usada na expressão.
Saída:

O programa exibirá a expressão na notação posfixa.
O resultado da avaliação da expressão posfixa será mostrado.
Código
O código-fonte está no arquivo posfixa.c. Aqui está uma visão geral das principais funções:

infixaParaPosfixa: Converte uma expressão infixa para a notação posfixa.
calcularPosfixa: Avalia a expressão posfixa com valores fornecidos.
main: Gerencia a entrada do usuário e exibe o resultado.
Requisitos
Compilador C: gcc ou outro compilador compatível com C.
