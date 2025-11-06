#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f4xx_hal.h"

// Địa chỉ sector lưu dữ liệu (ví dụ: Sector 6 của STM32F411 - 128KB)
#define FLASH_SECTOR_USED       FLASH_SECTOR_6
#define FLASH_SECTOR_ADDR       0x08040000  // Bắt đầu của Sector 6

HAL_StatusTypeDef Flash_Write_Array(uint32_t address, uint8_t *data, uint32_t size);
HAL_StatusTypeDef Flash_Read_Array(uint32_t address, uint8_t *data, uint32_t size);
HAL_StatusTypeDef Flash_Erase_Sector(uint32_t sector);

#endif
