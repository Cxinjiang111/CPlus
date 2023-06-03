/* forward iterator 
可应用于multipass （跳多步）算法，forward iterator 不允许在
range 中回头移动，只能向前
前置累加
++i 
语义：i从此指向下一个值
必然结果： i是deferenceable 或past the end 。&i=&++i，如果i==j，则++i==++j
后置累加
i++
语义：x tmp=i；++i； return tmp
必然结果： i是deference 或past the end

*/
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int> a={1,2,3,4,5};
    vector<int>::iterator pa=a.begin();
    vector<int>::iterator pb=a.begin();
    ++pa;
    pb++;
    for(vector<int>::iterator it=a.begin();it!=a.end();++it)
    {
        cout<<&(*it)<<endl;
    }
    cout<<&(*pa)<<"\t"<<*pa<<endl;
    cout<<&(*pb)<<"\t"<<*pb<<endl;



    
}