#include<iostream>
#include<string>
using namespace std;
/*
.1 定义
　　将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。4. Prototype（原型）
3.2 适用场景
　　使用建造者模式的典型场景如下。
　　■ 相同的方法，不同的执行顺序，产生不同的结果时，可以采用建造者模式。
　　■ 多个部件或零件，都可以装配到一个对象中，但是产生的运行结果又不相同时，则可以使用该模式。
　　■ 产品类非常复杂，或者产品类中的方法调用顺序不同产生了不同的效能，这个时候使用建造者模式。
　　■ 在对象创建过程中会使用到系统的一些其他对象，这些对象在产品对象的创建过程中不易得到时，
也可以采用建造者模式封装该对象的创建过程。该种场景只能是一个补偿方法，因为一个对象不容易获得，
而在设计阶段没有发现，要通过创建者模式柔化创建过程，本身已经违反设计的最初目标。
*/
//类太大了就拆开，类太小了就合并
class Product{
public:
    void setPart1(string part1){
        this->m_part1=part1;
    }
    void setPart2(string part2){
        this->m_part2=part2;
    }
    string getPart1(){
        return m_part1;
    }
    string getPart2(){
        return m_part2;
    }
private:
    string m_part1;
    string m_part2;
};
//
class OrderBuilder{
public:
    virtual ~OrderBuilder(){
        cout<<"~OrderBuilder()"<<endl;
    }    
    //方法相同
    virtual void setOrderPart1()=0;
    virtual void setOrderPart2()=0;
    virtual Product *getProduct()=0;//组合
};
//第一个大的功能实现类 具有相同的接口
class FirstOrderBuilder:public OrderBuilder{
public:
    FirstOrderBuilder(){
        m_Product=new Product;
    }
    void setOrderPart1(){
        m_Product->setPart1("getpart1");
    }
    void setOrderPart2(){
        m_Product->setPart2("getpart2");
    }
    ~FirstOrderBuilder(){
        delete m_Product;
        m_Product=nullptr;
    }
    Product *getProduct(){
        return m_Product;
    }
private:
    Product *m_Product;
}; 
//第一个大的功能实现类 具有相同的接口
class secondOrderBuilder:public OrderBuilder{
public:
    secondOrderBuilder(){
        m_Product=new Product;
    }
    void setOrderPart1(){
        m_Product->setPart1("secondgetpart1");
    }
    void setOrderPart2(){
        m_Product->setPart2("secondgetpart2");
    }
    ~secondOrderBuilder(){
        delete m_Product;
        m_Product=nullptr;
    }
    Product *getProduct(){
        return m_Product;
    }
private:
    Product *m_Product;
}; 
///负责管理实例创建的依赖关系，指挥构建者类创建实例
class Director{
public:
    Director(OrderBuilder*builder):m_pOrderBuilder(builder){

    }
    void construct(){
        m_pOrderBuilder->setOrderPart1();
        m_pOrderBuilder->setOrderPart2();
    }
private:
    OrderBuilder * m_pOrderBuilder;
};
int main(){
    OrderBuilder *mBuilder=new secondOrderBuilder;
    Director *director=new Director(mBuilder);
    director->construct();
    cout<<"-------------------"<<endl;
    Product *order=mBuilder->getProduct();
    order->getPart1();
    order->getPart2();
}



