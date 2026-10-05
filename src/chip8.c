#include "chip8.h"
#include <stdlib.h>
#include <string.h>

chip8_t *chip8_init(void) {
  chip8_t *chip = malloc(sizeof(chip8_t));
  // set program counter to the start (0x200)
  chip->pc = 0x200;
  chip->I = 0;
  chip->sp = 0;

  // clear memory, display & registers
  memset(chip->mem, 0, sizeof(chip->mem));
  memset(chip->fb, 0, sizeof(chip->fb));
  memset(chip->V, 0, sizeof(chip->V));
  memset(chip->stack, 0, sizeof(chip->stack));

  return chip;
}

void chip8_load_rom(const uint8_t *data, uint16_t size) {
  // TODO
  (void)data;
  (void)size;
}

void chip8_cycle(void) {
  // TODO: fetch, decode, execute
}

void chip8_tick_timers(void) {
  // TODO: decrement delay/sound timers at 60Hz
}
