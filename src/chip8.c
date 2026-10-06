#include "chip8.h"
#include <string.h>

void chip8_init(chip8_t *chip) {
  // clear memory, display & registers
  memset(chip, 0, sizeof *chip);

  // set program counter to the start (0x200)
  chip->pc = START_ADDRESS;
}

bool chip8_load_rom(chip8_t *chip, const uint8_t *data, size_t size) {
  if (size > MEM_SIZE - START_ADDRESS) {
    return false;
  }
  memcpy(&chip->mem[START_ADDRESS], data, size);
  return true;
}

void chip8_cycle(chip8_t *chip) {
  // TODO: fetch, decode, execute
  (void)chip;
}

void chip8_tick_timers(chip8_t *chip) {
  // TODO: decrement delay/sound timers at 60Hz
  (void)chip;
}
