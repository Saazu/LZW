#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#include <stdbool.h>

int stackPush (Stack **stk, int ch) {
	Stack *token = malloc(sizeof(Stack));
	token->ch = ch;
	token->next = (*stk);
	*stk = token;

	return 0;
}

int stackPop (Stack **stk) {
	if (*stk) {
		Stack *temp = *stk;
		int ch = (*stk)->ch;

		*stk = (*stk)->next;
		free(temp);
		return ch;
	}
	else {
		return 0;
	}
}

void printStack (Stack **stk) {

	Stack *token;
	for (token = *stk; token != 0; token = token->next) {
		printf("%c\n", token->ch);
	}
}

//dont need to free