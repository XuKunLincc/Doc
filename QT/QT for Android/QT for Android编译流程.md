##QT for Android编译流程
首先要提出疑问：
* QT是如何进行android的支持的呢
* QT for Android以一种什么样的机制编译的呢
* QT怎么来去新建一个Activity

###QT是如何进行android的支持的呢
我们可以进行猜测，QT对android的支持应该是使用了NDK。通过QT生成的一个so库来去调用android的一些自带的SO库。
在这之前呢，我们要先了解***android 应用程序是怎么从java代码中去调用到其系统的动态链接库的***
