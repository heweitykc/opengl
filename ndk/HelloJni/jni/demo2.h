#ifndef demo2_h
#define demo2_h

#include <GLES2/gl2.h>

void touchBegin(int x,int y);
void touchMove(int x,int y);
void touchEnd(int x,int y);

void glInit2(GLsizei width, GLsizei height);
void glReshape2(GLsizei w, GLsizei h);
void glRender2();

#endif
