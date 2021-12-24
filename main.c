#include "program.h"


int main(int argc, char *argv[]) {
    state_t state;
    initProgram(&state);
    debug(&state);
    step(&state,'>');
    debug(&state);


}
