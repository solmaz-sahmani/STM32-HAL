#ifndef MAX7219_H
#define MAX7219_H

#include "main.h"

/* MAX7219 Register Addresses */
#define MAX7219_REG_NOOP			0x00
#define MAX7219_REG_DIGIT0 			0x01
#define MAX7219_REG_DIGIT1 			0x02
#define MAX7219_REG_DIGIT2 			0x03
#define MAX7219_REG_DIGIT3 			0x04
#define MAX7219_REG_DIGIT4 			0x05
#define MAX7219_REG_DIGIT5 			0x06
#define MAX7219_REG_DIGIT6 			0x07
#define MAX7219_REG_DIGIT7 			0x08
#define MAX7219_REG_DECODEMODE 		0x09
#define MAX7219_REG_INTENSITY 		0x0A
#define MAX7219_REG_SCANLIMIT 		0x0B
#define MAX7219_REG_SHUTDOWN 		0x0C
#define MAX7219_REG_DISPLAYTEST 	0x0F

/* Display configuration */
#define MAX7129_NUM_DEVICES			2   // NUMBER OF MODULES
#define DISPLAY_WIDTH				8	// COLUMNS
#define DISPLAY_HEIGHT				16  // ROWS

/* Function Prototypes / Declaration */
void MAX7219_Init(void); // initialization chips(decode mode, intensity, scan limit, shutdown mode)
void MAX7219_SendByte(uint8_t data); //send 1byte from SPI
void MAX7219_SendCommand(uint8_t device_index, uint8_t reg, uint8_t data); // send command (reg address + data) into the one chip
void MAX7219_Clear(void); // shutdown entire display
void MAX7219_SetPixel(uint8_t x, uint8_t y, uint8_t state); // turn on/off led in a declare direction
void MAX7219_Update(void);

#endif
