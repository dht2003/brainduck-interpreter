#ifndef PROGRAM_H
#define PROGRAM_H

#define ARRAY_SIZE 30000
#define PROGRAM_STACK_SIZE 4096

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>


typedef struct State {
    int8_t arr[ARRAY_SIZE];
    int8_t *ptr;
    char *program;
    size_t programSize;
    unsigned int pc;
    stack *programStack;
} state_t;

enum tokens {
  RIGHT_TOKEN = '>'
, LEFT_TOKEN  = '<'
, INCREMENT_TOKEN = '+'
, DECREMENT_TOKEN = '-'
, OUTPUT_TOKEN = '.'
, INPUT_TOKEN = ','
, LOOP_START_TOKEN = '['
, LOOP_END_TOKEN = ']'};

state_t* initProgram(const char *fileName);

void freeProgram(state_t *state);

void step(state_t *state); 

void runProgram(const char *filename);

void printState(state_t *state,unsigned int arrStart,unsigned int arrEnd);

void debug(const char *filename);


#endif
