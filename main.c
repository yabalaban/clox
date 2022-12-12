#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char *argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 123);
    writeChunk(&chunk, OP_CONSTANT_LONG, 1);
    writeChunk(&chunk, constant, 1);
    writeChunk(&chunk, 0, 1);
    writeChunk(&chunk, 0, 1);
    constant = addConstant(&chunk, 321);
    writeChunk(&chunk, OP_CONSTANT, 2);
    writeChunk(&chunk, constant, 2);
    writeChunk(&chunk, OP_RETURN, 3);

    disassembleChunk(&chunk, "test chunk");
    
    freeChunk(&chunk);
    
    return 0;
}
