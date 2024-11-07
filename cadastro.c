#include <stdio.h>
#include "gerar_numero.c" // Função gerar número

// Definição da constante MAX_USUARIOS para limitar o número de cadastros de usuários. Para testes, podemos remover depois.
#define MAX_USUARIOS 2

// Estrutura para armazenar os dados do usuário. Qualquer duvida joga no stackoverflow ou gpt. Serve pra declarar uma estrutura de dados que iremos armazenar em um vetor.
typedef struct {
    char nome[100];
    char cpf[15];
    char dataNascimento[11];
    char email[100];
    char telefone[15];
    char senha[20];
    int conta_bancaria;
} Dados; // Nome da estrutura

// Cria um vetor que vai armazenar os usuários que terão todas as informações definidas pela estrutura acima. Cada indice nesse vetor terá todos os dados acima e são acessados por usuarios[index].variável. Por exemplo: usuarios[index].nome ou usuarios[index].cpf
Dados usuarios[MAX_USUARIOS];

// Variável para controlar a quantidade de usuários cadastrados
int contador_usuarios = 0;

// Função para cadastrar um novo usuário
void cadastrar_usuario () {
    // Verifica se o limite de usuários foi alcançado
    if (contador_usuarios >= MAX_USUARIOS) {
        printf("Não há mais espaço para cadastrar novos usuários\n");
        return;
    }

    // A cada novo usuário cadastrado a variável index é atualizada pelo contador. Quando um novo usuário for cadastrado, será cadastrado sempre no proxímo indice do vetor.
    int index = contador_usuarios;

    // Solicita e armazena o nome do usuário
    printf("Digite seu nome completo: ");
    fgets(usuarios[index].nome, sizeof(usuarios[index].nome), stdin);
    

    // Solicita e armazena o CPF do usuário
    printf("Digite seu CPF sem pontos ou hífen: ");
    fgets(usuarios[index].cpf, sizeof(usuarios[index].cpf), stdin);
    

    // Solicita e armazena a data de nascimento do usuário
    printf("Digite sua data de nascimento no formato DD/MM/AAAA: ");
    fgets(usuarios[index].dataNascimento, sizeof(usuarios[index].dataNascimento), stdin);
    
    getchar(); //Sem o getchar aqui essa porra buga.
    
    // Solicita e armazena o e-mail do usuário
    printf("E-mail: ");
    fgets(usuarios[index].email, sizeof(usuarios[index].email), stdin);
    

    // Solicita e armazena o número de telefone do usuário
    printf("Digite o número do telefone, incluindo o DDD, sem espaços ou caracteres especiais: ");
    fgets(usuarios[index].telefone, sizeof(usuarios[index].telefone), stdin);
    

    // Solicita e armazena a senha do usuário
    printf("Senha: ");
    fgets(usuarios[index].senha, sizeof(usuarios[index].senha), stdin);
    
    //Caso tenha dúvida sobre fgets joga no google também, a estrutura é simples de entender.
    
    // Incrementa o contador de usuários e consequentemente atualiza a variável index
    contador_usuarios++;


    // Chama a função gerar_numero e atribui um valor aleatorio para a variavel numero_da_conta
    int numero_da_conta = gerar_numero();

    //O dado "int conta bancária" definido dentro da estrutura "Dados" no inicio do código, é armazenado no vetor "usuários"
    usuarios[index].conta_bancaria = numero_da_conta;

    
    printf("Usuário Cadastrado com sucesso!\n");
}
// Não tem return 0; pq é uma função void, ela não retorna nada.
