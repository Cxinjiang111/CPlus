#include<iostream>
#include<functional>
#include<map>
using namespace std;
class TestClass{
public:
    int classMember(int a,int b){return a+b;}
};
void FUN(string s,function<int(int ,int)>fun)
{
    
}
int main()
{
    TestClass testObj;
    function<int (int a,int b)> f1=bind(&TestClass::classMember,testObj,placeholders::_1,placeholders::_2);
    int ret=f1(4,5);
    cout<<ret<<endl;
    map<string,function<int(int ,int)>> varmap;
    varmap["+"]=bind(&TestClass::classMember,testObj,placeholders::_1,placeholders::_2);
    cout<<varmap["+"](1,2)<<endl;
}