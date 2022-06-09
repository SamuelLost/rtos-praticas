/*
 * Pratica 05 - ;
 *
 * */

#include "FreeRTOS.h"
#include "task.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "MKL46Z4.h"
#include "pin_mux.h"

TaskHandle_t ledGreenHandler;
TaskHandle_t ledRedHandler;

void highLedGreen(){
	GPIOD->PCOR |= (1 << 5);
}

void lowLedGreen(){
	GPIOD->PSOR |= (1 << 5);
}

void highLedRed(){
	GPIOE->PCOR |= (1 << 29);
}

void lowLedRed(){
	GPIOE->PSOR |= (1 << 29);
}

void vTaskLedGreen(void *pvParameters){
	portTickType xLastWakeTime;
//	PRINTF("Executando a Task 1 pela primeira vez");

	xLastWakeTime = xTaskGetTickCount();
	while (true) {
//		printf("Task 1 está executando\r\n");
//		highLedGreen();
		GPIOD->PTOR = (1 << 5);
//		vTaskDelay(1000 / portTICK_PERIOD_MS);

		//vTaskDelayUntil --> a task fica no BLOCKED o tempo descontado pela ação anterior
		//por exemplo se foi gasto 500ms para acender dar o toggle, então a task ficará no
		//BLOCKED por 500ms. Coloca a task em execução a cada 1000ms, entra em execução a
		//cada 1000ms, é uma execução periódica.
		vTaskDelayUntil(&xLastWakeTime, (1000 / portTICK_PERIOD_MS));
//		lowLedGreen();

		//vTaskDelay() --> Coloca a task no BLOCKED pelo tempo especificado, ou seja, a partir
		//da chamada de bloqueio a task vai pro BLOCKED por 1000ms.
//		vTaskDelay(1000 / portTICK_PERIOD_MS);
//		vTaskDelayUntil(xLastWakeTime, (100 / portTICK_PERIOD_MS));
	}
}

void vTaskLedRed(void *pvParameters){
	portTickType xLastWakeTime;
//	PRINTF("Executando a Task 2 pela primeira vez");

	xLastWakeTime = xTaskGetTickCount();


	while (true) {
//		printf("Task 2 está executando\r\n");
//		highLedRed();
		GPIOE->PTOR = (1 << 29);
//		vTaskDelay coloca a task no estado blocked
//		vTaskDelay(2000 / portTICK_PERIOD_MS);
		vTaskDelayUntil(&xLastWakeTime, (2000 / portTICK_PERIOD_MS));
//		lowLedRed();
//		vTaskDelayUntil(xLastWakeTime, (2000 / portTICK_PERIOD_MS));
//		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}
void vApplicationIdleHook(){
	unsigned int ui = 0;
	unsigned long ul = 0;
	printf("IDLE!!\n");
	for(ui = 0; ui < 3; ui++) {
		for(ul = 0; ul < 10000000; ul++) {

		}
	}
}

int main(void){

	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	PORTD->PCR[5] |= (1 << 8);
	GPIOD->PDDR |= (1 << 5);
	GPIOD->PSOR |= (1 << 5);
	PORTE->PCR[29] |= (1 << 8);
	GPIOE->PDDR |= (1 << 29);
	GPIOE->PSOR |= (1 << 29);

	/* create task 1 */
	xTaskCreate(vTaskLedGreen, (signed char *)"TaskLedGreen", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	/* create task 2 */
	xTaskCreate(vTaskLedRed, (signed char *)"TaskLedRed", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	/* start the scheduler */
	vTaskStartScheduler();

	while(true){} /* should never reach here! */
}

