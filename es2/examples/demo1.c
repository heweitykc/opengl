#include "demo1.h"
 
const float vertexPositions[] = {
    0.75f, 0.75f, 0.0f, 1.0f,
    0.75f, -0.75f, 0.0f, 1.0f,
    -0.75f, -0.75f, 0.0f, 1.0f,
};

const char vshader[] = "in vec4 position;void main(){gl_Position = position;}";
const char fshader[] = "out vec4 outputColor;void main(){outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);}";



static void initVertex()
{
	GLuint positionBufferObject;
    glGenBuffers(1, &positionBufferObject);
    
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);	
}

void glInit(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
}

void glRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
}