##qt-creator中的 运行程序的 工作目录 与 程序所在的目录
**问题：**

在qt-creator中debug的时候，发现程序不能读写所在目录的配置文件，资源文件。
**原因：**

原来 运行程序的 工作目录 与 程序所在的目录是不同的概念。
**解决：**

跑跑这段代码就知道了：

    qDebug()<<"current applicationDirPath: "<<QCoreApplication::applicationDirPath();
    qDebug()<<"current currentPath: "<<QDir::currentPath();

