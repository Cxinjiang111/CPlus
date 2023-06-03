#include<iostream>
#include<vector>

using namespace std;
class alloc{

};
template<class T,class Alloc=alloc>
class V_ector{
public:
    typedef T value_type;//T 数值类型
    typedef value_type* iterator;//迭代器就是指向数据的指针
    template<class I>
    void insert(iterator position,I first,I last){
        cout<<"insert()"<<endl;
    }
};
//写这个就是为了发挥附加项的功能 class sequence=vector<T>
template<class T,class sequence=vector<T>>
class MM{
public:
    MM(sequence&ma):m_a(ma){}
    void print(sequence&m_a){
        for(auto s:m_a){
            cout<<s<<endl;
        }
    }
private:
    sequence m_a;
};
void t1(){
    int ia[5]={1,3,2,4,5};
    V_ector<int> x;
    V_ector<int>::iterator ite;//  V_ector<int>::iterator获得迭代器
    x.insert(ite,ia,ia+5);//I ->int* 
}
int main(){
    vector<int> aa{1,2,3,4,5};
    MM<int,vector<int>> m1(aa);
    m1.print(aa);
    return 0;
}
