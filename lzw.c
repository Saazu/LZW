#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "/c/cs323/Hwk4/code.h"
#include "hash.h"
#include "stack.h"
#include "/c/cs323/Hwk4/code.h"

int encode(int *args) {

	int numElements = 0;
	int maxBit = args[2];  //Max bit size for encode. 8 <= maxBit <= 20
	int maxSize = 1<<maxBit; //number of slots in string table
	int upper = (maxSize * 99) / 100;  //maximum number of slots to insert into string table
	int bitSize = CHAR_BIT+1;  //initial bit size

	Element *stringTable;  //string table of structs
	stringTable = calloc(maxSize, sizeof(Element));
	assert(stringTable);
	
	int *hash;  //hash table containing codes
	hash = calloc(maxSize, sizeof(int));
	assert(hash);

	//initialise table with ASCII chars
	numElements = initArray(stringTable, numElements, &hash, maxSize, upper);

	int c = EMPTY;
	int k = 0;
	putBits(bitSize, maxBit);

	while ((k = getchar()) != EOF) {
		if (searchHash (&hash, stringTable, c, k, maxSize) != -1) {
			c = searchHash (&hash, stringTable, c, k, maxSize);
		}
		else {
			putBits(bitSize, c);
			if (numElements <= upper) {
				numElements = insertArrayHash(stringTable, &hash, c, k, numElements, maxSize, upper);
				

				if (numElements >= (1<<bitSize) && (bitSize <= maxBit)) {
					//putBits(bitSize, (1 << bitSize) - 1);
					bitSize++;
				}
			}
			//numElements = prune(&hash, stringTable, maxSize, numElements);

			c = searchHash(&hash, stringTable, EMPTY, k, maxSize);
		}
	}

	if (c != EMPTY) {
		putBits(bitSize, c);
	}
	flushBits();

	//printHash(&hash, stringTable, numElements, maxSize);
	free(hash);
	free(stringTable); 
	return 0;
}

int decode (void) {
	int numElements = 0;
	int bitSize = CHAR_BIT+1;  //initial bit size
	int maxBit = getBits(bitSize);  //Max bit size for encode. 8 <= maxBit <= 20
	int maxSize = 1<<maxBit; //number of slots in string table
	int upper = (maxSize * 99) / 100;  //maximum number of slots to insert into string table
	
	Element *stringTable;  //string table of structs
	stringTable = calloc(maxSize, sizeof(Element));
	assert(stringTable);
	
	int *hash;  //hash table containing codes
	hash = calloc(maxSize, sizeof(int));
	assert(hash);

	//initialise table with ASCII chars
	numElements = initArray(stringTable, numElements, &hash, maxSize, upper);



	int oldC = EMPTY;
	int newC = 0;
	int c = 0;
	int k = 0;
	int finalK = 0;

	//stack for outputting chars
	Stack *stk = NULL;

	while ((newC = c = getBits(bitSize)) != EOF) {
		// if (numElements >= (1<<bitSize) && (bitSize <= maxBit)) {
		// 	bitSize++;
		// 	printf("bitSize: %d\n", bitSize);
		// }
		if (c > numElements) {
		//if (!codeExists(stringTable, c)) {
			stackPush(&stk, finalK);
			c = oldC;
		}

		while (stringTable[c].prefix != EMPTY) {
			stackPush(&stk, stringTable[c].ch);
			c = stringTable[c].prefix;
		}

		finalK = stringTable[c].ch;
		putchar(finalK);

		while (stk) {
			k = stackPop(&stk);
			putchar(k);
		}

		if (oldC != EMPTY && numElements <= upper) {
			numElements = insertArrayHash(stringTable, &hash, oldC, finalK, numElements, maxSize, upper);
		}

		oldC = newC;

		if(numElements + 1 >= (1<<bitSize) && bitSize <= maxBit){
			bitSize++;
		}
	}

	//printHash(&hash, stringTable, numElements, maxSize);

	free(hash);
	free(stringTable);
	return 0;
}

int main(int argc, char **argv) {

	//static char bin[64], bout[64];        // Small buffers for stdin/stdout
  	//setvbuf (stdin,  bin,  _IOFBF, 64);
  	//setvbuf (stdout, bout, _IOFBF, 64);

	int args[4] = {0};
	if (!strcmp((*argv+(strlen(argv[0])-6)), "decode")){
		if (argc > 1){
			fprintf(stderr, "usage: decode\n");
			exit(0);
		}
		else {
			args[0] = 1;

			decode();
		}
	}
	else{
		for (int i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-m")) {
				args[1] = 1;
				args[2] = strtol(argv[++i], NULL, 10);
			}
			if (!strcmp(argv[i], "-p")) {
				args[3] = 1;
			}
		}
		if (args[1] == 1 && args[2] == 0){
			fprintf(stderr, "encode: invalid maxBits -p\n");
			exit(0);
		}

		if (args[2] < 8 || args[2] > 20) {
			args[2] = 12;
		}
		encode(args);
	}
}