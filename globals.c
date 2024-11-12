#define MAX_USUARIOS 5 //Define uma constante limitando o número de usuários cadastrados. Usamos bastante no código para poder iterar todos os usuários cadastrados no vetor com loop for

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
} Dados; 

// Fiz um cadastro para nós 3 para que pudessemos testar a função de cadastro e de login.
Dados usuarios[MAX_USUARIOS] = {
    {//indice 0
        "Francisco Paulino",
        "00000000000",
        "00/00/0000",
        "francisco@paulino.com",
        "00000000000",
        "000000",
        12345678,
        10000
    },
    {//indice 1
        "Matheus Barbosa",
        "11111111111",
        "00/00/0000",
        "matheus@barbosa.com",
        "00000000000",
        "111111",
        87654321,
        10000
    },
    {// indice 2
        "Luan Kennedy",
        "22222222222",
        "00/00/0000",
        "luan@kennedy.com",
        "00000000000",
        "222222",
        01234567,
        10000
    }
};


int contador_usuarios = 3; //Contador para garantir que novos usuários sejam cadastrados sempre no próximo indice do vetor. O valor é incrementado a cada cadastro de usuário
