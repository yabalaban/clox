#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
    initVM();
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, constant, 1);

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, constant, 1);

    writeChunk(&chunk, OP_ADD, 2);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 3);
    writeChunk(&chunk, constant, 3);

    writeChunk(&chunk, OP_DIVIDE, 3);

    writeChunk(&chunk, OP_NEGATE, 4);
    writeChunk(&chunk, OP_RETURN, 4);

    interpret(&chunk);

    freeVM();
    freeChunk(&chunk);
    
    return 0;
}
