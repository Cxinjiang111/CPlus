#include<algorithm>
#include<vector>
#include<functional>
#include<iostream>
using namespace std;
template<class T>
struct display{
    void operator()(const T& lhs)
    {
        cout<<lhs<<"\t"
    }
};
//是否是奇数
struct even{
    bool operator()(const int &lhs)
    {
        return lhs%2?false:true;
    }
};
class even_by_two{
public:
    int operator()()const{
        return _x+=2;
    }
private:
    static int _x;
};
template<class T>
struct Less{
    bool operator()(const T& value)
    {
        return value<7?true:false;
    }
};

int even_by_two::_x=0;
int main()
{
    int ia[]={0,1,2,3,4,5,6,6,6,7,8};
    vector<int> iv(ia,ia+sizeof(ia)/sizeof(int));
    cout<<*adjacent_find(iv.begin(),iv.end())<<endl;

    cout<<*adjacent_find(iv.begin(),iv.end(),equal_to<int>())<<endl;

    cout<<count(iv.begin(),iv.end(),6)<<endl;

    cout<<count_if(iv.begin(),iv.end(),bind2nd(less<int>(),7))<<endl;
    cout<<count_if(iv.begin(),iv.end(),Less<int>())<<endl;
    //找出iv之中元素值为4的第一个元素的所在位置的值
    cout<<*find(iv.begin(),iv.end(),4)<<endl;

    cout<<*find_if(iv.begin(),iv.end(),bind2nd(greater<int>(),2))<<endl;

    vector<int> iv2(ia+6,ia+8);//{6,6}

    cout<<*(find_end(iv.begin(),iv.end(),iv2.begin(),iv2.end())+3)<<endl;

    cout<<*(find_first_of(iv.begin(),iv.end(),iv2.begin(),iv2.end())+3)<<endl;

    generate(iv2.begin(),iv2.end(),even_by_two());
    for_each(iv2.begin(),iv2.end(),display<int>());
    cout<<endl;

    generate_n(iv.begin(),3,even_by_two());
    for_each(iv.begin(),iv.end(),display<int>());
    cout<<endl;   

    remove(iv.begin(),iv.end(),6);
    for_each(iv.begin(),iv.end(),display<int>());
    cout<<endl;  

    vector<int> iv3(12);
    remove_copy(iv.begin(),iv.end(),iv3.begin(),6);
    for_each(iv.begin(),iv.end(),display<int>());
    cout<<endl;  

    remove_if(iv.begin(),iv.end(),bind2nd(less<int>(),6));
    for_each(iv.begin(),iv.end(),display<int>());
    cout<<endl;  
}