#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

struct FOODINFO {
    char name[50];
    int caloriesPer100g;
};


int main(){
    FILE *filePointer;
    char line[100]; 

    filePointer = fopen("1000Shuffled.csv", "r"); 

    if (filePointer == NULL) {
        printf("File opening failed.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), filePointer) != NULL) {
        struct FOODINFO food;

        char *token = strtok(line, ";");
        if(token != NULL) {
            strcpy(food.name, token);
            token = strtok(NULL, ";"); 
            if(token != NULL){
               food.caloriesPer100g = std::stoi(token);
            }
        printf("Food: %s and calories: %d per 100 grams\n", food.name,food.caloriesPer100g);
    }
    }
    fclose(filePointer);


    return 0;
}