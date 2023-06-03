#include<iostream>

class Library{
public:
    void step1(){
     std::cout<<"liarary step1()"<<std::endl;
    }
    void step3(){
     std::cout<<"liarary step3()"<<std::endl;
    }
    void step5(){
   std::cout<<"liarary step5()"<<std::endl;
    }
};
class application{
public:
    bool step2(){
        std::cout<<"application step2()"<<std::endl;
    }
    void step4(){
         std::cout<<"application step4()"<<std::endl;
    }
};