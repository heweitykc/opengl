#include <jni.h>
#include "demo2.h"

extern "C" {

	JNIEXPORT void JNICALL Java_com_example_hellojni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
	JNIEXPORT void JNICALL Java_com_example_hellojni_GL2JNILib_step(JNIEnv * env, jobject obj);

}

JNIEXPORT void JNICALL Java_com_example_hellojni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	glInit2(width,height);
}

JNIEXPORT void JNICALL Java_com_example_hellojni_GL2JNILib_step(JNIEnv * env, jobject obj)
{
	glRender2();
}
