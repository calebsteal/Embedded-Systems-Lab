/*
 * I2C.h
 *
 *  Created on: Feb. 10, 2021
 *      Author: Russ
 */

#ifndef SOURCE_I2CSENSOR_H_
#define SOURCE_I2CSENSOR_H_

// This file was obtained from Adafruit

/*=========================================================================
    FXOS8700 I2C ADDRESS/BITS AND SETTINGS
    -----------------------------------------------------------------------*/
/** 7-bit I2C address for this sensor */
#define FXOS8700_ADDRESS (0x1C) // 0011110 -- Corresponds to SA0 = 0, SA1 = 0
/** Device ID for this sensor (used as sanity check during init) */
#define FXOS8700_ID (0xC7) // 1100 0111
/*=========================================================================*//*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
/*!
    Raw register addresses used to communicate with the FXOS8700 magnetic sensor.
*/
typedef enum {
  FXOS8700_REGISTER_STATUS = 0x00,    /**< 0x00 */
  FXOS8700_REGISTER_OUT_X_MSB = 0x01, /**< 0x01 */
  FXOS8700_REGISTER_OUT_X_LSB = 0x02, /**< 0x02 */
  FXOS8700_REGISTER_OUT_Y_MSB = 0x03, /**< 0x03 */
  FXOS8700_REGISTER_OUT_Y_LSB = 0x04, /**< 0x04 */
  FXOS8700_REGISTER_OUT_Z_MSB = 0x05, /**< 0x05 */
  FXOS8700_REGISTER_OUT_Z_LSB = 0x06, /**< 0x06 */
  FXOS8700_REGISTER_WHO_AM_I =
      0x0D, /**< 0x0D (default value = 0b11000111, read only) */
  FXOS8700_REGISTER_XYZ_DATA_CFG = 0x0E, /**< 0x0E */
  FXOS8700_REGISTER_CTRL_REG1 =
      0x2A, /**< 0x2A (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_CTRL_REG2 =
      0x2B, /**< 0x2B (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_CTRL_REG3 =
      0x2C, /**< 0x2C (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_CTRL_REG4 =
      0x2D, /**< 0x2D (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_CTRL_REG5 =
      0x2E, /**< 0x2E (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_MSTATUS = 0x32,    /**< 0x32 */
  FXOS8700_REGISTER_MOUT_X_MSB = 0x33, /**< 0x33 */
  FXOS8700_REGISTER_MOUT_X_LSB = 0x34, /**< 0x34 */
  FXOS8700_REGISTER_MOUT_Y_MSB = 0x35, /**< 0x35 */
  FXOS8700_REGISTER_MOUT_Y_LSB = 0x36, /**< 0x36 */
  FXOS8700_REGISTER_MOUT_Z_MSB = 0x37, /**< 0x37 */
  FXOS8700_REGISTER_MOUT_Z_LSB = 0x38, /**< 0x38 */
  FXOS8700_REGISTER_TEMPERATURE = 0x51,
  FXOS8700_REGISTER_MCTRL_REG1 =
      0x5B, /**< 0x5B (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_MCTRL_REG2 =
      0x5C, /**< 0x5C (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_MCTRL_REG3 =
      0x5D, /**< 0x5D (default value = 0b00000000, read/write) */
} fxos8700Registers_t;



//void I2C_Init(I2C_Type *i2cType);

//void I2C_Write(I2C_Type *i2cType, int DeviceAddress, int StartAddress, int WriteDataNumBytes, uint8_t *WriteData);

//void I2C_Read(I2C_Type *i2cType, int DeviceAddress, int StartAddress, int WriteDataNumBytes, uint8_t *WriteData);



#endif /* SOURCE_I2CSENSOR_H_ */
