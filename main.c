#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char *argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    for (int i = 0; i < 324; ++i) {
        int constant = addConstant(&chunk, i);
        if (constant >> 8) {
            writeChunk(&chunk, OP_CONSTANT_LONG, i - i % 2);
            writeChunk(&chunk, constant & 0xff, i - i % 2);
            writeChunk(&chunk, (constant >> 8) & 0xff, i - i % 2);
            writeChunk(&chunk, (constant >> 16) & 0xff, i - i % 2);
        } else {
            writeChunk(&chunk, OP_CONSTANT, i - i % 2);
            writeChunk(&chunk, constant, i - i % 2);
        }
    }
    writeChunk(&chunk, OP_RETURN, 325);

    disassembleChunk(&chunk, "test chunk");
    
    freeChunk(&chunk);
    
    return 0;
}
