#include <stdio.h>
#include <stdlib.h> // Usamos a função srand para gerar número de conta
#include <time.h> //biblioteca para poder usarmos a função de gerar_numero
#include <string.h> //Biblioteca para usarmos função de comparar ou copiar strings
#include "globals.h" //Importa as estruturas de dados definidas em globals.c
#include "functions.h"  // Incluir o cabeçalho para as declarações de funções

// Função para obter a data e hora atuais
void obter_data_hora(char *dataHora) {
    time_t t;
    struct tm *tm_info;

    // Obtém o tempo atual
    time(&t);
    
    // Converte para a hora local
    tm_info = localtime(&t);

    // Formata a data e hora como "dd/mm/aaaa hh:mm:ss"
    strftime(dataHora, 20, "%d/%m/%Y %H:%M:%S", tm_info);
}

//Função para gerar número da conta
int gerar_numero() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios com a semente baseada no tempo atual
    return (rand() % 9000) + 1000;  // Garante que o número gerado tenha 4 dígitos (entre 1000 e 9999)
}

//Função para remover a quebra de linha no final de uma string
void remover_quebra_linha(char *str) {
    size_t len = strlen(str);  // Obtém o comprimento da string
    if (len > 0 && str[len - 1] == '\n') {  // Verifica se o último caractere é uma quebra de linha
        str[len - 1] = '\0';  // Substitui a quebra de linha por um caractere nulo
    }
}

//Função para cadastrar um novo usuário
void cadastrar_usuario() {

    // contador_usuarios é incrementada no fim do cadastro fazendo com que index seja atualizada. Dessa forma garantimos que o novo usuário sempre será cadastrado no próximo indice do vetor, tendo em vista que quando o ultimo usuário se cadastrou ele atualizou contador_usuarios.
    int index = contador_usuarios; 
    
    char nome[100], cpf[15], dataNascimento[11], email[100], telefone[15], senha[20]; //Variávei usadas.

    getchar(); // Limpa o buffer de entrada. Sem o getchar aqui a variável nome abaixo recebe um valor antes que possamos digitar

    // Solicita e armazena o nome do usuário. A função remover_quebra_linha remove o caractere \n que é armazenado pelo fgets no final de toda string. Sem essa função a verificação de usuário já cadastrado ou de redefinição de senha não funciona.
    printf("Digite seu nome completo: ");
    fgets(nome, sizeof(nome), stdin);
    remover_quebra_linha(nome); 

    // Solicita e armazena o CPF do usuário. Para CPF, E-mail e telefone que são dados mais sensiveis fiz uma verificação para que esses dados não sejam cadastrados mais de uma vez no vetor.
    printf("Digite seu CPF sem pontos ou hífen: ");
    fgets(cpf, sizeof(cpf), stdin);
    remover_quebra_linha(cpf);

    // Verifica se o CPF já está cadastrado. A função strcmp compara a string digitada pelo usuário com as armazenadas no vetor e caso encontre uma igual retorna 0 e cai na condição.
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

    getchar();  // Limpa o buffer de entrada pois a data de nascimento estava sendo preenchida antes que pudessemos digitar algo

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

    // Cadastra os dados digitados pelo usuário no vetor usuarios. A função strcpy copia a string da variável e joga no vetor no indice index que é sempre incrementado por contador_usuarios que está definido em globals.c Precisa usar essa função porquê em C o operador de atribuição = ou o de comparação == não funciona em string.
    strcpy(usuarios[index].nome, nome);
    strcpy(usuarios[index].cpf, cpf);
    strcpy(usuarios[index].dataNascimento, dataNascimento);
    strcpy(usuarios[index].email, email);
    strcpy(usuarios[index].telefone, telefone);
    strcpy(usuarios[index].senha, senha);

    //Gera um número aleatório de 4 digitos para a conta bancária e cadastra no vetor no indice do usuario
    int conta_bancaria = gerar_numero();

    // Esse laço verifica se o número gerado aleatoriamente já está no vetor usuários e caso já esteja, gera outro número e faz isso até que o número gerado não tenha sido cadastrado
    while (1) { 
        int numero_duplicado = 0; // Flag para verificar se existe duplicidade

        // Laço que percorre todas as contas do vetor para verificar se o número gerado já existe
        for (int i = 0; i < MAX_USUARIOS; i++) {
            if (usuarios[i].conta_bancaria == conta_bancaria) {
                numero_duplicado = 1; // Encontrou duplicado, marca a flag
                break; // Sai do laço porque encontrou um número duplicado
            }
        }

        // Se não encontrar duplicado, ou seja, numero_duplicado continua 0
        if (!numero_duplicado) {
            // Se não houver duplicidade, sai do laço while
            break;
        }

        // Caso o número seja duplicado, gera outro número de conta
        conta_bancaria = gerar_numero();
    }
    //adiciona o número no vetor
    usuarios[index].conta_bancaria = conta_bancaria;

    contador_usuarios++;  // Incrementa o contador de usuários
    printf("Usuário Cadastrado com sucesso!\n");
    printf("O número de sua nova conta bancária é %d", usuarios[index].conta_bancaria);
}

