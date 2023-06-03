#include<vector>
#include<iostream>
using namespace std;
int main()
{
    constexpr int num=10;
    int data[num];
     vector<int> v;
    v.insert(v.begin(),data,data+num);//這樣就通過區間加迭代器的形式拷貝可數組
    //
    vector<int>::iterator insertLoc(v.begin());
    for(int i=0;i<num;++i)
    {
        //每次進行單次單個位置插入 會花費num次時間調用insert
        insertLoc=v.insert(insertLoc,data[i]);
        ++insertLoc;
    }

}
#include<iterator>

int main()
{
    container::container(begin,end);
    //序列容器 返回容器的頭
    iterator container::erase(iterator begin,iterator end);
    //關聯容器
    void container::erase(iterator begin,iterator end);
}


