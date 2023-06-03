/*
情景⼆：ParamType⼀个通⽤引⽤
如果ParamType是⼀个通⽤引⽤那事情就⽐情景⼀更复杂了。如果ParamType被声明为通⽤引⽤（在
函数模板中假设有⼀个模板参数T,那么通⽤引⽤就是T&&),它们的⾏为和T&⼤不相同，完整的叙述请参
⻅Item24，在这有些最必要的你还是需要知道：
如果expr是左值，T和ParamType都会被推导为左值引⽤。这⾮常不寻常，第⼀，这是模板类型推
导中唯⼀⼀种T和ParamType都被推导为引⽤的情况。第⼆，虽然ParamType被声明为右值引⽤类
型，但是最后推导的结果它是左值引⽤。
如果expr是右值，就使⽤情景⼀的推导规则
*/
template<typename T>
void f(T&& param);//param现在是一个通用引用类型

void t1(){
    int x=27;
    const int cx=x;
    const int &rx=cx;
     f(x);//T--->int
     f(cx);//T--->const int
     f(rx);//T--->const int  rx是引用 将忽略掉引用部分
     f(27);//T->27 天然的右值
}
