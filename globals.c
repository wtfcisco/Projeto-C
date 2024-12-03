#include "globals.h"

//Estruturas e variáveis globais
Dados usuarios[MAX_USUARIOS] = {
    {//indice 0
        .nome = "Francisco Paulino",
        .cpf = "00000000000",
        .dataNascimento = "00/00/0000",
        .email = "francisco@paulino.com",
        .telefone = "00000000000",
        .senha = "000000",
        .conta_bancaria = 0000,
        .saldo = 10000,
        .transacao = {{0}},
        .contador_transacoes = 0       
    },
    {//indice 1
        .nome = "Matheus Barbosa",
        .cpf = "11111111111",
        .dataNascimento = "00/00/0000",
        .email = "matheus@barbosa.com",
        .telefone = "00000000000",
        .senha = "000000",
        .conta_bancaria = 1111,
        .saldo = 10000,
        .transacao = {{0}},
        .contador_transacoes = 0
    },
    {//indice 2
        .nome = "Luan Kennedy",
        .cpf = "22222222222",
        .dataNascimento = "00/00/0000",
        .email = "luan@kennedy.com",
        .telefone = "00000000000",
        .senha = "000000",
        .conta_bancaria = 2222,
        .saldo = 10000,
        .transacao = {{0}},
        .contador_transacoes = 0
    },
    {//indice 3
        .nome = "Ramon Rene",
        .cpf = "33333333333",
        .dataNascimento = "00/00/0000",
        .email = "ramon@rene.com",
        .telefone = "00000000000",
        .senha = "000000",
        .conta_bancaria = 3333,
        .saldo = 10000,
        .transacao = {{0}},
        .contador_transacoes = 0
    }
};

int contador_usuarios = 4; // Contador para garantir que novos usuários sejam cadastrados sempre no próximo indice do vetor
char dataHora[20] = "";    // Variável global para armazenar data e hora de transações
