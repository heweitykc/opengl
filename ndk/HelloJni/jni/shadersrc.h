#ifndef shadersrc_h
#define shadersrc_h

#include <GLES2/gl2.h>
#include <android/log.h>

#define LOG(format, ...) __android_log_print(ANDROID_LOG_INFO, "JNIMsg", format, __VA_ARGS__);

extern char VSRC_0[];
extern char FSRC_0[];

void buildShader(GLuint *prog,char *vscr, char *fsrc);

#endif
