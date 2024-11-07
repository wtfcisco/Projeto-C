#include <stdio.h>
#include "cadastro.c"
int main() {
    
    // O main até agora eu usei apenas para testar se todos os dados estão sendo armazenados corretamente no vetor usuarios e sim, funcionou.

    cadastrar_usuario();

    for (int i = 0; i < contador_usuarios; i++) {
        printf("\n--- Dados do Usuário %d ---\n", i + 1);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("CPF: %s\n", usuarios[i].cpf);
        printf("Data de Nascimento: %s\n", usuarios[i].dataNascimento);
        printf("E-mail: %s\n", usuarios[i].email);
        printf("Telefone: %s\n", usuarios[i].telefone);
        printf("Senha: %s\n", usuarios[i].senha);
        printf("Conta Bancária: %d\n", usuarios[i].conta_bancaria);
    }
    return 0;
}
