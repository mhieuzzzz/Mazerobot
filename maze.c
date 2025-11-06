#include "maze.h"
#include "ir_sensor.h"
#include "motor.h"
#include "buzzer_led.h"

uint8_t maze[MAZE_SIZE][MAZE_SIZE];
uint8_t robot_x = 0, robot_y = 0;
uint8_t robot_dir = 0; // 0: up,1:right,2:down,3:left

void learn_maze(void)
{
    // Skeleton wall-follow hoặc flood-fill
    while(!goal_reached())
    {
        read_IR_sensors();
        update_maze_map();
        // TODO: quyết định di chuyển
        move_forward();
    }
}

void update_maze_map(void)
{
    // Cập nhật maze[x][y] dựa trên ir_values
    // TODO: implement chi tiết
}

int goal_reached(void)
{
    // TODO: kiểm tra robot tới đích
    return 0;
}
