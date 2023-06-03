#include<vector>
#include<memory>
#include<algorithm>
using namespace std;
#define SOME_MAGIC_NUMBER 20
class Widget{};
struct DeleteObject{
    template<typename T>
    void operator()(const T*ptr)const{
        delete ptr;
    }
};
void do2()
{
    vector<Widget*>vwp;
    for_each(vwp.begin(),vwp.end(),DeleteObject());//這樣就不用顯示强調類型了
}
