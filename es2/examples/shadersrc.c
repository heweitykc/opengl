#include "opengl.h"

char VSRC_0[] =
//		"precision highp float;"		//needed by es2
		"attribute vec4 position; "
		"attribute vec4 color; "
		"uniform float loopDuration; "
		"uniform float time; "
		"varying vec4 fcolor; "
		"void main()"
		"{"
		"	fcolor = color;"
		"	float timeScale = 3.14159f * 2.0f / loopDuration;"
		"	float currTime = mod(time, loopDuration);"
		"	vec4 totalOffset = vec4(0.0f, 0.0f, 0.0f, 0.0f);"
		"	totalOffset.x = cos(currTime * timeScale) * 0.6f;"
		"	totalOffset.y = sin(currTime * timeScale) * 0.6f;"
		"	gl_Position = position + totalOffset;"
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

