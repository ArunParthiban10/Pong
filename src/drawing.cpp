#include <math.h>
#include "drawing.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <GL/glui.h>
#else

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glui.h>
#endif

#define PI 3.14f
#include <cstdlib>
#include <iostream>
#include <vector>
#include "environment.h"
#include "Object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
void menu(int id);
environment env;

int previousTime;
int currentTime;
int elapsedTime;
int window;

/*! \file */ 
void drawScore()
{
        
        int middlex=((env.getWINDOW_WIDTH()-20)/2);
        char p1[3];
        char p2[3];
        sprintf(p1,"%d",env.getp1Score());
        sprintf(p2,"%d",env.getp2Score());
        
        glRasterPos2f(middlex+23, 600);
        for(int i=0;i<strlen(p1);i++)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, p1[i]);
        
        glRasterPos2f(middlex-20, 600);
        for(int i=0;i<strlen(p2);i++)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, p2[i]);
        
        
}
void drawBorder()
{
        
        //Bottom border
        glLineWidth(3); 
        glColor3f(255, 255, 255);
        glBegin(GL_LINES);
        glVertex3f(20, 20, 0.0);
        glVertex3f(env.getWINDOW_WIDTH()-20,20, 0);
        
        //Left border
        glLineWidth(3); 
        glColor3f(255, 255, 255);
        glBegin(GL_LINES);
        glVertex3f(20, 20, 0.0);
        glVertex3f(20,env.getWINDOW_HEIGHT()-20, 0);
        
        //Top border
        glLineWidth(3); 
        glColor3f(255, 255, 255);
        glBegin(GL_LINES);
        glVertex3f(20,env.getWINDOW_HEIGHT()-20, 0);
        glVertex3f(env.getWINDOW_WIDTH()-20,env.getWINDOW_HEIGHT()-20, 0);
        
        //Right border
        glLineWidth(3); 
        glColor3f(255, 255, 255);
        glBegin(GL_LINES);
        glVertex3f(env.getWINDOW_WIDTH()-20,env.getWINDOW_HEIGHT()-20, 0);
        glVertex3f(env.getWINDOW_WIDTH()-20,20, 0);
        
        
        //Middle divider
        int middlex=((env.getWINDOW_WIDTH()-20)/2)+10;
        int top = env.getWINDOW_HEIGHT()-20;
        glLineWidth(1); 
        glColor3f(255, 255, 255);
        glBegin(GL_LINES);
        glVertex3f( middlex,top, 0);
        glVertex3f(middlex,20, 0);

        
        
        
        
        
}
void drawPaddle(Paddle p)
{
        
        int x = p.getbottomLeft().x;
        int y = p.getbottomLeft().y;

        glPushMatrix();
        glBegin(GL_QUADS);
        glTranslatef(p.getbottomLeft().x,p.getbottomLeft().y, 0.0f);
        glRotatef(p.getOrientationGLUT(), 0.0f, 0.0f, 1.0f);
        glTranslatef(-x,-y, 0.0f);

        glColor3d(255,0,0);
        glVertex2f(p.getbottomLeft().x,p.getbottomLeft().y);
        glVertex2f(p.gettopLeft().x,p.gettopLeft().y);
        glVertex2f(p.gettopRight().x,p.gettopRight().y);
        glVertex2f(p.getbottomRight().x,p.getbottomRight().y);
        glEnd();
        glPopMatrix();

}
void drawBall(Ball b)
{
        int ball_x = b.getPosition().x;
    	int ball_y = b.getPosition().y;
        int ball_radius= b.getRadius();
        glPushMatrix();
        glTranslatef(b.getPosition().x, b.getPosition().y, 0.0f);
        glRotatef(b.getOrientation(), 0.0f, 0.0f, 1.0f);
        glTranslatef(-ball_x,-ball_y, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(255, 255, 255);
        glVertex2f(ball_x,ball_y);
        for(int i =0; i<=360; i++)
        {
        glVertex2f(ball_x+(ball_radius*cos(i*PI/180)),ball_y+(ball_radius*sin(i*PI/180)));
        }
        glEnd();
        glPopMatrix();
}
void keySpecial ( unsigned char key, int x, int y)
{
	   env.keySpecialStates[key] =1;
        
           
           
}
void keyUp( unsigned char key, int x, int y)
{
        env.keySpecialStates[key] =0;
}
void keySpecialUp(int key,int x ,int y)
{
	   env.keySpecialStates[key]=1;
}
void keySpecialOperations(void)
{

    	if(env.keySpecialStates[GLUT_KEY_UP])
    	{
		    env.keySpecialStates[GLUT_KEY_UP]=0;
        

    	}
    	if(env.keySpecialStates[GLUT_KEY_DOWN])
    	{
    		env.keySpecialStates[GLUT_KEY_DOWN]=0;

    	}
    	if(env.keySpecialStates[GLUT_KEY_LEFT])
    	{
    		env.keySpecialStates[GLUT_KEY_LEFT]=0;

    	}
    	if(env.keySpecialStates[GLUT_KEY_RIGHT])
    	{
    		env.keySpecialStates[GLUT_KEY_RIGHT]=0;

    	}
}
/*! This function is called to update the display
    How it works is the elapsed time is calculated each loop
    and passed into our environment.update method
    */
void display(void)
{
    	// This function is called at each glutMainLoop.
    	// It draws each object each time.
        srand(time(NULL));

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        drawScore();
        drawBorder();
        for (int i=0; i<env.paddles.size();i++)
                drawPaddle(env.paddles[i]);
        for(int i=0; i<env.balls.size();i++)
                drawBall(env.balls[i]);

        
        

        previousTime = currentTime;
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        elapsedTime = currentTime - previousTime;
        
        

        int time = elapsedTime;
        env.update(time);
        keySpecialOperations(); 
        glPopMatrix();
        glutSwapBuffers();

}
/*! This function is called to freeze the dispay, so no objects are moving
    how it works is 0 is passed in to our environment updatge function
*/
void freezeDisplay(void){
        // This function is called at each glutMainLoop.
        // It draws each object each time.
        srand(time(NULL));

        drawScore();
        drawBorder();
        for (int i=0; i<env.paddles.size();i++)
                drawPaddle(env.paddles[i]);
        for(int i=0; i<env.balls.size();i++)
                drawBall(env.balls[i]);
        

        env.update(0);
        keySpecialOperations(); 
        glPopMatrix();
        glutSwapBuffers();
}

/*! This function unfreezes the display 
    It works by passing the display function into glutDisplayFunc
    all time varaibles are also updated every call, as robots will jump without
*/
void unFreeze(void){
    //You must update time, as glutGet returns a time based on the last time it was called
    //and will cause the next display call to cause all objects to jump  across the display 
    previousTime = currentTime;  
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    elapsedTime = currentTime - previousTime;

    glutDisplayFunc(display);
}

/*! This function unfreezes the display 
    It works by passing the display function into glutDisplayFunc
    all time varaibles are also updated every call, as robots will jump without
*/
void freeze(void){
    //You must update time, as glutGet returns a time based on the last time it was called
    //and will cause the next display call to cause all objects to jump  across the display
    previousTime = currentTime;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    elapsedTime = currentTime - previousTime;

    glutDisplayFunc(freezeDisplay);
}
/*! Reshapes the glut displayed window
    \param width represents window width
    \param height represents window height
    */
void reshape(int width, int height)
{
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, width, 0, height);
        glMatrixMode(GL_MODELVIEW);
}