//Função para realizar login
int realizar_login() {

    char confirmarCPF[12], confirmarSenha[50]; // Variáveis usadas.
    
    // Solicita e armazena o CPF do usuário
    printf("Digite o CPF: ");
    scanf("%s", confirmarCPF);

    // Solicita e armazena a senha do usuário
    printf("Digite a senha: ");
    scanf("%s", confirmarSenha);

    //Loop que itera por todos os CPFs e Senhas cadastradas e caso encontre eles no vetor, retorna o indice do usuário no vetor. Vamos precisar desse indice nas outras funções
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].cpf, confirmarCPF) == 0 && strcmp(usuarios[i].senha, confirmarSenha) == 0) {
            printf("Login efetuado com sucesso\n");
            printf("Bem-vindo %s\n", usuarios[i].nome);
            printf("Saldo: %.2f\n", usuarios[i].saldo);
            printf("Número da conta: %d", usuarios[i].conta_bancaria);
            return i;
        }
    }
    printf("CPF ou senha incorretos\n");
    return -1; //retorne -1 caso algum dado esteja incorreto.
}

//Função para resetar senha
void resetar_senha() {

    char nome[100], cpf[15], dataNascimento[11], email[100], telefone[15], senha[20]; // Variáveis
    int conta_bancaria, index = -1; //Atribuo o valor -1 para a variável index para tratamento de erros

    printf("Confirme seus dados cadastrados para redefinir a senha\n");

    printf("Número da conta: ");
    scanf("%d", &conta_bancaria);
    getchar();

    //Esse loop itera por todas as contas do vetor e caso localize a conta digitada index recebe o indice i
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (usuarios[i].conta_bancaria == conta_bancaria) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Conta não encontrada\n"); //Se a primeira condição for falsa index vai continuar sendo -1 e aqui retornamos ao primeiro menu do main.c
        return;
    }
    
    printf("Nome Completo: ");
    fgets(nome, sizeof(nome), stdin);
    remover_quebra_linha(nome);
    if (strcmp(usuarios[index].nome, nome) != 0) { //Itera por todos os nomes do vetor e compara com o nome digitado para verificar se a string é igual
        printf("Nome incorreto\n");
        return;
    }

    printf("CPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    remover_quebra_linha(cpf);
    if (strcmp(usuarios[index].cpf, cpf) != 0) { //Itera por todos os cpf  do vetor e compara com o nome digitado para verificar se a string é igual
        printf("CPF incorreto\n");
        return;
    }

    printf("Data de Nascimento: ");
    fgets(dataNascimento, sizeof(dataNascimento), stdin);
    remover_quebra_linha(dataNascimento);
    if (strcmp(usuarios[index].dataNascimento, dataNascimento) != 0) { //Itera por todas as datas do vetor e compara com o nome digitado para verificar se a string é igual
        printf("Data de Nascimento incorreta\n");
        return;
    }
    getchar(); // Sem o getchar aqui o programa buga e atribui o valor \n ao e-mail e dá e-mail incorreto

    printf("E-mail: ");
    fgets(email, sizeof(email), stdin);
    remover_quebra_linha(email);
    if (strcmp(usuarios[index].email, email) != 0) { //Itera por todos os emails do vetor e compara com o nome digitado para verificar se a string é igual
        printf("E-mail incorreto\n");
        return;
    }

    printf("Telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    remover_quebra_linha(telefone);
    if (strcmp(usuarios[index].telefone, telefone) != 0) { //Itera por todos os telefones do vetor e compara com o nome digitado para verificar se a string é igual
        printf("Telefone incorreto\n");
        return;
    }

    printf("Digite sua nova senha: ");    //Solicita nova asenha
    fgets(senha, sizeof(senha), stdin);
    remover_quebra_linha(senha);
    strcpy(usuarios[index].senha, senha); //Copia a senha da variavel senha para o vetor
    printf("Senha alterada com sucesso\n");
}

//Exibe os dados do usuário logado
void exibir_dados(int index) {
    
    printf("\n========Dados do Usuário========\n");
    printf("Nome Completo: %s\n", usuarios[index].nome);
    printf("CPF: %s\n", usuarios[index].cpf);
    printf("Data de Nascimento: %s\n", usuarios[index].dataNascimento);
    printf("E-mail: %s\n", usuarios[index].email);
    printf("Telefone: %s\n", usuarios[index].telefone);
    printf("Conta Bancária: %d\n", usuarios[index].conta_bancaria);
    printf("Saldo: R$ %2.f\n", usuarios[index].saldo);

}

//Função para operação de saque
void realizar_saque(int index) {

    float saque;

    printf("Digite o valor que deseja sacar: R$ ");

    if (scanf("%f", &saque) != 1 || saque <= 0) { //verifica se o valor é maior que 0
        printf("Valor de saque inválido. Por favor, insira um valor válido.\n");
        return;
    }

    if (saque > usuarios[index].saldo) { //verifica se o valor digitado é maior que o saldo disponivel
        printf("Saldo insuficiente. Seu saldo atual é: R$ %.2f\n", usuarios[index].saldo);
        return;
    }

    usuarios[index].saldo -= saque; //subtrai o valor saque do saldo

    obter_data_hora(dataHora);//Armazena a data e hora na variável global dataHora

    strcpy(usuarios[index].transacao[usuarios[index].contador_transacoes].dataHora, dataHora); //Armazena a data e hora no vetor transacao

    strcpy(usuarios[index].transacao[usuarios[index].contador_transacoes].descricao, "Saque"); //Armazena o tipo de operação no vetor transacao
    
    usuarios[index].transacao[usuarios[index].contador_transacoes].valor = saque; // Armazena o valor do saque no vetor transacao
    

    usuarios[index].contador_transacoes++; //incrementa o contador de transacoes
    
    
    printf("Saque realizado com sucesso! Seu novo saldo é: R$ %.2f\n", usuarios[index].saldo);
}

//Função para operação de deposito
void realizar_deposito(int index) {

    float deposito;

    printf("Digite o valor que deseja depositar: R$ ");

    if (scanf("%f", &deposito) != 1 || deposito <= 0) { //verifica se o valor é maior que 0
    printf("Valor de saque inválido. Por favor, insira um valor válido.\n");
    return;
}
    usuarios[index].saldo += deposito; // soma o valor de saldo com o valor de deposito

    obter_data_hora(dataHora); //armazena data e hora na variavel global dataHora

    strcpy(usuarios[index].transacao[usuarios[index].contador_transacoes].dataHora, dataHora); //armazena data e hora no vetor transacao

    strcpy(usuarios[index].transacao[usuarios[index].contador_transacoes].descricao, "Deposito"); //armazena o tipo de operação "deposito" no vetor transacao

    usuarios[index].transacao[usuarios[index].contador_transacoes].valor = deposito; // armazena o valor depositado no vetor transacao
    
    usuarios[index].contador_transacoes++; //incrementa o contador de transacoes

    printf("Deposito realizado com sucesso! Seu novo saldo é R$ %.2f\n", usuarios[index].saldo);
}

//Função para operação de transferencia
void realizar_transferencia(int index, int conta_destino) {
    float transferencia;
    int encontrado = -1; // Variável para armazenar o índice do usuário destinatário. Recebe por padrão -1 para caso a conta destino não seja encontrada no vetor

    // Loop para encontrar a conta de destino
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (usuarios[i].conta_bancaria == conta_destino) { 
            encontrado = i; // Armazena o índice do destinatário
            break;
        }
    }
    
    if (encontrado == -1) { //Caso a variável seja -1 significa que a conta digitada não foi encontrada
        printf("Conta de destino não encontrada.\n");
        return;
    }

    printf("Digite o valor da transferência: R$ ");
    if (scanf("%f", &transferencia) != 1 || transferencia <= 0) { //Verifica se é um valor númerico float diferente de 0
        printf("Valor de transferência inválido. Por favor, insira um valor válido.\n");
        return;
    }

    if (usuarios[index].saldo < transferencia) { //Verifica se há saldo o suficiente
        printf("Saldo insuficiente para a transferência.\n");
        return;
    }
    usuarios[index].saldo -= transferencia; //Retira o valor da transferencia do saldo do usuario logado
    usuarios[encontrado].saldo += transferencia; //Acrescenta o valor da transferencia do usuário destino.

    obter_data_hora(dataHora); //Armazena data e hora na variável global dataHora

    strcpy(usuarios[index].transacao[usuarios[index].contador_transacoes].dataHora, dataHora); //Armazena a data e hora no vetor transacao

    strcpy(usuarios[index].transacao[usuarios[index].contador_transacoes].descricao, "Transferencia"); //Armazena o tipo de operação no vetor transacao

    usuarios[index].transacao[usuarios[index].contador_transacoes].valor = transferencia; //Armazena o valor da transferencia no vetor transacao

    strcpy(usuarios[index].transacao[usuarios[index].contador_transacoes].nome_destinatario, usuarios[encontrado].nome); //Armazena o nome do destinatario no vetor transacao

    // Esse bloco realiza as mesmas operações do bloco anterior porém para o destinatario. Assim o destinatario pode conferir no extrato a transferencia que recebeu
    strcpy(usuarios[encontrado].transacao[usuarios[encontrado].contador_transacoes].dataHora, dataHora); 

    strcpy(usuarios[encontrado].transacao[usuarios[encontrado].contador_transacoes].descricao, "Transferencia Recebida");

    usuarios[encontrado].transacao[usuarios[encontrado].contador_transacoes].valor = transferencia;

    strcpy(usuarios[encontrado].transacao[usuarios[encontrado].contador_transacoes].nome_remetente, usuarios[index].nome);

    //Incrementa o contador de transações de ambos os usuários para garantir que novas transações sejam cadastradas sempre no proximo indice do vetor
    usuarios[index].contador_transacoes++;
    usuarios[encontrado].contador_transacoes++;

    printf("Transferência realizada com sucesso!\n");
    printf("Seu novo saldo é de: R$ %.2f\n", usuarios[index].saldo);
}

