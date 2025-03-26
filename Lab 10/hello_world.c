/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_port.h"
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */

int16_t SensorResults[3];

int main(void)
{
	char ch;
	char instring[20];
	int i = 0;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	PRINTF("hello world.\r\n");

	while (1)
	{
		i=0;
	    while (1==1)
	    {
	    	ch = GETCHAR();
	    	instring[i++] = ch;
	    	while ((ch != '\n') && (i<20))
	    	{
	    		ch = GETCHAR();
	    		instring[i++] = ch;
	    		GPIO_PortToggle(GPIOA, 1u << 1);
	    	}

	    	instring[i] = 0;
	    	i = 0;

	    	while (instring[i] != 0){
	    		PUTCHAR(instring[i++]);
	    	}

	    	switch (instring[0]){
	    	case 'a':
	    	PRINTF("\rCommand 'a' detected\n\r");
	    	GPIO_PortToggle(GPIOD, 1u << 5);
	    	break;

	    	case 'b':
	    		PRINTF("\rCommand 'b' detected\n\r");
	    		EnableIRQ(PORTC_IRQn);
	    		while(1==1){}								// Fudge function - GETCHAR has a bad habit of locking up the Kinetis
	    		break;

	    	case 'p':
	    		PRINTF("\rCommand 'p' detected\n\r");
	    		EnableIRQ(PORTC_IRQn);
	    		PIT_INIT();
	    		while(1==1){}
	    		break;

	    	case 'f':
	    		PRINTF("\rCommand 'f' detected\n\r");
	    		PWM_Init();
	    		EnableIRQ(PORTC_IRQn);
	    		PIT_INIT();
	    		while(1==1) {
	    			for(i = 0; i< 100; i++) {
	    				FTM_UpdatePwm(i);
	    				delay(10000);
	    			}
	    			for(i = 100; i>0; i--) {
	    				FTM_UpdatePwm(i);
						delay(10000);
	    			}
	    		}

	    	case 'i':
	    		PRINTF("\rCommand 'i' detected\n\r");
	    		I2C_Init();
	    		PWM_Init();
	    		GPIO_PortSet(GPIOD, 1U << 5);
	    		GPIO_PortSet(GPIOA, 1U << 1);
	    		while(1==1){
	    			ReadSensorsOnce(SensorResults);
	    		    if (SensorResults[0]<0) SensorResults[0] = -SensorResults[0];
	    		    if (SensorResults[1]<0) SensorResults[1] = -SensorResults[1];
	    		    if (SensorResults[2]<0) SensorResults[2] = -SensorResults[2];
	    		    PRINTF("X:%d Y:%d Z:%d\r\n",SensorResults[0],SensorResults[1],SensorResults[2]);
	    		    FTM_UpdatePwm(SensorResults[0]>>8);
	    		    delay(3000000);
	    		}
	    		break;

	    	case 'g':
	    	    PRINTF("\rCommand 'g' detected\n\r");
	    	    I2C_Init();
	    	    PWM_Init();
	    	    GPIO_PortSet(GPIOD, 1U << 5);
	    	    GPIO_PortSet(GPIOA, 1U << 1);
	    	    PIT_INIT();
	    	    while(1==1){

	    	    }
	    	    break;

			case 'm':
				PRINTF("\rCommand 'm' detected\n\r");
				I2C_Init();
				while(1==1){
					ReadMagOnce(SensorResults);
					PRINTF("X:%d Y:%d Z:%d \n\r", SensorResults[0], SensorResults[1], SensorResults[2]);
					delay(30000000);
				}
				break;

			case 't':
				PRINTF("\rCommand 't' detected\n\r");
				I2C_Init();
				PWM_Init();
				GPIO_PortSet(GPIOD, 1U << 5);
				GPIO_PortSet(GPIOA, 1U << 1);
				while(1==1){
					ReadTemp();
					ReadSensorsOnce(SensorResults);
					if (SensorResults[0]<0) SensorResults[0] = -SensorResults[0];
					if (SensorResults[1]<0) SensorResults[1] = -SensorResults[1];
					if (SensorResults[2]<0) SensorResults[2] = -SensorResults[2];
					FTM_UpdatePwm(SensorResults[0]>>8, SensorResults[1]>>8);
					ReadMagOnce(SensorResults);
					delay(30000000);
				}
				break;

	    	default:
	    		PRINTF("\rUnrecognized command\n\r");
	    		break;
	    	} // end case

	    	i = 0;
	    }
	}
}

void PORTC_IRQHandler(void){
	PRINTF("Why is Dr. Russ always out of town :(\n");
	PORT_ClearPinsInterruptFlags(PORTC, (1U << 1));
	GPIO_PortToggle(GPIOD, (1U << 5));
}

void delay(int j) {
    volatile uint32_t i = 0;
    for (i = 0; i < j; ++i) {
        __asm("NOP");
    }
}
