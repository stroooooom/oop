#include <GLUT/glut.h> 

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double x;
	double y;
	double z;
} Point;

Point p1 = {0, 0, 0};
Point p2 = {0, 20, 0};
Point p3 = {20, 20, 0};
Point p4 = {20, 0, 0};

Point p5 = {0, 0, 10};
Point p6 = {0, 20, 10};
Point p7 = {20, 20, 10};
Point p8 = {20, 0, 10};

Point points[] = {p1, p2, p3, p4};

double D = 2, W = 5, H = 3;


int draw_line(Point p0, Point p1)
{
	double x0 = p0.x, y0 = p0.y, z0 = p0.z;
	double x1 = p1.x, y1 = p1.y, z1 = p1.z;
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0); 
		glVertex2f(W*x0/(z0+D), H*y0/(z0+D)); 
		glVertex2f(W*x1/(z1+D), H*y1/(z1+D));
	glEnd();
}

void display() 
{ 
	printf("\n::display");
	glClear(GL_COLOR_BUFFER_BIT);   

	draw_line(p1, p2);
	draw_line(p2, p3);
	draw_line(p3, p4);
	draw_line(p4, p1);

	// draw_line(p5, p6);
	// draw_line(p6, p7);
	// draw_line(p7, p8);
	// draw_line(p8, p5);

	draw_line(p1, p5);
	draw_line(p2, p6);
	draw_line(p3, p7);
	draw_line(p4, p8);

	glFlush();    
} 

void processNormalKeys(unsigned char key, int xx, int yy)
{
	printf("\nCurrent pressed key = %c (%d)", key, key);
    if (key == 113) //  <Q>
    {
    	printf("\nExiting program...\n");
    	exit(0);
    }
}

void processArrowKeys(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT:
			printf("\nLeft key pressed");
			p1.x -= 1;
			p2.x -= 1;
			p3.x -= 1;
			p4.x -= 1;
			break;
		case GLUT_KEY_RIGHT:
			printf("\nRight key pressed");
			p1.x += 1;
			p2.x += 1;
			p3.x += 1;
			p4.x += 1;
			break;
		case GLUT_KEY_UP:
			//
			break;
		case GLUT_KEY_DOWN:
			//
			break;
		}
		display();
}

int main(int argc, char **argv) 
{
	setbuf(stdout, NULL);

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(240, 240); 
	glutInitWindowPosition(100, 300); 
	glutCreateWindow("OOP 1");

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processArrowKeys);

	gluOrtho2D(-80.0,80.0,-80.0,80.0);
//	glClearColor(1.0, 1.0, 1.0, 1.0); 
//	glMatrixMode(GL_PROJECTION); //	glLoadIdentity(); 
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}