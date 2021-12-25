#include "program.h"

static size_t fileSize(const char *fileName);
static void readProgram(state_t *state, const char *fileName);

bool initProgram(state_t *state,const char *fileName) {
    state->ptr = state->arr;
    state->pc = 0;
    for (int i = 0; i < ARRAY_SIZE; i++)
        state->arr[i] = 0;
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
        state->pc++;
    }
    else if (instruction == '<') {
        state->ptr--;
        state->pc++;
    }
    else if (instruction == '+') {
        (*state->ptr)++;
        state->pc++;
    }
    else if (instruction == '-') {
        (*state->ptr)--;
        state->pc++;
    }
    else if (instruction == '.') {
        putchar(*state->ptr);
        state->pc++;
    }
    else if (instruction == ',') {
        *state->ptr = getchar();
        state->pc++;
    }
    else if (instruction == '[') {

    }
    else {
        return false;
    }
    return true;
}

void runProgram(state_t *state) {
   for (size_t i = 0; i < state->programSize; i++)  {
       if (state->program[i] == '[') {
           while (*state->ptr) {
               for (int j = i; state->program[j] != ']'; j++) {
                   step(state,state->program[j]);
               }
           }
           for (int j = i; state->program[j] != ']'; j++) i++;
       }
       else  {
           step(state,state->program[i]);
       }

   }
}

void debug(state_t *state,unsigned int arrStart,unsigned int arrEnd) {
    if (arrStart > ARRAY_SIZE -  1  || arrEnd > ARRAY_SIZE ) {
        printf("Error: Index out of array\n");
        exit(1);
    }
    printf("Pointer:%lx\nPointed Value:%d\n", state->ptr - state->arr,*(state->ptr));
    if (arrStart != 0 || arrEnd != 0) {
        printf("Array : ");
        for (unsigned int i = arrStart ; i < arrEnd; i++) 
            printf("%d ",state->arr[i]);
        printf("\n");
    }
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