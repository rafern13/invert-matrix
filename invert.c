#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

void mostrarMatriz(Fraction **matriz, int tamanho);

int main()
{
  while(1) {
      printf("Bem vindo a calculadora de matriz invertida.\n");
      int tamanho;
      printf("Defina o tamanho da matriz (deve ser quadrada): ");
      scanf("%d", &tamanho);

      Fraction **matriz = (Fraction **)malloc(tamanho * sizeof(Fraction *));
      for (int i = 0; i < tamanho; i++)
        matriz[i] = (Fraction *)malloc(tamanho * 2 * sizeof(Fraction));

      printf("Ótimo. Uma matriz %dx%d foi criada. Agora, vamos definir os valores dela.\n", tamanho, tamanho);
      for (int i = 0; i < tamanho; i++)
      {
        for (int j = 0; j < tamanho; j++)
        {
          printf("Linha %d, coluna %d: ", i + 1, j + 1);
          int n;
          scanf("%d", &n);
          Fraction f = {n, 1};
          matriz[i][j] = f;
        }
      }

      // cria matriz identidade
      for (int i = 0; i < tamanho; i++)
      {
        for (int j = tamanho; j < tamanho * 2; j++)
        {
          Fraction f = {i == j - tamanho ? 1 : 0, 1};
          matriz[i][j] = f;
        }
      }

      // subtrai as equações para tirar os números à esquerda
      for (int i = 0; i < tamanho - 1; i++)
      {
        Fraction n = matriz[i][i];
        for (int j = i + 1; j < tamanho; j++)
        {
          Fraction n2 = matriz[j][i];
          Fraction m = fsimplify(fdiv(n2, n));
          for (int k = 0; k < tamanho * 2; k++)
          {
            Fraction r = fsimplify(fsub(matriz[j][k], fsimplify(fmul(matriz[i][k], m))));
            matriz[j][k] = r;
          }
        }
        printf("\n");
        mostrarMatriz(matriz, tamanho);
      }

      // subtrai as equações para tirar os números à direita
      for (int i = tamanho - 1; i > 0; i--)
      {
        Fraction n = matriz[i][i];
        for (int j = i - 1; j >= 0; j--)
        {
          Fraction n2 = matriz[j][i];
          Fraction m = fsimplify(fdiv(n2, n));
          for (int k = 0; k < tamanho * 2; k++)
          {
            matriz[j][k] = fsimplify(fsub(matriz[j][k], fsimplify(fmul(matriz[i][k], m))));
          }
        }
        printf("\n");
        mostrarMatriz(matriz, tamanho);
      }

      // normaliza a matriz
      // em outras palavras, transforma a matriz da esquerda em identidade
      for (int i = 0; i < tamanho; i++)
      {
        Fraction div = matriz[i][i];
        for (int j = 0; j < tamanho * 2; j++)
        {
          matriz[i][j] = fsimplify(fdiv(matriz[i][j], div));
          if (matriz[i][j].denominator == -0)
            matriz[i][j].denominator = 0;
        }
      }

      printf("\n");
      mostrarMatriz(matriz, tamanho);

      for (int i = 0; i < tamanho; i++)
        free(matriz[i]);
      free(matriz);
    
    char again;
    printf("\n\nDeseja operar novamente? [s/n]");
    scanf("%s", &again);
    if (again == 'n' || again == 'N') {
      return 0;
    } else {
      printf("\n");
    }
  }
}

void mostrarMatriz(Fraction **matriz, int tamanho)
{
  for (int i = 0; i < tamanho; i++)
  {
    for (int j = 0; j < tamanho * 2; j++)
    {
      Fraction f = fsimplify(matriz[i][j]);
      if (f.denominator == 1) {
        printf("%7d ", f.numerator);
      } else printf("%5d/%d ", f.numerator, f.denominator);
    }
    printf("\n");
  }
}