#include "program.h"


int main(int argc, char *argv[]) {
    state_t state;
    initProgram(&state,"test.bf");
    runProgram(&state);
    debug(&state,0,0);


}
