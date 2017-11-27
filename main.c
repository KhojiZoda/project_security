
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
    unsigned char output;
    int arrayOne[8];
    int arrayTwo[8];
    FILE *encode;
    FILE *decode;
    long filesize;
    unsigned long i;
    int err;

    filename = "test.txt";
    filesize = file_to_string(filename, &buffer);
    if(!filesize){
        printf("\n\n** Filesize equal to 0 ! Error **");
        return -1;
    }
    buffer_encryption = calloc((filesize*2),sizeof(char));
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
    buffer_decryption = calloc((filesize/2), sizeof(char));
    if(NULL == buffer_decryption){
        printf("\n\n **Error on buffer encryption ! **");
        return -1;
    }
    unsigned long h = 0;
    printf("\n\nStarting decryption ...\n");
    t3 = clock();
    for(i=0;i<filesize;i=i+2){
        returnCharInBinary(arrayOne, buffer2[i]);
        returnCharInBinary(arrayTwo, buffer2[i+1]);
        output = getDecodedBinary(arrayOne, arrayTwo);
        buffer_decryption[h] = output;
        h++;
    }
    decode = fopen("test.txtd","wb");
    fwrite(buffer_decryption, sizeof(char), filesize/2, decode);
    t4 = clock();
    time2 = (float)(t4-t3)/CLOCKS_PER_SEC;           // GET TIME
    printf(" > Done %.4f seconds\n\n", time2);
    free(buffer2);
    free(buffer_decryption);

/*
    thread_args2 args2;
    args2.buffer = buffer2;
    args2.filesize = filesize;
    buffer_decryption = calloc((filesize/2), sizeof(char));
    args2.buffer_decryption = buffer_decryption;
    args2.filesize = filesize;
    printf("\n\nStarting decryption ...\n");
    t3 = clock();
    for(i = 0; i < NUM_THREADS; i++){
        err = pthread_create(&(args2.thread_id[i]), NULL, &thread_decode, (void *)&args2);
        if (err != 0) {
            printf("Can't create thread :[%s]\n", strerror(err));
        }
    }
    for(i=0; i < NUM_THREADS; i++){
        if(pthread_equal(pthread_self(), args2.thread_id[i])){
            pthread_join(args2.thread_id[i], NULL);
        }
    }
    decode = fopen("test.txtd","wb");
    fwrite(args2.buffer_decryption, sizeof(char), filesize/2, decode);
    //for(i=0;i<4;i++){
        //printf("%c",args.buffer_encryption[i]);
    //}
    t4 = clock();
    time2 = (float)(t4-t3)/CLOCKS_PER_SEC;           // GET TIME
    printf(" > Done %.4f seconds\n\n", time2);
    free(buffer2);
    free(buffer_decryption);
    */
    fclose(decode);

  /**********************************************************

  Parse given txt file to get the matrix inside the file
  and save the matrix inside a char array

  **********************************************************/
/*
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
  */
  return 0;
}
