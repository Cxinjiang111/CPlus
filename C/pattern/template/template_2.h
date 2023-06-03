#include<iostream>

class Library{  //父类
public:
void run(){  //稳定的template method
        step1();
    if(step2()){
        step3();
    }
    for(int i=0;i<4;i++){
        step4();//支持变化==》虚函数的多态调用
    }
    step5();
}
virtual ~Library(){}
protected:
    void step1(){ //稳定
         std::cout<<"liarary step1()"<<std::endl;
    }
    void step3(){
        std::cout<<"liarary step3()"<<std::endl;
    }
    void step5(){
        std::cout<<"liarary step5()"<<std::endl;
    }

    virtual bool step2()=0; //变化
    virtual void step4()=0;
};
class application:public Library{
    protected:
    virtual bool step2(){
        std::cout<<"application step2()"<<std::endl;
        return true;
    }
    virtual void step4(){
    std::cout<<"application step4()"<<std::endl;
    }
};
