#include "maze.h"
#include "ir_sensor.h"
#include "motor.h"
#include "buzzer_led.h"
#include "flash.h"
#include <string.h>

uint8_t maze[MAZE_SIZE][MAZE_SIZE];
uint8_t robot_x = MAZE_SIZE/2, robot_y = MAZE_SIZE/2; // start roughly giữa
uint8_t robot_dir = 0; // up

/* Simple helper to mark adjacent cell based on robot_dir */
static void mark_adjacent(uint8_t rel_idx, uint8_t val)
{
    // rel_idx: 0 = front, 1 = right, 2 = back, 3 = left
    int dir = (robot_dir + rel_idx) % 4;
    int nx = robot_x, ny = robot_y;
    if(dir == 0) ny--;
    else if(dir == 1) nx++;
    else if(dir == 2) ny++;
    else if(dir == 3) nx--;

    if(nx >= 0 && nx < MAZE_SIZE && ny >= 0 && ny < MAZE_SIZE)
        maze[ny][nx] = val;
}

/* Basic decision: wall-follow (right-hand) skeleton */
static void decide_and_move(void)
{
    // thresholds: define in ir_sensor.c ; here assume read_IR_sensors filled ir_values[]
    // Prioritize: right -> front -> left -> back (right-hand wall-follow)
    read_IR_sensors();
    int front_block = (ir_values[0] > IR_THRESHOLD_FRONT); // sensor mapping depends on wiring
    int right_block = (ir_values[1] > IR_THRESHOLD_SIDE);
    int left_block  = (ir_values[2] > IR_THRESHOLD_SIDE);

    // update map
    mark_adjacent(0, front_block ? WALL : EMPTY);
    mark_adjacent(1, right_block ? WALL : EMPTY);
    mark_adjacent(3, left_block ? WALL : EMPTY);

    if (!right_block) {
        // turn right + move
        turn_right();
        robot_dir = (robot_dir + 1) % 4;
        move_forward();
        // update robot cell
        if(robot_dir == 0) robot_y--;
        else if(robot_dir == 1) robot_x++;
        else if(robot_dir == 2) robot_y++;
        else robot_x--;
    } else if (!front_block) {
        // go straight
        move_forward();
        if(robot_dir == 0) robot_y--;
        else if(robot_dir == 1) robot_x++;
        else if(robot_dir == 2) robot_y++;
        else robot_x--;
    } else if (!left_block) {
        turn_left();
        robot_dir = (robot_dir + 3) % 4;
        move_forward();
        if(robot_dir == 0) robot_y--;
        else if(robot_dir == 1) robot_x++;
        else if(robot_dir == 2) robot_y++;
        else robot_x--;
    } else {
        // dead-end: turn back
        turn_right(); turn_right();
        robot_dir = (robot_dir + 2) % 4;
        move_forward();
        if(robot_dir == 0) robot_y--;
        else if(robot_dir == 1) robot_x++;
        else if(robot_dir == 2) robot_y++;
        else robot_x--;
        buzzer_on();
        HAL_Delay(50);
        buzzer_off();
    }
}

void learn_maze(void)
{
    // init maze unknown
    memset(maze, EMPTY, sizeof(maze));
    maze[robot_y][robot_x] = VISITED;

    // Safety: max steps to avoid infinite loops
    int steps = 0;
    const int MAX_STEPS = 2000;

    while(!goal_reached() && steps < MAX_STEPS)
    {
        update_maze_map();
        decide_and_move();
        maze[robot_y][robot_x] = VISITED;
        steps++;
    }

    // indicate completion
    buzzer_on();
    HAL_Delay(200);
    buzzer_off();
}

/* update_maze_map reads sensors and mark adjacent cells (front/right/left) */
void update_maze_map(void)
{
    read_IR_sensors();
    // assume mapping: ir_values[0]=front, [1]=right, [2]=left, [3]=back (or adjust)
    if(ir_values[0] > IR_THRESHOLD_FRONT) mark_adjacent(0, WALL); else mark_adjacent(0, EMPTY);
    if(ir_values[1] > IR_THRESHOLD_SIDE)  mark_adjacent(1, WALL); else mark_adjacent(1, EMPTY);
    if(ir_values[2] > IR_THRESHOLD_SIDE)  mark_adjacent(3, WALL); else mark_adjacent(3, EMPTY);
    // back optional
}

/* placeholder for goal detection: adjust according to your maze */
int goal_reached(void)
{
    // Example: goal at center top
    if (robot_x == MAZE_SIZE-2 && robot_y == 1) return 1;
    return 0;
}
