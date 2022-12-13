#ifndef clox_line_h
#define clox_line_h

#include "common.h"

typedef struct {
    int count; 
    int capacity;
    uint32_t *lines;
    uint32_t *rle;
} LineArray;

void initLineArray(LineArray *array);
void freeLineArray(LineArray *array);
void writeLineArray(LineArray *array, uint32_t line);
uint32_t getLine(LineArray *array, uint32_t offset);

#endif 