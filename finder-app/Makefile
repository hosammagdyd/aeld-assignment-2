# Makefile for finder-app/writer
#
# Assignment 2: File Operations and Cross Compiler
#
# Builds the "writer" C application.
#
# Usage:
#   make                                          -> native build (uses gcc)
#   make CROSS_COMPILE=aarch64-none-linux-gnu-    -> cross build (uses
#                                                      aarch64-none-linux-gnu-gcc)
#   make clean                                    -> removes writer + all .o files
#
# CROSS_COMPILE is a standard GNU Make/kernel-build convention: it's a
# *prefix* string prepended to tool names. Left empty (the default), CC
# resolves to plain "gcc". Set on the command line to the cross toolchain's
# prefix (note the trailing dash, e.g. "aarch64-none-linux-gnu-"), CC
# resolves to "aarch64-none-linux-gnu-gcc".

CROSS_COMPILE ?=
CC            := $(CROSS_COMPILE)gcc

CFLAGS        ?= -Wall -Wextra -g -std=gnu11
LDFLAGS       ?=

TARGET        := writer
SRCS          := writer.c
OBJS          := $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

# $@ = target name (writer), $^ = all prerequisites (writer.o)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# $< = first prerequisite (writer.c)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
