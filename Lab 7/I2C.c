
#include "I2C.h"

#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_uart.h"
#include "fsl_i2c.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#define MAX_TRANSFER_SIZE 20 // Used to set up the data arrays for reading/writing I2C


i2c_master_config_t masterConfig;
I2C_Type base;
i2c_master_transfer_t transfer;

static uint8_t ReceiveData[MAX_TRANSFER_SIZE];
static uint8_t SendData[MAX_TRANSFER_SIZE];


int I2C_Write(I2C_Type *i2cType, int DeviceAddress, int StartAddress, int WriteDataNumBytes, int StartAddressSize, uint8_t *WriteData)
{
	i2c_master_transfer_t transfer;
	int result;

	//PRINTF("Initializing write struct... ");
	transfer.flags = 0;
	transfer.slaveAddress = DeviceAddress;
	transfer.direction = kI2C_Write;
	transfer.subaddress = StartAddress;
	transfer.subaddressSize = StartAddressSize;
	transfer.data = WriteData;
	transfer.dataSize = WriteDataNumBytes;
	//PRINTF("Sending ... " );

	result = I2C_MasterTransferBlocking(i2cType, &transfer);

	return result;

}

int I2C_Read(I2C_Type *i2cType, int DeviceAddress, int StartAddress, int WriteDataNumBytes, int StartAddressSize, uint8_t *WriteData)
{
	i2c_master_transfer_t transfer;
	int result;

	//PRINTF("Initializing read struct...");
	transfer.flags = 0;
	transfer.slaveAddress = DeviceAddress;
	transfer.direction = kI2C_Read;
	transfer.subaddress = StartAddress;
	transfer.subaddressSize = StartAddressSize;
	transfer.data = WriteData;
	transfer.dataSize = WriteDataNumBytes;
	//PRINTF("Reading ... " );

	result = I2C_MasterTransferBlocking(i2cType, &transfer);
	return result;
}

// For reference
//typedef struct _i2c_master_transfer
//{
    //uint32_t flags;            /*!< A transfer flag which controls the transfer. */
    //uint8_t slaveAddress;      /*!< 7-bit slave address. */
    //i2c_direction_t direction; /*!< A transfer direction, read or write. */
    //uint32_t subaddress;       /*!< A sub address. Transferred MSB first. */
    //uint8_t subaddressSize;    /*!< A size of the command buffer. */
    //uint8_t *volatile data;    /*!< A transfer buffer. */
    //volatile size_t dataSize;  /*!< A transfer size. */
//} i2c_master_transfer_t;

void I2C_Init(void)
{
	int i;

	//PRINTF("\rInitializing I2C...\n\r");
	I2C_MasterGetDefaultConfig(&masterConfig);
	//masterConfig.baudRate_Bps = 400000; //Using default of 100,000
	I2C_MasterInit(I2C0, &masterConfig, 20971520U);



	PRINTF("Checking for FXOS8700: ");
	i = I2C_Read(I2C0, FXOS8700_ADDRESS,FXOS8700_REGISTER_WHO_AM_I,1,1,ReceiveData);
	PRINTF("Read value 0x%x Return value 0x%x\n\r",ReceiveData[0],i);
	if(ReceiveData[0]!=FXOS8700_ID){
		PRINTF("Accelerometer not found %d\n\r",i);
	} else {
		PRINTF("Accelerometer found %d\n\r",i);

		// Put accelerometer in standby
		SendData[0] = 0x00;
		i = I2C_Write(I2C0, FXOS8700_ADDRESS,FXOS8700_REGISTER_CTRL_REG1,1,1,SendData);

		// Then program it

		//SendData[1] = 0x02;
		//write8(FXOS8700_REGISTER_CTRL_REG2, 0x02);/* High resolution */
		SendData[0] = 0x02;
		i = I2C_Write(I2C0, FXOS8700_ADDRESS,FXOS8700_REGISTER_CTRL_REG2,1,1,SendData);

		//SendData[0] = 0x15; -- This will also take it out of standby
		//write8(FXOS8700_REGISTER_CTRL_REG1, 0x15);/* Active, Normal Mode, Low Noise, 100Hz in Hybrid Mode */
		SendData[0] = 0x15;
		i = I2C_Write(I2C0, FXOS8700_ADDRESS,FXOS8700_REGISTER_CTRL_REG1,1,1,SendData);

		//Report last status byte
		PRINTF("Write to accel: %d ",i);

		/* Configure the magnetometer */
		SendData[0] = 0x1F;
		SendData[1] = 0x20;
		i = I2C_Write(I2C0, FXOS8700_ADDRESS,FXOS8700_REGISTER_MCTRL_REG1,2,1,SendData);
		//write8(FXOS8700_REGISTER_MCTRL_REG1, 0x1F);/* Hybrid Mode, Over Sampling Rate = 16 */
		//write8(FXOS8700_REGISTER_MCTRL_REG2, 0x20);/* Jump to reg 0x33 after reading 0x06 */
		PRINTF("Write to mag: %d\r\n",i);
	}

}

int ReadSensorsOnce(int16_t *Results){

    int i;

    i = I2C_Read(I2C0, FXOS8700_ADDRESS,FXOS8700_REGISTER_STATUS,7,1,ReceiveData);
    PRINTF("Read from accel: %d \r\n",i);

    if (i==0){
        PRINTF("Status: %02x",ReceiveData[0]);
        Results[0] = (ReceiveData[1]<<8)|ReceiveData[2];
        PRINTF(" X: %d", Results[0]);
        Results[1] = (ReceiveData[3]<<8)|ReceiveData[4];
        PRINTF(" Y: %d",Results[1]);
        Results[2] = (ReceiveData[5]<<8)|ReceiveData[6];
        PRINTF(" Z: %d",Results[2]);
        PRINTF("\r\n");
    } else {
        PRINTF("Did not read!\r\n");
    }

}
