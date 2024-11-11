#include <stdio.h>
#include "functions.c"

int main() {
    
    int usuario = 0, opcao = 0;

    while (opcao != 4) {
        
        printf("1 - Login\n");
        printf("2 - Cadastrar-se\n");
        printf("3 - Esqueci minha senha\n");
        printf("4 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                usuario = realizar_login();
                break;
            case 2:
                cadastrar_usuario();
                break;
            case 3:
                resetar_senha();
                break;
            case 4:
                break;
            default:
                printf("Digite uma opção válida\n");
                break;
        }
        if (usuario != -1) {
            printf("1 - Deposito\n");
            printf("2 - Saque\n");
            printf("3 - Transferencia\n");
            printf("4 - Exibir Dados\n");
            printf("5 - Sair\n");
            scanf("%d", &opcao);
            if (opcao == 4) {
                exibir_dados(usuario);
            }
        }
    }
}
