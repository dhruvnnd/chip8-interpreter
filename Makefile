CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g
DEBUG_FLAGS = -g -O0 -DDEBUG

chip8: src/main.c src/chip8.c src/chip8.h
	$(CC) $(CFLAGS) -o $@ src/main.c src/chip8.c

debug: CFLAGS += $(DEBUG_FLAGS)
debug: chip8 

clean:
	rm -f chip8
