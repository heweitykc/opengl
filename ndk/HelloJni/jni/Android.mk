
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hello-jni
LOCAL_SRC_FILES := hello-jni.cpp demo2.cpp shadersrc.cpp geomtool.cpp\
					camera.cpp EulerAngles.cpp MathUtil.cpp Matrix4x3.cpp\
					Quaternion.cpp RotationMatrix.cpp TouchController.cpp Vector3.cpp
LOCAL_LDLIBS := -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
