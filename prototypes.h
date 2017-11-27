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
	long      filesize;
} thread_args;

typedef struct thread_args2 {
	pthread_t thread_id[NUM_THREADS];
	unsigned char*     buffer;
	unsigned char*     buffer_decryption;
	long      filesize;
} thread_args2;

void* thread_work(void* structure);
void* thread_decode(void* structure);
void getCharInBinary(unsigned char *ouput, unsigned char c);
void returnCharInBinary(int *result,unsigned char c);
void getEncodedBinary(unsigned char *output, int *binaryArray);
char getDecodedBinary(int *arrayOne, int *arrayTwo);
unsigned long file_to_string(char* filename, unsigned char **buffer);
