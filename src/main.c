#include <stdio.h>
#include <stdlib.h>
#include "../include/HuffmanTree.h"
string ReadText(char*, size_t *);

int main(){
    char dir[100] = "..\\TextSamples\\sample2.txt";
    size_t * lenght = malloc(sizeof(size_t));
    string data = ReadText(dir, lenght);

    HuffmanCoding(data, *lenght);
    return 0;
}

string ReadText(char * dir, size_t * length){
    //Open file
    FILE *fptr = fopen(dir, "r");
    //Get text lenght with the position read of the pointer
    fseek(fptr, 0, SEEK_END); 
    *length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    *length+=1;

    //Allocate the space for the data
    string data = calloc(*length, sizeof(char));
    //Read and store the text
    fgets(data, *length, fptr);
    printf("\nDATA RETREAVED (%ld):\n%s\n", (*length), data);
    fclose(fptr);
    return data;
}