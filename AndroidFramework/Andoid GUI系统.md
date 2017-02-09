###Andoid GUI系统
**前言：**
>在android系统中，控制着屏幕最直接的服务就是SurfaceFinger。所有的android的程序不管是APP还是C++写的程序都是通过操作SurfaceFinger来进行UI的绘制的。因为SurfaceFinger其实就是对FrameBuffer的一个封装。

####从开机动画开始来去解析Android的GUI系统
首先在BootAnimation的构造函数中会new一个*SurfaceComposerClient*对象保存在*mSession*中