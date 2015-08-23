#include "RenderEnv.h"
#include <iostream>
extern environment env;

using namespace std;



/*! This function starts the simulation. By Placing 
    the lights and robots on the environment.
  */
void RenderEnv::startSimulation()
{
        Paddle player_1(1);
        Paddle player_2(2);
        Ball b;
        env.registerWith(player_1);
        env.registerWith(player_2);
        env.registerWith(b);
}



