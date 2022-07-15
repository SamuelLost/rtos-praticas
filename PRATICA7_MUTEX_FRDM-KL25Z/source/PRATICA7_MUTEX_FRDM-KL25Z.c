/**
 * @file    PRATICA7_MUTEX_FRDM-KL25Z.c
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
#include "queue.h"
#include "task.h"
#include "semphr.h"
/* TODO: insert other definitions and declarations here. */
xSemaphoreHandle xPrinftMutex;
//TaskHandle_t taskHandler;

void taskMsg(void *pvParameters) {
    char *msg = (char *)pvParameters;
    int i;

    while(true) {
    	//Para desabilitar o semáforo e as mensagens ficarem embaralhadas
    	// basta comentar as linhas referentes ao semáforo, 29 e 32.
    	xSemaphoreTake(xPrinftMutex, portMAX_DELAY);
        printf("%s\n", msg);
        PRINTF("%s\r\n", msg);
        xSemaphoreGive(xPrinftMutex);
        for (i = 0; i < 2000000; i++);
    }
}
/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
	/* Init UART */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    /* create mutex */ 
    xPrinftMutex = xSemaphoreCreateMutex();

    /* create msg task 1 */
    xTaskCreate(taskMsg, "TaskString1", configMINIMAL_STACK_SIZE * 4, (void *)"--- 0123456789 ---", 1, NULL);
    /* create msg task 2 */
    xTaskCreate(taskMsg, "TaskString2", configMINIMAL_STACK_SIZE * 4, (void *)"*** abcdefghij ***", 1, NULL);
    /* start the scheluder */
	vTaskStartScheduler();

	while(true); /* should never reach here! */

    return 0 ;
}