// Função para exibir o extrato do usuário logado.
void exibir_extrato(int index) {
    if (usuarios[index].contador_transacoes == 0) { // Verifica se o usuário tem transações
        printf("Nenhuma transação encontrada.\n");
        return;
    }

    printf("=============================================== Extrato Bancário ===============================================\n");
    for (int i = 0; i < usuarios[index].contador_transacoes; i++) {
        // Verifica se os campos principais estão preenchidos
        if (usuarios[index].transacao[i].dataHora[0] != '\0' && 
            usuarios[index].transacao[i].descricao[0] != '\0' && 
            usuarios[index].transacao[i].valor != 0.0) {
            
            printf("Data: %s | ", usuarios[index].transacao[i].dataHora); //Printa data e hora
            printf("Operação: %s | ", usuarios[index].transacao[i].descricao); //Printa o tipo de operação saque transferencia ou deposito
            
        
            if (strcmp(usuarios[index].transacao[i].descricao, "Transferencia") == 0) { // se for transferencia printa o nome do destinatario
                printf("Valor: R$ %.2f para %s\n", usuarios[index].transacao[i].valor, usuarios[index].transacao[i].nome_destinatario);
            }else if (strcmp(usuarios[index].transacao[i].descricao, "Transferencia Recebida") == 0) { // se for transferencia recebida printa o nome do remetente
                printf("Valor: R$ %.2f | Remetente: %s\n", usuarios[index].transacao[i].valor, usuarios[index].transacao[i].nome_remetente);
            }      
            else {
                printf("Valor: R$ %.2f\n", usuarios[index].transacao[i].valor); //se for saque ou deposito printa apenas o valor sem nome nenhum
            }                      
        }
    }
    printf("================================================================================================================\n");
}

