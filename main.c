/*
*   Name : DELMER
*   Firstname : Pierre
*   Date : 10/11/2017
*   Class : 2A1
*   Course : Security
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "prototypes.h"




int main(int argc, char** argv)
{
    float time;
    clock_t t1, t2; // Declaring to calculate more precisely the time of execution.
    t1 = clock();
    FILE *source;
    FILE *encode;
    int l;
    char output1[4];
    char output2[4];
    char output3[4];
    char output4[4];
    int code[8];
    int code2[8];
    int code3[8];
    int code4[8];
    unsigned char c;
    source = fopen("test.txt", "r");
    encode = fopen("test.txtc","w+");
    if(source == NULL){
        perror("Error in opening file");
        return -1;
    }
    while(feof(source) == 0){           // Return a different value than 0 when the file ends.
        c = fgetc(source);
        getCharInBinary(code,(int)c);
        getEncodedBinary(code,output1); // G4 1
        for(l=0;l<4;l++){
            fputc(output1[l],encode);
        }
    }
    t2 = clock();
    time = (float)(t2-t1)/CLOCKS_PER_SEC;           // GET TIME
    printf("\n\n * ENCRYPTION DONE IN %.4f seconds *", time);


  /**********************************************************

  Parse given txt file to get the matrix inside the file
  and save the matrix inside a char array

  **********************************************************/

  char character;
  FILE *matrix_file;
  char matrix[32];
  int matrix_length=0;
  matrix_file = fopen("key.txt", "r");
  while ((character = getc(matrix_file)) != EOF){
  if (character == '1' || character == '0') {
    matrix[matrix_length] = character;
    matrix_length++;
    }
  }
  return 0;
}
