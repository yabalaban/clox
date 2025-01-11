#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "vm.h"

VM vm;

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_LONG() (READ_BYTE() + (READ_BYTE() << 8) + (READ_BYTE() << 16))
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define READ_CONSTANT_LONG() (vm.chunk->constants.values[READ_LONG()])
#define BINARY_OP(op)                                                          \
  do {                                                                         \
    double b = pop();                                                          \
    double a = pop();                                                          \
    push(a op b);                                                              \
  } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("        ");
    for (int i = 0; i < vm.stack.count; i++) {
      printf("[ ");
      printValue(vm.stack.values[i]);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case OP_CONSTANT_LONG: {
      Value constant = READ_CONSTANT_LONG();
      push(constant);
      break;
    }
    case OP_ADD:
      BINARY_OP(+);
      break;
    case OP_SUBTRACT:
      BINARY_OP(-);
      break;
    case OP_MULTIPLY:
      BINARY_OP(*);
      break;
    case OP_DIVIDE:
      BINARY_OP(/);
      break;
    case OP_NEGATE:
      push(-pop());
      break;
    case OP_RETURN: {
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    }
    }
  }

#undef BINARY_OP
#undef READ_CONSTANT_LONG
#undef READ_CONSTANT
#undef READ_LONG
#undef READ_BYTE
}

void initVM() { initValueArray(&vm.stack); }

void freeVM() { freeValueArray(&vm.stack); }

InterpretResult interpret(char *source) {
  compile(source);
  run();
  return INTERPRET_OK;
}

void push(Value value) { writeValueArray(&vm.stack, value); }

Value pop() { return vm.stack.values[--vm.stack.count]; }
