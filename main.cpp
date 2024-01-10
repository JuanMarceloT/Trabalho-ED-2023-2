#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "ABP.h"
#include "AVL.h"

void ShowStasts(TREESTATS s){
  printf("================== ESTATISTICAS %s ==================", s.tree);
  printf("\nNumero de nodos: %d", s.nodes);
  printf("\nAltura: %d", s.height);
  printf("\nRotações: %d", s.rotations);
  printf("\nComparações: %d", s.comp);
}

int main(int argc, char *argv[]) {

  if (argc != 4) {
    printf("Argumentos insuficientes");
    return 1;
  }

  FILE *SourceFIle;
  char line[50];
  SourceFIle = fopen(argv[1], "r");

  if (SourceFIle == NULL) {
    printf("File opening failed.\n");
    return 1;
  }

  AVL avl;


  while (fgets(line, sizeof(line), SourceFIle) != NULL) {
    FOODINFO food;

    char *token = strtok(line, ";");
    if (token != NULL) {
      strcpy(food.name, token);
      token = strtok(NULL, ";");
      if (token != NULL) {
        food.caloriesPer100g = std::stoi(token);
      }
      avl.insert(food);
      //printf("Food: %s and calories: %d per 100 grams\n",food.name,food.caloriesPer100g);
    }
  }
  fclose(SourceFIle);
  //avl.print();
  





  FILE *IngestionFile;

  IngestionFile = fopen(argv[2], "r");

  if (IngestionFile == NULL) {
    printf("File opening failed.\n");
    return 1;
  }

  int totalCalories = 0;

//opening the output file 

 FILE *OutputFile;
  OutputFile = fopen(argv[3], "w");

  if (OutputFile == NULL) {
    printf("Failed to create file.\n");
    return 1;
  }
  //fprintf(OutputFile, "%s", "test");
  fprintf(OutputFile, "Calorias calculadas para %s usando a tabela %s.\n", argv[2], argv[1]);



  while (fgets(line, sizeof(line), IngestionFile) != NULL) {
    struct FOODINFO food;
    int CaloriesIn = 0;

    char *token = strtok(line, ";");
    if (token != NULL) {
      strcpy(food.name, token);
      token = strtok(NULL, ";");
      if (token != NULL) {
        food.caloriesPer100g = avl.GetCalories(food.name);
        CaloriesIn = (food.caloriesPer100g) * std::stoi(token);
        CaloriesIn /= 100;
        totalCalories += CaloriesIn;
      }
      fprintf(OutputFile ,"\n%dg de %s (%d calorias por 100g) = %d calorias", std::stoi(token), food.name, food.caloriesPer100g, CaloriesIn);
      //printf("Food: %s and calories: %d per 100 grams\n",food.name,food.caloriesPer100g);
    }
  }
  fclose(IngestionFile);
  
  fprintf(OutputFile, "\n\nTotal de %d calorias consumidas no dia.", totalCalories);

    fclose(OutputFile);

    ShowStasts(avl.GetStats());


  return 0;
}