#include<iostream>
#include<vector>
using namespace std;
int main()
{
    typedef vector<int> intvec;
    typedef intvec::iterator intveciter;
    typedef intvec::const_iterator intvecconstiter; 
    intvec v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    intveciter it;
    intvecconstiter conit;
    /*
    //如果下面条件判断实现问题的话则conit!=it 便可编译通过
    if(it!=conit)//为假，说明相等intveciter于intvecconstiter此时是一致的
    //it!=conit 这个调用的是iterator 中的operator！ 
    //这些实现将const_iterator的operator==作为const_iterator的一个成员函数而不是非成员函数。而问题的解
    //决之道显得非常有趣：只要像这样交换两个iterator的位置：
    {
        cout<<"！="<<endl;
    }
    else{
        cout<<"=="<<endl;
    }
    */
   //编译没有任何问题，那就是该STL可以支持这种形式的比较 如果编译不过的话，可交换二者的未知即可
    //if(it-conit>=2)
    if(conit-it>=2)//编译没有任何问题，那就是该STL可以支持这种形式的比较 
    {
        cout<<"ok"<<endl;
    }
    else{
        cout<<"not ok"<<endl;
    }
    return 0;
}







