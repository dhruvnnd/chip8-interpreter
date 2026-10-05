#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

#define MEM_SIZE 1 << 12

typedef struct chip8_t {
  uint8_t mem[4096];
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

chip8_t *chip8_init(void);
void chip8_load_rom(const uint8_t *data, uint16_t size);
void chip8_cycle(void);
void chip8_tick_timers(void);

#endif // CHIP8_H
