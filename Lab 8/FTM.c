/*
 * FTM.c
 *
 *  Created on: Feb 5, 2021
 *      Author: sam
 */
#include "fsl_ftm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer instance/channel used for board */
#define BOARD_TIMER_BASEADDR       FTM0
#define BOARD_FIRST_TIMER_CHANNEL  7U
#define BOARD_SECOND_TIMER_CHANNEL 6U
#define BOARD_FTM_PRESCALE_DIVIDER kFTM_Prescale_Divide_128
/* Get source clock for TPM driver */
#define BOARD_TIMER_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#define BOARD_TIMER_PERIPHERAL FTM0


/* Initialize timer module */
void PWM_Init(void)
{
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam[2];

    /* Configure ftm params with frequency 24kHZ */
    // The code uses the FIRST channel (channel 7) which is connected to PTA2, Green LED
    ftmParam[0].chnlNumber            = (ftm_chnl_t)BOARD_FIRST_TIMER_CHANNEL;
    ftmParam[0].level                 = kFTM_LowTrue;
    ftmParam[0].dutyCyclePercent      = 0U;
    ftmParam[0].firstEdgeDelayPercent = 0U;
    ftmParam[0].enableDeadtime        = false;

    // The code uses the SECOND channel (channel 6) which is connected to PTA1, Red LED
    ftmParam[1].chnlNumber            = (ftm_chnl_t)BOARD_SECOND_TIMER_CHANNEL;
    ftmParam[1].level                 = kFTM_LowTrue;
    ftmParam[1].dutyCyclePercent      = 0U;
    ftmParam[1].firstEdgeDelayPercent = 0U;
    ftmParam[1].enableDeadtime        = false;
    /*
     * ftmInfo.prescale = kFTM_Prescale_Divide_1;
     * ftmInfo.bdmMode = kFTM_BdmMode_0;
     * ftmInfo.pwmSyncMode = kFTM_SoftwareTrigger;
     * ftmInfo.reloadPoints = 0;
     * ftmInfo.faultMode = kFTM_Fault_Disable;
     * ftmInfo.faultFilterValue = 0;
     * ftmInfo.deadTimePrescale = kFTM_Deadtime_Prescale_1;
     * ftmInfo.deadTimeValue = 0;
     * ftmInfo.extTriggers = 0;
     * ftmInfo.chnlInitState = 0;
     * ftmInfo.chnlPolarity = 0;
     * ftmInfo.useGlobalTimeBase = false;
     */
    FTM_GetDefaultConfig(&ftmInfo);

    /* Initialize FTM module */
    FTM_Init(BOARD_TIMER_BASEADDR, &ftmInfo);

    FTM_SetupPwm(BOARD_TIMER_BASEADDR, ftmParam, 2U, kFTM_EdgeAlignedPwm, 24000U, BOARD_TIMER_SOURCE_CLOCK);
    FTM_StartTimer(BOARD_TIMER_BASEADDR, kFTM_SystemClock);
}

/* Update the duty cycle of an active pwm signal */
void FTM_UpdatePwm(uint16_t x, uint16_t y)
{
    /* Start PWM mode with updated duty cycle */
	/* x = duty cycle of output expressed as a percentage */
    FTM_UpdatePwmDutycycle(BOARD_TIMER_PERIPHERAL, kFTM_Chnl_7, kFTM_EdgeAlignedPwm, x);
    FTM_UpdatePwmDutycycle(BOARD_TIMER_PERIPHERAL, kFTM_Chnl_6, kFTM_EdgeAlignedPwm, y);


    /* Software trigger to update registers */
    FTM_SetSoftwareTrigger(BOARD_TIMER_PERIPHERAL, true);
}
