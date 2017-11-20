
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
    char *buffer;
    char *buffer2;
    char *buffer_encryption;
    char *buffer_decryption;
    FILE *encode;
    unsigned long filesize;
    unsigned long i;
    int err;
    /*
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
    */
    filename = "test.txt";
    filesize = file_to_string(filename, &buffer);
    if(!filesize){
        printf("\n\n** Filesize equal to 0 ! Error **");
        return -1;
    }
    //for(l=0;l<filesize;l++){
      //  printf("%c\n",buffer[l]);
    //}

    /*
    *   Filesize * 4 cause Hexa means 4 value on a single char encoded
    */
    buffer_encryption = malloc((filesize*2) + (int) + sizeof(char));
    if(NULL == buffer_encryption){
        printf("\n\n **Error on buffer encryption ! **");
        return -1;
    }

    thread_args args;
    args.buffer = buffer;
    args.buffer_encryption = buffer_encryption;
    args.filesize = filesize;

    t1 = clock();

    for(i = 0; i < NUM_THREADS; i++){
        /*
        getCharInBinary(output, buffer[i]);
        buffer_encryption[(i*2)] = output[0];
        buffer_encryption[(i*2)+1] = output[1];
        */
        err = pthread_create(&(args.thread_id[i]), NULL, &thread_work, (void *)&args);
        if (err != 0) {
            printf("Can't create thread :[%s]\n", strerror(err));
        }
    }


    for(i=0; i < NUM_THREADS; i++){
        pthread_join(args.thread_id[i], NULL);
    }


    encode = fopen("test.txtc","wb");
    fwrite(buffer_encryption, sizeof(char), filesize*2, encode);
    t2 = clock();
    time = (float)(t2-t1)/CLOCKS_PER_SEC;           // GET TIME
    printf("\n\n * ENCRYPTION DONE IN %.4f seconds *\n\n", time);
    free(buffer);
    free(buffer_encryption);
    /*
    *
    *           DECODE
    *
    */
    filenameDecode = "test.txtc";
    filesize = file_to_string(filename, &buffer2);
    if(!filesize){
        printf("\n\n** Filesize equal to 0 ! Error **");
        return -1;
    }
    buffer_decryption = malloc((filesize/2) + (int) + sizeof(char));
    if(NULL == buffer_encryption){
        printf("\n\n **Error on buffer encryption ! **");
        return -1;
    }

    args.buffer = buffer2;
    args.buffer_encryption = buffer_decryption;
    args.filesize = filesize;

    for(i = 0; i < NUM_THREADS; i++){
        /*
        getCharInBinary(output, buffer[i]);
        buffer_encryption[(i*2)] = output[0];
        buffer_encryption[(i*2)+1] = output[1];
        */
        err = pthread_create(&(args.thread_id[i]), NULL, &thread_decode, (void *)&args);
        if (err != 0) {
            printf("Can't create thread :[%s]\n", strerror(err));
        }
    }

    for(i=0; i < NUM_THREADS; i++){
        pthread_join(args.thread_id[i], NULL);
    }
    /*

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
    */

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
