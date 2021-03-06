/*
*   Security Project
*   Name of the Project : CODEC 2A1
*   Made by : DELMER Pierre & ABDULLAZODA Khojiakbar
*   Date : 29/11/2017
*   Class : 2A1
*   Course : Security
*   File : Functions file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <pthread.h>
#include "prototypes.h"

/*
*   Get any char transformed in binary by their value in %d.
*   Declaring an array without loop is quicker.
*   Ratio speed : 1.7
*/

void getCharInBinary(unsigned char *output, unsigned char c, void *args){
    int result[8]; // Line declaration is 1.7 quicker than a loop
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
    result[4] = 0;
    result[5] = 0;
    result[6] = 0;
    result[7] = 0;

    if(c >= 128){
        result[0] = 1;
        c -= 128;
    }
    if(c >= 64){
        result[1] = 1;
        c -= 64;
    }
    if(c >= 32){
        result[2] = 1;
        c -= 32;
    }
    if(c >= 16){
        result[3] = 1;
        c -= 16;
    }
    if(c >= 8){
        result[4] = 1;
        c -= 8;
    }
    if(c >= 4){
        result[5] = 1;
        c -= 4;
    }
    if(c >= 2){
        result[6] = 1;
        c -= 2;
    }
    if(c >= 1){
        result[7] = 1;
        c -= 1;
    }
        getEncodedBinary(output, result, args);
}

void returnCharInBinary(int *result, unsigned char c){
    // Line declaration is 1.7 quicker than a loop
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
    result[4] = 0;
    result[5] = 0;
    result[6] = 0;
    result[7] = 0;

    if(c >= 128){
        result[0] = 1;
        c -= 128;
    }
    if(c >= 64){
        result[1] = 1;
        c -= 64;
    }
    if(c >= 32){
        result[2] = 1;
        c -= 32;
    }
    if(c >= 16){
        result[3] = 1;
        c -= 16;
    }
    if(c >= 8){
        result[4] = 1;
        c -= 8;
    }
    if(c >= 4){
        result[5] = 1;
        c -= 4;
    }
    if(c >= 2){
        result[6] = 1;
        c -= 2;
    }
    if(c >= 1){
        result[7] = 1;
        c -= 1;
    }
}

unsigned long file_to_string(char* filename, unsigned char** buffer)
{
    FILE* pointer_file;
    unsigned long filesize;
    unsigned long off_end;
    int rc;
    /*
     * Open the file
     */
    pointer_file = fopen(filename, "rb");
    if (NULL == pointer_file) {
        return 0;
    }
    /*
     * Get filesize
     */
    rc = fseek(pointer_file, 0L, SEEK_END);
    if (0 != rc) {
        return 0;
    }
    if (0 > (off_end = ftell(pointer_file))) {
        return 0;
    }
    filesize = off_end;
    /*
     * Allocate a buffer to hold the whole file
     */
    *buffer = calloc(filesize, sizeof(char));
    if (NULL == *buffer) {
        return 0;
    }
    rewind(pointer_file);
    /*
     * Store file into buffer
     */
    if (filesize != fread(*buffer, 1, filesize, pointer_file)) {
        free(*buffer);
        return 0;
    }
    if (EOF == fclose(pointer_file)) {
        free(*buffer);
        return 0;
    }
    return filesize;
}


/*
*   Get any binary number transformed in HexaDecimal.
*/

void getEncodedBinary(unsigned char *output, int *binaryArray, void* structure){
    thread_args* args = structure;
    int i;
    output[0] = 0;
    output[1] = 0;
    int result;

    /* 1.4740s With small matrice after deleting 2 loop that took too many ressources. Better duplicate for high speed.
    *   Deleting 2 loops + 3 creation of variables made us win 1s on a 10Mo file. From 2.34s to 1.47s.
    * Speed ratio without loop : 1.7x quicker than with a loop.
    */

    for(i=0;i<8;i++){
            result = 0;
            result += binaryArray[0] * args->matrice[0][i];
            result += binaryArray[1] * args->matrice[1][i];
            result += binaryArray[2] * args->matrice[2][i];
            result += binaryArray[3] * args->matrice[3][i];

            if(result %2 == 1){
                switch(i){
                    case 0:
                        output[0] += 128;
                        break;
                    case 1:
                        output[0] += 64;
                        break;
                    case 2:
                        output[0] += 32;
                        break;
                    case 3:
                        output[0] += 16;
                        break;
                    case 4:
                        output[0] += 8;
                        break;
                    case 5:
                        output[0] += 4;
                        break;
                    case 6:
                        output[0] += 2;
                        break;
                    case 7:
                        output[0] += 1;
                        break;
                }
            }

            result = 0;

            result += binaryArray[4] * args->matrice[0][i];
            result += binaryArray[5] * args->matrice[1][i];
            result += binaryArray[6] * args->matrice[2][i];
            result += binaryArray[7] * args->matrice[3][i];

            if(result %2 == 1){
                switch(i){
                    case 0:
                        output[1] += 128;
                        break;
                    case 1:
                        output[1] += 64;
                        break;
                    case 2:
                        output[1] += 32;
                        break;
                    case 3:
                        output[1] += 16;
                        break;
                    case 4:
                        output[1] += 8;
                        break;
                    case 5:
                        output[1] += 4;
                        break;
                    case 6:
                        output[1] += 2;
                        break;
                    case 7:
                        output[1] += 1;
                        break;
                }
            }
        }
}

char getDecodedBinary(int *arrayOne, int *arrayTwo, int *identity){
    unsigned char output = 0;
    if(arrayOne[identity[0]] == 1){
        output +=128;
    }
    if(arrayOne[identity[1]] == 1){
        output +=64;
    }
    if(arrayOne[identity[2]] == 1){
        output +=32;
    }
    if(arrayOne[identity[3]] == 1){
        output +=16;
    }
    if(arrayTwo[identity[0]] == 1){
        output +=8;
    }
    if(arrayTwo[identity[1]] == 1){
        output +=4;
    }
    if(arrayTwo[identity[2]] == 1){
        output +=2;
    }
    if(arrayTwo[identity[3]] == 1){
        output +=1;
    }
    return output;
}

// THREAD FUNCTION TO ENCODE

void* thread_work(void* structure){
    thread_args* args = structure;
    int thread = -1;
    unsigned char output[2];
    long i;
    int j;
    for(j=0;j<NUM_THREADS;j++){
        if(pthread_equal(pthread_self(), args->thread_id[j])){
            thread = j;
        }
    }
    if (thread < 0) { exit(30); }
	for (i = thread; i < args->filesize; i += NUM_THREADS) {
        getCharInBinary(output, args->buffer[i], args);
        args->buffer_encryption[(i*2)] = output[0];
        args->buffer_encryption[(i*2)+1] = output[1];
	}
    pthread_exit(NULL);
    return 0;
}
