#ifndef MAZE_H
#define MAZE_H

#include "main.h"

#define MAZE_SIZE 16
#define EMPTY 0
#define WALL 1
#define VISITED 2

extern uint8_t maze[MAZE_SIZE][MAZE_SIZE];
extern uint8_t robot_x, robot_y;
extern uint8_t robot_dir; // 0: up,1:right,2:down,3:left

void learn_maze(void);
void update_maze_map(void);
int goal_reached(void);

#endif // MAZE_H
