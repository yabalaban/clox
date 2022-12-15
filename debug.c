#include <stdio.h>

#include "debug.h"
#include "line.h"
#include "value.h"

static uint32_t constantInstruction(const char *name, Chunk *chunk, int offset);
static uint32_t constantLongInstruction(const char *name, Chunk *chunk, int offset);
static uint32_t simpleInstruction(const char *name, int offset);

void disassembleChunk(Chunk *chunk, const char *name) {
    printf("== %s ==\n", name);

    for (uint32_t offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

uint32_t disassembleInstruction(Chunk *chunk, uint32_t offset) {
    static uint32_t prev_line = -1;
    
    printf("%04d ", offset);

    uint32_t line = getLine(&chunk->lines, offset);
    if (offset > 0 && line == prev_line) {
        printf("   | ");
    } else {
        printf("%4d ", line);
        prev_line = line;
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
        case OP_NIL:
            return simpleInstruction("OP_NIL", offset);
        case OP_TRUE:
            return simpleInstruction("OP_TRUE", offset);
        case OP_FALSE:
            return simpleInstruction("OP_FALSE", offset);
        case OP_EQUAL:
            return simpleInstruction("OP_EQUAL", offset);
        case OP_GREATER:
            return simpleInstruction("OP_GREATER", offset);
        case OP_LESS:
            return simpleInstruction("OP_LESS", offset);
        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        case OP_NOT:
            return simpleInstruction("OP_NOT", offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

static uint32_t constantInstruction(const char *name, Chunk *chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

static uint32_t constantLongInstruction(const char *name, Chunk *chunk, int offset) {
    uint8_t l = chunk->code[offset + 1];
    uint8_t m = chunk->code[offset + 2];
    uint8_t h = chunk->code[offset + 3];
    uint16_t constant = (h << 16) + (m << 8) + l;
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 4;
}

static uint32_t simpleInstruction(const char *name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}
