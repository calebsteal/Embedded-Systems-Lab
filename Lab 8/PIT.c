/*
 * PIT.c
 *
 *  Created on: 1/29/2021
 *      Author: Dr. Russ
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_pit.h"
#include "fsl_gpio.h"

#include "clock_config.h"

#include <fsl_clock.h>


int pit_counter = 0;
int report_counter = 0;
long current_time = 0;

#define PIT_INTERVAL_MICROSEC	100000U
#define TICKS_PER_REPORT	100

extern int16_t SensorResults[3];

void PIT0_IRQHandler(void) //Note the "magic name".  This will override the default ISR.
{

    /* Clear interrupt flag.*/
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK);
	ReadSensorsOnce(SensorResults);

		if (SensorResults[0]<0) SensorResults[0] = -SensorResults[0];
		if (SensorResults[1]<0) SensorResults[1] = -SensorResults[1];
		if (SensorResults[2]<0) SensorResults[2] = -SensorResults[2];

	FTM_UpdatePwm(SensorResults[0]>>8,SensorResults[1]>>8);

}

void PIT_INIT(void)
{

	uint32_t BusClockFreq;
	/* Structure of initialize PIT */
	pit_config_t pitConfig;
	PIT_GetDefaultConfig(&pitConfig);
	pitConfig.enableRunInDebug = true;

	/* Init pit module */
	PIT_Init(PIT, &pitConfig);

	/* Set timer period for channel 0 */
	// Setting it to 5 seconds so not quite as annoying as 1 second
	BusClockFreq = CLOCK_GetBusClkFreq();
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(PIT_INTERVAL_MICROSEC, BusClockFreq));
	PRINTF("\r\nPit clock is %d Hz",BusClockFreq);
	PRINTF("\r\nPit interrupt every %d microseconds",PIT_INTERVAL_MICROSEC);
	PRINTF("\r\nPit report every %d interrupts",TICKS_PER_REPORT);


	/* Enable timer interrupts for channel 0 */
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

	/* Enable at the NVIC */
	EnableIRQ(PIT0_IRQn);
	//NVIC_SetPriority(PIT0_IRQn,2); // sets priority of PIT interrupt to 2

	/* Start channel 0 */
	PRINTF("\r\nStarting PIT Timer\n\r");
	PIT_StartTimer(PIT, kPIT_Chnl_0);

}
