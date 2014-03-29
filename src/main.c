#include "GL\glut.h"
#include <math.h>

GLdouble dvect[] = {0.25, 0.5, 0.0};
GLint circle_points = 100;
const float PI=3.1415926;
GLfloat xangle = 0;

void vertexRender()
{
	static GLfloat data[] = {
		5,   5, 5,  1, 0, 1,
		5,  5, -5,  0, 1, 1,
		-5, 5, -5,  1, 1, 1,

		-5, 5, 5,  1, 0, 1,
		5,  -5, 5,  0, 1, 1,
		-5, -5, 5,  1, 1, 1,

		-5, -5, -5,  1, 0, 1,
		5,  -5, -5,  0, 1, 1
	};
	static GLubyte index0[] =  {
		0,1,2,	0,2,3,
		0,7,1,	0,4,7,
		1,7,6,	1,6,2,
		2,6,5,	2,3,5,
		0,5,4,	0,3,5,
		5,6,7,	4,5,7
	};
	
	xangle+=0.1;
	glRotatef(xangle,0,0,0);
	
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 6*sizeof(GLfloat), data);
	glColorPointer(3,  GL_FLOAT, 6*sizeof(GLfloat), &data[3]);

	glDrawElements(GL_TRIANGLES, sizeof(index0), GL_UNSIGNED_BYTE, index0);
}

void render(void)
{
	int i;
	float center=0.5;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(1);

	//»­¾ØÐÎ
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(0.25,0.25);
		glVertex2f(0.75,0.25);
		glVertex2f(0.75,0.75);
		glVertex2f(0.25,0.75);
	glEnd();

	//»­Ô²
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<circle_points;i++){
		GLdouble angle = 2*PI*i/circle_points;
		glVertex2f(center+cos(angle)*0.5, center+sin(angle)*0.5);
	}
	glEnd();

	//¶¥µã»æÖÆ
	vertexRender();
	
	glFlush();
}

void setup()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -111.0, 111.0);
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Simple");
	glutPositionWindow(100,100);
	glutDisplayFunc(render);
	setup();
	glutMainLoop();
}
