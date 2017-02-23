##添加我们的类到SDK中
>让我们的开发的源码中特有的类加进SDK中，有两种方法可以实现

**1.在源码中编译SDK**

        # source ./build/envset.sh
        # lunch 目标平台
        # make upate-api
        # make sdk

**2.直接修改官方的源码**
>扩展知识 Doc/java/Java Package和jar包

- 找到我们的类out/target/common/obj/JAVA_LIBRARIES/framework_intermediates/classes/android/os
- 复制出来
- 找到官方SDK中的android.jar SDKdir/sdk\platforms\android-version\android.jar
- 使用压缩工具，把我们的类扔到android/os/目录下
- 保存
