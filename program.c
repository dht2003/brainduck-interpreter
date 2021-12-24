#include "program.h"


void initProgram(state_t *state) {
    state->ptr = state->arr;
    for (int i = 0; i < ARRAY_SIZE; i++)
        state->arr[i] = 'a';
}


bool step(state_t *state,char instruction) {
    if (instruction == '>') {
        state->ptr++;
    }
    else if (instruction == '<') {
        state->ptr--;
    }
    else if (instruction == '+') {
        (*state->ptr)++;
    }
    else if (instruction == '-') {
        (*state->ptr)--;
    }
    else if (instruction == '.') {
        putchar(*state->ptr);
    }
    else if (instruction == '.') {
        *state->ptr = getchar();
    }
    else {
        return false;
    }
    return true;
}

void debug(state_t *state) {
    printf("Pointer:%lx\nPointed Value:%c\n", state->ptr - state->arr,*(state->ptr));
}


