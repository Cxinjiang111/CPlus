#include<iostream>
using namespace std;
class GamePlayer{
public:
    enum{NumTurns=5};
    int scores[NumTurns];
};
class GamePlayer1{
public:
    static const int NumTurns=5;
    static const int NumTurns2=5;//没有占用内存
    int scores[NumTurns];
};
#define NumTurns_1 5
class GamePlayer2{
public:
    int scores[NumTurns_1];
};
int main()
{
    GamePlayer g;
    //cout<<&(g.NumTurns)<<endl;//enum 更有点像define 此时没有地址这个概念  你不想要别人去他的地址，此时用处更大，也不会导致额外的空间
    cout<<sizeof(g)<<endl;  //20
    GamePlayer1 g1;
    cout<<sizeof(g1)<<endl;//20
    GamePlayer1 g2;
    cout<<sizeof(g2)<<endl;//20
    return 0;
}