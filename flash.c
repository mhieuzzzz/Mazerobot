#include "flash.h"

HAL_StatusTypeDef Flash_Erase_Sector(uint32_t sector)
{
    HAL_StatusTypeDef status;
    FLASH_EraseInitTypeDef eraseInitStruct;
    uint32_t SectorError = 0;

    HAL_FLASH_Unlock();

    eraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    eraseInitStruct.Sector = sector;
    eraseInitStruct.NbSectors = 1;

    status = HAL_FLASHEx_Erase(&eraseInitStruct, &SectorError);

    HAL_FLASH_Lock();
    return status;
}

HAL_StatusTypeDef Flash_Write_Array(uint32_t address, uint8_t *data, uint32_t size)
{
    HAL_StatusTypeDef status = HAL_OK;
    HAL_FLASH_Unlock();

    for (uint32_t i = 0; i < size; i += 1)
    {
        status = HAL_FLASH_Program(TYPEPROGRAM_BYTE, address + i, data[i]);
        if (status != HAL_OK)
            break;
    }

    HAL_FLASH_Lock();
    return status;
}

HAL_StatusTypeDef Flash_Read_Array(uint32_t address, uint8_t *data, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        data[i] = *(volatile uint8_t *)(address + i);
    }
    return HAL_OK;
}
