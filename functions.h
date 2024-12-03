#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// declaração das funções do arquivo functions.c
void obter_data_hora(char *dataHora);
int gerar_numero();
void remover_quebra_linha(char *str);
void cadastrar_usuario();
int realizar_login();
void resetar_senha();
void exibir_dados(int index);
void realizar_saque(int index);
void realizar_deposito(int index);
void realizar_transferencia(int index, int conta_destino);
void menu_bancario(int usuario);

#endif // FUNCTIONS_H
