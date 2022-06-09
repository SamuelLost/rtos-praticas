/*
 * The Clear BSD License
 * Copyright 2017-2018 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v4.1
processor: MKL46Z256xxx4
package_id: MKL46Z256VLL4
mcu_data: ksdk2_0
processor_version: 0.0.13
board: FRDM-KL46Z
functionalGroups:
- name: BOARD_InitPeripherals
  called_from_default_init: true
  selectedCore: core0
- name: BOARD_InitButtonsPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitLEDsPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitACCELPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitMAGPeripheral
  selectedCore: core0
- name: BOARD_InitDEBUG_UARTPeripheral
  id_prefix: BOARD_
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitButtonsPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * SW1_SW3 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SW1_SW3'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitButtonsPeripheral'
- peripheral: 'GPIOC'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_SW1_SW3_init(void) {
  /* Make sure, the clock gate for port C is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * BOARD_InitLEDsPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LED_RED initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LED_RED'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitLEDsPeripheral'
- peripheral: 'GPIOE'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTE_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_LED_RED_init(void) {
  /* Make sure, the clock gate for port E is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * LED_GREEN initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LED_GREEN'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitLEDsPeripheral'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTD_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_LED_GREEN_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * BOARD_InitACCELPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * ACCEL_I2C initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'ACCEL_I2C'
- type: 'i2c'
- mode: 'I2C_Polling'
- type_id: 'i2c_2566d7363e7e9aaedabb432110e372d7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'I2C0'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'BusInterfaceClock'
    - clockSourceFreq: 'GetFreq'
    - i2c_master_config:
      - enableMaster: 'true'
      - enableStopHold: 'false'
      - baudRate_Bps: '100000'
      - glitchFilterWidth: '0'
    - quick_selection: 'QS_I2C_1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t BOARD_ACCEL_I2C_config = {
  .enableMaster = true,
  .enableStopHold = false,
  .baudRate_Bps = 100000,
  .glitchFilterWidth = 0
};

void BOARD_ACCEL_I2C_init(void) {
  /* Initialization function */
  I2C_MasterInit(BOARD_ACCEL_I2C_PERIPHERAL, &BOARD_ACCEL_I2C_config, BOARD_ACCEL_I2C_CLK_FREQ);
}

/***********************************************************************************************************************
 * INT1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'INT1'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'GPIOC'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_PORTD_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_INT1_init(void) {
  /* Make sure, the clock gate for port C is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * INT2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'INT2'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_PORTD_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_INT2_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * BOARD_InitMAGPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * MAG_I2C initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'MAG_I2C'
- type: 'i2c'
- mode: 'I2C_Polling'
- type_id: 'i2c_2566d7363e7e9aaedabb432110e372d7'
- functional_group: 'BOARD_InitMAGPeripheral'
- peripheral: 'I2C0'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'BusInterfaceClock'
    - clockSourceFreq: 'GetFreq'
    - i2c_master_config:
      - enableMaster: 'true'
      - enableStopHold: 'false'
      - baudRate_Bps: '100000'
      - glitchFilterWidth: '0'
    - quick_selection: 'QS_I2C_1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t MAG_I2C_config = {
  .enableMaster = true,
  .enableStopHold = false,
  .baudRate_Bps = 100000,
  .glitchFilterWidth = 0
};

void MAG_I2C_init(void) {
  /* Initialization function */
  I2C_MasterInit(MAG_I2C_PERIPHERAL, &MAG_I2C_config, MAG_I2C_CLK_FREQ);
}

/***********************************************************************************************************************
 * INT2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'INT2'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitMAGPeripheral'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_PORTD_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void INT2_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * BOARD_InitDEBUG_UARTPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LPSCI_1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPSCI_1'
- type: 'lpsci'
- mode: 'polling'
- type_id: 'lpsci_d7d643c7d665ff9a7a181303138bb697'
- functional_group: 'BOARD_InitDEBUG_UARTPeripheral'
- peripheral: 'UART0'
- config_sets:
  - lpsciConfig_t:
    - lpsciConfig:
      - clockSource: 'UartClock'
      - lpsciSrcClkFreq: 'BOARD_BootClockRUN'
      - baudRate_Bps: '115200'
      - parityMode: 'kLPSCI_ParityDisabled'
      - stopBitCount: 'kLPSCI_OneStopBit'
      - idleLineType: 'kLPSCI_IdleLineStartBit'
      - enableTx: 'false'
      - enableRx: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpsci_config_t BOARD_LPSCI_1_config = {
  .baudRate_Bps = 115200,
  .parityMode = kLPSCI_ParityDisabled,
  .stopBitCount = kLPSCI_OneStopBit,
  .idleLineType = kLPSCI_IdleLineStartBit,
  .enableTx = false,
  .enableRx = false
};

void BOARD_LPSCI_1_init(void) {
  LPSCI_Init(BOARD_LPSCI_1_PERIPHERAL, &BOARD_LPSCI_1_config, BOARD_LPSCI_1_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
}

void BOARD_InitButtonsPeripheral(void)
{
  /* Initialize components */
  BOARD_SW1_SW3_init();
}

void BOARD_InitLEDsPeripheral(void)
{
  /* Initialize components */
  BOARD_LED_RED_init();
  BOARD_LED_GREEN_init();
}

void BOARD_InitACCELPeripheral(void)
{
  /* Initialize components */
  BOARD_ACCEL_I2C_init();
  BOARD_INT1_init();
  BOARD_INT2_init();
}

void BOARD_InitMAGPeripheral(void)
{
  /* Initialize components */
  MAG_I2C_init();
  INT2_init();
}

void BOARD_InitDEBUG_UARTPeripheral(void)
{
  /* Initialize components */
  BOARD_LPSCI_1_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}