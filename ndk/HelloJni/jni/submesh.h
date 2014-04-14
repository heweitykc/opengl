#ifndef submesh_h
#define submesh_h

#include <GLES2/gl2.h>

struct submesh { 
	int vlen;
	int vsize;
	int ilen;
	GLfloat *vtxs;
	GLubyte *idxs;
};

#endif
