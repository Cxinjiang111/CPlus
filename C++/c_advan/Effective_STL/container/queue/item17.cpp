/*
使用交換技巧來修正過剩容
*/
#include<vector>
#include<iostream>
using namespace std;
int main()
{
    vector<int> v(10000);

    v.push_back(1);

    std::cout<<v.size()<<"   "<<v.capacity()<<std::endl;

    //vector<int>(v).swap(v);//可以時自身進行適當的收縮
    vector<int>().swap(v);
    v.push_back(1);//清除v而且最小化他的容量    
    std::cout<<v.size()<<"   "<<v.capacity()<<std::endl;
    return 0;
}





