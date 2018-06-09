
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
    else x -= 1;

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
    if(x>19)
        x=19;
    else if(x<0)
        x=0;
    else if(y<0)
        y=0;
    else if(y>=20)
        y=19;

    return map[x][y];
}
int numOfTimesForward(int dir, int x, int y, int (&map)[20][20])
{
    myMoveForward(&dir, &x, &y);
    if(x>19)
        x=19;
    else if(x<0)
        x=0;
    else if(y<0)
        y=0;
    else if(y>=20)
        y=19;

    return map[x][y];
}
int numOfTimesRight(int dir, int x, int y, int (&map)[20][20])
{
    myTurnRight(&dir);
    myMoveForward(&dir, &x, &y);
    if(x>19)
        x=19;
    else if(x<0)
        x=0;
    else if(y<0)
        y=0;
    else if(y>=20)
        y=19;

    return map[x][y];
}


void microMouseServer::studentAI()
{
    /*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
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
    static int i=0;
    static int map [20][20] = {0};
    static int x=0, y=0, dir=0;

    if (!isWallLeft())
    {
        if (!isWallForward())
        {
            if (numOfTimesLeft(&dir, &x, &y, &map) <= numOfTimesForward(&dir, &x, &y, &map))
                myTurnLeft(&dir);
                turnLeft();
        }

        myTurnLeft(&dir);
        turnLeft();
    }
    else if (!isWallRight())
    {
        myTurnRight(&dir);
        turnRight();
    }
    else if(isWallForward())
    {
        myTurnRight(&dir);
        myTurnRight(&dir);
        turnRight();
        turnRight();
    }
    myMoveForward(&dir, &x, &y);
    moveForward();

    if (i==0 && !isWallLeft() && !isWallForward() && isWallRight() )
        i=1;
    else if (i==0 && isWallLeft() && !isWallForward() && !isWallRight() )
        i=6;
    else if ((i==1 || i==2 || i==3 || i==6 || i==7 || i==8) && isWallLeft() && isWallForward() && !isWallRight() )
        i++;
    else if ((i==4 || i==9) && !isWallLeft() && isWallForward() && !isWallRight() )
        foundFinish();
    else i=0;


}
