/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>

// Função de escrita
void criarArquivo(float ad1, float ad2, float ad3, float ad4, float ad5, int enviar, int lider, const char *dataAtual) {
  float kit = ad1 + ad2 + ad3 + ad4 + ad5;
  // Cria nome do arquivo
  char nomeArquivo[50];
  //snprintf cria a string formatada
  snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", dataAtual); 
  // Abre arquivo para escrita
  FILE *arquivo = fopen(nomeArquivo, "a");
  // Verifica se o arquivo foi aberto com sucesso
  if (arquivo) {
    if (enviar == 1) {
      // Escreve os valores dos aditivos
      fprintf(arquivo, "%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;\n", ad1, ad2, ad3, ad4, ad5, kit);
    }
    // Fecha o arquivo
    if (lider == 1) {
      fclose(arquivo);
    }
  }
}

int main() {
  // Parâmetros de exemplo
  float ad1 = 0.5;
  float ad2 = 0.7;
  float ad3 = 5.0;
  float ad4 = 0.2;
  float ad5 = 0.9;
  int enviar = 1;
  int lider = 1;
  const char *dataAtual = "2023-09-25";

  // Chamando função criarArquivo
  criarArquivo(ad1, ad2, ad3, ad4, ad5, enviar, lider, dataAtual);

  printf("Arquivo criado com sucesso!\n");

  return 0;
}