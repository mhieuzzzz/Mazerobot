#include "maze.h"
#include "flash.h"
#include "motor.h"
#include "ir_sensor.h"
#include "fast_run.h"
#include "main.h"

#define MAZE_SIZE 16

Cell maze[MAZE_SIZE][MAZE_SIZE];
uint8_t current_x = 0, current_y = 0;
uint8_t direction = 0; // 0: North, 1: East, 2: South, 3: West

void maze_init(void)
{
    for (int y = 0; y < MAZE_SIZE; y++)
        for (int x = 0; x < MAZE_SIZE; x++)
        {
            maze[y][x].wall_north = 0;
            maze[y][x].wall_east  = 0;
            maze[y][x].wall_south = 0;
            maze[y][x].wall_west  = 0;
            maze[y][x].visited    = 0;
        }
}

void learn_maze(void)
{
    maze_init();
    current_x = 0;
    current_y = 0;
    direction = 0; // bắt đầu hướng Bắc

    while (1)
    {
        read_ir_sensors();
        maze[current_y][current_x].visited = 1;

        // Giả lập đọc tường (thực tế đọc giá trị ADC IR)
        if (front_wall_detected())  maze[current_y][current_x].wall_north = 1;
        if (left_wall_detected())   maze[current_y][current_x].wall_west = 1;
        if (right_wall_detected())  maze[current_y][current_x].wall_east = 1;

        // di chuyển sang ô mới
        motor_forward(50);
        HAL_Delay(500);
        motor_stop();

        current_y++;
        if (current_y >= MAZE_SIZE - 1) break; // dừng học đơn giản

        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // debug LED
    }

    save_maze_to_flash();
}

void save_maze_to_flash(void)
{
    HAL_StatusTypeDef status;
    status = Flash_Erase_Sector(FLASH_SECTOR_USED);
    if (status == HAL_OK)
    {
        Flash_Write_Array(FLASH_SECTOR_ADDR, (uint8_t *)maze, sizeof(maze));
    }
}

void load_maze_from_flash(void)
{
    Flash_Read_Array(FLASH_SECTOR_ADDR, (uint8_t *)maze, sizeof(maze));
}
