#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE (!TRUE)


#define SIZE_STACK 100

typedef int EType;
typedef struct stack Stack;

struct stack {
	int top;
	EType elems[SIZE_STACK];
};

void initStack(Stack* stack); 
int isEmpty(Stack* stack);
int isFull(Stack* stack);

int push(Stack* stack, EType value); 
int pop(Stack* stack, EType* value);
void printStack(Stack* stack);

int main(int argc, char* argv[]) 
{
	EType val = 0;
	Stack stack;
	initStack(&stack);
	push(&stack, 10);
	push(&stack, 20);
	push(&stack, 30);
	pop(&stack, &val);
	
	return 0;
}

void initStack(Stack* stack)
{
	stack->top = -1;
	memset(stack->elems, 0, sizeof(EType) * SIZE_STACK);
}

int isEmpty(Stack* stack)
{
	return (stack->top == -1);
}

int isFull(Stack* stack)
{
	return (stack->top >= SIZE_STACK - 1);
}

int push(Stack* stack, EType value)
{
	if (isFull(stack))	return -1;
	
	stack->top++; 
	stack->elems[stack->top] = value; 

	return value;
}

int pop(Stack* stack, EType* value)
{	
	if (isEmpty(stack)) return -1;

	*value = stack->elems[stack->top];
	stack->top--;

	return *value;
}

void printStack(Stack* stack)
{
	int pos = stack->top;
	while (pos >= 0)
	{
		printf("%d ", stack->elems[pos--]);
	}
	printf("\n");
}

