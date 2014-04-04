#include "GL\glew.h"
#include "GL\glut.h"

//宏定义
#define VERTICES 0
#define INDICES 1
#define NUM_BUFFERS 2

//缓冲区标示符
GLuint buffers[NUM_BUFFERS];

static GLfloat cube[]={-1.0f, -1.0f, -5.0f, //前面的正方形
	1.0f, -1.0f,-5.0f,
	1.0f, 1.0f, -5.0f, 
	-1.0f, 1.0f, -5.0f,
	-1.0f, -1.0f, -10.0f,//背面的正方形
	1.0f, -1.0f, -10.0f,
	1.0f, 1.0f, -10.0f,
	-1.0f, 1.0f, -10.0f
};

static GLubyte index[]={0, 1, 2, 3, //前面
	0, 3, 7, 4, //左面
	5, 6, 2, 1, //右面
	7, 6, 5, 4, //后面
	3, 2, 6, 7, //上面
	1, 0, 4, 5 //地面
};

void SetupRC()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//生成缓冲区标示符
	glGenBuffers(NUM_BUFFERS, buffers);
	//绑定缓冲区对象，并设置顶点数组
	glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);
}

void DisplayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 1.0f);

	glPushMatrix();

	glEnableClientState(GL_VERTEX_ARRAY);

	//绑定缓冲区对象，并进行渲染
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	glutSwapBuffers();
}

void ReshapeFunc(int w, int h)
{
	float fAspect = 1.0 * w / h;

	if(h == 0) h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(35.0f, fAspect, 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int args, char* argv[])
{
	GLenum err;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	err = glewInit();
	if(GLEW_OK != err){
	  	printf("Error:%s\n", glewGetErrorString(err));
		return;
	}

	glutCreateWindow("VBO");
	glutPositionWindow(100,100);

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	SetupRC();
	glutMainLoop();
}
