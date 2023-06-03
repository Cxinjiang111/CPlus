/*用empty来代替size是否为0
*/
// if(c.szie()==0);
// if(c.empty());
//以上二者等价
/*
事实上，empty()是个inline函数 empty是个常数时间操作，size是个线性时间
*/
#include<list>
#include<algorithm>
using namespace std;
int main()
{
    list<int> list1;
    list<int> list2;

    list1.splice(
        list1.end(),list2,//把list2
        find(list2.begin(),list2.end(),5),//第一次出现5到
        find(list2.rbegin(),list2.rend(),10).base()//最后第一出现10的所有节点移到list1的结尾
    );   


}

