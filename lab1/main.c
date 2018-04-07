#include <GLUT/glut.h> 

#include <stdio.h>
#include <stdlib.h>

#include "load_object.h"

#define KEY_SPACE 32
#define KEY_Q 113

typedef enum {
	TRANSPOSE,
	SCALE,
	ROTATE,
} Command;

static Object *object = NULL;
static Command current_command = TRANSPOSE;
static Axis current_axis = X;

void draw_line(Vertex p0, Vertex p1)
{
	double x0 = p0.x, y0 = p0.y, z0 = p0.z;
	double x1 = p1.x, y1 = p1.y, z1 = p1.z;
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0); 
		glVertex2f(x0, y0); 
		glVertex2f(x1, y1); 
	glEnd();
}

void display_command()
{
	glColor3f(1, 1, 1);
	char *cmd = NULL;
	int cnt = 0;
	switch (current_command) {
		case TRANSPOSE:
			cmd = "TRANSPOSE";
			cnt = 9;
			break;
		case SCALE:
			cmd = "SCALE";
			cnt = 5;
			break;
		case ROTATE:
			cmd = "ROTATE";
			cnt = 6;
			break;
	}
	for (int i = 0; i < cnt; i++)
	{
		glRasterPos2f(-0.8+0.2*i, 4);
    	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cmd[i]);
    }

}

void display() 
{ 
	glClear(GL_COLOR_BUFFER_BIT);   

	display_command();
	render_object(object, draw_line);

	glFlush();    
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == KEY_SPACE)
    {
    	if (current_command == TRANSPOSE) { current_command = SCALE; }
    	else if (current_command == SCALE) { current_command = ROTATE; }
    	else if (current_command == ROTATE) { current_command = TRANSPOSE; }
    //	printf("\nCurrent_command changed to %d", current_command);
    	display();
    }
    else if (key == KEY_Q)
    {
    	printf("\nExiting program...\n");
    	exit(0);
    }
}

void processArrowKeys(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT:
			if (current_command == TRANSPOSE) { transpose_object(object, -1, 0, 0); }
			if (current_command == SCALE) { scale_object(object, 0.9, 1, 1); }
			if (current_command == ROTATE) { rotate_object(object, -10, Y); }
			break;
		case GLUT_KEY_RIGHT:
			if (current_command == TRANSPOSE) { transpose_object(object, 1, 0, 0); }
			if (current_command == SCALE) { scale_object(object, 1.1, 1, 1); }
			if (current_command == ROTATE) { rotate_object(object, 10, Y); }
			break;
		case GLUT_KEY_UP:
			if (current_command == TRANSPOSE) { transpose_object(object, 0, 1, 0); }
			if (current_command == SCALE) { scale_object(object, 1, 1.1, 1); }
			if (current_command == ROTATE) { rotate_object(object, 10, X); }
			break;
		case GLUT_KEY_DOWN:
			if (current_command == TRANSPOSE) { transpose_object(object, 0, -1, 0); }
			if (current_command == SCALE) { scale_object(object, 1, 0.9, 1); }
			if (current_command == ROTATE) { rotate_object(object, -10, X); }
			break;
		}
		display();
}

void init_window(int *argc, char **argv, int weight, int height, char *window_name)
{
	setbuf(stdout, NULL);

	glutInit(argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(weight, height);
	glutCreateWindow(window_name);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processArrowKeys);

	gluOrtho2D(-5.0,5.0,-5.0,5.0);

	glutDisplayFunc(display);
	glutMainLoop();
}

int main(int argc, char **argv)  
{
	int err = load_object("cube2.txt", &object);
	if (err != NO_ERROR) { return err; }

	init_window(&argc, argv, 500, 500, "OOP 1");

	return 0;
}