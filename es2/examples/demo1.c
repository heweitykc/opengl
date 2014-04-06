#include "demo1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define VERTEX_POS_INDEX 0
#define VERTEX_POS_SIZE 6
#define LOG(format, ...) printf(format, __VA_ARGS__)

extern char VSRC_0[];
extern char FSRC_0[];
extern GLfloat vtxs[];
extern GLubyte idxs[];

static char buf[1024];
static GLuint prog;
static Loader loader;

static DWORD current0;
static DWORD current1;

static float width;
static float height;

static void fileTest()
{
	loader.load("Monster32\\drr_01.jpg");
	//LOG("file=%s\n",loader.getbuff());
}

static GLuint compile(const char * source, int type) {
	GLint len;
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderInfoLog(shader, 1024, &len, buf);
	LOG("complile=%s", buf);
	return shader;
}

static void buildShader()
{
	GLint vs,fs,status;
	
	vs = compile(VSRC_0, GL_VERTEX_SHADER);
	fs = compile(FSRC_0, GL_FRAGMENT_SHADER);

	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);

	glBindAttribLocation(prog, VERTEX_POS_INDEX,   "position");
	glBindAttribLocation(prog, VERTEX_POS_INDEX+1, "color");

	glLinkProgram(prog);

	glDetachShader(prog, fs);
	glDeleteShader(fs);
	glDetachShader(prog, vs);
	glDeleteShader(vs);

	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	glGetProgramInfoLog(prog, 1024, NULL, buf);
	LOG("link=%s", buf);
}

static void uploadData()
{
	GLuint vertex_buffer;
	GLuint index_buffer;

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*VERTEX_POS_SIZE*3, vtxs, GL_STATIC_DRAW);

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*3, idxs, GL_STATIC_DRAW);
	
	glVertexAttribPointer(VERTEX_POS_INDEX, 3,   GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, BUFFER_OFFSET(0));
	glVertexAttribPointer(VERTEX_POS_INDEX+1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, BUFFER_OFFSET(12));
}

static void draw()
{
	GLint offsetUnif, perspectiveMatrixUnif;

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glUseProgram(prog);

	float fFrustumScale = 1.0f;
	float fzNear = 0.5f;
	float fzFar = 3.0f;
	float theMatrix[16];
	memset(theMatrix, 0, sizeof(float)*16);

	theMatrix[0] = fFrustumScale/(width/height);
	theMatrix[5] = fFrustumScale;
	theMatrix[10] = (fzFar+fzNear)/(fzNear-fzFar);
	theMatrix[14] = (2*fzFar*fzNear)/(fzNear-fzFar);
	theMatrix[11] = -1.0f;

	offsetUnif = glGetUniformLocation(prog, "offset");
	perspectiveMatrixUnif = glGetUniformLocation(prog, "perspectiveMatrix");
	glUniform2f(offsetUnif, 0.0f, 0.0f);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, theMatrix);

	glEnableVertexAttribArray(VERTEX_POS_INDEX);
	glEnableVertexAttribArray(VERTEX_POS_INDEX+1);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);

	glUseProgram(0);
	glDisableVertexAttribArray(VERTEX_POS_INDEX);
	glDisableVertexAttribArray(VERTEX_POS_INDEX+1);
}

void glInit(GLsizei w, GLsizei h)
{
	width = (float)w;
	height = (float)h;
	glViewport(0, 0, w, h);
	glClearColor(1.0f, 0.5f, 0.5f, 1.0f);

	buildShader();
	uploadData();

	fileTest();
}

void glRender()
{
	current1 = TIME;
	int diff = current1 - current0;
	//LOG("frame time=%d\n", diff);
	current0 = current1;

	draw();
}