/*! Idle fuction called by glut
    No parameters taken
 */
void idle(void)
{
         if ( glutGetWindow() != window ){
                glutSetWindow(window);
        }

        glutPostRedisplay();
}
/*! 
   This function is called when the couse is clicked.
   * It uses the coordinate and calls lightToggle function in the environment
   *  
*/
void mouseClick(int button, int state, int x, int y)
{
        //button is pressed
        if( button ==0 && state == 1)
        {

        }
}

/*! Call this function to create the glut display
    a submenu is also created using GLUI
    funcitonality includes four buttons: quit, pause, resume, and start
    When a button is clicked, the function that is mapped to it is called
*/
int runGlut()
{
	
    	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    	glutInitWindowSize(env.getWINDOW_WIDTH(),env.getWINDOW_HEIGHT());
        glutInitWindowPosition(500, 500);   

        //Set our window int identifier when you first create the glut window
    	window = glutCreateWindow("PROGRAM");
    	glutDisplayFunc(freezeDisplay);
    	glutReshapeFunc(reshape);
    	glutIdleFunc(idle);
        glutMouseFunc(mouseClick);
        glutKeyboardFunc(keySpecial);
        glutKeyboardUpFunc(keyUp);
        glutSpecialUpFunc(keySpecialUp);

        GLUI *glui = GLUI_Master.create_glui( "GLUI",0,1652,500 );
        GLUI_Panel *newPanel = new GLUI_Panel(glui, "Controls");
        glui->add_button_to_panel(newPanel, "Quit", 0,(GLUI_Update_CB)exit);
        glui->add_button_to_panel(newPanel, "Pause", 1, (GLUI_Update_CB)freeze);
        glui->add_button_to_panel(newPanel, "Resume", 2, (GLUI_Update_CB)unFreeze);
        glui->add_button_to_panel(newPanel, "Start", 3,(GLUI_Update_CB)unFreeze);

        glui->set_main_gfx_window( window );
        GLUI_Master.set_glutIdleFunc( idle );

    	glutMainLoop();
        return EXIT_SUCCESS;
}






