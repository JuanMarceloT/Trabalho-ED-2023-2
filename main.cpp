#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
//avl e e abp





struct FOODINFO {
    char name[50];
    int caloriesPer100g;
};


int main(int argc, char* argv[]){
    FILE *SourceFIle;
    char line[100]; 
    SourceFIle = fopen(argv[1], "r"); 

    if (SourceFIle == NULL) {
        printf("File opening failed.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), SourceFIle) != NULL) {
        struct FOODINFO food;

        char *token = strtok(line, ";");
        if(token != NULL) {
            strcpy(food.name, token);
            token = strtok(NULL, ";"); 
            if(token != NULL){
               food.caloriesPer100g = std::stoi(token);
            }
        //printf("Food: %s and calories: %d per 100 grams\n", food.name,food.caloriesPer100g);
    }
    }
    fclose(SourceFIle);
    


    FILE *OutputFile; 
    OutputFile = fopen(argv[2], "w"); 

    if (OutputFile == NULL) {
        printf("Failed to create file.\n");
        return 1;
    }
    fprintf(OutputFile,"%s" ,"test");


    fclose(OutputFile);
    return 0;
}