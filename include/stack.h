#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Stack {
    unsigned int *arr;
    int capacity;
    int top;
} stack;

stack *createStack(unsigned int capacity);

void push(stack *s, unsigned int value);

unsigned int pop(stack *s);

unsigned int peek(stack s);

bool isEmpty(stack s);

bool isFull(stack s);

void freeStack(stack *s);

void printStack(stack s);

#endif 