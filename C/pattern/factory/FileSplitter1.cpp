#include<iostream>
/*
简单工厂模式的结构组成：
工厂类(ShoesFactory)：工厂模式的核心类，会定义一个用于创建指定的具体实例对象的接口。
抽象产品类(Shoes)：是具体产品类的继承的父类或实现的接口。
具体产品类(NiKeShoes\AdidasShoes\LiNingShoes)：工厂类所创建的对象就是此具体产品实例。
简单工厂模式的特点：
工厂类封装了创建具体产品对象的函数。
简单工厂模式的缺陷：
扩展性非常差，新增产品的时候，需要去修改工厂类。
简单工厂模式的代码：
Shoes为鞋子的抽象类（基类），接口函数为Show()，用于显示鞋子广告。
NiKeShoes、AdidasShoes、LiNingShoes为具体鞋子的类，
分别是耐克、阿迪达斯和李宁鞋牌的鞋，它们都继承于Shoes抽象类
*/
class Shoes{
public:
    virtual void show()=0;
    virtual ~Shoes(){}
};
//具体实现类
class NikeShoes:public Shoes{
public :
    void show(){
        std::cout<<"NIKe shoes"<<std::endl;
    }
};

class AdidasShoes:public Shoes{
public :
    void show(){
        std::cout<<"NIKe shoes"<<std::endl;
    }
};
class LiNingShoes:public Shoes{
public :
    void show(){
        std::cout<<"NIKe shoes"<<std::endl;
    }
};
//实现
enum SHOES_TYPE{
    NIKE,
    LINING,
    ADIDAS
};
class ShoesFactory{
public:
    Shoes *CreatorShoes(SHOES_TYPE type){
        switch(type)
        {
            case NIKE:
                return new NikeShoes();
            break;
            case LINING:
                return new AdidasShoes();
            break;
            case ADIDAS:
                return new LiNingShoes();
            break;
        }
    }
};
int main(){
    ShoesFactory shoesFactory;//先创建工厂对象，
    Shoes *pNikeShoes=shoesFactory.CreatorShoes(NIKE);//创建指定类型的具体鞋子铲平对象
    if(pNikeShoes!=nullptr){
        pNikeShoes->show();
        delete pNikeShoes;
        pNikeShoes=nullptr;
    }
     Shoes *pLiNingShoes=shoesFactory.CreatorShoes(LINING);//创建指定类型的具体鞋子铲平对象
    if(pLiNingShoes!=nullptr){
        pLiNingShoes->show();
        delete pLiNingShoes;
        pLiNingShoes=nullptr;
    }
     Shoes *pAdidasShoes=shoesFactory.CreatorShoes(ADIDAS);//创建指定类型的具体鞋子铲平对象
    if(pAdidasShoes!=nullptr){
        pAdidasShoes->show();
        delete pAdidasShoes;
        pAdidasShoes=nullptr;
    }

}