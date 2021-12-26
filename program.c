#include "program.h"

static size_t fileSize(const char *fileName);
static void readProgram(state_t *state, const char *fileName);

bool initProgram(state_t *state,const char *fileName) {
    state->ptr = state->arr;
    state->pc = 0;
    state->programStack = createStack(PROGRAM_STACK_SIZE);
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


void step(state_t *state) {
    char instruction = state->program[state->pc++];
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
    else if (instruction == ',') {
        *state->ptr = getchar();
    }
    else if (instruction == '[') {
        push(state->programStack,state->pc);
    }
    else if (instruction == ']') {
        if (*state->ptr)
            state->pc =  pop(state->programStack);
    }
}

void runProgram(state_t *state) {
    while (state->pc < state->programSize)
        step(state);
}

void printState(state_t *state,unsigned int arrStart,unsigned int arrEnd) {
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
    printf("PC: %u\n",state->pc);
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

void debug(state_t *state,const char *filename) {
    printf("Entering debug mode:\n");
    initProgram(state,filename);
    char instruct[256];
    do {
        printf(">");
        scanf("%s",&instruct);
        if (strcmp(instruct,"info") == 0) 
            printState(state,0,0); // TODO add option to show array
        else if (strcmp(instruct,"step") == 0) { 
            if (state->pc < state->programSize)
                step(state);
            else 
                printf("Error: program has already ended\n");
        }
        else if (strcmp(instruct,"program") == 0) {
            for (size_t i = 0; i < state->programSize; i++)
                printf("%c",state->program[i]);
            printf("\n");
        }
        else if (strcmp(instruct,"reset") == 0) 
            initProgram(state,filename);
        else if (strcmp(instruct,"help") == 0)
            printf("help"); // TODO write help instructions
    } while (strcmp(instruct,"exit") != 0);
    freeProgram(state);
}