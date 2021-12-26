#ifndef PROGRAM_H
#define PROGRAM_H

#define ARRAY_SIZE 30000
#define PROGRAM_STACK_SIZE 4096

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


typedef struct State {
    int8_t arr[ARRAY_SIZE];
    int8_t *ptr;
    char *program;
    size_t programSize;
    unsigned int pc;
    stack *programStack;
} state_t;

bool initProgram(state_t *state,const char *fileName);

void freeProgram(state_t *state);

void step(state_t *state); 

void runProgram(state_t *state);

void printState(state_t *state,unsigned int arrStart,unsigned int arrEnd);

void debug(state_t *state,const char *filename);


#endif
