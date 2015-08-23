#include "Position.h"
#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
public:
	Paddle ();
        Paddle (int);
        
        Paddle(Position,Position,Position,Position);
        
        Position getbottomLeft();
        Position gettopLeft();
        Position gettopRight();
        Position getbottomRight();
                        
        void     setbottomLeft(int, int);
        void     settopLeft(int,int);
        void     settopRight(int,int);
        void     setbottomRight(int,int);
        void     move(int,int[]);
        void     translate(int);
        int      getOrientationGLUT();
        bool     collisionBorder();
        int     collisionBall(int,int);
        int      getPlayer();

private:
        Position bottomLeft;
        Position topLeft;
        Position topRight;
        Position bottomRight;
        int      speed;
        int      player;
        int      orientation;
        static const int SCALAR=1000;
};
#endif
