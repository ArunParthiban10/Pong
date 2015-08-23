#include "RenderEnv.h"
#include <cstdlib>


#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

int main(int argc, char** argv)
{

        
        RenderEnv newEnv;
        newEnv.startSimulation();
        glutInit(&argc, argv);
        runGlut();
        
}
