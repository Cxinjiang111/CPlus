/*尽量使用区间成员函数代替他们的单元素兄弟
● 一般来说使用区间成员函数可以输入更少的代码。
● 区间成员函数会导致代码更清晰更直接了当。
****
当处理标准序列容器时，应用单元素成员函数比完成同样目的
的区间成员函数需要更多地内存分配，更频繁地拷贝对象，而且/或者造成多余操作。

*/

void print(vector<int>&v)
{
    for(int i=0;i<v.size();++i)
    {
        cout<<v[i]<<"\t";
    }
}
void f1(vector<int>&v1,vector<int>&v2)
{ 
    //assign(_InputIterator  __first, _InputIterator  __last)
    v1.assign(v2.begin()+v2.size()/2,v2.end());//v1  _OutputIterator v1的内容完全是 _InputIterator [__first, __last]
    print(v1);
}
void f2(vector<int>&v1,vector<int>&v2)
{
    //等价于下面这个循环操作
    v1.clear();
    for(vector<int>::const_iterator ci=v2.begin()+v2.size()/2;ci!=v2.end();++ci)
    {
        v1.push_back(*ci);
    }
    print(v1);
}
void f3(vector<int>&v1,vector<int>&v2)
{   
// 算法也来替代
    v1.clear();
    //inline _OI copy(_II __first, _II __last, _OI __result)
    copy(v2.begin()+v2.size()/2,v2.end(),back_inserter(v1));
    print(v1);
}
int main()
{
    vector<int> v1;
    for(int i=0;i<3;i++)
    {
        v1.push_back(i);
    }
    vector<int> v2;
    for(int i=0;i<8;i++)
    {
        v2.push_back(i*10);
    }
    f1(v1,v2);
    cout<<"========="<<endl;
    f2(v1,v2);
    cout<<"========="<<endl;
    f3(v1,v2);
    cout<<"========="<<endl;


    return 0;
}




