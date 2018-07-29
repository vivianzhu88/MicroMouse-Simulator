#include "micromouseserver.h"
#include <QQueue>
using namespace std;

//keep track of direction

typedef struct node
{
    int timesVisited;
    bool hasQ, isStart, isEnd;
    struct node *previous, *north, *south, *east, *west;
}NODE;

void myTurnLeft(int *dir)
{
    if (*dir==0)
        *dir = 3;
    else *dir-=1;
}

void myMoveForward(int *dir, int *x, int *y)
{
    if (*dir==0)
        *y += 1;
    else if (*dir==1)
        *x += 1;
    else if (*dir==2)
        *y -= 1;
    else *x -= 1;
}

void myTurnRight(int *dir)
{
    if (*dir==3)
        *dir = 0;
    else *dir+=1;
}

//Keeps track of how many times mouse has been at certain square
int numOfTimesLeft(int dir, int x, int y, NODE (&map)[20][20])
{
    myTurnLeft(&dir);
    myMoveForward(&dir, &x, &y);
    return map[x][y].timesVisited;
}

int numOfTimesForward(int dir, int x, int y, NODE (&map)[20][20])
{
    myMoveForward(&dir, &x, &y);
    return map[x][y].timesVisited;
}

int numOfTimesRight(int dir, int x, int y, NODE (&map)[20][20])
{
    myTurnRight(&dir);
    myMoveForward(&dir, &x, &y);
    return map[x][y].timesVisited;
}

void linkCell(int dir, int x, int y, NODE (&map)[20][20])
{
    if(dir==0)
        map[x][y].north = &map[x][y+1];
    else if(dir==1)
        map[x][y].east = &map[x+1][y];
    else if(dir==2)
        map[x][y].south = &map[x][y-1];
    else
        map[x][y].west = &map[x-1][y];
}

void findShortestPath(NODE (&map)[20][20])
{

    QQueue<NODE*> queue;
    int x=0, y=0;
    NODE *holder;
    bool loop =false;

    if (map[x][y].north)
    {
        if(!map[x][y].north->hasQ)
        {
            queue.enqueue(map[x][y].north);
            map[x][y].north->hasQ = true;
            map[x][y].north->previous = &(map[x][y]);
        }
    }
    if (map[x][y].south)
    {
        if (!map[x][y].south->hasQ)
        {
            queue.enqueue(map[x][y].south);
            map[x][y].south->hasQ = true;
            map[x][y].south->previous = &map[x][y];
        }
    }
    if (map[x][y].east)
    {
        if(!map[x][y].east->hasQ)
        {
            queue.enqueue(map[x][y].east);
            map[x][y].east->hasQ = true;
            map[x][y].east->previous = &map[x][y];
        }
    }
    if (map[x][y].west)
    {
        if(!map[x][y].west->hasQ)
        {
            queue.enqueue(map[x][y].west);
            map[x][y].west->hasQ = true;
            map[x][y].west->previous = &map[x][y];
        }
    }

    // find path to end
    while(!loop)
    {
        holder = queue.dequeue();

        loop = holder->isEnd;

        // queues only if hasQ is false
        if (holder->north)
        {
            if(!holder->north->hasQ)
            {
                queue.enqueue(holder->north);
                holder->north->hasQ = true;
                holder->north->previous = holder;
            }
        }
        if (holder->south)
        {
            if(!holder->south->hasQ)
            {
                queue.enqueue(holder->south);
                holder->south->hasQ = true;
                holder->south->previous = holder;
            }
        }
        if (holder->east)
        {
            if(!holder->east->hasQ)
            {
                queue.enqueue(holder->east);
                holder->east->hasQ = true;
                holder->east->previous = holder;
            }
        }
        if (holder->west)
        {
            if(!holder->west->hasQ)
            {
                queue.enqueue(holder->west);
                holder->west->hasQ = true;
                holder->west->previous = holder;
            }
        }
    }

    // set timesVisited of nodes in shortest path to 0
    while(!holder->isStart)
    {
        holder->timesVisited = 0;
        holder = holder->previous;
    }

}

void microMouseServer::studentAI()
{

 /* The following are the eight functions that you can call. Feel free to create your own fuctions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *bool moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);
*/

    static NODE map[20][20];
    static int x=0, y=0, dir=0;
    static int Lcount, Rcount;
    static bool hasRunBefore = false;

    if(!hasRunBefore)
    {
       //stuff here only happens once
        memset(map, 0, sizeof(map));
        map[0][0].isStart = true;
        hasRunBefore = true;
    }

    for(int i=0; i<4; i++){
        if(!isWallForward()){
            linkCell(dir, x, y, map);
        }
        turnRight();
        myTurnRight(&dir);
    }

    //Making way through maze
    if(!isWallLeft() &&
       !(!isWallForward() && numOfTimesLeft(dir, x, y, map) > numOfTimesForward(dir, x, y, map)) &&
       !(!isWallRight() && numOfTimesLeft(dir, x, y, map) > numOfTimesRight(dir, x, y, map))
            )
    {
        turnLeft();
        myTurnLeft(&dir);
        Lcount += 1;
        Rcount = 0;
    }
    else if (!isWallForward() &&
         !(!isWallLeft() && numOfTimesForward(dir, x, y, map) > numOfTimesLeft(dir, x, y, map)) &&
         !(!isWallRight() && numOfTimesForward(dir, x, y, map) > numOfTimesRight(dir, x, y, map))
          )
    {
        Lcount = 0;
        Rcount = 0;
    }
    else if (!isWallRight() &&
         !(!isWallLeft() && numOfTimesRight(dir, x, y, map) > numOfTimesLeft(dir, x, y, map)) &&
         !(!isWallForward() && numOfTimesRight(dir, x, y, map) > numOfTimesForward(dir, x, y, map))
          )
    {
        turnRight();
        myTurnRight(&dir);
        Lcount = 0;
        Rcount += 1;
    }
    else
    {
        turnRight();
        turnRight();
        myTurnRight(&dir);
        myTurnRight(&dir);
        Lcount = 0;
        Rcount = 0;
    }

    //End or continue
    if (Lcount == 3 || Rcount == 3)
    {
        foundFinish();
        map[x][y].isEnd = true;
        findShortestPath(map);
        /*memset(map, 0, sizeof(map));
        dir=0;
        x=0;
        y=0;*/
    }
    else
    {
        myMoveForward(&dir, &x, &y);
        moveForward();
        map[x][y].timesVisited += 1;
    }

}
