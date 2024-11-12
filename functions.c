#include <stdio.h>
#include <stdlib.h>
#include <time.h> //biblioteca para poder usarmos a função de gerar_numero
#include <string.h> //Biblioteca para usarmos função de comparar ou copiar strings
#include "globals.c" //Importa as estruturas de dados definidas em globals.c

// Função para gerar um número aleatório de 8 dígitos
int gerar_numero() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios com a semente baseada no tempo atual
    return (rand() % 90000000) + 10000000;  // Garante que o número gerado tenha 8 dígitos
}

// Função para remover a quebra de linha no final de uma string
void remover_quebra_linha(char *str) {
    size_t len = strlen(str);  // Obtém o comprimento da string
    if (len > 0 && str[len - 1] == '\n') {  // Verifica se o último caractere é uma quebra de linha
        str[len - 1] = '\0';  // Substitui a quebra de linha por um caractere nulo
    }
}

// Função para cadastrar um novo usuário
void cadastrar_usuario () {
    if (contador_usuarios >= MAX_USUARIOS) {  // Verifica se o número máximo de usuários foi atingido
        printf("Não há mais espaço para cadastrar novos usuários\n");
        return;
    }

    int index = contador_usuarios; // contador_usuarios é incrementada no fim do cadastro fazendo com que index seja atualizada. Dessa forma garantimos que o novo usuário sempre será cadastrado no próximo indice do vetor, tendo em vista que quando o ultimo usuário se cadastrou ele atualizou contador_usuarios.
    char nome[100], cpf[15], dataNascimento[11], email[100], telefone[15], senha[20];

    
    getchar(); //Por algum motivo, sem o getchar aqui a porra inteira da função buga

    // Solicita e armazena o nome do usuário. A função remover_quebra_linha remove o caractere \n que é armazenado pelo fgets no final de toda string. Sem essa função a verificação de usuário já cadastrado não funciona.
    printf("Digite seu nome completo: ");
    fgets(nome, sizeof(nome), stdin);
    remover_quebra_linha(nome);

    

    // Solicita e armazena o CPF do usuário
    printf("Digite seu CPF sem pontos ou hífen: ");
    fgets(cpf, sizeof(cpf), stdin);
    remover_quebra_linha(cpf);

    

    // Verifica se o CPF já está cadastrado. A função strcmp compara o cpf digitado pelo usuário com todos os cpfs armazenados no vetor para verificar se esse cpf já está cadastrado. O mesmo vale para e-mail e telefone.
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            printf("CPF já cadastrado\n");
            return;
        }
    }

    // Solicita e armazena a data de nascimento do usuário
    printf("Digite sua data de nascimento no formato DD/MM/AAAA: ");
    fgets(dataNascimento, sizeof(dataNascimento), stdin);
    remover_quebra_linha(dataNascimento);

    getchar();  // Aqui também mesma coisa do anterior

    // Solicita e armazena o e-mail do usuário
    printf("E-mail: ");
    fgets(email, sizeof(email), stdin);
    remover_quebra_linha(email);

    // Verifica se o e-mail já está cadastrado
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            printf("E-mail já cadastrado\n");
            return;
        }
    }

    // Solicita e armazena o número de telefone do usuário
    printf("Digite o número do telefone, incluindo o DDD, sem espaços ou caracteres especiais: ");
    fgets(telefone, sizeof(telefone), stdin);
    remover_quebra_linha(telefone);

    // Verifica se o número de telefone já está cadastrado
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].telefone, telefone) == 0) {
            printf("Número de telefone já cadastrado\n");
            return;
        }
    }

    // Solicita e armazena a senha do usuário
    printf("Senha: ");
    fgets(senha, sizeof(senha), stdin);
    remover_quebra_linha(senha);

    // Cadastra os dados do usuário no vetor. A função strcpy copia a string da variável e joga no vetor no indice index que é sempre incrementado por contador_usuarios que está definido em globals.c Precisa usar essa função porquê em C o operador de atribuição = ou o de comparação == não funciona em string.
    strcpy(usuarios[index].nome, nome);
    strcpy(usuarios[index].cpf, cpf);
    strcpy(usuarios[index].dataNascimento, dataNascimento);
    strcpy(usuarios[index].email, email);
    strcpy(usuarios[index].telefone, telefone);
    strcpy(usuarios[index].senha, senha);

    // Usa a função gerar número e armazena na variável numero_da_conta
    int numero_da_conta = gerar_numero();
    usuarios[index].conta_bancaria = numero_da_conta;

    contador_usuarios++;  // Incrementa o contador de usuários
    printf("Usuário Cadastrado com sucesso!\n");
    printf("O número de sua nova conta bancária é %d", numero_da_conta);
}

