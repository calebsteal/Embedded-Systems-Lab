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

	    	default:
	    		PRINTF("\rUnrecognized command\n\r");
	    		break;
	    	} // end case
	    	i = 0;
	    }
	}
}
