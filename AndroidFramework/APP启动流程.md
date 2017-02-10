1，首先调用ActivityThread类的main函数。
public static void main(){
	...
	ActivityThread thread = new ActivityThread();	// 自己获取自己的一个实例 a
}
2，获取一个Handle对象保存在sMainThreadHandle 也就是我们主线程的handle


3，通过looper初始化一个application的context对象 调用函数handleBindApplication
### 这个context对象就是Application类，通过makeApplication()函数初始化

ContextImpl 的构造函数是private的 所以它不能被new出来，只能通过createAppContext函数来获取相应的实例

a--->	ActivityThread(){
			mResoureManager = ResoureManager.getInstance();	// 获取一个资源管理器 该类的构造函数为NULL，也就是什么都没做
}


