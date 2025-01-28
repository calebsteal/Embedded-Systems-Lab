Pin Mux modification

#include "fsl_gpio.h"

gpio_pin_config_t LEDRGB_RED_config = {
	.pinDirection = kGPIO_DigitalOutput,
	.outputLogic = OU
};

GPIO_PinInit(GPIOA, 1, &LEDRGB_RED_config);

PORT_SetPinMux(PORTA, 1, kPORT_MuxAsGPIO);

GPIO_PortToggle(GPIOA, 1u << 1);
