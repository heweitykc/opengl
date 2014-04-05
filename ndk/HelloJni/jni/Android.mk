
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hello-jni
LOCAL_SRC_FILES := hello-jni.c demo1.c shadersrc.c
LOCAL_LDLIBS := -lGLESv2 -ldl -llog

include $(BUILD_SHARED_LIBRARY)
