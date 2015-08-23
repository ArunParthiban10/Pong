#include "Paddle.h"
#include <cmath>  /* abs */
#include <math.h>  /* sin */
#include <iostream>
#define PI 3.14
using namespace std;
/*!
 * This is the default constructor. It's sets the player to 1 and 
 * positions the paddle on the right. The speed is set to 60.
 */
Paddle::Paddle()
{
        bottomLeft.x = 1111000;
        bottomLeft.y = 284000;
    
        topLeft.x = 1111000;
        topLeft.y = 364000;
    
        topRight.x = 1122000;
        topRight.y = 364000;
    
        bottomRight.x = 1122000;
        bottomRight.y = 284000;

        speed=60;
        player=1;
        orientation=90;

}
/*!
 * Constructor with one argument. It takes in an interger for the player number.
 * If 1 is passed in, a paddle is drawn on the right of the screen and when 2 is 
 * passed in, a paddle is drawing on the lefy. The speed is set to 60 and orientation
 * is set to 90 by default for both players.
 * \param int playerNumber to indicate the player.
 */
Paddle::Paddle(int playerNumber)
{
        
        if(playerNumber ==1)
        {
                bottomLeft.x = 1111000;
                bottomLeft.y = 284000;
            
                topLeft.x = 1111000;
                topLeft.y = 364000;
            
                topRight.x = 1122000;
                topRight.y = 364000;
            
                bottomRight.x = 1122000;
                bottomRight.y = 284000;
            
                orientation=90; 
                speed=60;
                player=1;
        }
        else if(playerNumber ==2)
        {
                bottomLeft.x = 30000;
                bottomLeft.y = 284000;
            
                topLeft.x = 30000;
                topLeft.y = 364000;
            
                topRight.x = 40000;
                topRight.y = 364000;
            
                bottomRight.x = 40000;
                bottomRight.y = 284000;
            
                orientation=90;
                speed=60;  
                player =2;
        }
}
/*!
 * Constructor with 4 arguments. It takes in four positions and draws a paddle
 * use those values.
 * \param Position bl is the bottom left coordinates of the paddle
 * \param Position tl is the top left coordinates of the paddle
 * \param Position tr is the top right coordinates of the paddle
 * \param Position br is the bottom right coordinates of the paddle
*/
Paddle::Paddle(Position bl,Position tl,Position tr,Position br)
{
        bottomLeft  = bl;
        topLeft     = tl;
        topRight    = tr;
        bottomRight = br;
        orientation=90;
}
/*!
 * This is a getter method that returns the bottom left position of the 
 * paddle. Takes no arguments.
 */
Position Paddle::getbottomLeft()
{
        Position p;
        p.x=bottomLeft.x/SCALAR;
        p.y=bottomLeft.y/SCALAR;
        return p;
}
/*!
 * This is a getter method that returns the top left position of the 
 * paddle. Takes no arguments.
 */
Position Paddle::gettopLeft()
{
        Position p;
        p.x=topLeft.x/SCALAR;
        p.y=topLeft.y/SCALAR;
        return p;
}
/*!
 * This is a getter method that returns the top right position of the 
 * paddle. Takes no arguments.
 */
Position Paddle::gettopRight()
{
        Position p;
        p.x=topRight.x/SCALAR;
        p.y=topRight.y/SCALAR;
        return p;
}
/*!
 * This is a getter method that returns the bottom right position of the 
 * paddle. Takes no arguments.
 */
Position Paddle::getbottomRight()
{
        Position p;
        p.x=bottomRight.x/SCALAR;
        p.y=bottomRight.y/SCALAR;
        return p;
}
/*!
 * This is a setter method that sets the x and y coordinates of the 
 * bottom left corner of the paddle. It takes in 2 arguments.
 * \param int x for the x position
 * \param int y for the y position
 */
void Paddle::setbottomLeft(int x, int y)
{
        bottomLeft.x=x*SCALAR;
        bottomLeft.y=y*SCALAR;
}
/*!
 * This is a setter method that sets the x and y coordinates of the 
 * top left corner of the paddle. It takes in 2 arguments.
 * \param int x for the x position
 * \param int y for the y position
 */
void Paddle::settopLeft(int x,int y)
{
        topLeft.x=x*SCALAR;
        topLeft.y=y*SCALAR;
}
/*!
 * This is a setter method that sets the x and y coordinates of the 
 * top left right of the paddle. It takes in 2 arguments.
 * \param int x for the x position
 * \param int y for the y position
 */