// Função para exibir o menu do usuário logado.
void menu_bancario(int usuario) {
    int opcao = 0, conta_destino;
    
    while (opcao != 6) {
        printf("\n============================\n"); //Menu de usuário
        printf("1 - Saque\n");
        printf("2 - Deposito\n");
        printf("3 - Transferencia\n");
        printf("4 - Exibir Extrato\n");
        printf("5 - Exibir Dados\n");
        printf("6 - Sair\n");
        printf("============================\n");
        scanf("%d", &opcao);

        switch (opcao) { //switch com a opcao digitada para chamar as funções do arquivo functions.c. Todas as funções recebem como parametro o indice do usuario logado
            case 1:
                realizar_saque(usuario); //chama a função de saque
                break;
            case 2:
                realizar_deposito(usuario); //chama a função de deposito
                break;
            case 3:
                printf("Digite o número da conta de quem você deseja transferir: ");
                if (scanf("%d", &conta_destino) != 1 || usuarios[usuario].conta_bancaria == conta_destino ) { //Verifica se o valor é numerico e se a conta é igual a do usuario logado
                    printf("Operação não permitida. Digite uma conta válida para transferencia.\n");
                    break;
                }
                realizar_transferencia(usuario, conta_destino); // Recebe como parametro o indice do usuario logado e a conta do destinatario
                break;
            case 4:
                exibir_extrato(usuario); //chama a função extrato
                break;
            case 5:
                exibir_dados(usuario); //chama a função exibir dados
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Digite uma opção válida\n");
                break;
        }
    }
}
