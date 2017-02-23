##Java 中的Package和jar包
>**目标：**搞清楚java中import和package以及jar的用法和关系

我们在编译的时候，我们import的jar包或者package生成class必须要存在，才能编译通过。
现在在Android中，有两个问题。
一：SDK中的android.jar是如何生成的
二：为什么android的系统镜像中没有android.jar？那么程序是怎么运行的

####编译jar包
    jar cvf jarname.jar classname.class
    如果目标class是被package的话那么我们要把目录也打包起来

####jar包的本质
    jar包实际上就是一个压缩包，包含了我们的class文件，
    但是部分的class文件是package的，package过的文件需要放到
    和package对应的文件夹中。而jar在打包package需要把文件夹
    也打包进来。这样才能找到相应的package

    假设我们系统的jar路径下有A.jar(打包了package q.w.e.A.class)
    还有B.jar(打包了package a.s.d.B.class)
    那么其实在java看来就是该路径上多了几个文件夹,里面包含相应的class文件
    |q
    |--w
    |---e
    |a
    |--s
    |---d    

####jar的名字是否会影响编译
jar包的名字不会影响编译

####在命令行中指定jar路径
java -Djava.ext.dirs=dir Main

####同一个package可以编译在不同的jar包中吗
>可以

        假设a.b.c.Test.class被打包到了Test.jar包和Test2.jar包中
        而且，我们的程序中使用了Test类，并且以上两个Jar包都位于
        系统的jar路径上，那么在使用的不会冲突。而且是调用Test.jar
        包中的Test.class，因为它的文件名排得比较前