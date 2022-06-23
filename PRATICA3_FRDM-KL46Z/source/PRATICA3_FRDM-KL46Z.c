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

#define CODE_LED_GREEN 1
#define CODE_LED_RED 2


TaskHandle_t ledGreenHandler;
TaskHandle_t ledRedHandler;

static unsigned long int idle_tick_counter = 0;
void vApplicationIdleHook(void)
{
	unsigned long int tick = xTaskGetTickCount();
	while (xTaskGetTickCount() == tick);
	idle_tick_counter++;
}

void taskCPUUsage(void *pvParameters)
{
	unsigned long int idle_tick_last, ticks;
	idle_tick_last = idle_tick_counter = 0;
	for (;;) {
		/* wait for 3 seconds */
		vTaskDelay(1000/portTICK_PERIOD_MS);

		/* calculate quantity of idle ticks per second */
		if (idle_tick_counter > idle_tick_last)
			ticks = idle_tick_counter - idle_tick_last;
		else
			ticks = 0xFFFFFFFF - idle_tick_last + idle_tick_counter;
		ticks /= 3;

		/* print idle ticks per second */
		printf("%ld idle ticks per second (out of %ld)\n", ticks, configTICK_RATE_HZ);

		/* calc and print CPU usage */
		ticks = (configTICK_RATE_HZ - ticks)/10;
		printf("CPU usage: %d%%\n", ticks);

		/* update idle ticks */
		idle_tick_last = idle_tick_counter;
	}
}

void taskUseCPU(void *pvParameters)
{
	unsigned int i, j;
	for (;;) {
		for (i = 0, j = 0; i < 10000; i++){
			j *= i + 12.34;
		}
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}


void highLedGreen(){
	PORTD->PCR[5] |= (1 << 8);
	GPIOD->PDDR |= (1 << 5);
	GPIOD->PCOR |= (1 << 5);
}

void lowLedGreen(){
	PORTD->PCR[5] |= (1 << 8);
	GPIOD->PDDR |= (1 << 5);
	GPIOD->PSOR |= (1 << 5);
}

void highLedRed(){
	PORTE->PCR[29] |= (1 << 8);
	GPIOE->PDDR |= (1 << 29);
	GPIOE->PCOR |= (1 << 29);
}

void lowLedRed(){
	PORTE->PCR[31] |= (1 << 8);
	GPIOE->PDDR |= (1 << 29);
	GPIOE->PSOR |= (1 << 29);
}

void taskLedGreen(void *pvParameters){
	while (true) {
		highLedGreen();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		lowLedGreen();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void taskLedRed(void *pvParameters){
	while (true) {
		highLedRed();
		vTaskDelay(2000 / portTICK_PERIOD_MS);
		lowLedRed();
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

int main(void){

	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	/* create task 1 */
	xTaskCreate(taskLedGreen, (signed char *)"TaskLedGreen", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	/* create task 2 */
	xTaskCreate(taskLedRed, (signed char *)"TaskLedRed", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	/* create task to show CPU usage */
	xTaskCreate(taskCPUUsage, (signed char *)"Task CPU Usage", configMINIMAL_STACK_SIZE * 4, (void *)NULL, 0, NULL);

	/* create task to use CPU */
	xTaskCreate(taskUseCPU, (signed char *)"TaskUseCPU", configMINIMAL_STACK_SIZE, (void *)NULL, 1, NULL);

	/* start the scheduler */
	vTaskStartScheduler();

	while(true){} /* should never reach here! */
}

