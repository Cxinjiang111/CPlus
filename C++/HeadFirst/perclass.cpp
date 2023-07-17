#include<iostream>
using namespace std;
class FlyBehaviour{
public:
    virtual void fly() = 0;

};
class FlyFly:public FlyBehaviour{
    void fly(){
        cout<<"I can fly!"<<endl;
    }
};
class FlyNoFly:public FlyBehaviour{
    void fly(){
        cout<<"I can't fly!"<<endl;
    }
};

class QuckBehaviour{
public:
    virtual void quck() = 0;
};
class QuckNoquck:public QuckBehaviour{
    void quck()
    {
        cout<<"NOQuck!"<<endl;
    }
};
class Quckquck:public QuckBehaviour{
    void quck()
    {
        cout<<"Quck!"<<endl;
    }
};
class Duck{
private:
    FlyBehaviour* flyBehaviour=nullptr;
    QuckBehaviour* quckBehaviour=nullptr;
public:
    void SetQuckBehaviour(FlyBehaviour* flyBehaviour){ flyBehaviour = flyBehaviour;}
    Duck()
    {
        this->flyBehaviour = new FlyFly();
        this->quckBehaviour = new Quckquck();
    }
    ~Duck(){};
    void performQuck() {
        quckBehaviour->quck();
    }
};

int  main(int argc, char **argv)
{
    Duck *duck=new Duck();
    duck->performQuck();
    return 0;
}