#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(){
    FILE *filePointer;
    char line[100]; 

    filePointer = fopen("1000Shuffled.csv", "r"); 

    if (filePointer == NULL) {
        printf("File opening failed.\n");
        return 1;
    }

    fclose(filePointer);


    return 0;
}