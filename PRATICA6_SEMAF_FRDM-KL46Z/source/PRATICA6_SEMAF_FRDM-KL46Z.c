/**
 * @file    PRATICA6_SEMAF_FRDM-KL46Z.c
 * @brief   Application entry point.
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* TODO: insert other definitions and declarations here. */
#define LED_RED 	29
#define LED_GREEN 	5
#define SW1			2
#define SW2			4
#define ON 			1
#define OFF 		0

typedef struct {
	unsigned int num;
	unsigned int status;
} LedInfo;

xSemaphoreHandle xSemphrHandle;

void vLedsInit() {
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	PORTE->PCR[LED_RED] |= (1 << 8);
	GPIOE->PDDR |= (1 << LED_RED);
}

void vSwitchsInit() {
    vSemaphoreCreateBinary(xSemphrHandle);
    //Realiza um take no semáforo para garantir que ele ficará indisponível
    //As tasks não foram criadas ainda. Então passa direto e não bloqueia.
    //O 0 se trata do tempo que  ficará bloqueado.
    xSemaphoreTake(xSemphrHandle, 0);
	
    PORTD->PCR[SW1] |= (1 << 8) | (1 << 1) | (1 << 0);
	PORTD->PCR[SW2] |= (1 << 8) | (1 << 1) | (1 << 0);

//	GPIOD->PDDR = ~(1 << SW1) | ~(1 << SW2);
}

void drvLedsSet(int num, int status) {
	if(num == LED_GREEN) {
		if(status == ON) {
			GPIOD->PSOR |= (1 << LED_GREEN);
		} else {
			GPIOD->PCOR |= (1 << LED_GREEN);
		}
	} else if(num == LED_RED){
		if(status == ON) {
			GPIOE->PSOR |= (1 << LED_RED);
		} else {
			GPIOE->PCOR |= (1 << LED_RED);
		}
	}
}

void taskLed(void *pvParameters) {
	xQueueHandle ledQueue = (xQueueHandle) pvParameters;
	LedInfo led;

	for(;;) {
		xQueueReceive(ledQueue, &led, portMAX_DELAY);
		drvLedsSet(led.num, led.status);
	}
}

void taskButton(void *pvParameters){
	xQueueHandle ledQueue = (xQueueHandle) pvParameters;
	LedInfo led;
	led.status = OFF;
	led.num = LED_RED;
	for (;;) {
		if (drvButtonsSW1Pressed() && (led.status == OFF)) {
			printf("SW 1 -- ON\n");
			led.status = ON;
			xQueueSendToBack(ledQueue, &led, portMAX_DELAY);
		}else if (drvButtonsSW2Pressed() && (led.status == ON)) {
			printf("SW 2 -- OFF\n");
			led.status = OFF;
			xQueueSendToBack(ledQueue, &led, portMAX_DELAY);
		}
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}
/*
 * @brief   Application entry point.
 */
int main(void) {
    
    xQueueHandle queue;
    vLedsInit();
    vSwitchsInit();

    if(xSemphrHandle != NULL) {
        /* create leds task */
        xTaskCreate(taskLed, "TaskLed", configMINIMAL_STACK_SIZE, (void *)queue, 1, NULL);
        /* create buttons task */
        xTaskCreate(taskButton, "TaskButton", configMINIMAL_STACK_SIZE, (void*)queue, 1, NULL);
        /* start the scheluder */
        vTaskStartScheduler();

        while(true); /* should never reach here! */

    }
    return 0 ;
}
