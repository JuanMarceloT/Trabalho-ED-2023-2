#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cctype>

#include "ABP.h"
#include "AVL.h"



void ShowStasts(TREESTATS s) {
  printf("\n================== ESTATISTICAS %s ==================", s.tree);
  printf("\nNumero de nodos: %d", s.nodes);
  printf("\nAltura: %d", s.height);
  printf("\nRotações: %d", s.rotations);
  printf("\nComparações: %d", s.comp);
  printf("\n");
}

void FPrintStasts(TREESTATS s, FILE *file) {
  fprintf(file, "\n================== ESTATISTICAS %s ==================", s.tree);
  fprintf(file, "\nNumero de nodos: %d", s.nodes);
  fprintf(file, "\nAltura: %d", s.height);
  fprintf(file, "\nRotações: %d", s.rotations);
  fprintf(file, "\nComparações: %d", s.comp);
  fprintf(file, "\n");
}

void toLowerCase(char* str) {
    if (str == nullptr) {
        return;  // Handle null pointer
    }

    for (; *str != '\0'; ++str) {
        *str = std::tolower(static_cast<unsigned char>(*str));
    }
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

  AVL avl = AVL();
  ABP abp = ABP();

  while (fgets(line, sizeof(line), SourceFIle) != NULL) {
    FOODINFO food;

    char *token = strtok(line, ";");
    if (token != NULL) {
      toLowerCase(token);
      strcpy(food.name, token);
      token = strtok(NULL, ";");
      if (token != NULL) {
        food.caloriesPer100g = std::stoi(token);
      }
      avl.insert(food);
      abp.insert(food);
    }
  }
fclose(SourceFIle);
    bool error = false;
  SourceFIle = fopen(argv[1], "r");

  if (SourceFIle == NULL) {
    printf("File opening failed.\n");
    return 1;
  }

  while (fgets(line, sizeof(line), SourceFIle) != NULL) {
    FOODINFO food;

    char *token = strtok(line, ";");
    if (token != NULL) {
      toLowerCase(token);
      strcpy(food.name, token);
      pNodoA *calavl = avl.find(food.name);
      pNodoA *calabp = abp.find(food.name);
      if(strcmp(calabp->info.name,calavl->info.name) == 0){
        token = strtok(NULL, ";");
        if (token != NULL) {
            if(calabp->info.caloriesPer100g != std::stoi(token))
                error = true;
        }
      }else{
        error = true;
      }
    }
  }
fclose(SourceFIle);


if(!error)
    printf("Passou teste da insercao");
else    
    printf("nao passou no teste da insercao");





  return 0;
}