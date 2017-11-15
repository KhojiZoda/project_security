
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

int main(int argc, char** argv){
    float time, time2;
    clock_t t1, t2, t3, t4; // Declaring to calculate more precisely the time of execution.
    FILE *source;
    FILE *encode;
    FILE *decode;
    int l;
    char output[4];
    int input[4];
    int decodeBinary[8];
    int charFound;
    unsigned char c;
    unsigned char d;
    source = fopen("test.txt", "r");
    encode = fopen("test.txtc","w+");
    if(source == NULL){
        perror("Error in opening file");
        return -1;
    }
    if(encode == NULL){
        perror("Error in creating file");
        return -1;
    }
    t1 = clock();
    while((c = fgetc(source)) != EOF && feof(source) == 0){           // Return a different value than 0 when the file ends.
        getCharInBinary(output,(int)c);
        for(l=0;l<4;l++){
            fputc(output[l],encode);
        }
    }
    t2 = clock();
    time = (float)(t2-t1)/CLOCKS_PER_SEC;           // GET TIME
    printf("\n\n * ENCRYPTION DONE IN %.4f seconds *\n\n", time);
    fclose(source);
    fclose(encode);


    /*
    *
    *           DECODE
    *
    */

    source = fopen("test.txtc", "r");
    decode = fopen("test.txtd", "w+");
    if(source == NULL){
        perror("Error in opening file");
        return -1;
    }
    if(decode == NULL){
        perror("Error in creating file");
        return -1;
    }
    int i = 0;
    int j = 0;
    t3 = clock();
    while((d = fgetc(source)) != EOF && feof(source) == 0){           // Return a different value than 0 when the file ends.
        if(i%2 == 0){
            HexaToBinary(input, d);
            for(l=0;l<4;l++){
                decodeBinary[l+j] = input[l];
            }
            if(j == 0){
                j += 4;
            }else{
                charFound = binaryToChar(decodeBinary);
                printf("%c",charFound);
                j = 0;
            }
        }
        i++;
    }
    t4 = clock();
    time2 = (float)(t4-t3)/CLOCKS_PER_SEC;
    printf("\n\n * DECRYPTION DONE IN %.4f seconds *", time2);

  /**********************************************************

  Parse given txt file to get the matrix inside the file
  and save the matrix inside a char array

  **********************************************************/

  char character;
  FILE *matrix_file;
  char matrix[4][8];
  int matrix_length=0;
  int matrix_tab=0;
  matrix_file = fopen("key.txt", "r");
  while ((character = getc(matrix_file)) != EOF){
    if (character == '1' || character == '0') {
      matrix[matrix_tab][matrix_length]=character;
      matrix_length++;
      if (matrix_tab>4 && matrix_tab%4==0) {
        matrix_tab++;
      }
    }
  }
  return 0;
}
