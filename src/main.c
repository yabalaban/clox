#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int, const char**) {
  Chunk chunk; 
  initChunk(&chunk);


  for (int i = 0; i < 356; i++) {
    writeConstant(&chunk, i, 100 + i);
  }
  writeChunk(&chunk, OP_RETURN, 125);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0; 
}


