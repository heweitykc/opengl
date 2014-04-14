#include <jni.h>
#include "demo2.h"

extern "C" {

	void
	Java_com_example_hellojni_DemoRenderer_nativeInit(JNIEnv*  env,jobject thiz)
	{
		glInit2(800,1100);
	}

	void
	Java_com_example_hellojni_DemoRenderer_nativeDone(JNIEnv*  env,jobject thiz)
	{

	}

	void
	Java_com_example_hellojni_DemoRenderer_nativeRender(JNIEnv*  env,jobject thiz)
	{
		glRender2();
	}

}
