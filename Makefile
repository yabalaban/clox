CC := clang
CFLAGS := -Wall -Wextra -std=c23 -g

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
TARGET := $(BIN_DIR)/app

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)	
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: run
run: $(TARGET)
	$(TARGET)
