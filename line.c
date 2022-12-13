#include <stdlib.h>
#include <stdio.h>

#include "line.h"
#include "memory.h"

void initLineArray(LineArray *array) {
    array->capacity = 0;
    array->count = 0;
    array->lines = NULL;
    array->rle = NULL;
}

void freeLineArray(LineArray *array) {
    FREE_ARRAY(uint32_t, array->lines, array->capacity);
    FREE_ARRAY(uint32_t, array->rle, array->capacity);
    initLineArray(array);
}

void writeLineArray(LineArray *array, uint32_t line) {
    if (array->count > 0 && array->lines[array->count - 1] == line) {
        array->rle[array->count - 1]++;
        return;
    }

    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->lines = GROW_ARRAY(uint32_t, array->lines, oldCapacity, array->capacity);
        array->rle = GROW_ARRAY(uint32_t, array->rle, oldCapacity, array->capacity);
    }

    array->lines[array->count] = line;
    array->rle[array->count] = 1;
    array->count++;
}

uint32_t getLine(LineArray *array, uint32_t offset) {
    uint32_t lower_bound = 0; 
    for (int idx = 0; idx < array->count; ++idx) {
       if (offset + 1 <= lower_bound + array->rle[idx]) {
            return array->lines[idx];
        } else {
            lower_bound += array->rle[idx];
        }
    }
    return array->lines[array->count - 1];
}
