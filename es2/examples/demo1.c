#include "demo1.h"

void glInit(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void glRender()
{
	glClear(GL_COLOR_BUFFER_BIT);

}