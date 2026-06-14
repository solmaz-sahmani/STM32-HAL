#include "max7219.h"

extern SPI_HandleTypeDef hspi1;

uint8_t frame_buffer[DISPLAY_HEIGHT];

void MAX7219_SendByte(uint8_t data)
{
	HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
}

void MAX7219_SendCommand(uint8_t device_index, uint8_t reg, uint8_t data)
{
	HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_RESET);

	for(int8_t i = MAX7129_NUM_DEVICES - 1; i >= 0; i--)
	{
		if (i == device_index)
		{
			MAX7219_SendByte(reg);
			MAX7219_SendByte(data);
		}
		else
		{
			MAX7219_SendByte(MAX7219_REG_NOOP);
			MAX7219_SendByte(0x00);
		}
	}

	HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_SET);
}

void MAX7219_Init(void)
{
	for(uint8_t device = 0; device < MAX7129_NUM_DEVICES; device++)
	{
		MAX7219_SendCommand(device, MAX7219_REG_SHUTDOWN, 0x01);
        MAX7219_SendCommand(device, MAX7219_REG_DISPLAYTEST, 0x00);
        MAX7219_SendCommand(device, MAX7219_REG_DECODEMODE, 0x00);
        MAX7219_SendCommand(device, MAX7219_REG_SCANLIMIT, 0x07);
        MAX7219_SendCommand(device, MAX7219_REG_INTENSITY, 0x08);
	}

    MAX7219_Clear();
}

void MAX7219_Clear(void)
{
    for (uint8_t row = 0; row < DISPLAY_HEIGHT; row++)
    {
        frame_buffer[row] = 0x00;
    }

    MAX7219_Update();
}

void MAX7219_SetPixel(uint8_t x, uint8_t y, uint8_t state)
{
    if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT)
    {
        return;
    }

    if (state)
    {
        frame_buffer[y] |= (1 << (7 - x));
    }
    else
    {
        frame_buffer[y] &= ~(1 << (7 - x));
    }
}

void MAX7219_Update(void)
{
    for (uint8_t row = 0; row < DISPLAY_HEIGHT; row++)
    {
        uint8_t device = row / 8;
        uint8_t digit_register = MAX7219_REG_DIGIT0 + (row % 8);

        MAX7219_SendCommand(device, digit_register, frame_buffer[row]);
    }
}
