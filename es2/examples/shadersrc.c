#include "opengl.h"

char VSRC_0[] =
//		"precision highp float;"		//needed by es2
		"attribute vec4 position; "
		"attribute vec4 color; "
		"uniform vec2 offset; "
		"varying vec4 fcolor; "
		"void main()"
		"{"
		"	fcolor = color;"
		"	vec4 totaloffset = vec4(offset.x,offset.y,0,0);"
		"	gl_Position = position + totaloffset;"
		"}";

char FSRC_0[] =
//		"precision highp float;"		//needed by es2
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