void Paddle::settopRight(int x,int y)
{
        topRight.x=x*SCALAR;
        topRight.y=y*SCALAR;
}
/*!
 * This is a setter method that sets the x and y coordinates of the 
 * b corner of the paddle. It takes in 2 arguments.
 * \param int x for the x position
 * \param int y for the y position
 * */
void Paddle::setbottomRight(int x,int y)
{
        bottomRight.x=x*SCALAR;
        bottomRight.y=y*SCALAR;
}
/*!
 * This fucntins moves the paddle based of the key pressed and the elapsed time.
 * It uses the time passed in along with the speed to calculate the distance 
 * travelled. If the 'i' key is pressed, the right paddle moves up and if 'k' is pressed
 * the right paddle is moved down. If 'w' is pressed, the left paddle moves up and if 's' is pressed
 * the left paddle moves down.
 * \param int time is the elapsed time
 * \param int key[] is the array which holds keys pressed
 */
void Paddle::move(int time, int key[])
{
        int distance = (speed*time)/100;
        
        if(key[105]==1 && player==1)
        {
               orientation=90;
               translate(distance);               
               
        }
        if(key[107]==1 && player==1)
        {
               orientation=-90;
               translate(distance);
        }
        
        if(key[119]==1 && player ==2)
        {
                orientation =90;
                translate(distance);
        }
        
        if(key[115]==1 && player ==2)
        {
                orientation =-90;
                translate(distance);
        }
        if(collisionBorder())
                        translate(-distance);
        
}
void Paddle::translate(int pixels)
{
        pixels = pixels * SCALAR;

        float y = sin( orientation * PI / 180);
        
        
        bottomLeft.y = bottomLeft.y + ( y * pixels);
        
        topLeft.y = topLeft.y + ( y * pixels);
        
        bottomRight.y = bottomRight.y + ( y * pixels);
        
        topRight.y = topRight.y + ( y * pixels);
}
/*!
 * This function checks if the paddles are colliding with the border.
 * Since the paddles only move up or down (Along the y axis), so collisions
 * with top and bottom borders are taken into account. If there is a collision
 * true is retruned and false otherwise.
 * */
bool Paddle::collisionBorder()
{
        if( topLeft.y>628000  || bottomLeft.y<20000)
                return true;
        return false;
}
/*!
This function takes in the coordinates of the ball and 
checks if the paddle is colliding with it. 
If the ball is colliding with the top quarter of the right paddle
the function returns 1. If the paddle is colliding with the middle 
quarter of the right paddle, the function returns 2 and if it's colliding 
with the bottom quarter of the paddle, the function returns 3. Similarly,
the function returns 5,6 and 7 for the top,middle and bottom quarter of the 
left paddle respectively.
\param int x for the x coordinate
\param int y for the y coordinate
*/
int Paddle::collisionBall(int x,int y)
{
        if(getPlayer()==1)
        {
                int bx= getbottomLeft().x;
                int by= getbottomLeft().y;
                
                int tx= gettopLeft().x;
                int ty= gettopLeft().y;
                
                //There is a Collision. +10 for radius
                if(x+10>=bx && (y>by && y<ty))
                {
                        if((ty-y)<20) // Collision with top quarter
                                return 1;
                        else
                        if((y-by)<20) // Collision with middle quarter
                                return 2;
                        else          // Collision with bottom quarter
                                return 3;
                }
        }
        if(getPlayer()==2)
        {
                int bx= getbottomRight().x;
                int by= getbottomRight().y;
                
                int tx= gettopRight().x;
                int ty= gettopRight().y;
                
                if(x-10<=bx && (y>by && y<ty)) //-10 for radius
                {
                        
                        if((ty-y)<20) // collision with top quarter
                                return 5;
                        else
                        if((y-by)<20) // collision with middle quarter
                                return 6;
                        else          // collision with bottom quarter
                                return 7;
                        
                }
        }
        return 4;
}
/*!
 * This function returns the value of the orientation for glut.
 */
int Paddle::getOrientationGLUT()
{
        return orientation;
}
/*!
 * This function retrurns the player. It takes no argumetns. 
 */
int Paddle::getPlayer()
{
        return player;
}

