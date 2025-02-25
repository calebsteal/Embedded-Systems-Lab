/*
 * Copyright 2019 ,2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MK22FN512xxx12
package_id: MK22FN512VLH12
mcu_data: ksdk2_0
processor_version: 9.0.0
board: FRDM-K22F
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "fsl_gpio.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '1', peripheral: UART1, signal: TX, pin_signal: ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA/RTC_CLKOUT}
  - {pin_num: '2', peripheral: UART1, signal: RX, pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN}
  - {pin_num: '24', peripheral: TPIU, signal: SWO, pin_signal: PTA2/UART0_TX/FTM0_CH7/JTAG_TDO/TRACE_SWO/EZP_DO, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t LEDRGB_RED_config = {
    		.pinDirection = kGPIO_DigitalOutput,
		.outputLogic = 1U
    };

    gpio_pin_config_t LEDRGB_GREEN_config = {
        		.pinDirection = kGPIO_DigitalOutput,
    		.outputLogic = 1U
     };

    gpio_pin_config_t LEDRGB_BLUE_config = {
		.pinDirection = kGPIO_DigitalOutput,
		.outputLogic = 1U
    };

    const port_pin_config_t SW2 = {
    		kPORT_PullUp,				// Internal pull-up resistor is enabled
			kPORT_FastSlewRate,		// Fast Slew Rate is enabled
			kPORT_PassiveFilterDisable,	// Passive filter is disabled
			kPORT_OpenDrainDisable,		// Open Drain is disabled
			kPORT_LowDriveStrength,		// Low drive strength is configured
			kPORT_MuxAsGpio,		// Pin is configured as PTC1
			kPORT_UnlockRegister,		// Pin Control Register fields [15:0] are not locked
    };

    // PORTC1 (pin 44) is configured as PTC1
    PORT_SetPinConfig(PORTC, 1U, &SW2);
    PORT_SetPinInterruptConfig(PORTC, 1u, kPORT_InterruptFallingEdge);

    /* Initialize GPIO functionality on PTA1 (pin 23) and PTD5 (FIXME: Add pin number here) */
    GPIO_PinInit(GPIOA, 1, &LEDRGB_RED_config);
    GPIO_PinInit(GPIOA, 2, &LEDRGB_GREEN_config);
    GPIO_PinInit(GPIOD, 5, &LEDRGB_BLUE_config);

    /* PORTA1 (pin 23) is configured as PTA1 and PORTD5 is configured as PTD5 */
    PORT_SetPinMux(PORTA, 1, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, 5, kPORT_MuxAsGpio);

    /* PORTA2 (pin 24) is configured as TRACE_SWO */
    PORT_SetPinMux(BOARD_LEDRGB_GREEN_PORT, BOARD_LEDRGB_GREEN_PIN, kPORT_MuxAsGpio);

    PORTA->PCR[2] = ((PORTA->PCR[2] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
                      * corresponding PE field is set. */
                     | PORT_PCR_PS(kPORT_PullDown)

                     /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
                     | PORT_PCR_PE(kPORT_PullDisable));

    /* PORTE0 (pin 1) is configured as UART1_TX */
    PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt3);

    /* PORTE1 (pin 2) is configured as UART1_RX */
    PORT_SetPinMux(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, kPORT_MuxAlt3);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART1TXSRC_MASK)))

                  /* UART 1 transmit data source select: UART1_TX pin. */
                  | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
