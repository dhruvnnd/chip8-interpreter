CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

chip8: src/main.c src/chip8.c src/chip8.h
	$(CC) $(CFLAGS) -o $@ src/main.c src/chip8.c

clean:
	rm -f chip8
