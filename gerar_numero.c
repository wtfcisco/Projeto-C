#include <stdlib.h>
#include <time.h>

int gerar_numero() {
    // Inicializa a semente do gerador de números aleatórios dentro da função. A semente é baseada no tempo atual
    srand(time(NULL)); 

    // Gera um número aleatório de 8 dígitos
    return (rand() % 90000000) + 10000000;  // Garante que o número tenha 8 dígitos

    // Eu particulamente não entendi nada da sintaxe desse código aqui, essas funções em C são pouco legíveis e fazem pouco sentido.
}
