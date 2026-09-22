#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void) {
  printk("chip8-interpreter: hello from stm32-nucleof446re\n");

  if (!gpio_is_ready_dt(&led)) {
    printk("chip8-interpreter: gpio not ready dt\n");
    return 0;
  }

  int ret;
  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT);
  if (ret < 0) {
    printk("chip8-interpreter: gpio configure failed: %d\n", ret);
    return 0;
  }
  while (1) {
    k_sleep(K_SECONDS(1));
    gpio_pin_toggle_dt(&led);
    printk("still alive\n");
  }
  return 0;
}
