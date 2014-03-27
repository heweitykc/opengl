#include "GL\glut.h"

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.25,0.25,0.0);
		glVertex3f(0.75,0.25,0.0);
		glVertex3f(0.75,0.75,0.0);
		glVertex3f(0.25,0.75,0.0);
	glEnd();
	glFlush();
}


void SetupRC()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Simple");
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}