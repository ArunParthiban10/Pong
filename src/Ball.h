#ifndef BALL_H
#define BALL_H
#include "Object.h"
#include "Paddle.h"
#include <vector>
#include <unistd.h>
//Inherits position and radius variables, along with
//methods set/getposition and getDistance from Object class

class Ball : public Object 
{

public:

        //Constructors for Robot, includes default constructor
        Ball ();
        int move(int,std::vector<Paddle>);//

        

};
#endif
