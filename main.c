#include <stdio.h>
#include "globals.h" // Estruturas e Variáveis globais
#include "functions.h" // Funções do projeto

int main() {
    int usuario, opcao = 0;

    while (opcao != 4) { //loop irá repetir enquanto a opção não for 4, sair
        printf("\n============================\n");
        printf("1 - Login\n");
        printf("2 - Cadastrar-se\n");
        printf("3 - Esqueci minha senha\n");
        printf("4 - Sair\n");
        printf("============================\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                usuario = realizar_login(); // a função realizar_login retorna o indice do usuario logado no vetor, caso usuario ou senha incorreto retorna -1
                if (usuario == -1) { 
                    printf("Falha no login, tente novamente.\n");
                } else {
                    menu_bancario(usuario);  // Recebe como parametro o usuário logado e acessa o menu desse usuario
                    usuario = -1;  // Reseta o usuário após sair do menu bancário                    
                }
                break;
            case 2:
                cadastrar_usuario();
                break;

            case 3:
                resetar_senha();
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Digite uma opção válida\n");
                break;
        }
    }
    return 0;
}
