##NDK链接第三方库

####链接静态链接库
android.mk格式如下

首先声明静态库：

    LOCAL_PATH := $(call my-dir)
    include $(CLEAR_VARS)
    LOCAL_MODULE := static
    LOCAL_SRC_FILES := static.a
    include $(PREBUILT_STATIC_LIBRARY)

使用静态库：

    include $(CLEAR_VARS)
    LOCAL_MODULE := modulename
    LOCAL_C_INCLUDES += includepath
    LOCAL_SRC_FILES := sourcefile.cpp
    LOCAL_STATIC_LIBRARIES := liblogapian
    include $(BUILD_EXECUTABLE)


####链接动态链接库
和链接静态库方法一致 只需将include $(PREBUILT_STATIC_LIBRARY)更改为include $(PREBUILT_SHARED_LIBRARY)即可