/*
*   Security Project
*   Name of the Project : CODEC 2A1
*   Made by : DELMER Pierre & ABDULLAZODA Khojiakbar
*   Date : 29/11/2017
*   Class : 2A1
*   Course : Security
*   File : Header of our functions file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 4

typedef struct thread_args {
	pthread_t thread_id[NUM_THREADS];
	unsigned char*     buffer;
	unsigned char*     buffer_encryption;
	int **matrice;
	long      filesize;
} thread_args;


void* thread_work(void* structure);
void getCharInBinary(unsigned char *ouput, unsigned char c, void *args);
void returnCharInBinary(int *result,unsigned char c);
void getEncodedBinary(unsigned char *output, int *binaryArray, void *args);
char getDecodedBinary(int *arrayOne, int *arrayTwo, int *identity);
unsigned long file_to_string(char* filename, unsigned char **buffer);
