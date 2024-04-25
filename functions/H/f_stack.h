#ifndef KSTACK
#define KSTACK
#include "functions.h"
// Data structure to represent a stack

// Utility function to initialize the stack
struct stack* newStack(int capacity);
 
// Utility function to return the size of the stack
int size(struct stack *pt);
 
// Utility function to check if the stack is empty or not
int IsStackEmpty(struct stack *pt) ;
// Utility function to check if the stack is full or not
int isFull(struct stack *pt) ;
// Utility function to add an element `x` to the stack
void push(struct stack *pt, int x);
 
// Utility function to return the top element of the stack
int peek(struct stack *pt);
 
// Utility function to pop a top element from the stack
int pop(struct stack *pt);
#include "f_stack.c"
#endif