// Função para realizar login do usuário. A função está como DadosLogin realiza_login porquê ela retorna um dado do tipo DadosLogin que contém um dado char e um float e foi definido no arquivo globals.c || Dessa forma conseguimos retornar dois valores pelo return invés de só um.
int realizar_login() {
    char confirmarCPF[12], confirmarSenha[50];
    
    // Solicita e armazena o CPF do usuário
    printf("Digite o CPF: ");
    scanf("%s", confirmarCPF);

    // Solicita e armazena a senha do usuário
    printf("Digite a senha: ");
    scanf("%s", confirmarSenha);


    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].cpf, confirmarCPF) == 0 && strcmp(usuarios[i].senha, confirmarSenha) == 0) {
            printf("Login efetuado com sucesso\n");
            printf("Bem-vindo %s\n", usuarios[i].nome);
            printf("Saldo: %.2f\n", usuarios[i].saldo);
            return i;  // Retorna o índice do usuário logado para que os dados desse usuários possam ser acessados pela função exibir_dados
        }
    }
    printf("CPF ou senha incorretos\n");
    return -1;
}


void resetar_senha() {

    char nome[100], cpf[15], dataNascimento[11], email[100], telefone[15], senha[20];
    int conta_bancaria, index = -1;

    printf("Confirme seus dados cadastrados para redefinir a senha\n");

    printf("Número da conta: ");
    scanf("%d", &conta_bancaria);
    getchar();
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (usuarios[i].conta_bancaria == conta_bancaria) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Conta não encontrada\n");
        return;
    }
    
    printf("Nome Completo: ");
    fgets(nome, sizeof(nome), stdin);
    remover_quebra_linha(nome);
    if (strcmp(usuarios[index].nome, nome) != 0) {
        printf("Nome incorreto\n");
        return;
    }

    printf("CPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    remover_quebra_linha(cpf);
    if (strcmp(usuarios[index].cpf, cpf) != 0) {
        printf("CPF incorreto\n");
        return;
    }

    printf("Data de Nascimento: ");
    fgets(dataNascimento, sizeof(dataNascimento), stdin);
    remover_quebra_linha(dataNascimento);
    if (strcmp(usuarios[index].dataNascimento, dataNascimento) != 0) {
        printf("Data de Nascimento incorreta\n");
        return;
    }
    getchar(); // Sem o getchar aqui o programa buga e atribui o valor \n ao e-mail e dá e-mail incorreto

    printf("E-mail: ");
    fgets(email, sizeof(email), stdin);
    remover_quebra_linha(email);
    if (strcmp(usuarios[index].email, email) != 0) {
        printf("E-mail incorreto\n");
        return;
    }

    printf("Telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    remover_quebra_linha(telefone);
    if (strcmp(usuarios[index].telefone, telefone) != 0) {
        printf("Telefone incorreto\n");
        return;
    }

    printf("Digite sua nova senha: ");
    fgets(senha, sizeof(senha), stdin);
    remover_quebra_linha(senha);
    strcpy(usuarios[index].senha, senha);
    printf("Senha alterada com sucesso\n");
}


void exibir_dados(int index) {

    printf("\n========Dados do Usuário========\n");
    printf("Nome Completo: %s\n", usuarios[index].nome);
    printf("CPF: %s\n", usuarios[index].cpf);
    printf("Data de Nascimento: %s\n", usuarios[index].dataNascimento);
    printf("E-mail: %s\n", usuarios[index].email);
    printf("Telefone: %s\n", usuarios[index].telefone);
    printf("Conta Bancária: %d\n", usuarios[index].conta_bancaria);
    printf("Saldo: %2.f\n", usuarios[index].saldo);

}
