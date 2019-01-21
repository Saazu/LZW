#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"


int initArray(Element * array, int numEl, int **hash, int maxSize, int upper) {
	for (int i = 1; i < 257; i++) {
		numEl = insertArrayHash(array, hash, EMPTY, i-1, numEl, maxSize, upper);
	}
	
	return numEl;
}

int insertArrayHash(Element *array, int **hash, int prefix, int ch, int numElements, int maxSize, int upper) {
	
	//if (numElements >= upper) {
	//	return -1;
	//} 
	numElements++;
	array[numElements].prefix = prefix;
	array[numElements].ch = ch;
	
	insertHash (hash, prefix, ch, numElements, maxSize);
	return numElements; //code for string
}

// code is equivalent to numElements...
void insertHash (int **hash, int prefix, int ch, int code, int maxSize) {
	int index;
	index = REDUCE(INIT(prefix, ch), maxSize);

	if ((*hash)[index] == 0){
		(*hash)[index] = code;
	}
	else {
	
		int NSTEPS = 1;
		int count = 0;
		while (((*hash)[index] != 0) && count < maxSize) {
			
			index = REDUCE(INIT(prefix, ch) + STEP(prefix, ch, NSTEPS++), maxSize);
			count++;
			if ((*hash)[index] == 0){
				(*hash)[index] = code;
				return;
				//printf("Index: %d   Code: %d\n", index, (*hash)[index]);
			}
		}
		
	}
	
}

bool inArray(Element *array, int prefix, int ch, int code) {
	if (array[code].prefix == prefix && array[code].ch == ch)
		return true;
	return false;
}

bool codeExists(Element *array, int code) {
	if (array[code].prefix == 0 && array[code].ch == 0 ) {
		return false;
	}
	return true;
}

int searchHash (int **hash, Element *array, int prefix, int ch, int maxSize) {
	int searchIndex;
	searchIndex = REDUCE(INIT(prefix, ch), maxSize);
	int NSTEPS = 1;
	int count = 0;
	
	while ((*hash)[searchIndex] != 0 && count < maxSize){
		if (inArray(array, prefix, ch, (*hash)[searchIndex]) )
			return (*hash)[searchIndex];
		else {
			searchIndex = REDUCE(INIT(prefix, ch) + STEP(prefix, ch, NSTEPS++), maxSize);
			count++;
		}
	}
	return -1;
}

int prune (int **hash, Element *array, int maxSize, int numElements) {
	int newNumEl = 0;
	//int upper = (maxSize * 99) / 100;
	int pos;
	//int p;
	//int c;

	for (int i = 1; i <= numElements; i++) {
		if (array[i].prefix == EMPTY) {
			array[i].isPrefix = 1;
		}
		pos = array[i].prefix;
		array[pos].isPrefix = 1;
	}

	for (int i = 1; i <= numElements; i++) {
		if (array[i].isPrefix) {
			newNumEl++;

			hash[i] = newNumEl;

			array[newNumEl].prefix = hash[(array[i].prefix)];
			array[newNumEl].ch = array[i].ch;
			array[newNumEl].isPrefix = 0;
		}
	}

	memset(hash, 0, maxSize);
	for (int i = 1; i <= newNumEl; i++) {
		insertHash(hash, array[i].prefix, array[i].ch, i, maxSize);
	}

	return newNumEl;
}

void printHash (int **hash, Element *array, int numElements, int maxSize) {
	int i;
	int code;
	printf("num elements is: %d", numElements);
	for (i = 1; i <= numElements; i++) {
		code = searchHash(hash, array, array[i].prefix, array[i].ch, maxSize);
		printf("Entry: %d Prefix: %d  Char: %c Code: %d\n",i, array[i].prefix, array[i].ch, code );
	}
}