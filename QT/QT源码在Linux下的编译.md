##QT源码在Linux下的编译
>**目标：**掌握在QT在Linux环境下的编译

####一、下载源码以及创建相关目录
* setup1: 下载源码
* setup2: 在usr/local/lib目录下创建 qt%version%目录作为安装目录

####二、编译前配置configure
./configure -prefix /usr/local/lib/qt4.8.6 -nomake examples -opengl desktop -platform linux-g++ -debug -opensource -nomake tests