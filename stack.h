#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*  
 * This is the interface for a stack of tokens
 *
 * This is the type of the objects entered in the stack.
 */

struct stack {
  int ch : 9;
  struct stack *next;
};
typedef struct stack Stack;


int stackPush (Stack **stk, int ch);

int stackPop (Stack **stk);

void printStack (Stack **stk);