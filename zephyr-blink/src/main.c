/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 500

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

void main(void)
{
    int ret;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led)) {
        printk("Error: LED device %s is not ready\n", led.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    printk("LED blinking on %s pin %d\n", led.port->name, led.pin);

    while (1) {
        // Toggle do LED usando a nova API
        gpio_pin_toggle_dt(&led);
        k_msleep(SLEEP_TIME_MS);
    }
}



//codigo original zephyr-blink
// #include <stdio.h>
// #include <zephyr/kernel.h>
// #include <zephyr/drivers/gpio.h>

// /* 1000 msec = 1 sec */
// #define SLEEP_TIME_MS   500

// /* The devicetree node identifier for the "led0" alias. */
// #define LED0_NODE DT_ALIAS(led0)

// /*
//  * A build error on this line means your board is unsupported.
//  * See the sample documentation for information on how to fix this.
//  */
// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

// int main(void)
// {
// 	int ret;
// 	bool led_state = true;

// 	if (!gpio_is_ready_dt(&led)) {
// 		return 0;
// 	}

// 	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
// 	if (ret < 0) {
// 		return 0;
// 	}

// 	while (1) {
// 		ret = gpio_pin_toggle_dt(&led);
// 		if (ret < 0) {
// 			return 0;
// 		}

// 		led_state = !led_state;
// 		printf("LED state: %s\n", led_state ? "ON" : "OFF");
// 		k_msleep(SLEEP_TIME_MS);
// 	}
// 	return 0;
// }
