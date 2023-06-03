#include<iostream>
#include<string>
using namespace std;
class Foo{
public:
    int _id;
    long _data;
    string _str;

public:
    Foo():_id(0){
    cout<<"default ctor"<<this<<"_id="<<_id<<endl;
    }
    Foo(int i):_id(i){
        cout<<"ctor"<<this<<"_id="<<_id<<endl;
    }
    ~Foo(){}
    //申请非数组的new
    static void *operator new(size_t size){
        Foo*p=(Foo*)malloc(size);
        return p;
    }
    static void operator delete(void*pdead,size_t size)
    {
        free(pdead);
    }
    //申请数组的new
    static void *operator new[](size_t size){
            Foo*p=(Foo*)malloc(size);
        return p;
    }
    static void operator delete[](void*pdead,size_t size)
    {
        for(size_t i=0;i<size;++i)//有问题 重复释放pdead这个内存地址
        free(pdead+i*sizeof(Foo));
    }
};
int main()
{
    // Foo *pf=new Foo();//
    // delete pf;

    Foo*pArray=new Foo[5];
    delete[]pArray;

//------------调用全局operator new 而不是进入Foo中的new 重载运算符
    // Foo*ppf=::new Foo(5);
    // ::delete ppf;

}
