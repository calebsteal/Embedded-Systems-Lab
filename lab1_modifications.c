Pin Mux modification

// In pin_mux.c
#include "fsl_gpio.h"

// After Port E clock enable
gpio_pin_config_t LEDRGB_RED_config = {
	.pinDirection = kGPIO_DigitalOutput,
	.outputLogic = OU
};

/* Initialize GPIO functionality on PTA1 (pin 23) */
GPIO_PinInit(GPIOA, 1, &LEDRGB_RED_config);

 /* PORTA1 (pin 23) is configured as PTA1 */
PORT_SetPinMux(PORTA, 1, kPORT_MuxAsGPIO);

// In hello_world.c, under PUTCHAR
GPIO_PortToggle(GPIOA, 1u << 1);
