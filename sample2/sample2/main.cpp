#include "GL\glut.h"

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


void SetupRC()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Simple");
	glutDisplayFunc(RenderScene);

	SetupRC();

	glutMainLoop();
}