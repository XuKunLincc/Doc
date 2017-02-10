##在QT for Android上实现对物理按键的监听
>运行的目标平台比较特殊，有几个比较特殊的物理按键，其实现机制和按键机制不一样，并且从F9多了几个功能键到F27

我们现在就一步步来看看怎么处理

**1.首先实现监听Menu键**

>需要了解的技术：[QMenu](http://doc.qt.io/qt-5/qmenu.html) [QAction](http://doc.qt.io/qt-5/qaction.html) [信号和槽](http://doc.qt.io/qt-5/signalsandslots.html) ***[QEvent](http://doc.qt.io/qt-5/eventsandfilters.html)***

通过学习QT的Event机制我们可以知道，该如何去实现监听Menu键。在QT的event系统中，当有event产生时会被QT系统扔到消息队列中等待处理。而我们的应用程序就可以通过event()函数来进行获取，而且我们可以对event进行过滤，决定我们把什么event进行抛弃。

在程序的MianWindow中重写父类的*void keyPressEvent(QKeyEevnt * event)*函数，在此函数可以获取到Android的各种按键监听。

**2.实现监听示教器上的其他物理按键**
>出现的问题： 无法监听到F9以后的按键并抛出异常
<span style="color: red">W/libNodepad.so( 1868): (null):0 ((null)): Unhandled key code  271 !</span>

只要我们把问题解决了，自然就能监听到其他的物理按键了。
**判断：**QT的源码中对未知的key code进行了异常抛出，分析QT对于event的源码，然后判断是哪里出了问题

#####1、找Bug常用手法，通过异常抛出我们可以通过关键字在源码上查找   
通过关键字**Unhandled key code**在源码路径上查找，找到抛出异常的地方在***/QTSrc/qtbase\src\plugins\platforms\android\androidjniinput.cpp***的函数***mapAndroidKey()***;

通过分析，QT for Android的事件分发会从QTActivity的onKeyDown开始分发到QT系统中