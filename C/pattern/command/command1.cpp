#include<iostream>
#include<list>
using namespace std;
/*
16.1 定义
　　将一个请求封装成一个对象，从而让你使用不同的请求把客户端参数化，
对请求排队或者记录请求日志，可以提供命令的撤销和恢复功能。
16.2.优点
　　■ 类间解耦。调用者角色与接收者角色之间没有任何依赖关系，
调用者实现功能时只需要调用Command中的execute()方法即可，不需要了解是哪个接收者执行。
　　■ 可扩展性。Command 的子类可以非常容易地扩展，
而调用者Invoker和高层次的模块Client不产生严重的代码耦合。
　　■ 命令模式结合其他模式会更优秀。命令模式可以结合责任链模式，
实现命令族解析任务，结合模板方法模式，则可以减少Command子类的膨胀问题。
16.3 缺点
　　■ 使用命令模式可能会导致系统中出现过多的具体命令类，
因此需要在项目中慎重考虑使用。
16.4 应用场景
　　■ 使用命令模式作为“回调”在面向对象系统中的替代。
“回调”讲的便是将一个函数登记上，然后在以后调用此函数。
　　■ 需要在不同的时间指定请求、将请求排队。
　　■ 系统需要支持命令的撤销（undo）。命令对象可以把状态存储起来，
等到客户端需要撤销时，可以调用undo()方法，将命令所产生的效果撤销。
　　■ 需要将系统中所有的数据更新操作保存到日志里，以便在系统崩溃时，
可以根据日志读回所有的数据更新命令，
重新调用 execute()方法一条一条执行这些命令，从而恢复系统在崩溃前所做的数据更新。
　　■ 一个系统需要支持交易（transaction）。一个交易结构封装了一组数据更新命令。
使用命令模式来实现交易结构可以使系统增加新的交易类型
*/
//抽象基类
class Order{
public:
    virtual void execute()=0;
};
//功能接口
class Stock{
public:
    void buy(){
        cout<<"stock [name:]"+name+"Quantity"<<qauntity<<"] bought"<<endl;
    }
    void sell(){
          cout<<"stock [name:]"+name+"Quantity"<<qauntity<<"] bought"<<endl;
    }
private:
    string name="ABC";
    int qauntity=10;
};
///-----请求接口-------------
class BuyStock:public Order{
private:
    Stock abcstock;
public:
    BuyStock(Stock abcstock){
        this->abcstock=abcstock;
    }
    void execute(){
        abcstock.sell();
    }
};
class SellStock:public Order{
private:
    Stock abcstock;
public:
    SellStock(Stock abcstock){
        this->abcstock=abcstock;
    }
    void execute(){
        abcstock.buy();
    }
};
//-----维护客户端的集合链表----------
class Broker{
private:
    list<Order*>orderList;
public:
    void takeOrder(Order*order){
        orderList.push_back(order);
    }
    void placeOrders(){
        list<Order*>::iterator iter=orderList.begin();
        for(;iter!=orderList.end();iter++){
            (*iter)->execute();
            delete (*iter);
        }
        orderList.clear();
    }
};
int main(){
    Stock abcStock;
    Order *buyStockOrder= new BuyStock(abcStock);
    Order *sellStockOrder=new SellStock(abcStock);
    Broker broker;

    broker.takeOrder(buyStockOrder);
    broker.takeOrder(sellStockOrder);
    broker.placeOrders();
    delete buyStockOrder;
    buyStockOrder=NULL;
    delete sellStockOrder;
    sellStockOrder= NULL;
}