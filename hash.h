#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include "/c/cs323/Hwk4/code.h"




#define INIT(p,c) (p)                              // Initial slot
#define STEP(p,c,n) ((2*n) * (((p)<<CHAR_BIT)|(c)) + 1)  // Step to next slot
#define REDUCE(h, size) ((h) & ((size)-1))
#define UNKNOWN -1
#define EMPTY 0
#define INCR_NBITS -2

struct elt {
	int prefix : 20;
	int ch   : 9;
	bool isPrefix;
};
typedef struct elt Element;

int initArray(Element *array, int numElements, int **hash, int maxSize, int upper);

int insertArrayHash(Element *array, int **hash, int prefix, int ch, int numElements, int maxSize, int upper);

//returns true or false
bool inArray(Element *array, int prefix, int ch, int code);

//returns true or false
bool codeExists(Element *array, int code);

//int *makeHash(int size);
//returns -1 if it fails
void insertHash (int **hash, int prefix, int ch, int code, int maxSize);

//returns -1 if not found
int searchHash (int **hash, Element *array, int prefix, int ch, int maxSize);

void printHash (int **hash, Element *array, int numElements, int maxSize);

int prune (int **hash, Element *array, int maxSize, int numElements);
//void printArray(Element *array);