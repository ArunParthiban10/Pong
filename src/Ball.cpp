#include "Ball.h"
#include "Object.h"
#include <iostream>
#define PI 3.14
using namespace std;
/*!
Default constructor. Sets the position of the ball to 
576,324 which is the center of the screen. The radius is 
set to 10 and speed to 40. Initial orientation is 10
*/
Ball::Ball()
{
        setPosition(576,324);
        setRadius(10);
        setOrientation(10);
        setSpeed(40);
}
/*!
This function moves the ball using the time and speed to calculate distance.
It takes in two arguments- time and a vector of Paddles. If the ball hits 
the top or the bottom borders, it bounces off. If the ball goes out of the left
border of the right border, it re-spawns in the center. If the ball hits the top quarter
of the paddles, it bounces up and bounces down if it hits the bottom of the paddle.
\param int time for the elapsed time
\param vector<Paddles> for the paddles vector
*/
int Ball::move(int time,vector<Paddle> paddles)
{
        
        
        int distance =(getSpeed() * time)/100;
        int collide = collisionBorder(getPosition().x,getPosition().y);
        for(int i=0; i<paddles.size();i++)
        {
               int pcollide =  paddles[i].collisionBall(getPosition().x,getPosition().y);
               if( pcollide<4)
                {
                        
                        
                        if(pcollide==1)
                        {
                                orientation=150;
                                
                        }
                        else
                        if(pcollide==2)
                        {
                                orientation=240;
                               
                        }
                        else
                        {
                                orientation+=181;
                               
                        }
                                
                        translate(distance);
                        setSpeed(getSpeed()+5);
                        
                        
                }
                if(pcollide >4)
                {
                        if(pcollide==5)
                        {
                                orientation=70;
                                
                        }
                        else
                        if(pcollide==6)
                        {
                                orientation=310;
                                
                        }
                        else
                        {
                                orientation-=181;
                                
                        }
                                
                        translate(distance);
                        setSpeed(getSpeed()+5);
                        
                       
                }
                
        }
        if(collide==0)
        {
                
                translate(distance);
        }
        else
        {       //right
                if(collide==1)
                {
                        
                        setPosition(576,324);
                        translate(distance);
                       
                        return 2;
                        
                }
                if(collide==2)//left
                {
                        
                        setPosition(576,324);
                        translate(distance);
                        
                        return 1;
                }
                
                if(collide ==3)//bottom
                {
                        if(orientation%360>270 || orientation%360<90)
                                orientation=50;
                        else
                             orientation=130;   
                        
                        translate(distance);
                         
                }
                if(collide ==4)//top
                {
                        
                        
                        if(orientation%360<=90 || orientation%360>270 )
                                orientation=320;
                        else
                                orientation=230;
                        translate(distance);
                         
                }
                
                
        }
        
}





































































