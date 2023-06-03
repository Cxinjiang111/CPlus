#include<vector>
#include<algorithm>
#include<list>
#include<map>
#include<string>
using namespace std;
struct CIStringCompare{
   bool operator()(){
    }
};
class Widget{};
void fun()
{
    map<string,vector<Widget>::iterator,CIStringCompare>  a;//CIStringCompare比较的规则

    typedef  map<string,vector<Widget>::iterator,CIStringCompare>::iterator map_iterator;
//typedef提供的词法的封装 ，typedef并不能阻止用户使用或依赖任何他们不应该用的
}

/*
要限制如果用一个容器类型替换另一个容器可能需要修改的代码，就需要在类中隐藏那个容器，而且通过
类的接口限制容器特殊信息可见性的数量。
*/
class Customer{};
//对于装有Customer的vector进行一些个性化 特殊化处理相比于直接 vector<Customer> 
class CustomerList{
private:
    typedef vector<Customer> CustomerContainer;
    typedef CustomerContainer::iterator CustomerContainer_iter;//外界无法可见，避免了随意使用和修改的可能性

public://通过这个接口 限制list特殊信息的可见性
    void insert(Customer &c){
        num1.insert(c);
    }

private:
    CustomerContainer num1;

};

int main()
{
    // CustomerList::CustomerContainer a;
    // CustomerList::CustomerContainer_iter it=a.begin();

}

