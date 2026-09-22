#include "zephyr/sleep.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void) {
  printk("chip8-interpreter: hello from stm32-nucleof446re\n");

  while (1) {
    k_sleep(K_SECONDS(1));
    printk("still alive\n");
  }
  return 0;
}
