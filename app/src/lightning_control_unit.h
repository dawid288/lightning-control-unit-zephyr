//
// Created by inż. Dawid Pisarczyk on 28.12.2025.
//

#ifndef LIGHTNING_CONTROL_UNIT_H
#define LIGHTNING_CONTROL_UNIT_H

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include "gpio.h"
#include "can.h"
#include "can_ids.h"

typedef struct {
    const struct device *can_device;
    struct gpio_dt_spec can_tx_led;
    struct gpio_dt_spec can_rx_led;
}lcu_can_t;

void lcu_lights_driver_thread(void *p1, void *p2, void *p3);
void lcu_lights_logic_thread(void *p1, void *p2, void *p3);

void lcu_can_init();






#endif //LIGHTNING_CONTROL_UNIT_H
