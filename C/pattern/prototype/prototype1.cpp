#include<iostream>
//基类
class ISplitter{
public:
    virtual ISplitter *clone()=0;//克隆自己来创建对象
    virtual void show()=0;
virtual ~ISplitter(){}
};
class BinarySpliter:public ISplitter{
public :
     BinarySpliter():ISplitter(){
    } 
     ~BinarySpliter(){}
     ISplitter *clone(){
         std::cout<<"ok success"<<std::endl;
        return new BinarySpliter(*this);
    }
    void show(){
        std::cout<<"show()"<<std::endl;
    }  
};
int main(){
    ISplitter *prototype=new BinarySpliter();//必须申请的功能函数原型对象
    ISplitter*splitter=prototype->clone();//申请对象，
    splitter->show();//指向对象的功能函数
}