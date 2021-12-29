#include <program.h>


int main(int argc, char *argv[]) {
    state_t state;
    initProgram(&state,"test.bf");
    runProgram(&state);
    printState(&state,0,50);
    freeProgram(&state);
    //debug(&state,"test.bf");
}
