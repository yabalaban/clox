#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int, const char **) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  for (int i = 0; i < 255; i++) {
    writeConstant(&chunk, i, 123);
  }

  writeConstant(&chunk, 1.2, 123);
  writeConstant(&chunk, 3.4, 123);
  writeChunk(&chunk, OP_ADD, 123);
  writeConstant(&chunk, 5.6, 123);
  writeChunk(&chunk, OP_DIVIDE, 123);
  writeChunk(&chunk, OP_NEGATE, 123);
  writeChunk(&chunk, OP_RETURN, 123);

  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}
