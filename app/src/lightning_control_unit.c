//
// Created by inż. Dawid Pisarczyk on 28.12.2025.
//

#include "lightning_control_unit.h"

LOG_MODULE_REGISTER(lightning_control_unit);

lcu_can_t can = {
    .can_device = DEVICE_DT_GET(DT_ALIAS(can)),
    .can_rx_led = GPIO_DT_SPEC_GET(DT_ALIAS(can_rx_led), gpios),
};


void lcu_can_rx_callback(const struct device *dev, struct can_frame *frame, void *user_data) {
    char *receiver = (char *) user_data;
    printf("Odebrano:%s; %u\n", receiver, frame->data[0]);
}

struct can_filter lcu_filter = {
    .flags = 0U,
    .id = CAN_ID_BUTTONS_LIGHTS_MASK,
    .mask = CAN_STD_ID_MASK
};

void lcu_can_init() {
    int ret;
    ret = can_init(can.can_device, HYDROGREEN_CAN_BAUD_RATE);
    if (ret == 0) {
        LOG_INF("CAN initialized correctly");
    }
    ret = can_add_rx_filter_(can.can_device, lcu_can_rx_callback, &lcu_filter);
    if (ret >= 0) {
        LOG_INF("CAN rx filter [%d] has been added succesfully", ret);
    }
}

#define LCU_LIGHTS_LOGIC_STACK_SIZE 512
#define LCU_LIGHTS_LOGIC_PRIORITY 5

K_THREAD_STACK_DEFINE(lcu_lights_logic_stack_area, LCU_LIGHTS_LOGIC_STACK_SIZE);
struct k_thread lcu_lights_logic_thread_data;

void lcu_lights_logic_thread(void *p1, void *p2, void *p3) {

}

#define LCU_LIGHTS_DRIVER_STACK_SIZE 512
#define LCU_LIGHTS_DRIVER_PRIORITY 5

K_THREAD_STACK_DEFINE(lcu_lights_driver_stack_area, LCU_LIGHTS_DRIVER_STACK_SIZE);
struct k_thread lcu_lights_driver_thread_data;

void lcu_lights_driver_thread(void *p1, void *p2, void *p3) {

}



void lcu_tasks_init() {
    k_tid_t lcu_lights_logic_tid = k_thread_create(&lcu_lights_logic_thread_data, lcu_lights_logic_stack_area,
                                     K_THREAD_STACK_SIZEOF(lcu_lights_logic_stack_area),
                                     lcu_lights_logic_thread,
                                     NULL, NULL, NULL,
                                     LCU_LIGHTS_LOGIC_PRIORITY, 0, K_NO_WAIT);

    k_tid_t lcu_lights_driver_tid = k_thread_create(&lcu_lights_driver_thread_data, lcu_lights_driver_stack_area,
                                     K_THREAD_STACK_SIZEOF(lcu_lights_driver_stack_area),
                                     lcu_lights_driver_thread,
                                     NULL, NULL, NULL,
                                     LCU_LIGHTS_DRIVER_PRIORITY, 0, K_NO_WAIT);
}





