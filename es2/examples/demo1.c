#include "demo1.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#define VERTEX_POS_INDEX 0

const char vsrc[] =
		"attribute vec4 position; void main(){ gl_Position = position;}";
const char fsrc[] =
		"void main(){ gl_FragColor = vec4(1.0,1.0,1.0,1.0);}";

const GLfloat vtxs[] = {
		0.0f,0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f
};
const GLubyte idxs[] = {0, 1, 2};
static char buf[1024];

GLfloat _xAngle = 0.0f;
GLfloat _yAngle = 0.0f;
GLuint prog;

static GLuint compile(const char * source, int type) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	GLint len;
	glGetShaderInfoLog(shader, 1024, &len, buf);
	printf("complile=%s", buf);
	return shader;
}

static void buildShader()
{
	GLint vs,fs,status;
	
	vs = compile(vsrc, GL_VERTEX_SHADER);
	fs = compile(fsrc, GL_FRAGMENT_SHADER);

	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);

	glBindAttribLocation(prog, VERTEX_POS_INDEX, "position");

	glLinkProgram(prog);

	glDetachShader(prog, fs);
	glDeleteShader(fs);
	glDetachShader(prog, vs);
	glDeleteShader(vs);

	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	glGetProgramInfoLog(prog, 1024, NULL, buf);
	printf("link=%s", buf);
}

static void draw()
{
	GLuint vertex_buffer;
	GLuint index_buffer;
	GLint additive;

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glUseProgram(prog);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 4*3*3, vtxs, GL_STATIC_DRAW);

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3, idxs, GL_STATIC_DRAW);
	
	glVertexAttribPointer(VERTEX_POS_INDEX, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));	
	glEnableVertexAttribArray(VERTEX_POS_INDEX);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);

	glUseProgram(0);
	glDisableVertexAttribArray(VERTEX_POS_INDEX);
}

static void draw2()
{
	GLint additive;

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(prog);

	glVertexAttribPointer(VERTEX_POS_INDEX, 3, GL_FLOAT, GL_FALSE, 0, vtxs);	
	glEnableVertexAttribArray(VERTEX_POS_INDEX);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void glInit(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glClearColor(1.0f, 0.5f, 0.5f, 1.0f);

	buildShader();
}

void glRender()
{
	draw();
}
