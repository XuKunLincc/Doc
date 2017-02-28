##修改默认Activity
>**目标：**修改QT for Android默认Activity

####1、新建一个Activity去继承QtActivity即可
*注意事项*
需要知道QtActivity的包名*org.qtproject.qt5.android.bindings.QtActivity*

####2、修改AndroidMainfest.xml文件
将activity:name指向我们的Activity