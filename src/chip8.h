#ifndef CHIP8_H
#define CHIP8_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MEM_SIZE (1 << 12)
#define START_ADDRESS 0x200

typedef struct chip8_t {
  uint8_t mem[MEM_SIZE];
  uint8_t V[16]; // 16 general-purpose 8-bit registers

  uint16_t I;  // 16-bit index register  for memory address
  uint16_t pc; // 16-bit program counter (points to current instruction)

  uint16_t stack[16]; // 16-level call stack for subroutines
  uint8_t sp;         // 8-bit stack pointer

  uint8_t delay_timer;
  uint8_t sound_timer;

  uint8_t keypad[16];

  uint8_t fb[64 * 32];
} chip8_t;

void chip8_init(chip8_t *chip);
bool chip8_load_rom(chip8_t *chip, const uint8_t *data, size_t size);
void chip8_cycle(chip8_t *chip);
void chip8_tick_timers(chip8_t *chip);

#endif // CHIP8_H
