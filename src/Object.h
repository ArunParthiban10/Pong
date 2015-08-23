#include <cmath>  /* abs */
#include <math.h>  /* sin */
#include "Position.h"
#ifndef OBJECT_H
#define OBJECT_H
/*!
 * Object class, everything inherits from this
 */
#define PI 3.14159265
class Object 
{
public:
	/*!
         * Variables for position and radius and color
        */
        Position position;
        int orientation;
        int radius;
        //Color could be 'R','G','B'?
        int pixelsPerSecond;
        static const int SCALAR = 1000;

        /*!
         * Default and other constructors
         */       
        Object ();
        //xpos,ypos,radius
        Object (int, int, int);
        //xpos,ypos,radius,color
        Object (int, int, int, char);

        /*!
         * Methods for functionality
         */       
        void setPosition (int, int);
        Position getPosition();

        void setOrientation (int);
        int getOrientation ();

        void setRadius(int);
        int getRadius();

	int collisionBorder(int, int);

        //Set and get speed, in pixelsPerSecond
        void setSpeed (int);
        int getSpeed (); 

        void setColor(char);
        char getColor();

        bool collisionObstacle(Object r);
        int getDistance(Position);
        
        void orientTowards(Position);
        int angleOf(Position);

        //Rotates the robot by the specified input, in degrees
        void rotate (int);
        void translate (int);

protected:
	char color;

};
#endif
