#include <assert.h>
#include <stdlib.h>

#include "line.h"
#include "memory.h"

void initLineArray(LineArray *array) {
  array->capacity = 0;
  array->count = 0;
  array->lines = NULL;
}

void writeLineArray(LineArray *array, int line) {
  if (array->count && array->lines[array->count - 1].value == line) {
    array->lines[array->count - 1].len++;
  } else {
    if (array->capacity < array->count + 1) {
      int oldCapacity = array->capacity;
      array->capacity = GROW_CAPACITY(oldCapacity);
      array->lines =
          GROW_ARRAY(Line, array->lines, oldCapacity, array->capacity);
    }

    array->lines[array->count] = (Line){
        .value = line,
        .len = 1,
    };
    array->count++;
  }
}

void freeLineArray(LineArray *array) {
  FREE_ARRAY(Line, array->lines, array->count);
  initLineArray(array);
}

int getLine(LineArray *array, size_t index) {
  size_t base = 0;
  for (int i = 0; i < array->count; i++) {
    base += array->lines[i].len;
    if (base > index) {
      return array->lines[i].value;
    }
  }
  assert("rle assertion: wrong line index\n");
  return -1;
}
