#include "environment.h"
#include "Paddle.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <vector>
using namespace std;
/*!
* default constructor
  initializes private variables
*/
environment::environment()
{
        pi=3.14;
        WINDOW_HEIGHT=648;
        WINDOW_WIDTH=1152;
        Paddle p;
        paddles.push_back(p);
        p1Score=0;
        p2Score=0;
}
/*!
 * Updates the environment based on the elapsed time
 \param int time for elapsed time.
*/
void environment::update(int time)
{
        int key=0;
        if (keySpecialStates[101]==1)
        {
                
                key=101;
        }
        if(keySpecialStates[103]==1)
        {
               
               key=103;
        }
        if(keySpecialStates[119]==1)
        {
                key = 119;
        }
        if(keySpecialStates[115]==1)
        {
                key = 115;
        }
        for(int i=0;i<paddles.size();i++)
        {
                paddles[i].move(time,keySpecialStates);
                
                
        }
        int score =balls[0].move(time,paddles);
        if (score == 1)
        {
                p1Score++;
        }
        if(score == 2)
        {
                p2Score++;
        }
                
        
}

void environment::registerWith(Paddle p)
{
        paddles.push_back(p);
}
void environment::registerWith(Ball b)
{
        balls.push_back(b);
}
/*!
 * returns the width of the environment.No parameters.
 */
int environment::getWINDOW_WIDTH()
{
        return WINDOW_WIDTH;
}

/*!
 * returns the height of the environment.No parameters.
 */
int environment::getWINDOW_HEIGHT()
{
        return WINDOW_HEIGHT;
}

/*!
 * sets the width of the environment.
 \param int width for width of the environment
 */
void environment::setWINDOW_WIDTH(int width)
{
        WINDOW_WIDTH=width;
}

/*!
 * sets the height of the environment.
 \param int height for height of the environment
 */
void environment::setWINDOW_HEIGHT(int height)
{
        WINDOW_HEIGHT=height;
}
void environment::setp1Score(int s)
{
        p1Score=s;
}
void environment::setp2Score(int s)
{
        p2Score=s;
}

int environment::getp1Score()
{
        return p1Score;
}
int environment::getp2Score()
{
        return p2Score;
}
//To ensure pthread gets compiled
void environment::junk() {
  int i;
  i=pthread_getconcurrency();
};
