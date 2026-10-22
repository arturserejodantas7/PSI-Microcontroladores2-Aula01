#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* Tempo entre cada troca de estado (acende/apaga) de cada LED */
#define LED1_INTERVALO_MS 1000
#define LED2_INTERVALO_MS 350

/* LED RGB da placa: led0 = verde, led1 = azul */
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);

int main(void)
{
    if (!gpio_is_ready_dt(&led1) || !gpio_is_ready_dt(&led2)) {
        return 0;
    }

    gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);

    int64_t proximo1 = k_uptime_get() + LED1_INTERVALO_MS;
    int64_t proximo2 = k_uptime_get() + LED2_INTERVALO_MS;

    while (1) {
        int64_t agora = k_uptime_get();

        if (agora >= proximo1) {
            gpio_pin_toggle_dt(&led1);
            proximo1 += LED1_INTERVALO_MS;
        }
        if (agora >= proximo2) {
            gpio_pin_toggle_dt(&led2);
            proximo2 += LED2_INTERVALO_MS;
        }

        /* Dorme até o próximo LED precisar trocar */
        int64_t espera = MIN(proximo1, proximo2) - k_uptime_get();
        if (espera > 0) {
            k_msleep((int32_t)espera);
        }
    }
    return 0;
}