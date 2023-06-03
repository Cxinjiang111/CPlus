#include<iostream>
/*
数组实参
上⾯的内容⼏乎覆盖了模板类型推导的⼤部分内容，但这⾥还有⼀些小细节值得注意，⽐如在模板类型
推导中指针不同于数组，虽然它们两个有时候是完全等价的。关于这个等价最常⻅的例⼦是在很多上下
⽂中数组会退化为指向它的第⼀个元素的指针，⽐如下⾯就是允许的做法：


*/
void t1(){
    const char name[]="iiiii";
    const char *ptrToName=name;//数组回退化为指针
}
//数组回退化指针，即下方二式相等
template<typename T>
void f1( T a[])//f0
{

}
template<typename T>
void f2( T *a)//f1
{

}
/*
因为数组形参会视作指针形参，所以传递给模板的⼀个数组类型会被推导为⼀个指针类型。这意味着在
模板函数f的调⽤中，它的模板类型参数T会被推导为const char* ：
*/
template<typename T>
void f3(T&param)//f2
{

}
void t2(){
     int a[5]={1,2,3};
     f2(a);//T ---->const int*  f0或f1
    /*
但是现在难题来了，虽然函数不能接受真正的数组，但是可以接受指向数组的引⽤！
所以我们修改f为传引⽤
*/
    int b[5]={1,2,3};
    f3(b);//f2 这是传的是数组
/*
T被推导为了真正的数组！这个类型包括了数组的⼤小，在这个例⼦中T被推导为const char[13]，
param则被推导为const char(&)[13]。
*/
}
//有趣的是，对模板函数声明为⼀个指向数组的引⽤使得我们可以在模板函数中推导出数组的⼤小：
//在编译期间返回⼀个数组⼤小的常量值（数组形参没有名字，因为我们只关⼼数组的⼤小）
//constexpr告诉编译器在编译器运行 计算结果
//noexcept通知编译器这是安全的函数，不许报异常
//⾄于arraySize被声明为noexcept，会使得编译器⽣成更好的代码
template<typename T,std::size_t N>
constexpr std::size_t arraySize(T(&)[N])noexcept{
    return N;
}
void t3(){
    int keyVal[]={1,2,3,4,5,6};
    int mappdevals[arraySize(keyVal)];//这个居然能推导出新数组的大小，神奇
    //由于是编译器运行，上述写法不会报错
    std::cout<<sizeof(mappdevals)/sizeof(int);//6
}
int main(){

    t3();
    return 0;
}




