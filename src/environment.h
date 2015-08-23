#include "drawing.h"
#include "Paddle.h"
#include <pthread.h>
#include "Ball.h"
#include <vector>
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
class environment
{
public:

        
        
        environment();
        std::vector<Paddle> paddles; 
        std::vector<Ball> balls;
        void update(int);
        int  getp1Score();
        int  getp2Score();
        void setp1Score(int);
        void setp2Score(int); 
        //initializes robots;
        void init();


        void registerWith(Paddle p);
        void registerWith(Ball b);
        //Getters and setters for window height
        int getWINDOW_HEIGHT();
        int getWINDOW_WIDTH();
        void setWINDOW_HEIGHT(int);
        void setWINDOW_WIDTH(int);
        int keyPressed;
        int keySpecialStates[256];
        void junk();
        





        
private:
        
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;
        double pi;
        int p1Score;
        int p2Score;

        
};
#endif
