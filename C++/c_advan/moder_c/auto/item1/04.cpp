/*
情景三：ParamType既不是指针也不是引⽤
当ParamType既不是指针也不是引⽤时，我们通过传值（pass-by-value）的⽅式处理：
这意味着⽆论传递什么param都会成为它的⼀份拷⻉——⼀个完整的新对象。事实上param成为⼀个新
对象这⼀⾏为会影响T如何从expr中推导出结果。
1. 和之前⼀样，如果expr的类型是⼀个引⽤，忽略这个引⽤部分
2. 如果忽略引⽤之后expr是⼀个const，那就再忽略const。如果它是volatile，也会被忽略

注意即使cx和rx表⽰const值，param也不是const。这是有意义的。param是⼀个拷⻉⾃cx和rx且现
在独⽴的完整对象。具有常量性的cx和rx不可修改并不代表param也是⼀样。这就是为什么expr的常量
性或易变性（volatileness)在类型推导时会被忽略：因为expr不可修改并不意味着他的拷⻉也不能被修
改。
认识到只有在传值给形参时才会忽略常量性和易变性这⼀点很重要，正如我们看到的，对于形参来说指
向const的指针或者指向const的引⽤在类型推导时const都会被保留。但是考虑这样的情况，expr是⼀
个const指针，指向const对象，expr通过传值传递给param：

*/
template<typename T>
void f(T param)//已传值的方式的处理parama
{

}

void t1(){
    int x=27;
    const int cx=x;
    const int &rx=cx;//忽略const &--->int rx=cx
     f(x);//T--->  int
     f(cx);//T---> int
     f(rx);//T---> int  
}
// 在这⾥，解引⽤符号（*）的右边的const表⽰ptr本⾝是⼀个const：ptr不能被修改为指向其它地址，也
// 不能被设置为null（解引⽤符号左边的const表⽰ptr指向⼀个字符串，这个字符串是const，因此字符串
// 不能被修改）。当ptr作为实参传给f，像这种情况，ptr⾃⾝会传值给形参，根据类型推导的第三条规
// 则，ptr⾃⾝的常量性将会被省略，所以param是const char* 。也就是说⼀个常量指针指向const字符
// 串，在类型推导中这个指针指向的数据的常量性将会被保留，但是指针⾃⾝的常量性将会被忽略。
template<typename T>
void f2(T param){
    const char* x="xxxx";
    param=x;//这么干的原因在于传入的T作为常量指针 ，指针自身的常量性将会被忽略
}
//ptr是⼀个常量指针，指向常量对象
const char* ptr="fun eith pointer";
void t2(){
    f2(ptr);
}
int main(){
    t2();

    return 0;
}