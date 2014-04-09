#include "shadersrc.h"
#include <stdio.h>

static char buf[1024];

char VSRC_0[] =
//		"precision highp float;"		//needed by es2
		"attribute vec4 position; "
		"attribute vec4 color; "
		"uniform vec3 offset; "
		"uniform mat4 viewMatrix;"
		"uniform mat4 perspectiveMatrix;"
		"varying vec4 fcolor; "
		"void main()"
		"{"
			"vec4 cameraPos = position + vec4(offset.x, offset.y, offset.z, 0.0);"
    
			"gl_Position =  viewMatrix * perspectiveMatrix * cameraPos;"
			"fcolor = color;"
		"}";

char FSRC_0[] =
//		"precision highp float;"		//needed by es2
		"varying vec4 fcolor;"
		"void main()"
		"{"
		"	gl_FragColor = fcolor;"
		"}";

static GLuint compile(const char * source, int type) {
	GLint len;
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderInfoLog(shader, 1024, &len, buf);
	LOG("complile=%s", buf);
	return shader;
}

void buildShader(GLuint *prog,char *vscr, char *fsrc)
{
	GLint vs,fs,status;
	
	vs = compile(vscr, GL_VERTEX_SHADER);
	fs = compile(fsrc, GL_FRAGMENT_SHADER);

	*prog = glCreateProgram();
	glAttachShader(*prog, vs);
	glAttachShader(*prog, fs);

	glLinkProgram(*prog);

	glDetachShader(*prog, fs);
	glDeleteShader(fs);
	glDetachShader(*prog, vs);
	glDeleteShader(vs);

	glGetProgramiv(*prog, GL_LINK_STATUS, &status);
	glGetProgramInfoLog(*prog, 1024, NULL, buf);
	LOG("link=%s", buf);
}