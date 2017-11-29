
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
#include <ctype.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include "prototypes.h"

int main(int argc, char** argv){
    float time, time2;
    clock_t t1, t2, t3, t4; // Declaring to calculate more precisely the time of execution.
    char *filename;
    char *filenameDecode;
    unsigned char *buffer;
    unsigned char *buffer2;
    unsigned char *buffer_encryption;
    unsigned char *buffer_decryption;
    FILE *encode;
    FILE *decode;
    long filesize;
    unsigned long i;
    int err;

    filename = "9Mo.jpeg";
    filesize = file_to_string(filename, &buffer);
    if(!filesize){
        printf("\n\n** Filesize equal to 0 ! Error **");
        return -1;
    }
    buffer_encryption = malloc((filesize*2)*sizeof(char));
    if(NULL == buffer_encryption){
        printf("\n\n **Error on buffer encryption ! **");
        return -1;
    }
    thread_args args;
    args.buffer = buffer;
    args.buffer_encryption = buffer_encryption;
    args.filesize = filesize;
    printf("\n\nStarting encryption ...\n");
    t1 = clock();

    for(i = 0; i < NUM_THREADS; i++){
        err = pthread_create(&(args.thread_id[i]), NULL, &thread_work, (void *)&args);
        if (err != 0) {
            printf("Can't create thread :[%s]\n", strerror(err));
        }
    }


    for(i=0; i < NUM_THREADS; i++){
        pthread_join(args.thread_id[i], NULL);
    }


    encode = fopen("test.txtc","wb");
    fwrite(args.buffer_encryption, sizeof(char), filesize*2, encode);
    t2 = clock();
    time = (float)(t2-t1)/CLOCKS_PER_SEC;           // GET TIME
    printf(" > Done %.4f seconds", time);
    free(buffer);
    free(buffer_encryption);
    fclose(encode);

    /*
    *
    *           DECODE
    *
    */


    filenameDecode = "test.txtc";
    filesize = file_to_string(filenameDecode, &buffer2);
    if(!filesize){
        printf("\n\n** Filesize equal to 0 ! Error **");
        return -1;
    }
    /*if(NULL == buffer_encryption){
        printf("\n\n **Error on buffer encryption ! **");
        return -1;
    }*/
    args.buffer = buffer2;
    args.buffer_encryption = calloc((filesize), sizeof(char));
    args.filesize = filesize;
    printf("\n\nStarting decryption ...\n");
    t3 = clock();
    for(i = 0; i < NUM_THREADS; i++){
        err = pthread_create(&(args.thread_id[i]), NULL, &thread_decode, (void *)&args);
        if (err != 0) {
            printf("Can't create thread :[%s]\n", strerror(err));
        }
    }
    for(i=0; i < NUM_THREADS; i++){
        if(pthread_equal(pthread_self(), args.thread_id[i])){
            pthread_join(args.thread_id[i], NULL);
        }
    }
    remove("image.txtd");
    decode = fopen("image.txtd","at");
    fwrite(args.buffer_encryption, sizeof(char), filesize, decode);
    t4 = clock();
    time2 = (float)(t4-t3)/CLOCKS_PER_SEC;           // GET TIME
    printf(" > Done %.4f seconds\n\n", time2);
    free(buffer2);
    free(args.buffer_encryption);
    fclose(decode);

  /**********************************************************

  Parse given txt file to get the matrix inside the file
  and save the matrix inside a char array

  **********************************************************/

  char character;
  FILE *matrix_file;
  int matrix[4][8];
  int int_char,i,j;
  int matrix_length=0;
  int matrix_tab=0;

  matrix_file = fopen("key.txt", "r");
  while ((character = getc(matrix_file)) != EOF){
    if (character == '1' || character == '0') {
      int_char = character-48;
      matrix[matrix_tab][matrix_length] = int_char;
      matrix_length++;
      if (matrix_length>=8) {
        matrix_length=0;
        matrix_tab++;
      }
    }
  }
  return 0;
}
