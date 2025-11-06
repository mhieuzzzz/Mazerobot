#include "flash.h"
#include "maze.h"
#include "stm32f4xx_hal.h"

/* Choose a safe flash address for storing maze.
   WARNING: You must set this correctly to avoid overwriting program.
   0x08020000 is an example; adjust based on your flash layout.
*/
#define FLASH_USER_START_ADDR   ((uint32_t)0x08020000)
#define FLASH_USER_END_ADDR     ((uint32_t)0x08020FFF)
#define FLASH_WORD_SIZE         4

extern uint8_t maze[MAZE_SIZE][MAZE_SIZE];

void save_maze_to_flash(void)
{
    HAL_FLASH_Unlock();

    // Erase necessary pages - simple approach: erase range
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PageError = 0;

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS; // STM32F4 flash variant may differ
    // For simplicity use mass erase style or use appropriate sector number. This is MCU dependent.
    // TODO: Replace with proper erase for your MCU or use HAL_FLASHEx_Erase for sectors.

    // Here we'll perform a simple word program (without explicit erase) ONLY if you know pages are free.
    // Safer: erase page with proper API. Implementation depends on device flash layout.

    // Program data
    uint32_t addr = FLASH_USER_START_ADDR;
    uint8_t *p = (uint8_t*)maze;
    uint32_t len = MAZE_SIZE * MAZE_SIZE;

    for(uint32_t i=0;i<len;i+=FLASH_WORD_SIZE)
    {
        uint32_t word = 0xFFFFFFFF;
        // pack up to 4 bytes
        for(int b=0;b<4;b++){
            uint32_t idx = i + b;
            uint8_t byte = 0xFF;
            if(idx < len) byte = p[idx];
            word |= ((uint32_t)byte) << (8*b);
        }

        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + i, (uint64_t)word) != HAL_OK)
        {
            // handle error
            HAL_FLASH_Lock();
            return;
        }
    }

    HAL_FLASH_Lock();
}

void load_maze_from_flash(void)
{
    uint32_t addr = FLASH_USER_START_ADDR;
    uint8_t *p = (uint8_t*)maze;
    uint32_t len = MAZE_SIZE * MAZE_SIZE;

    for(uint32_t i=0;i<len;i++)
    {
        p[i] = *((uint8_t*)(addr + i));
    }
}
