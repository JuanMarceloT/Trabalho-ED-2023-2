#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cctype>

#include "ABP.h"
#include "AVL.h"

void ShowStasts(TREESTATS s)
{
  printf("\n================== ESTATISTICAS %s ==================", s.tree);
  printf("\nNumero de nodos: %d", s.nodes);
  printf("\nAltura: %d", s.height);
  printf("\nRotações: %d", s.rotations);
  printf("\nComparações: %d", s.comp);
  printf("\n");
}

void FPrintStasts(TREESTATS s, FILE *file)
{
  fprintf(file, "\n================== ESTATISTICAS %s ==================", s.tree);
  fprintf(file, "\nNumero de nodos: %d", s.nodes);
  fprintf(file, "\nAltura: %d", s.height);
  fprintf(file, "\nRotações: %d", s.rotations);
  fprintf(file, "\nComparações: %d", s.comp);
  fprintf(file, "\n");
}

void toLowerCase(char *str)
{
  if (str == nullptr)
  {
    return; 
  }

  for (; *str != '\0'; ++str)
  {
    *str = std::tolower(static_cast<unsigned char>(*str));
  }
}

int main(int argc, char *argv[])
{

  if (argc != 4)
  {
    printf("Argumentos insuficientes");
    return 1;
  }

  FILE *SourceFIle;
  char line[50];
  SourceFIle = fopen(argv[1], "r");

  if (SourceFIle == NULL)
  {
    printf("Erro na abertura do arquivo.\n");
    return 1;
  }

  AVL avl = AVL();
  ABP abp = ABP();

  while (fgets(line, sizeof(line), SourceFIle) != NULL)
  {
    FOODINFO food;

    char *token = strtok(line, ";");
    if (token != NULL)
    {
      toLowerCase(token);
      strcpy(food.name, token);
      token = strtok(NULL, ";");
      if (token != NULL)
      {
        food.caloriesPer100g = std::stoi(token);
      }
      avl.insert(food);
      abp.insert(food);
    }
  }
  fclose(SourceFIle);

  FILE *IngestionFile;

  IngestionFile = fopen(argv[2], "r");

  if (IngestionFile == NULL)
  {
    printf("Erro na abertura do arquivo.\n");
    return 1;
  }

  int totalCalories = 0;

  // opening the output file

  FILE *OutputFile;
  OutputFile = fopen(argv[3], "w");

  if (OutputFile == NULL)
  {
    printf("Erro na criacao do arquivo.\n");
    return 1;
  }
  fprintf(OutputFile, "Calorias calculadas para %s usando a tabela %s.\n",
          argv[2], argv[1]);

  while (fgets(line, sizeof(line), IngestionFile) != NULL)
  {
    pNodoA *food;
    int CaloriesIn = 0;

    char *token = strtok(line, ";");
    if (token != NULL)
    {
      toLowerCase(token);
      if (token != NULL)
      {
        abp.find(token);
        food = avl.find(token);
        token = strtok(NULL, ";");
        CaloriesIn = (food->info.caloriesPer100g) * std::stoi(token);
        CaloriesIn /= 100;
        totalCalories += CaloriesIn;
      }
    }
    fprintf(OutputFile, "\n%dg de %s (%d calorias por 100g) = %d calorias",
            std::stoi(token), food->info.name, food->info.caloriesPer100g, CaloriesIn);
  }

  fclose(IngestionFile);

  fprintf(OutputFile, "\n\nTotal de %d calorias consumidas no dia.\n",
          totalCalories);

  FPrintStasts(abp.GetStats(), OutputFile);
  FPrintStasts(avl.GetStats(), OutputFile);

  fclose(OutputFile);

  // ShowStasts(abp.GetStats());
  // ShowStasts(avl.GetStats());

  return 0;
}