#define _POSIX_C_SOURCE 199309L
#include <time.h>

#include "chip8.h"
#include <stdio.h>

#define CYCLES_PER_FRAME 10
#define FRAME_US 16666667L

static void draw(const chip8_t *chip) {
  printf("\033[H"); // move cursor to top-left
  for (int y = 0; y < SCREEN_H; y++) {
    for (int x = 0; x < SCREEN_W; x++) {
      putchar(chip->fb[y * SCREEN_W + x] ? '#' : ' ');
    }
    putchar('\n');
  }
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <rom.ch8>\n", argv[0]);
    return 1;
  }
  printf("chip-8 emulator\n");

  chip8_t chip;

  chip8_init(&chip);

  printf("loading program...\n");

  FILE *f = fopen(argv[1], "rb");
  if (!f) {
    perror("fopen");
    return 1;
  }

  uint8_t buf[MEM_SIZE - START_ADDRESS + 1];
  size_t n = fread(buf, 1, sizeof buf, f);
  fclose(f);

  if (!chip8_load_rom(&chip, buf, n)) {
    fprintf(stderr, "chip8: ROM too large\n");
    return 1;
  }

  printf("chip8: successfully loaded ROM (%s)\n", argv[1]);

  size_t i;
  int k = 0;
  for (i = 0; i < n; i++) {
    if (k == 8) {
      printf("\n");
      k = 0;
    }
    printf("0x%.2X ", buf[i]);
    k++;
  }
  printf("\n");

  printf("\033[2J"); // clear terminal once
  for (;;) {
    for (int i = 0; i < CYCLES_PER_FRAME; i++) {
      chip8_cycle(&chip);
    }
    chip8_tick_timers(&chip);
    draw(&chip);
    struct timespec ts = {0, FRAME_US};
    nanosleep(&ts, NULL);
  }
  return 0;
}
