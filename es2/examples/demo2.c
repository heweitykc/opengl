#include "demo2.h"
#include "shadersrc.h"
#include "submesh.h"
#include "geomtool.h"
#include "Vector3.h"
#include "camera.h"
#include "MathUtil.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define VERTEX_POS_INDEX 0
#define VERTEX_POS_SIZE 6

static GLuint prog;
static Loader loader;

static DWORD current0;
static DWORD current1;

static float width;
static float height;

static float rotationX = 0.0f;

static float viewMatrix[16];
static float cameraMatrix[16] = {
	1.0f,0.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,0.0f,1.0f
};

static Camera camera(Camera::AIRCRAFT);

static struct submesh *mesh0=NULL;
static GLfloat vtxs[] = {
	5,   5, 5,  1, 0, 0,
	5,  5, -5,  0, 1, 0,
	-5, 5, -5,  0, 0, 1,

	-5, 5, 5,  1, 0, 0,
	5,  -5, 5,  0, 1, 0,
	-5, -5, 5,   0, 0, 1,

	-5, -5, -5,  1, 0, 1,
	5,  -5, -5,   0, 0, 1
};

static GLubyte idxs[] = {
	0,1,2,	0,2,3,
	0,7,1,	0,4,7,
	1,7,6,	1,6,2,
	2,6,5,	2,3,5,
	0,5,4,	0,3,5,
	5,6,7,	4,5,7
};

static void fileTest()
{
	loader.load("Monster32\\drr_01.jpg");
	//LOG("file=%s\n",loader.getbuff());
}

static void initPerspetive()
{
	float aspect = 4.0f/3.0f;
	float zNear = 0.1f;
	float zFar = 1000;
	float fov = 45* kPi/180;
	camera.perspectiveFieldOfView(fov,aspect,zNear,zFar);
}

static void initData()
{
	mesh0 = (struct submesh*)malloc(sizeof(*mesh0));
	mesh0->vlen = 48;
	mesh0->vsize = 6;
	mesh0->vtxs = vtxs;

	mesh0->ilen = 36;
	mesh0->idxs = idxs;
}

static void uploadData()
{
	GLuint vbo;
	GLuint ibo;

	initData();

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
	GLint viewMatrixUnif, cameraMatrixUnif;

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(prog);

	memset(viewMatrix, 0, sizeof(float)*16);

	viewMatrix[0] = 1;
	viewMatrix[5] = 1;
	viewMatrix[10] = 1;
	viewMatrix[15] = 1;
	
	viewMatrix[5] = cos(rotationX);
	viewMatrix[6] = -sin(rotationX);
	viewMatrix[9] = sin(rotationX);
	viewMatrix[10] = -cos(rotationX);

	//viewMatrix[12] = 0;
	//viewMatrix[13] = 0;
	//viewMatrix[14] = -2;

	camera.getMatrix(cameraMatrix);

	glBindAttribLocation(prog, VERTEX_POS_INDEX, "position");
	glBindAttribLocation(prog, VERTEX_POS_INDEX+1, "color");

	viewMatrixUnif = glGetUniformLocation(prog, "viewMatrix");
	cameraMatrixUnif = glGetUniformLocation(prog, "cameraMatrix");
	glUniformMatrix4fv(viewMatrixUnif, 1, GL_FALSE, &viewMatrix[0]);
	glUniformMatrix4fv(cameraMatrixUnif, 1, GL_FALSE, &cameraMatrix[0]);

	glEnableVertexAttribArray(VERTEX_POS_INDEX);
	glEnableVertexAttribArray(VERTEX_POS_INDEX+1);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);

	glUseProgram(0);
	glDisableVertexAttribArray(VERTEX_POS_INDEX);
	glDisableVertexAttribArray(VERTEX_POS_INDEX+1);
}

void keyDown(unsigned int key)
{

}

void keyUp(unsigned int key)
{

}

void glInit2(GLsizei w, GLsizei h)
{
	width = (float)w;
	height = (float)h;
	glViewport(0, 0, w, h);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);                 //深度测试方式
	glShadeModel(GL_SMOOTH);

	initPerspetive();

	buildShader(&prog,VSRC_0,FSRC_0);
	uploadData();

	fileTest();
}

void glRender2()
{
	current1 = TIME;
	int diff = current1 - current0;
	rotationX += 0.01f;

	//LOG("frame time=%d\n", diff);
	current0 = current1;
	draw();
}
