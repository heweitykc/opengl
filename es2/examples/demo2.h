#ifndef demo2_h
#define demo2_h

#include <windows.h>
#include "opengl.h"
#include "fileio.h"

#define TIME GetTickCount();

void glInit2(GLsizei width, GLsizei height);
void glRender2();

#endif