#include <util.h>
#include <program.h>


const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

size_t fileSize(const char *fileName) {
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
