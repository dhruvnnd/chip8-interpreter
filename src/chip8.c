#include "chip8.h"
#include <string.h>

static void __draw(chip8_t *chip, uint8_t x, uint8_t y, uint8_t n) {
  // starting position wraps around screen
  uint8_t px = chip->V[x] % SCREEN_W;
  uint8_t py = chip->V[y] % SCREEN_H;

  chip->V[0xF] = 0;

  for (uint8_t row = 0; row < n; row++) {
    if (py + row >= SCREEN_H) {
      break; // clip at bottom edge
    }

    uint8_t sprite = chip->mem[chip->I + row];

    for (uint8_t col = 0; col < 8; col++) {
      if (px + col >= SCREEN_W) {
        break; // clip at right edge
      }

      if (sprite & (0x80 >> col)) {
        uint8_t *pixel = &chip->fb[(py + row) * SCREEN_W + (px + col)];
        if (*pixel) {
          chip->V[0xF] = 1; // a lit pixel is being turned off;collision
        }
        *pixel ^= 1;
      }
    }
  }
}

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
    if (opcode == 0x00E0)
      memset(chip->fb, 0, sizeof chip->fb);
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
    __draw(chip, x, y, n);
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
