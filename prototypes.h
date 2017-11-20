#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 4

typedef struct thread_args {
	pthread_t thread_id[NUM_THREADS];
	char*     buffer;
	char*     buffer_encryption;
	unsigned long      filesize;
} thread_args;

void* thread_work(void* structure);
void* thread_decode(void* structure);
void getCharInBinary(char *ouput, char c);
void returnCharInBinary(int *result, char c);
void getEncodedBinary(char *output, int *binaryArray);
void getDecodedBinary(unsigned char *output, int *arrayOne, int *arrayTwo);
void HexaToBinary(int *input, char hexa);
int binaryToChar(int *binaryArray);
unsigned long file_to_string(char* filename, char **buffer);
