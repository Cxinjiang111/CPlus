#include<algorithm>
#include<vector>
#include<functional>
#include<iostream>
using namespace std;
template<class T>
struct display{
    void operator()(const T&x)const{
        cout<<x<<"\t";
    }
};
//是否时偶数
struct even{
    bool operator()(int x)const{
        return x%2?false:true;
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