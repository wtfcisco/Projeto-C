#include <stdio.h>
#include <stdlib.h>
#include <time.h> //biblioteca para poder usarmos a função de gerar_numero
#include <string.h> //Biblioteca para usarmos função de comparar ou copiar strings
#include "globals.c" //Importa as estruturas de dados definidas em globals.c


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
void cadastrar_usuario() {
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

// Função para realizar login
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
            return i;  // Retorna o índice do usuário logado para que os dados desse usuários possam ser acessados pelas demais funções e pelo main.c
        }
    }
    printf("CPF ou senha incorretos\n");
    return -1; //retorne -1 caso algum dado esteja incorreto.
}

// Função para resetar senha
void resetar_senha() {

    char nome[100], cpf[15], dataNascimento[11], email[100], telefone[15], senha[20];
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


void realizar_saque(int index) {

    float saque;


    printf("Digite o valor que deseja sacar: ");

    if (scanf("%f", &saque) != 1 || saque <= 0) { //verifica se o valor é numérico e se é maior que 0
        printf("Valor de saque inválido. Por favor, insira um valor válido.\n");
        return;
    }

    if (saque > usuarios[index].saldo) { //verifica se o valor digitado é maior que o saldo disponivel
        printf("Saldo insuficiente. Seu saldo atual é: R$ %.2f\n", usuarios[index].saldo);
        return;
    }

    usuarios[index].saldo -= saque; //subtrai o valor saque do saldo
    usuarios[index].transacao[usuarios->contador_transacoes].valor = saque; 
    strcpy(usuarios[index].transacao[usuarios->contador_transacoes].descricao, "Saque");
    obter_data_hora(dataHora);
    strcpy(usuarios[index].transacao[usuarios->contador_transacoes].dataHora, dataHora);
    usuarios->contador_transacoes++;
    
    
    printf("Saque realizado com sucesso! Seu novo saldo é: R$ %.2f\n", usuarios[index].saldo);
}


void realizar_deposito(int index) {

    float deposito;

    printf("Digite o valor que deseja depositar: ");

    if (scanf("%f", &deposito) != 1 || deposito <= 0) { //verifica se o valor é numerico e se é maior que 0
    printf("Valor de saque inválido. Por favor, insira um valor válido.\n");
    return;
}
    usuarios[index].saldo += deposito; // soma o valor de saldo com o valor de deposito
    usuarios[index].transacao[usuarios->contador_transacoes].valor = deposito; 
    strcpy(usuarios[index].transacao[usuarios->contador_transacoes].descricao, "Deposito");
    obter_data_hora(dataHora);
    strcpy(usuarios[index].transacao[usuarios->contador_transacoes].dataHora, dataHora);
    usuarios->contador_transacoes++;


    printf("Deposito realizado com sucesso! Seu novo saldo é R$ %.2f\n", usuarios[index].saldo);
}


void realizar_transferencia(int index, int conta_destino) {
    float transferencia;
    int encontrado = -1; // Variável para armazenar o índice do usuário destinatário

    // Loop para encontrar a conta de destino
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (usuarios[i].conta_bancaria == conta_destino) { 
            encontrado = i; // Armazena o índice do destinatário
            break;
        }
    }
    
    if (encontrado == -1) {
        printf("Conta de destino não encontrada.\n");
        return;
    }

    printf("Digite o valor da transferência: ");
    if (scanf("%f", &transferencia) != 1 || transferencia <= 0) {
        printf("Valor de transferência inválido. Por favor, insira um valor válido.\n");
        return;
    }

    if (usuarios[index].saldo < transferencia) {
        printf("Saldo insuficiente para a transferência.\n");
        return;
    }

    // Realiza a transferência
    usuarios[index].saldo -= transferencia;
    usuarios[encontrado].saldo += transferencia;

    strcpy(usuarios[index].transacao[usuarios[index].contador_transacoes].nome_destinatario, usuarios[encontrado].nome);
    strcpy(usuarios[index].transacao[usuarios->contador_transacoes].descricao, "Transferencia");
    usuarios->contador_transacoes++;

    printf("Transferência realizada com sucesso!\n");
    printf("Seu novo saldo é de: R$ %.2f\n", usuarios[index].saldo);
}


void exibir_extrato(int index) {
    for (int i = 0; i < MAX_TRANSACAO; i++) {
        // Verifica se os campos principais estão preenchidos:
        if (usuarios[index].transacao[i].dataHora[0] != '\0' && 
            usuarios[index].transacao[i].descricao[0] != '\0' && 
            usuarios[index].transacao[i].valor != 0.0) {
            // Se tiver dados válidos, imprime a transação
            printf("Data: %s | ", usuarios[index].transacao[i].dataHora);
            printf("%s | ", usuarios[index].transacao[i].descricao);
            printf("Valor: %.2f\n", usuarios[index].transacao[i].valor);
        }
        if (strcmp(usuarios[index].transacao[i].descricao, "Transferencia") == 0) {
            printf(" Para (%s)", usuarios[index].transacao[i].nome_destinatario);

        }
    }   
}


void menu_bancario(int usuario) {
    int opcao = 0, conta_destino;
    while (opcao != 5) {
        printf("\n============================\n");
        printf("1 - Saque\n");
        printf("2 - Deposito\n");
        printf("3 - Transferencia\n");
        printf("4 - Exibir Dados\n");
        printf("5 - Exibir Extrato\n");
        printf("6 - Sair\n");
        printf("============================\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                realizar_saque(usuario);
                break;
            case 2:
                realizar_deposito(usuario);
                break;
            case 3:
                printf("Digite o número da conta de quem você deseja transferir: ");
                scanf("%d", &conta_destino);
                realizar_transferencia(usuario, conta_destino);
                break;
            case 4:
                exibir_dados(usuario);
                break;
            case 5:
                exibir_extrato(usuario);
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


