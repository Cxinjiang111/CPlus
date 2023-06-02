/*
const 意味着两个流概念 bitwise constness 和logical constness
bitwise const阵营的人相估，成员函数只有在不史改对象之任何成员变量(static 除外）时才可以说是const。 
也就是说它不更改对象内的任何一 个bit。这种论点的 好处是很容易侦测违反点： 编译器只需寻找成员变量的赋值动作即可。
 bitwise constness正是C开－ 对常量性(constness)的定义， 因此con吐成员函数不可以更改对象内任何 non-static成员变量。

不幸的是许多成员函数虽然不十足具备const性质却能通过bitwise测试。 更 具体地说， 
一个更改”指针所指物” 的成员函数星然个能算是const,但如果只有指针（而非其所指物）隶属十对象，
那么称此函数为bitwise const不会引发编译器异议。 这导致反直观结果。 假设我们有一个TextBlock-like class, 
它将数据存储为char*而不是string, 因为它需要和一 个不认识string对象的CAPI沟通：
*/
#include<iostream>
#include<string>
using namespace std;
class CTextBlock{
public:
    CTextBlock(char* t):pText(t){};
    char&operator[](std::size_t position) { //const成员函数
        cout<<"non-const"<<endl;
        return pText[position];//返回一个reference指向对象的值 
    }
    //希望他返回一个不可变的值
    char&operator[](std::size_t position) const{ //const成员函数
        cout<<"const "<<endl;
        return pText[position];//返回一个reference指向对象的值 
    }
private:
    char*pText;
};
int main()
{
    char h[6]={"hello"};
    const CTextBlock cctb(h);
    char *pc=&cctb[0];
    *pc='J';//前面cctb声明时为const 那么我就想保护cctb不会改变，然后加上const 返回值却依然改变了值，这不太合理
    for(unsigned i=0;i<6;++i){
        cout<<cctb[i];
    }
/* output
const 
const 
Jconst 
econst 
lconst 
lconst 
oconst 
*/
    return 0;
}