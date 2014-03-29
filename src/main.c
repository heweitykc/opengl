#include "GL\glut.h"
#include <math.h>

GLdouble dvect[] = {0.25, 0.5, 0.0};
GLint circle_points = 100;
const float PI=3.1415926;

void render(void)
{
	int i;
	float center=0.5;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);

	
	glBegin(GL_LINE_LOOP);
		glVertex2f(0.25,0.25);
		glVertex2f(0.75,0.25);
		glVertex2f(0.75,0.75);
		glVertex2f(0.25,0.75);
	glEnd();
	
	glColor3f(1.0, 1.0, 1.0);
	printf("sin=%.1f\n", sin(PI/2));
	glBegin(GL_LINE_LOOP);
	for(i=0;i<circle_points;i++){
		GLdouble angle = 2*PI*i/circle_points;
		glVertex2f(center+cos(angle)*0.5, center+sin(angle)*0.5);
	}
	glEnd();
	
	glFlush();
}

void setup()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void test()
{
	double num = 2341112.89700112;
	printf("test=%0.10f", num);
}

void main()
{
	//test();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Simple");
	glutPositionWindow(100,100);
	glutDisplayFunc(render);
	setup();
	glutMainLoop();
}
