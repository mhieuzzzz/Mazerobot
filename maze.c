#include "maze.h"
#include "motor.h"
#include "ir_sensor.h"
#include "flash.h"
#include "main.h"

#define MAZE_SIZE 16

Cell maze[MAZE_SIZE][MAZE_SIZE];
uint8_t current_x = 0, current_y = 0;
uint8_t direction = 0; // 0: North, 1: East, 2: South, 3: West

void learn_maze(void)
{
    maze_init();
    current_x = 0;
    current_y = 0;
    direction = 0;

    while (1)
    {
        // Đọc cảm biến
        read_ir_sensors();

        // Ghi nhận tường theo hướng hiện tại
        if (front_wall_detected())  maze[current_y][current_x].wall_north = 1;
        if (left_wall_detected())   maze[current_y][current_x].wall_west = 1;
        if (right_wall_detected())  maze[current_y][current_x].wall_east = 1;

        maze[current_y][current_x].visited = 1;

        // Debug LED
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(100);

        // Nếu phía trước không có tường → tiến tới
        if (!front_wall_detected())
        {
            motor_forward(50);
            HAL_Delay(600);
            motor_stop();

            if (direction == 0) current_y++;
            else if (direction == 1) current_x++;
            else if (direction == 2 && current_y > 0) current_y--;
            else if (direction == 3 && current_x > 0) current_x--;
        }
        else
        {
            // Gặp tường: rẽ phải nếu có thể, nếu không thì trái
            if (!right_wall_detected())
            {
                motor_turn_right(50);
                HAL_Delay(400);
                motor_stop();
                direction = (direction + 1) % 4;
            }
            else if (!left_wall_detected())
            {
                motor_turn_left(50);
                HAL_Delay(400);
                motor_stop();
                direction = (direction + 3) % 4;
            }
            else
            {
                // Bế tắc -> quay đầu
                motor_turn_left(50);
                HAL_Delay(800);
                motor_stop();
                direction = (direction + 2) % 4;
            }
        }

        // Dừng nếu đã khám phá hết một đoạn (ví dụ 8x8)
        if (current_x >= 8 && current_y >= 8)
            break;
    }

    // Lưu map vào Flash
    save_maze_to_flash();

    // Báo hoàn thành
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_Delay(300);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
}
