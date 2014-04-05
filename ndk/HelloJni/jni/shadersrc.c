#include <GLES2/gl2.h>

char VSRC_0[] =
		"precision highp float;"
		"attribute vec4 position; "
		"attribute vec4 color; "
		"varying vec4 fcolor; "
		"void main()"
		"{"
		"	fcolor = color;"
		"	gl_Position = position;"
		"}";

char FSRC_0[] =
		"precision highp float;"
		"varying vec4 fcolor;"
		"void main()"
		"{"
		"	gl_FragColor = fcolor;"
		"}";


GLfloat vtxs[] = {
		0.0f,0.5f,0.0f,	  1.0f,0.0f,0.0f,
		-0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
		0.5f,-0.5f,0.0f,  0.0f,0.0f,1.0f
};

GLubyte idxs[] = {0, 1, 2};

