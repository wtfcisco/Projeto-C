#include <stdio.h>
#define MAX_USUARIOS 10

typedef struct {
    char nome[100];
    char cpf[15];
    char dataNascimento[11];
    char email[100];
    char telefone[15];
    char senha[20];
} Dados;

Dados usuarios[MAX_USUARIOS];
int contador_usuarios = 0;

void cadastrar_usuario () {

    if (contador_usuarios >= MAX_USUARIOS) {
        printf("Não há mais espaço para cadastrar novos usuários\n");
        return;
    }

    int index = contador_usuarios;

    printf("Digite seu nome completo: ");
    fgets(usuarios[index].nome, sizeof(usuarios[index].nome), stdin);
    
}
