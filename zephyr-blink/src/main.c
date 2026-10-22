#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED1_INTERVALO_MS 1000
#define LED2_INTERVALO_MS 500

#define TAMANHO_PILHA 512
#define PRIORIDADE    7

/* LED RGB da placa: led0 = verde, led1 = azul */
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);

static void pisca(const struct gpio_dt_spec *led, int intervalo_ms)
{
    if (!gpio_is_ready_dt(led)) {
        return;
    }
    gpio_pin_configure_dt(led, GPIO_OUTPUT_INACTIVE);

    while (1) {
        k_msleep(intervalo_ms);
        gpio_pin_toggle_dt(led);
    }
}

static void thread_led1(void *p1, void *p2, void *p3)
{
    pisca(&led1, LED1_INTERVALO_MS);
}

static void thread_led2(void *p1, void *p2, void *p3)
{
    pisca(&led2, LED2_INTERVALO_MS);
}

K_THREAD_DEFINE(tid_led1, TAMANHO_PILHA, thread_led1, NULL, NULL, NULL, PRIORIDADE, 0, 0);
K_THREAD_DEFINE(tid_led2, TAMANHO_PILHA, thread_led2, NULL, NULL, NULL, PRIORIDADE, 0, 0);

int main(void)
{
    return 0;
}