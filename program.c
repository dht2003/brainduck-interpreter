#include "program.h"

static size_t fileSize(const char *fileName);
static void readProgram(state_t *state, const char *fileName);

bool initProgram(state_t *state,const char *fileName) {
    state->ptr = state->arr;
    state->programSize = fileSize(fileName);
    state->program = malloc(state->programSize * sizeof(char));
    if (state->program == NULL) {
        printf("Could not allocate memory for program\n");
        return false;
    }
    readProgram(state,fileName);
    return true;
}

void freeProgram(state_t *state) {
    free(state->program);
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

void runProgram(state_t *state) {
    
}

void debug(state_t *state) {
    printf("Pointer:%lx\nPointed Value:%c\n", state->ptr - state->arr,*(state->ptr));
    printf("Program: ");
    for (size_t i = 0; i < state->programSize; i++)
        printf("%c",state->program[i]);
    printf("\nProgram Size: %zu\n", state->programSize);
}


static size_t fileSize(const char *fileName) {
    size_t numInstructions = 0;
    FILE *file = fopen(fileName,"r");
    char instruction;
    do {
        instruction = (char) fgetc(file);
        if (instruction == '<' || instruction == '>' 
        || instruction == '+' || instruction == '-' || instruction == '[' || instruction == ']' || instruction == '.' || instruction == ',') {
            numInstructions++;
        }
    } while(instruction != EOF);
    fclose(file);
    return numInstructions;
}

static void readProgram(state_t *state, const char *fileName) {
    FILE *file = fopen(fileName,"r");
    char instruction;
    char *index = state->program;
    do {
        instruction = (char) fgetc(file);
        if (instruction == '<' || instruction == '>' 
        || instruction == '+' || instruction == '-' || instruction == '[' || instruction == ']' || instruction == '.' || instruction == ',') {
           *index++ = instruction;
        }
    } while(instruction != EOF);
    fclose(file);
}