#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
    initVM();
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, constant, 1);
    for (int i = 0; i < 324; ++i) {
        constant = addConstant(&chunk, 1);
        if (constant >> 8) {
            writeChunk(&chunk, OP_CONSTANT_LONG, i - i % 2);
            writeChunk(&chunk, constant & 0xff, i - i % 2);
            writeChunk(&chunk, (constant >> 8) & 0xff, i - i % 2);
            writeChunk(&chunk, (constant >> 16) & 0xff, i - i % 2);
        } else {
            writeChunk(&chunk, OP_CONSTANT, 1);
            writeChunk(&chunk, constant, 1);
        }
        writeChunk(&chunk, OP_ADD, 1);
    }

    writeChunk(&chunk, OP_RETURN, 2);

    interpret(&chunk);

    freeVM();
    freeChunk(&chunk);
    
    return 0;
}
