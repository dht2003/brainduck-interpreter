#include "stack.h"


stack *createStack(unsigned int capacity) {
    stack *s = (stack *) malloc(sizeof(stack));
    if (s == NULL) {
        printf("Error: Could not allocate memory for stack\n");
        exit(EXIT_FAILURE);
    }
    s->capacity = capacity;
    s->top = -1;
    s->arr = (unsigned int *) malloc(sizeof(unsigned int) * capacity);
    if (s == NULL) {
        printf("Error: Could not allocate memory for stack's array\n");
        exit(EXIT_FAILURE);
    }
    return s;
}

bool isFull(stack s) {
    return s.capacity - 1 == s.top;
}

bool isEmpty(stack s) {
    return s.top == -1;
}

unsigned int pop(stack *s) {
    if (isEmpty(*s)) {
        printf("Error: can't pop because stack is Empty\n");
        exit(1);
    }
    return s->arr[s->top--];
}

unsigned int peek(stack s) {
    if (isEmpty(s)) {
       printf("Error: can't peek because stack is Empty\n");
       exit(1);
    }
    return s.arr[s.top];
}

void push(stack *s,unsigned int value) {
    if (isFull(*s)) {
        printf("Error: can't push because stack is full\n");
        exit(1);
    }
    s->arr[++(s->top)] = value;
}

void freeStack(stack *s) {
    free(s->arr);
    free(s);
}

void printStack(stack s) {
    printf("Stack: ");
    for (int i = 0; i <= s.top; i++) 
        printf("%u ", s.arr[i]);
    printf("\n");
}