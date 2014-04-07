#ifndef gamemain_h
#define gamemain_h

#include <windows.h>
#include "opengl.h"
#include "fileio.h"

#define TIME GetTickCount();

void glInit(GLsizei width, GLsizei height);
void glRender();

#endif