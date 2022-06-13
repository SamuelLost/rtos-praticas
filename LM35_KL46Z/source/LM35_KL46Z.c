/* p7_3.c: A to D conversion of channel 0
 * This program converts the analog input from channel 0 (PTE20)
 * using software trigger continuously. PTE20 is connected to
 * an LM34 Fahrenheit temperature sensor. The conversion result
 * is displayed as temperature through UART0 virtual serial port.
 * 16-bit precision is used for conversion. At higher precision,
 * the noise is more significant so 32 samples averaging is used.
 * The LM34 output voltage is 10mV/degreeF. The ADC of FRDM-KL25Z
 * uses 3.3V as Vref so:
 * temperature = result * 330.0 / 65536
 * Open a terminal emulator at 115200 Baud rate at the host PC and
 * observe the output.
 */
#include "MKL46Z4.h"
#include <stdio.h>
#include "fsl_clock.h"

void ADC0_init(void);
void delayMs(int n);

int main (void) {
	int result;
	ADC0_init(); /* Configure ADC0 */
	while (1) {
		ADC0->SC1[0] = 0; /* start conversion on channel 0 */
		while(!(ADC0->SC1[0] & 0x80)) { } /* wait for COCO */
		result = ADC0->R[0]; /* read conversion result and clear COCO flag */
//		temperature = result * 330.0 / 65536; /* convert voltage to temperature */
//		printf("\r\nTemp = %6.2dC", temperature); /* convert to string */

		float umid = 100 - (result / 65536.0) * 100;

		printf("Umidade %d%%\n", (int) umid);

		ADC0->SC1[0] = 9; /* start conversion on channel 0 */
		while(!(ADC0->SC1[0] & 0x80)) { } /* wait for COCO */
		result = ADC0->R[0]; /* read conversion result and clear COCO flag */
//		temperature = result * 330.0 / 65536; /* convert voltage to temperature */
//		printf("\r\nTemp = %6.2dC", temperature); /* convert to string */

		float temperature = result * 330.0 / 65536;

		printf("Temperatura %d C\n", (int) temperature);
	}
}
void ADC0_init(void)
{
	SIM->SCGC5 |= (1 << 10); /* clock to PORTE */
	PORTB->PCR[1] = 0; /* PTB1 analog input */


	SIM->SCGC5 |= 0x2000; /* clock to PORTE */
	PORTE->PCR[20] = 0; /* PTE20 analog input */
	SIM->SCGC6 |= 0x8000000; /* clock to ADC0 */
	ADC0->SC2 &= ~0x40; /* software trigger */
	ADC0->SC3 |= 0x07; /* 32 samples average */
	/* clock div by 4, long sample time, single ended 16 bit, bus clock */
	ADC0->CFG1 = 0x40 | 0x10 | 0x0C | 0x00;
}

/* Delay n milliseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */
void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}
