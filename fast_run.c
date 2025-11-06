#include "fast_run.h"
#include "maze.h"
#include "motor.h"
#include <stdlib.h>
#include <string.h>

/* Simple BFS pathfinder that returns a list of moves
   We'll implement a BFS on the grid maze[][]. Then follow the path.
*/

typedef struct {
    int x,y;
} Node;

#define MAX_QUEUE (MAZE_SIZE*MAZE_SIZE)

static int visited[MAZE_SIZE][MAZE_SIZE];
static Node parent[MAZE_SIZE][MAZE_SIZE];

/* Return 1 if cell is walkable */
static int is_walkable(int x,int y)
{
    if(x<0||x>=MAZE_SIZE||y<0||y>=MAZE_SIZE) return 0;
    if(maze[y][x] == WALL) return 0;
    return 1;
}

static int reconstruct_and_follow(int sx,int sy,int gx,int gy)
{
    // Reconstruct path from goal to start via parent[][] then follow commands
    Node path[MAX_QUEUE];
    int len = 0;
    int cx = gx, cy = gy;
    while (!(cx == sx && cy == sy))
    {
        path[len].x = cx;
        path[len].y = cy;
        len++;
        Node p = parent[cy][cx];
        cx = p.x; cy = p.y;
        if(len > MAX_QUEUE) return 0;
    }
    // path currently goal->start, follow in reverse
    for(int i=len-1;i>=0;i--)
    {
        int nx = path[i].x, ny = path[i].y;
        // decide direction to move, relative to current robot_x/robot_y/robot_dir
        // For simplicity use absolute moves: adjust robot to face needed direction then move_forward()
        int dx = nx - robot_x;
        int dy = ny - robot_y;
        int needed_dir;
        if(dx == 1 && dy == 0) needed_dir = 1;
        else if(dx == -1 && dy == 0) needed_dir = 3;
        else if(dx == 0 && dy == -1) needed_dir = 0;
        else needed_dir = 2;

        // Turn robot to needed_dir
        while(robot_dir != needed_dir)
        {
            // choose shortest turn
            int diff = (needed_dir - robot_dir + 4) % 4;
            if(diff == 1) { turn_right(); robot_dir = (robot_dir+1)%4; }
            else if(diff == 3) { turn_left(); robot_dir = (robot_dir+3)%4; }
            else { turn_right(); robot_dir = (robot_dir+1)%4; } // 180 deg
        }
        // Move forward one cell (should be controlled via encoders for precision)
        move_forward();
        // update robot position
        robot_x = nx; robot_y = ny;
    }
    return 1;
}

void fast_run(void)
{
    // choose start and goal; here we use robot_x, robot_y as start and sample goal
    int sx = robot_x, sy = robot_y;
    int gx = MAZE_SIZE-2, gy = 1; // same as goal in maze.c; tune accordingly

    // BFS queue
    Node q[MAX_QUEUE];
    int qh=0, qt=0;

    memset(visited,0,sizeof(visited));
    parent[sy][sx].x = sx; parent[sy][sx].y = sy;

    q[qt++] = (Node){sx,sy};
    visited[sy][sx] = 1;

    int found = 0;
    while(qh < qt)
    {
        Node cur = q[qh++];
        if(cur.x == gx && cur.y == gy) { found = 1; break; }

        // neighbors: up,right,down,left
        const int dx[4] = {0,1,0,-1};
        const int dy[4] = {-1,0,1,0};
        for(int k=0;k<4;k++)
        {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];
            if(nx<0||nx>=MAZE_SIZE||ny<0||ny>=MAZE_SIZE) continue;
            if(visited[ny][nx]) continue;
            if(!is_walkable(nx,ny)) continue;
            visited[ny][nx] = 1;
            parent[ny][nx].x = cur.x;
            parent[ny][nx].y = cur.y;
            q[qt++] = (Node){nx,ny};
        }
    }

    if(found) {
        reconstruct_and_follow(sx,sy,gx,gy);
    } else {
        // no path
        buzzer_on();
        HAL_Delay(500);
        buzzer_off();
    }
}
