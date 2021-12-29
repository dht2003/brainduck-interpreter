#include <program.h>

enum tokens {
  RIGHT_TOKEN = '>'
, LEFT_TOKEN  = '<'
, INCREMENT_TOKEN = '+'
, DECREMENT_TOKEN = '-'
, OUTPUT_TOKEN = '.'
, INPUT_TOKEN = ','
, LOOP_START_TOKEN = '['
, LOOP_END_TOKEN = ']'};

static size_t fileSize(const char *fileName);
static void readProgram(state_t *state, const char *fileName);
static unsigned int findMatch(state_t state,unsigned int start);

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
    freeStack(state->programStack);
    free(state->program);
}


void step(state_t *state) {
    char instruction = state->program[state->pc++];
    if (instruction == RIGHT_TOKEN) {
        state->ptr++;
    }
    else if (instruction == LEFT_TOKEN) {
        state->ptr--;
    }
    else if (instruction == INCREMENT_TOKEN) {
        (*state->ptr)++;
    }
    else if (instruction == DECREMENT_TOKEN) {
        (*state->ptr)--;
    }
    else if (instruction == OUTPUT_TOKEN) {
        putchar(*state->ptr);
    }
    else if (instruction == INPUT_TOKEN) {
        *state->ptr = getchar();
    }
    else if (instruction == LOOP_START_TOKEN) {
        if (*state->ptr) 
            push(state->programStack,state->pc);
        else  {
            state->pc = findMatch(*state,state->pc);
            state->pc++;
        }
    }
    else if (instruction == LOOP_END_TOKEN) {
        if (*state->ptr)
            state->pc =  peek(*state->programStack);
        else  {
            pop(state->programStack);
        }
    }
}

void runProgram(state_t *state) {
    while (state->pc < state->programSize)
        step(state);
}

void printState(state_t *state,unsigned int arrStart,unsigned int arrEnd) {
    if (arrStart > ARRAY_SIZE -  1  || arrEnd > ARRAY_SIZE ) {
        fprintf(stderr, "Error: Index out of array\n");
        exit(EXIT_FAILURE);
    }
    printf("Pointer:%lx\nPointed Value:%d\n", state->ptr - state->arr,*(state->ptr));
    if (arrStart != 0 || arrEnd != 0) {
        printf("Array : ");
        for (unsigned int i = arrStart ; i < arrEnd; i++) 
            printf("%d ",state->arr[i]);
        printf("\n");
    }
    printStack(*state->programStack);
    printf("Current Instruction: %c\n",state->program[state->pc]);
}


static size_t fileSize(const char *fileName) {
    size_t numInstructions = 0;
    FILE *file = fopen(fileName,"r");
    if (file == NULL) {
       fprintf(stderr, "Can't open file : %s\n",fileName); 
       exit(EXIT_FAILURE);
    }    
    char instruction;
    do {
        instruction = (char) fgetc(file);
        if (instruction == LEFT_TOKEN || instruction == RIGHT_TOKEN 
        || instruction == INCREMENT_TOKEN || instruction == DECREMENT_TOKEN || instruction == LOOP_START_TOKEN || instruction == LOOP_END_TOKEN || instruction == OUTPUT_TOKEN || instruction == INPUT_TOKEN) {
            numInstructions++;
        }
    } while(instruction != EOF);
    fclose(file);
    return numInstructions;
}

static void readProgram(state_t *state, const char *fileName) {
    FILE *file = fopen(fileName,"r");
    if (file == NULL) {
       fprintf(stderr, "Can't open file : %s\n",fileName); 
       exit(EXIT_FAILURE);
    }
    char instruction;
    char *index = state->program;
    do {
        instruction = (char) fgetc(file);
        if (instruction == LEFT_TOKEN || instruction == RIGHT_TOKEN 
        || instruction == INCREMENT_TOKEN || instruction == DECREMENT_TOKEN || instruction == LOOP_START_TOKEN || instruction == LOOP_END_TOKEN || instruction == OUTPUT_TOKEN || instruction == INPUT_TOKEN) {
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
        scanf("%255s",&instruct);
        if (strcmp(instruct,"i") == 0) 
            printState(state,0,0); // TODO add option to show array
        else if (strcmp(instruct,"s") == 0) { 
            if (state->pc < state->programSize)
                step(state);
            else 
                printf("program has already ended\n");
        }
        else if (strcmp(instruct,"p") == 0) {
            for (size_t i = 0; i < state->programSize; i++)
                printf("%c",state->program[i]);
            printf("\n");
        }
        else if (strcmp(instruct,"r") == 0) 
            initProgram(state,filename);
        else if (strcmp(instruct,"h") == 0)
            printf("help"); // TODO write help instructions
    } while (strcmp(instruct,"e") != 0);
    freeProgram(state);
}

static unsigned int findMatch(state_t state,unsigned int start) {
    int skips = 0;
    for (unsigned int i = start; i < state.programSize; i++) {
        if (state.program[i] == LOOP_END_TOKEN) {
            if (skips == 0) return i;
            else skips--;
        }
        else if (state.program[i] == LOOP_START_TOKEN) 
            skips++;
    }
    fprintf(stderr,"Error: can't find a match\n");
    exit(EXIT_FAILURE);
}