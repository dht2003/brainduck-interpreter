#include <program.h>


int main(int argc, char *argv[]) {
    // TODO : add debugger support
    if (argc != 2) {
        printf("Usage: brainfuck-interpreter [Input File]");
        exit(EXIT_FAILURE);
    }
    runProgram(argv[1]);
}
