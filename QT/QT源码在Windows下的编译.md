##QT源码在Windows下的编译
>**目标：**修改QT源码，然后重新编译，而且目标平台是Andoid


官网描述：http://doc.qt.io/qt-5/windows-building.html

###环境搭建
#####编译器为mingw

>以下工具都需要设置在环境变量中

* Python
* Prel
* Ruby
* 支持C++11标准的编译器
* mignw-make
------------
#####编译器为Vs

> Python Prel Ruby 依然是必要的

- 执行C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat

> 执行该bat的作用是将VS的编译器和nmake加进环境变量中


###配置
 >通过qt源码目录下的configure进行编译和配置，关键指令如下

     configure.bat -prefix D:\MyQt\QT5.7.1 -nomake examples  -opengl desktop -platform win32-g++ -debug -opensource
 - prefix 设置QT的install路径
 - platform 设置编译器平台 win32-g++ 表示使用的是mignw-make
 - nomake examples表示不编译官方的例子
 - debug 表示编译的是debug版本
 - opengl 对于opnegl的支持选择

>在windows平台下

###编译
    mingw32-make

###编译后install
    mingw32-make install

###重新编译或配置
To reconfigure, run mingw32-make confclean and configure.
需要执行make distclean 然后重新configure下

###配置QT Creator
>将我们编译的版本导入我们的QT Creator中，然后我们在使用QT Creator开发QT程序的时候就可以使用我们自己编译的版本

- **step1:**

>选择我们编译的QT

 ![step1](http://i1.piimg.com/567571/3a3e3e8b4e505af8.png)

- **setp2:**

>设置构建套件

![setp2.1](http://p1.bpimg.com/567571/7aedb206613814b8.png)
![setp2.2](http://i1.piimg.com/567571/e4d2ef38addda15e.png)
