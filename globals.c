//Define uma constante limitando o número de usuários cadastrados. Usamos bastante no código para poder iterar todos os usuários cadastrados no vetor com loop for
#define MAX_USUARIOS 100
#define MAX_TRANSACAO 100
 
typedef struct {
    char descricao[100]; // Ex.: "Depósito", "Saque", "Transferência"
    float valor;
    char dataHora[20];
    char nome_destinatario[50];
} Extrato;


//Define uma typedef struct. Uma estrutura de dados que pode conter mais de um tipo de dados, e podemos nomear essa estrutura como quisermos, chamei-a de Dados.
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

// Fiz um cadastro para nós 3 para que pudessemos testar a função de cadastro e de login.
Dados usuarios[MAX_USUARIOS] = {
    {//indice 0
        .nome = "Francisco Paulino",
        .cpf = "00000000000",
        .dataNascimento = "00/00/0000",
        .email = "francisco@paulino.com",
        .telefone= "00000000000",
        .senha = "000000",
        .conta_bancaria = 12345678,
        .saldo = 10000,
        .transacao = {{}},
        .contador_transacoes = 0       
    },
    {//indice 1
        .nome = "Matheus Barbosa",
        .cpf = "11111111111",
        .dataNascimento = "00/00/0000",
        .email = "matheus@barbosa.com",
        .telefone= "00000000000",
        .senha = "111111",
        .conta_bancaria = 87654321,
        .saldo = 10000,
        .transacao = {{}},
        .contador_transacoes = 0
    },
    {// indice 2
        .nome = "Luan Kennedy",
        .cpf = "22222222222",
        .dataNascimento = "00/00/0000",
        .email = "luan@kennedy.com",
        .telefone= "00000000000",
        .senha = "222222",
        .conta_bancaria = 01234567,
        .saldo = 10000,
        .transacao = {{}},
        .contador_transacoes = 0
    }
};

int contador_usuarios = 3; //Contador para garantir que novos usuários sejam cadastrados sempre no próximo indice do vetor. O valor é incrementado a cada cadastro de usuário
char dataHora[20] = "";
