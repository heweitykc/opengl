#include "opengl.h"

extern const char VSRC_0[] =
		"in vec4 position; "
		"in vec4 color; "
		"out vec4 fcolor; "
		"void main()"
		"{"
		"	fcolor = color;"
		"	gl_Position = position;"
		"}";

extern const char FSRC_0[] =
		"in vec4 fcolor;"
		"void main()"
		"{"
		"	float lerpValue = gl_FragCoord.y/500.0f;"
		"	gl_FragColor = fcolor;"
		"}";


extern const GLfloat vtxs[] = {
		0.0f,0.5f,0.0f,	  1.0f,0.0f,0.0f,
		-0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
		0.5f,-0.5f,0.0f,  0.0f,0.0f,1.0f
};

extern const GLubyte idxs[] = {0, 1, 2};

