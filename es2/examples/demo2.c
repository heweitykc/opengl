#include "demo2.h"
#include "shadersrc.h"
#include "submesh.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define VERTEX_POS_INDEX 0
#define VERTEX_POS_SIZE 6

static GLuint prog;
static Loader loader;

static DWORD current0;
static DWORD current1;

static float width;
static float height;

static float fFrustumScale = 1.0f;
static float fzNear = 0.5f;
static float fzFar = 3.0f;
static float theMatrix[16];
static struct submesh *mesh0=NULL;
static GLfloat vtxs[] = {
		-0.5f,0.5f,-2.0f,	  1.0f,0.0f,0.0f,
		-0.5f,-0.5f,-2.0f,	  0.0f,1.0f,0.0f,
		0.5f,-0.5f,-2.0f,     0.0f,0.0f,1.0f,
		0.5f,0.5f,-2.0f,      1.0f,1.0f,1.0f
};
static GLubyte idxs[] = {0, 1, 2, 0, 2, 3};

static void fileTest()
{
	loader.load("Monster32\\drr_01.jpg");
	//LOG("file=%s\n",loader.getbuff());
}

static void uploadData()
{
	GLuint vbo;
	GLuint ibo;
	mesh0 = (struct submesh*)malloc(sizeof(*mesh0));
	mesh0->vlen = 24;
	mesh0->vsize = 6;
	mesh0->vtxs = vtxs;

	mesh0->ilen = 6;
	mesh0->idxs = idxs;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh0->vlen, mesh0->vtxs, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*mesh0->ilen, mesh0->idxs, GL_STATIC_DRAW);
	
	glVertexAttribPointer(VERTEX_POS_INDEX, 3,   GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, BUFFER_OFFSET(0));
	glVertexAttribPointer(VERTEX_POS_INDEX+1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, BUFFER_OFFSET(12));
}

static void draw()
{
	GLint offsetUnif, perspectiveMatrixUnif;

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glUseProgram(prog);

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

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

	glUseProgram(0);
	glDisableVertexAttribArray(VERTEX_POS_INDEX);
	glDisableVertexAttribArray(VERTEX_POS_INDEX+1);
}

void glInit2(GLsizei w, GLsizei h)
{
	width = (float)w;
	height = (float)h;
	glViewport(0, 0, w, h);
	glClearColor(1.0f, 0.5f, 0.5f, 1.0f);

	buildShader(&prog,VSRC_0,FSRC_0, VERTEX_POS_INDEX, VERTEX_POS_INDEX+1);
	uploadData();

	fileTest();
}

void glRender2()
{
	current1 = TIME;
	int diff = current1 - current0;
	//LOG("frame time=%d\n", diff);
	current0 = current1;
	draw();
}
