#ifndef PROGRAM_H
#define PROGRAM_H

#define ARRAY_SIZE 30000

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct State {
    int8_t arr[ARRAY_SIZE];
    int8_t *ptr;
} state_t;

void initProgram(state_t *state);

bool step(state_t *state,char instruction); 

void debug(state_t *state);

#endif
