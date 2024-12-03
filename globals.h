#ifndef GLOBALS_H
#define GLOBALS_H

#define MAX_USUARIOS 99
#define MAX_TRANSACAO 99

// Estrutura para armazenar informações das transações
typedef struct {
    char descricao[100]; // Ex.: "Depósito", "Saque", "Transferência"
    float valor;
    char dataHora[20];
    char nome_destinatario[50]; // Nome do destinatário em transferências
    char nome_remetente[50];    // Nome do remetente em transferências
} Extrato;

// Estrutura para armazenar informações dos usuários
typedef struct {
    char nome[100];
    char cpf[15];
    char dataNascimento[11];
    char email[100];
    char telefone[15];
    char senha[20];
    int conta_bancaria;
    float saldo;
    int contador_transacoes;
    Extrato transacao[MAX_TRANSACAO];
} Dados;

// Declaração das variáveis globais
extern Dados usuarios[MAX_USUARIOS];
extern int contador_usuarios;
extern char dataHora[20];

#endif // GLOBALS_H
