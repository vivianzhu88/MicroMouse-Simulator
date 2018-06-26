
#include "micromouseserver.h"
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
int numOfTimesLeft(int dir, int x, int y, int (&map)[20][20])
{
    myTurnLeft(&dir);
    myMoveForward(&dir, &x, &y);
    return map[x][y];
}
int numOfTimesForward(int dir, int x, int y, int (&map)[20][20])
{
    myMoveForward(&dir, &x, &y);
    return map[x][y];
}
int numOfTimesRight(int dir, int x, int y, int (&map)[20][20])
{
    myTurnRight(&dir);
    myMoveForward(&dir, &x, &y);
    return map[x][y];
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
    //static int i=0;
    static int map [20][20] = {0};
    static int x=0, y=0, dir=0;
    static int Lcount, Rcount;

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
    }

    //End or continue
    if (Lcount == 3 || Rcount == 3)
    {
        foundFinish();
        memset(map, 0, sizeof(map));
        dir=0;
        x=0;
        y=0;
    }
    else
    {
        myMoveForward(&dir, &x, &y);
        moveForward();
        map[x][y] += 1;
    }

}
