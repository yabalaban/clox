# Compiler settings
CC := cc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c2x -O2
CPPFLAGS := -MMD -MP
LDFLAGS :=
LDLIBS :=

# Project files
TARGET := clox
SRCDIR := src
OBJDIR := obj
INCDIR := include

# Find all source and header files
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)
HEADERS := $(wildcard $(INCDIR)/*.h)

# Include directories
CPPFLAGS += -I$(INCDIR)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Formatting 
style:
	@for src in $(HEADERS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@for src in $(SRCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@echo "Done"

.PHONY: style

# Clean rules
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Rebuild everything
.PHONY: rebuild
rebuild: clean all
