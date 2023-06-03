#include<iostream>
#include<ostream>
using namespace std;
class INF{
public:
  friend  ostream& operator<<(ostream &os,const INF&i){
        os<<'['<<i.m_i<<']';
        return os;
    }
public:
    INF(int &i):m_i(i){}

    INF&operator++(){
        ++(this->m_i);
        return *this;
    }
    const INF operator++(int){
        INF temp=*this;
        ++(*this);
        return temp;
    }

    INF&operator--(){
        --(this->m_i);
        return *this;
    }
    const INF operator--(int){
        INF temp=*this;
        --(*this);
        return temp;
    }
    //
    int&operator*()const{
        return (int&)m_i;
    //以上转换告诉编译器，确实要将const int 转为non-const lvalue 
    }
private:
    int m_i;
};
int main(){
    int a=5;
    INF I(a);
    cout<<I++<<endl; //5
    cout<<++I<<endl; // 7
    cout<<--I<<endl; // 6
    cout<<I--<<endl; //6 
    cout<<*I<<endl;  // 5
    
    return 0;
}



