#include<iostream>
using namespace std;
class Shoes{
public:
    virtual void Show() = 0;
    virtual ~Shoes(){}
};

class NiKeShoes:public Shoes{
public:
     void Show(){
        cout<<"nike "<<endl;
    }
};

class Clothe{
public:
    virtual void Show()=0;
    virtual ~Clothe(){}
};
class UniqloClothe:public Clothe{
public:
    void Show(){
        cout<<"uniqucloth"<<endl;
    }
};
// 抽象模板工厂类
// 模板参数：AbstractProduct_t 产品抽象类
template<class AbstractProduct_t>
class AbstractFactory{
public:
    virtual AbstractProduct_t*CreateProduct()=0;
    virtual ~AbstractProduct_t(){}
};
// 具体模板工厂类
// 模板参数：AbstractProduct_t 产品抽象类，ConcreteProduct_t 产品具体类
template<class AbstractProduct_t,class ConcreateProduct_t>
class ConcreteFactory:public AbstractFactory{
public:
    AbstractProduct_t *CreateProduct(){
        return new ConcreateProduct_t();
    }

};
int main()
{
    // 构造耐克鞋的工厂对象
    ConcreteFactory<Shoes, NiKeShoes> nikeFactory;
    // 创建耐克鞋对象
    Shoes *pNiKeShoes = nikeFactory.CreateProduct();
    // 打印耐克鞋广告语
    pNiKeShoes->Show();

    // 构造优衣库衣服的工厂对象
    ConcreteFactory<Clothe, UniqloClothe> uniqloFactory;
    // 创建优衣库衣服对象
    Clothe *pUniqloClothe = uniqloFactory.CreateProduct();
    // 打印优衣库广告语
    pUniqloClothe->Show();

    // 释放资源
    delete pNiKeShoes;
    pNiKeShoes = NULL;

    delete pUniqloClothe;
    pUniqloClothe = NULL;

    return 0;
}



