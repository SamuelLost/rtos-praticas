///*
// * Copyright 2016-2022 NXP
// * All rights reserved.
// *
// * Redistribution and use in source and binary forms, with or without modification,
// * are permitted provided that the following conditions are met:
// *
// * o Redistributions of source code must retain the above copyright notice, this list
// *   of conditions and the following disclaimer.
// *
// * o Redistributions in binary form must reproduce the above copyright notice, this
// *   list of conditions and the following disclaimer in the documentation and/or
// *   other materials provided with the distribution.
// *
// * o Neither the name of NXP Semiconductor, Inc. nor the names of its
// *   contributors may be used to endorse or promote products derived from this
// *   software without specific prior written permission.
// *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// */
//
///**
// * @file    PRATICA5_FRDM-KL46Z.c
// * @brief   Application entry point.
// */
//#include <stdio.h>
//#include "board.h"
//#include "peripherals.h"
//#include "pin_mux.h"
//#include "clock_config.h"
//#include "MKL46Z4.h"
//#include "fsl_debug_console.h"
//
//#include "FreeRTOS.h"
//#include "task.h"
//#include "queue.h"
///* TODO: insert other include files here. */
//#define LED_RED 	31
//#define LED_GREEN 	5
//#define SW1			13
//#define SW2			4
//#define ON 			1
//#define OFF 		0
//
//int flag = 0;
//int flag2 = 0;
///* TODO: insert other definitions and declarations here. */
//typedef struct {
//	unsigned int num;
//	unsigned int status;
//} LedInfo;
//
//void PORTC_PORTD_IRQHandler(void) {
//	if(GPIOD->PDIR & (1<<SW2)) {
//		flag = 1;
//	} else {
//		flag = 0;
//	}
//
//	// W1C em Interrupt Status Flag da PORTA_D_4
//	PORTD->PCR[SW2] |= (1 << 24);
//}
//
//void PORTA_IRQHandler(void) {
//	if(GPIOA->PDIR & (1 << SW1)) {
//		flag2 = 1;
//	} else {
//		flag2 = 0;
//	}
//	PORTA->PCR[SW1] |= (1 << 24);
//}
//void vLedsInit() {
//	CLOCK_EnableClock(kCLOCK_PortA);
//	CLOCK_EnableClock(kCLOCK_PortD);
//	CLOCK_EnableClock(kCLOCK_PortE);
//
////	PORTD->PCR[LED_GREEN] |= (1 << 8);
////	GPIOD->PDDR |= (1 << LED_GREEN);
////	GPIOD->PSOR |= (1 << LED_GREEN);
//	PORTE->PCR[LED_RED] |= (1 << 8);
//	GPIOE->PDDR |= (1 << LED_RED);
////	GPIOE->PSOR |= (1 << LED_RED);
//}
//
//void vSwitchsInit() {
//	PORTA->PCR[SW1] |= (1 << 8) | (1 << 1) | (1 << 0) | (0xB << 16);
//	PORTD->PCR[SW2] |= (1 << 8) | (1 << 1) | (1 << 0) | (0xB << 16);
//}
//
//void drvLedsSet(int num, int status) {
//	if(num == LED_GREEN) {
//		if(status == ON) {
//			GPIOD->PSOR |= (1 << LED_GREEN);
//		} else {
//			GPIOD->PCOR |= (1 << LED_GREEN);
//		}
//	} else if(num == LED_RED){
//		if(status == ON) {
//			GPIOE->PSOR |= (1 << LED_RED);
//		} else {
//			GPIOE->PCOR |= (1 << LED_RED);
//		}
//	}
//}
//
//void taskLed(void *pvParameters) {
//	xQueueHandle ledQueue = (xQueueHandle) pvParameters;
//	LedInfo led;
//
//	for(;;) {
//		xQueueReceive(ledQueue, &led, portMAX_DELAY);
//		drvLedsSet(led.num, led.status);
//	}
//}
//
//int drvButtonsSW1Pressed(void) {
//	if(GPIOD->PDIR & (1 << 4)) {
//		return 1;
//	}
//	return 0;
//}
//
//int drvButtonsSW2Pressed(void) {
//	if(GPIOD->PDIR & (1 << 2)) {
//		return 1;
//	}
//	return 0;
//}
//
//void taskButton(void *pvParameters){
//	xQueueHandle ledQueue = (xQueueHandle) pvParameters;
//	LedInfo led;
//	led.status = OFF;
//	led.num = LED_RED;
//	for (;;) {
//		if (flag2 && (led.status == OFF)) {
//			printf("teste\n");
//			led.status = ON;
//			xQueueSendToBack(ledQueue, &led, portMAX_DELAY);
//		}else if (flag && (led.status == ON)) {
//			printf("2teste\n");
//			led.status = OFF;
//			xQueueSendToBack(ledQueue, &led, portMAX_DELAY);
//		}
//		vTaskDelay(100 / portTICK_PERIOD_MS);
//	}
//}
///*
// * @brief   Application entry point.
// */
//int main(void) {
//
//	xQueueHandle ledQueue;
//	vLedsInit();
//
//	vSwitchsInit();
//
//	ledQueue = xQueueCreate(5, sizeof(LedInfo));
//
//
//	/* create leds task */
//	xTaskCreate(taskLed, "TaskLed", configMINIMAL_STACK_SIZE, (void *)ledQueue, 1, NULL);
//	/* create buttons task */
//	xTaskCreate(taskButton, "TaskButton", configMINIMAL_STACK_SIZE, (void *)ledQueue, 1, NULL);
//	/* start the scheduler */
//	vTaskStartScheduler();
//
//	while(true){} /* should never reach here! */
//    return 0 ;
//}
