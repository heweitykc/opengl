#include <jni.h>
#include <android/log.h>
#include "demo1.h"

void
Java_com_example_hellojni_DemoRenderer_nativeInit(JNIEnv*  env,jobject thiz)
{
	glInit(800,1100);
}

void
Java_com_example_hellojni_DemoRenderer_nativeDone(JNIEnv*  env,jobject thiz)
{

}

void
Java_com_example_hellojni_DemoRenderer_nativeRender(JNIEnv*  env,jobject thiz)
{
	glRender();
}

jstring
Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
#if defined(__arm__)
  #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #define ABI "armeabi-v7a/NEON"
    #else
      #define ABI "armeabi-v7a"
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
   #define ABI "x86"
#elif defined(__mips__)
   #define ABI "mips"
#else
   #define ABI "unknown"
#endif
    return (*env)->NewStringUTF(env, "Hello from JNI callee!  Compiled with ABI " ABI ".");
}
