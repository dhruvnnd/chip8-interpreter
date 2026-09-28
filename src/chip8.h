#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

// TODO: define chip8_t struct (memory, registers, stack, PC, I, timers,
// framebuffer, keypad)

void chip8_init(void);
void chip8_load_rom(const uint8_t *data, uint16_t size);
void chip8_cycle(void);
void chip8_tick_timers(void);

#endif // CHIP8_H
