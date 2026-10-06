#include "chip8.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  // TODO: load ROM from argv[1], run chip8_cycle() loop, print framebuffer
  printf("chip-8 emulator\n");

  chip8_t chip;

  chip8_init(&chip);

  return 0;
}
