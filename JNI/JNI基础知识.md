##JNI基础知识
>**目的：**掌握基本的JNI技术

####调用Java对象方法
    思考：我们的方法是和对象相关的，而不是仅仅和类相关
    所以我们在调用CallMethod函数的时候要传递我们的对象进去
- 首先获取一个对象的jclass 可以通过GetObjectClass或者FindClass来实现
- 获取想调用方法的ID 通过GetMethodID()函数进行获取，需要注意的一点是如果是要获取static方法，那么我需要使用GetStaticMethodID函数来进行获取
- 然后调用CallMethod()进行调用Java函数

####创建一个java对象
- 首先，我们要获取我们需要实例化的类的一个jclass对象,通过 *FindClass*来进行获取
- 但是在创建对象前我们需要把我们的构造函数弄出来，因为我们知道一个类中或许不止一个构造函数，通过不同构造函数构造的对象其含义不同
