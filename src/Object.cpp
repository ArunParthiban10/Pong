#include "Object.h"

/*!
 * Null/default constructor
 \param xPosition for x coordinate
 \param yPosition for y coordinate
 \param radius for radius, in int
 */
Object::Object()
{
	position.x = 0;
	position.y = 0;
	radius = 1;
}

/*!
 * Constructor with three passed parameters
 \param int x for x coordinate
 \param int y for y coordinate
 \param int r for radius
 */
Object::Object(int x, int y, int r)
{
	position.x  = x * SCALAR;
	position.y = y * SCALAR;
	radius = r;
}

/*!
 * Constructor with three passed parameters
 \param int x for x coordinate
 \param int y for y coordinate
 \param int r for radius
 \param char c for color
 */
Object::Object(int x, int y, int r, char c)
{
	position.x  = x * SCALAR;
	position.y = y * SCALAR;
	radius = r;

	//We should ensure that color is only r,g,b,or y if possible
	color = c;
}


/*!
 * sets position for a given object for x and y parameters
 \param int x to set x coordinate
 \param int y to set y coordinate
 */
void Object::setPosition(int x, int y)
{
	position.x = x * SCALAR;
	position.y = y * SCALAR;
}

/*!
 * returns position for a given object
 */
Position Object::getPosition()
{
        Position p;
        p.x = position.x / SCALAR;
        p.y = position.y / SCALAR;
	return p;
}



/*!
 * sets radius for a given object
 \param int r to set radius
 */
void Object::setRadius(int r)
{
	radius = r;
}

/*!
 * returns radius for a given object
 */
int Object::getRadius()
{
	return radius;
}

/*! This function requires one parameters: p.
         \param p the position the object should be oriented towards
 */
void Object::orientTowards(Position p)
{
        
        int deltaY = p.y - position.y;
        int deltaX = p.x - position.x;
        if (deltaX > 0)
        {
                
                float slope = (deltaY) / (deltaX);
                setOrientation(atan(slope) * 180 / PI );
        } 
	else if (deltaX < 0)
        {
                float slope = (deltaY) / (deltaX);
                setOrientation( (atan(slope) * 180 / PI ) + (180) );
        } 
	else
        {
                if (deltaY > 0)
                {
                        setOrientation(90);
                } 
		else
                {
                        setOrientation(270);
                }
        }
        
        
}

/*! This function requires one parameters: p.
         \param p the position the objectis located at
 */
int Object::angleOf(Position p)
{
        
        int deltaY = p.y - position.y;
        int deltaX = p.x - position.x;
        if (deltaX > 0)
        {
                
                float slope = (deltaY) / (deltaX);
                return (atan(slope) * 180 / PI ) - orientation;
        } 
	else if (deltaX < 0)
        {
                float slope = (deltaY) / (deltaX);
                return ( (atan(slope) * 180 / PI ) + (180) ) - orientation;
        } 
	else
        {
                if (deltaY > 0)
                {
                        return (90) - orientation;
                } 
		else
                {
                        return (270) - orientation;
                }
        }
        
        
}


/*!
 * sets color for a given object
 \param char c to set color
 */
void Object::setColor(char c)
{
	color = c;
}

/*!
 * returns color for a given object
 */
char Object::getColor()
{
	return color;
}

void Object::setSpeed (int speed)
{
        /*! This function requires one parameters: speed.
         \param speed is the velocity in pixels per second
         */
        
	//Ensure that speed is never set below 0
	if (speed <= 0)
	{
		pixelsPerSecond = 0;
	}
        else 
        if(speed>55)
                pixelsPerSecond=55;
	else	
	{
		pixelsPerSecond = speed;
	}
}

/*! This function requires no parameters,returns speed in pixelsPerSecond
 */
int Object::getSpeed ()
{
        
        
        return pixelsPerSecond;
} 


/*!
 * returns distance of object and a given position
 \param Position p for calculating the distance
 */
int Object::getDistance(Position p)
{
        int px = p.x;
        int py = p.y;
    	return sqrt( ( (px - getPosition().x) * (px - getPosition().x) )
                + ( (py - getPosition().y) * (py - getPosition().y) ) );

}
void Object::setOrientation (int degrees)
{
        /*! This function requires one parameters: degrees.
         \param degrees the number of degrees for the robots orientation
         */
        
        //Handle cases where input is over 360 degrees
    	orientation = (degrees % 360) ;
 
}
/*!
        Checks to see if the robot has collided with the border
        returns an array of four elements each representing a border
        if there is a collision with the right border, returns 1
        if there is a collision with the upper border, returns 2
        if there is a collision with the left border, returns 3
        if there is a collision with the bottom border, returns 4
        \param x and y are both coordinates of the new position 
	\param *array is a array of robot objects containing the robot, obstacles, and the target
 */

int Object::collisionBorder(int x, int y)
{
        int robot_radius = radius;  //*1.25 for radius with arrow
        
        //right
        if(x+getRadius()>1122 )
	{
                return 1;
	}
        //left
        if(x-getRadius()<30)
	{
                return 2;
	}
        //bottom
        if(y-getRadius()<30)
	{
                return 3;
	}
        //top
        if(y+getRadius()>628)
	{
                return 4;
	}
        
        return 0;
                
   
}
/*!
 * returns true if Is object is colliding with another object
 * returns false otherwise
 \param Object r for object to test collision against.
 */ 
bool Object::collisionObstacle(Object r)
{
        int distance = r.getDistance(getPosition());
        int radius_distance = getRadius()*1.25 + r.radius ; //*1.25 for radius with arrow
	
        if(distance < radius_distance)
        {
                return true;
                
        }
        return false;
}

/*! This function requires one parameter: degrees.
         \param degrees the number of degrees to be rotated clockwise
 */
void Object::rotate (int degrees)
{
	// Use modulus so if we rotate over 360 degrees, it resets to 0
        orientation = (orientation + degrees) % 360;
}

/*! This function requires no parameters,returns Orientation
 */
int Object::getOrientation ()
{
        //Return orientation
        return - 90 + orientation;
}
//translate jumps the object forward a set number of pixels
//ignoring borders and other obstacles

/*! This function requires one parameters: pixels.
 \param pixels the distance to be travelled in pixels
 */
void Object::translate(int pixels)
{


//set radius to specified input, in pixels
        pixels = pixels * SCALAR;
        
        //x and y are used to determine the proper slope
        float y = sin( orientation * PI / 180); //converted orientation to radians from degrees
        float x = cos( orientation * PI / 180);
        position.x = position.x + ( x * pixels);
        position.y = position.y+ ( y * pixels);
        

}
