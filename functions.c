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

    getchar();  // Corrige problemas com o buffer do teclado após o uso de fgets

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
}

// Função para realizar login do usuário. A função está como DadosLogin realiza_login porquê ela retorna um dado do tipo DadosLogin que contém um dado char e um float e foi definido no arquivo globals.c || Dessa forma conseguimos retornar dois valores pelo return invés de só um.
DadosLogin realizar_login() {
    char confirmarCPF[12], confirmarSenha[50];

    // Solicita e armazena o CPF do usuário
    printf("Digite o CPF: ");
    scanf("%s", confirmarCPF);

    // Solicita e armazena a senha do usuário
    printf("Digite a senha: ");
    scanf("%s", confirmarSenha);

    DadosLogin nomeSaldo; // Declaração de uma variável do tipo DadosLogin. Essa variável irá armazenar nome e saldo

    // A função strcmp compara o cpf e senha armazenados no vetor com o cpf e senha armazenados nas variáveis confirmarCPF e confirmarSenha e retorna o valor 0 caso ambos sejam iguais. Se os dados digitados pelo usuário estiverem corretos a variável nomeSaldo recebe o nome e o saldo do usuário logado e a função retorna a variável nomeSaldo que vamos usar para fazer as operações bancárias. Lembrando que o nome é do tipo string então usamos a função strcpy para copiar o NOME do usuário cadastrado para a variável nomeSaldo pois em C o operador de atribuição = não funciona em string. Já o saldo é do tipo float então não precisamos usar strcpy.
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].cpf, confirmarCPF) == 0 && strcmp(usuarios[i].senha, confirmarSenha) == 0) {
            strcpy(nomeSaldo.nome, usuarios[i].nome);
            nomeSaldo.saldo = usuarios[i].saldo;
            printf("Login Efetuado Com Sucesso\nBem Vindo %s.", nomeSaldo.nome);
            return nomeSaldo;  // Retorna os dados do usuário logado. O return interrompe o código então o bloco abaixo só será executado caso o usuário digite cpf ou senha incorretos
        }
    }

    // Caso o login falhe
    printf("CPF ou Senha Incorretos.");
    DadosLogin erro = {"", 0.0};  // Retorna dados vazios em caso de erro
    return erro;
}
