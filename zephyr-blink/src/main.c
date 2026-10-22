#include <zephyr/kernel.h>

void minha_thread(void *p1, void *p2, void *p3)
{
    while (1) {
        printk("Thread executando!\n");
        k_msleep(1000);
    }
}

K_THREAD_DEFINE(minha_thread_id, 512, minha_thread, NULL, NULL, NULL, 7, 0, 0);

int main(void)
{
    printk("Main iniciou\n");

    while (1) {
        printk("Main executando\n");
        k_msleep(2000);
    }
    return 0;
}