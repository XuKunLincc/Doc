##NDK编译

### 指定编译路径和配置文件
宏NDK_PROJECT_PATH指定编译路径
宏APP_BUILD_SCRIPT指定编译脚本

### 使用其他C++运行库
宏 APP_STL指定C++运行库
值：
stlport_static 静态编译
其他运行库支持：http://blog.sina.com.cn/s/blog_602f877001014qe5.html


###编译动态库
F:\work\logapi_z\src>ndk-build NDK_PROJECT_PATH=./ APP_BUILD_SCRIPT=./Android.mk APP_STL=stlport_static

###Android.mk
    LOCAL_PATH := $(call my-dir)
    include $(CLEAR_VARS)
    SRCFILE = $(wildcard $(LOCAL_PATH)//*.cpp $(LOCAL_PATH)//linux/*.cpp)
    LOCAL_SRC_FILES := $(SRCFILE)
    LOCAL_C_INCLUDES += $(LOCAL_PATH) $(LOCAL_PATH)//linux
    LOCAL_MODULE := logapi_and
    include $(BUILD_SHARED_LIBRARY)

###添加编译选项
使用**LOCAL_CFLAGS**进行添加
**比如：**
- 添加宏定义：-D宏
- 支持C++ exceptions： -fexceptions


###C++支持
使用**APP_STL**进行选择C++运行库


###指定Application.mk路径
ndk-build NDK_APPLICATION_MK=youfile