/*
 情景一 ParamType是⼀个指针或引⽤但不是通⽤引⽤
1. 如果expr的类型是⼀个引⽤，忽略引⽤部分 
、、这个类型是引用能不能看成是起别名，这样就和没有引用这个概念了
2. 然后剩下的部分决定T，然后T与形参匹配得出最终ParamType

*/
template<typename T>
void f(T &param);//
void t1(){
    int x=27;
    const int cx=x;
    const int &rx=cx;//rx是别名 
    f(x);// T--->int
    f(cx);//T--->const int
    f(rx);//T--->const int  rx是引用 将忽略掉引用部分
}