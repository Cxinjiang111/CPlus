#include<algorithm>
#include<vector>
#include<functional>
#include<iostream>
#include<iterator>
#include<string>
using namespace std;
template<class T>
struct display
{
    void operator()(const T&x)const{
        cout<<x<<"\t";
    }
};
class OP{
    public:
    bool operator()(const int& lhs,const int&rhs)
    {
        return lhs==rhs+1;
    }
};
int main()
{
    int ia[9]={0,1,2,3,4,5,6,7,8};
    vector<int> iv1{0,1,2,4,5,6}; // 0,1,2,4,5,6
    vector<int> iv2(ia,ia+9);    //  0,1,2,3,4,5,6,7,8
    cout<<*(mismatch(iv1.begin(),iv1.end(),iv2.begin()).first)<<endl;  // 4
    cout<<*(mismatch(iv1.begin(),iv1.end(),iv2.begin()).second)<<endl; // 3
    /*以上判断两个区间的第一个不匹配点，返回一个有两个迭代器组成的pair
    其中第一个迭代器指向第一个区间的不匹配点，第二个迭代器指向第二区间的不匹配点。
    */

   cout<<equal(iv1.begin(),iv1.end(),iv2.begin())<<endl;//0
   cout<<equal(iv1.begin(),iv1.end(),&iv2[4])<<endl;   // 0
    vector<int> iv4{1,2,3,4,5};
    vector<int> iv3{2,3,4,5,6}; 
    //          iv3 迭代器作为rhs iv4 作为lhs            
   cout<<equal(iv3.begin(),iv3.end(),iv4.begin(),OP())<< endl;//1

    //填充3个7 从开始迭代器开始以此填充
    //fill_n(iv1.begin(),3,7);//如果填充的数目超过自身迭代器的大小时，就会报错
    //for_each(iv1.begin(),iv1.end(),[](int i){cout<<i<<"\t";});
    cout<<endl;


    vector<int>::iterator ite1=iv1.begin();
    vector<int>::iterator ite2=ite1;
    advance(ite2,3);
    cout<<*ite2<<endl;//4
    for_each(iv1.begin(),iv1.end(),[](int i){cout<<i<<"\t";});
        cout<<endl;
    iter_swap(ite1,ite2);//仅仅交换两个迭代器的位置也就是交换迭代器所指的值
    for_each(iv1.begin(),iv1.end(),[](int i){cout<<i<<"\t";});
        cout<<endl;

}
