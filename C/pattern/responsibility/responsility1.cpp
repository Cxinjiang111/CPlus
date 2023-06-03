#include<iostream>
using namespace std;

/*
使多个对象都有机会处理请求，从而避免了请求的发送者和接收者之间的耦合关系。
将这些对象连成一条链，并沿着这条链传递该请求，直到有对象处理它为止。
15.2 优点
　　■ 责任链模式将请求和处理分开，请求者不知道是谁处理的，处理者可以不用知道请求的全貌。
　　■ 提高系统的灵活性。
15.3 缺点
　　■ 降低程序的性能，每个请求都是从链头遍历到链尾，当链比较长的时候，性能会大幅下降。
　　■ 不易于调试，由于采用了类似递归的方式，调试的时候逻辑比较复杂。
注意责任链中的节点数量需要控制，避免出现超长链的情况，这就需要设置一个最大的节点数量，
超过则不允许增加节点，避免无意识地破坏系统性能。
15.3. 应用场景
　　■ 一个请求需要一系列的处理工作。
　　■ 业务流的处理，例如，文件审批。
　　■ 对系统进行补充扩展。
*/
class Player{
private:
    Player*successor=NULL;
public:
    virtual void handle(int i)=0;
    void setSuccessor(Player*Successor){
        this->successor=Successor;
    }
    void next(int index){
        if(successor!=nullptr){
            successor->handle(index);
        }else{
            cout<<" game over"<<endl;
        }
    }
};
class PlayerA:public Player{
public:
    PlayerA(Player*successor){
        this->setSuccessor(successor);
    }
    void handle(int i){ //这是递归调用next(i);
        if(i==1){
            cout<<"PlayerA drking"<<endl;
        }else{
            cout<<"PlayerA down "<<endl;
            next(i);
        }
    }
};
class PlayerB:public Player{
public:
    PlayerB(Player*successor){
        this->setSuccessor(successor);
    }
    void handle(int i){ //这是递归调用next(i);
        if(i==1){
            cout<<"PlayerB drking"<<endl;
        }else{
            cout<<"PlayerB down "<<endl;
            next(i);
        }
    }
};
int main(){
    //play--->  *playA ------>*PlayB---->NULL
    //(Play*A)   (*PlayB)     (NULL)
    Player*play=new PlayerA(new PlayerB(NULL));
    play->handle(2);
    delete play;
    play=nullptr;
}