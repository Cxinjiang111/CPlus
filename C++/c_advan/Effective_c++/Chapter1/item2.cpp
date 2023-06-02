#include<iostream>
using namespace std;
/*尽量以const, enum,inline 替换 #define

*/
// int a=5;
// const int* p=&a;
class GamePlayer{
public:
/*
为了将常量的作用域限制于class内， 必须让他成为class的一个成员，而为确保常量 
至多只有一份实体，你必须让他成为一个static成员
*/
    static const int NumTurns=5;//申明式 
    int scores[NumTurns];//这里数组就没法用NumTurns  所以上面只能static const int NumTurns=5；=
};
/*
然而你所看到的是NumTurns的声明式曲非定义式。通常C+＋要求你对你所使
用的任何东西提供个定义式，但如果它是个class专属常最又是static且为整数类型(integraltype,例如ints,chars, boo ls)，则需特殊处理。只要不取它们的地址，
你可以声明并使用它们而无须提供定义式。但如果你取某个class专属常量的地址，
或纵使你不取其地址而你的编译器坚持要看到一个定义式，你就必须提供定义式，
*/
const int GamePlayer::NumTurns;//NumTurns的定义式  

//
// class GamePlaye1{
// private:
//     const int NumTurns=5;//申明式 
//     //int scores[NumTurns];//这里没有static就会出错 
// };

int main()
{
    GamePlayer g;
    cout<<&(g.NumTurns)<<endl;
    /*
    没有const int GamePlayer::NumTurns;//NumTurns的定义式 这行代码
    那么&(g.NumTurns) 这个就会出错undefined reference to `GamePlayer::NumTurn 
    此时必须加上定义式这行，
    */

    return 0;
}