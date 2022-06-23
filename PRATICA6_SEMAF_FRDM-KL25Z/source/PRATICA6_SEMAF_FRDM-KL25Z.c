
/**
 * @file    PRATICA6_SEMAF_FRDM-KL25Z.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* TODO: insert other definitions and declarations here. */
#define LED_RED 	18 //B18
#define LED_GREEN 	19 //B19
#define LED_BLUE    1 //D1
#define SW1			0
#define SW2			4
#define ON 			1
#define OFF 		0
#define TOGGLE      2

typedef struct {
	unsigned int num;
	unsigned int status;
} LedInfo;

xSemaphoreHandle xSemphrHandle;
void PORTD_IRQHandler(void) {
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	if(PORTD->ISFR & (1 << SW1)){
        printf("Interrupcao SW1\n");

		PORTD->ISFR |= (1 << SW1);

		xSemaphoreGiveFromISR(xSemphrHandle, &xHigherPriorityTaskWoken);

		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);

	}else if(PORTD->ISFR & (1 << SW2)){
        printf("Interrupcao SW2\n");
		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

		PORTD->ISFR |= (1 << SW2);

		xSemaphoreGiveFromISR(xSemphrHandle, &xHigherPriorityTaskWoken);

		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
	}
}
void vLedsInit() {
	
	CLOCK_EnableClock(kCLOCK_PortB);

	PORTB->PCR[LED_RED] |= (1 << 8);
	GPIOB->PDDR |= (1 << LED_RED);
}

void vSwitchsInit() {
    CLOCK_EnableClock(kCLOCK_PortD);
    vSemaphoreCreateBinary(xSemphrHandle);
    //Realiza um take no semáforo para garantir que ele ficará indisponível
    //As tasks não foram criadas ainda. Então passa direto e não bloqueia.
    //O 0 se trata do tempo que  ficará bloqueado.
    xSemaphoreTake(xSemphrHandle, 0);
	
    PORTD->PCR[SW1] |= (1 << 8) | (1 << 1) | (1 << 0);
	PORTD->PCR[SW2] |= (1 << 8) | (1 << 1) | (1 << 0);

    PORTD->PCR[SW1] |= (0b1010 << 16);
    PORTD->PCR[SW2] |= (0b1010 << 16);
}

void drvLedsSet(int num, int status) {
	if(num == LED_BLUE) {
		if(status == ON) {
			GPIOD->PSOR |= (1 << LED_GREEN);
		} else if(status == OFF) {
			GPIOD->PCOR |= (1 << LED_GREEN);
		} else {
            GPIOD->PTOR |= (1 << LED_GREEN);
        }
	} else if(num == LED_RED){
		if(status == ON) {
			GPIOB->PSOR |= (1 << LED_RED);
		} else if(status == OFF){
			GPIOB->PCOR |= (1 << LED_RED);
		} else {
            GPIOB->PTOR |= (1 << LED_RED);
        }
	} else {
        if(status == ON) {
			GPIOB->PSOR |= (1 << LED_GREEN);
		} else if(status == OFF){
			GPIOB->PCOR |= (1 << LED_GREEN);
		} else {
            GPIOB->PTOR |= (1 << LED_GREEN);
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


	for (;;) {
        if(xSemaphoreTake(xSemphrHandle, portMAX_DELAY)) {
        	led.status = TOGGLE;
        	led.num = LED_RED;
//            printf("TaskButton ---\n");
		    xQueueSendToBack(ledQueue, &led, portMAX_DELAY);
        }
	}
}
/*
 * @brief   Application entry point.
 */
int main(void) {
    
    xQueueHandle queue;
    vLedsInit();
    vSwitchsInit();

    queue = xQueueCreate(1, sizeof(LedInfo));
    NVIC_EnableIRQ(PORTD_IRQn);
    if(xSemphrHandle != NULL) {
        /* create leds task */
        xTaskCreate(taskLed, "TaskLed", configMINIMAL_STACK_SIZE, (void *)queue, 1, NULL);
        /* create buttons task */
        xTaskCreate(taskButton, "TaskButton", configMINIMAL_STACK_SIZE, (void *)queue, 1, NULL);
        /* start the scheluder */
        vTaskStartScheduler();

        while(true); /* should never reach here! */

    }
    return 0 ;
}
