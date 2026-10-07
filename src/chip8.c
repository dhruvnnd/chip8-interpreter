#include "chip8.h"
#include <string.h>

void chip8_init(chip8_t *chip) {
  // clear memory, display & registers
  memset(chip, 0, sizeof *chip);

  // set program counter to the start (0x200)
  chip->pc = START_ADDRESS;

  memcpy(&chip->mem[FONT_START], fontset, sizeof fontset);
}

bool chip8_load_rom(chip8_t *chip, const uint8_t *data, size_t size) {
  if (size > MEM_SIZE - START_ADDRESS) {
    return false;
  }
  memcpy(&chip->mem[START_ADDRESS], data, size);
  return true;
}

void chip8_cycle(chip8_t *chip) {
  uint16_t opcode = (chip->mem[chip->pc] << 8) | chip->mem[chip->pc + 1];
  chip->pc += 2;

  uint8_t x = (opcode >> 8) & 0xF;
  uint8_t y = (opcode >> 4) & 0xF;
  uint8_t n = opcode & 0xF;
  uint16_t nn = opcode & 0xFF;
  uint16_t nnn = opcode & 0xFFF;

  // switch instruction family
  switch (opcode & 0xF000) {
  case 0x0000: /* 00E0 CLS, 00EE RET */
    break;
  case 0x1000: /* 1nnn JP addr */
    chip->pc = nnn;
    break;
  case 0x2000: /* CALL addr */
    chip->sp++;
    chip->stack[chip->sp] = chip->pc;
    chip->pc = nnn;
    break;
  case 0x6000: /* LD Vx, byte */
    chip->V[x] = nn;
    break;
  case 0x7000: /* ADD Vx, byte */
    chip->V[x] += nn;
    break;
  case 0xA000: /* LD I, addr */
    chip->I = nnn;
    break;
  case 0xD000: /* DRW Vx, Vy, nibble */
               // draw
    break;
  default:
    (void)y;
    (void)x;
    (void)n;
    (void)nn;
    (void)nnn;
    printf("chip8: unhandled instruction family (%d)\n", (opcode & 0xF000));
    break;
  }
}

void chip8_tick_timers(chip8_t *chip) {
  if (chip->delay_timer > 0) {
    chip->delay_timer--;
  }
  if (chip->sound_timer > 0) {
    chip->sound_timer--;
  }
}
