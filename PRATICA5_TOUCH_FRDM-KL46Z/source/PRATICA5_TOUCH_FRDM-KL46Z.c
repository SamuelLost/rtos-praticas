/**
 * @file    PRATICA5_TOUCH_FRDM-KL46Z.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* TODO: insert other include files here. */
#include "Touch.h"

/* TODO: insert other definitions and declarations here. */
#define LED_RED     29
#define LED_GREEN 	5

#define ON 			1
#define OFF 		0

typedef struct {
	unsigned int num;
	unsigned int status;
} LedInfo;

typedef struct {
    uint32_t ulLeftToRight;
    uint32_t ulRightToLeft;
} ScansTouch;

void vLedsInit() {
    CLOCK_EnableClock(kCLOCK_PortE);
    PORT_SetPinMux(PORTE, 29, kPORT_MuxAsGpio);

    gpio_pin_config_t led_red = {kGPIO_DigitalOutput, 0};
    GPIO_PinInit(GPIOE, 29, &led_red);
}

void drvLedsSet(int num, int status) {
	if(num == LED_GREEN) {
		if(status == ON) {
			// GPIOD->PSOR |= (1 << LED_GREEN);
            GPIO_PortSet(GPIOD, (1 << LED_GREEN));
		} else {
			// GPIOD->PCOR |= (1 << LED_GREEN);
            GPIO_PortClear(GPIOD, (1 << LED_GREEN));
		}
	} else if(num == LED_RED){
		if(status == ON) {
			// GPIOE->PSOR |= (1 << LED_RED);
            GPIO_PortSet(GPIOE, (1 << LED_RED));
		} else {
			// GPIOE->PCOR |= (1 << LED_RED);
            GPIO_PortClear(GPIOE, (1 << LED_RED));
		}
	}
}

void vTaskLed(void *pvParameters) {
    xQueueHandle queue = (xQueueHandle) pvParameters;
    LedInfo led;
    ScansTouch values;
    led.num = LED_RED;
    while(1) {
        xQueueReceive(queue, &values, portMAX_DELAY);
        if(values.ulLeftToRight >= 1000) {
            led.status = ON;
            drvLedsSet(led.num, led.status);
        } else {
            led.status = OFF;
            drvLedsSet(led.num, led.status);
        }
    }
}

void vTaskTouch(void *pvParameters) {
    xQueueHandle queue = (xQueueHandle) pvParameters;
    ScansTouch values;
    while (1){
        values.ulLeftToRight = iTouchScan_LR();
        values.ulRightToLeft = iTouchScan_RL();
//        printf("Valor de x = %d\n", values.ulLeftToRight);

         xQueueSendToBack(queue, &values, portMAX_DELAY);
        // printf("Valor de y = %d\n", values.ulRightToLeft);
        vTaskDelay(100 / portTICK_PERIOD_MS);   
    }

    
}
/*
 * @brief   Application entry point.
 */
int main(void) {

    xQueueHandle queue;
    vLedsInit();
    vTouchInit();

    queue = xQueueCreate(1, sizeof(ScansTouch));

    xTaskCreate(vTaskLed, "TaskLed", configMINIMAL_STACK_SIZE, (void *) queue, 1, NULL);

    xTaskCreate(vTaskTouch, "TaskTouch", configMINIMAL_STACK_SIZE, (void *) queue, 1, NULL);

    vTaskStartScheduler();
    return 0 ;
}
