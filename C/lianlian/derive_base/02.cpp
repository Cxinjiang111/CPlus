#include<iostream>
using namespace std;
//实函数为编译期确定内存
class Base{
    private:
        //private 对virtual与非virtual没啥影响
        virtual void display(){cout<<"Base virtual  display"<<endl;}//虚基类
        void say(){cout<<"Base say"<<endl;}//实函数
    public:
        void f2(){cout<<"Base no override or no virtual "<<endl;}
        virtual void func(){cout<<"Base func()"<<endl;}//虚函数
        void f1(string a){cout<<"Base f1(string)"<<endl;}//两个f1()重载的   
        void f1(int a){cout<<"Base f1(int)"<<endl;}
        void exec(){
            display();
            say();
        }
};
class Derived:public Base{
    public:
        void dispaly(){cout<<"DerivedA diaplay()"<<endl;}//实函数可能覆盖基类
        void f1(int a,int b){cout<<"DerivedA f1(int,int)"<<endl;}//实函数
        void say(){cout<<"Derived say()"<<endl;}//实函数
        virtual void func(){cout<<"DerivedA func()"<<endl;}
        void use_base_f1(){
            Base::f1(2);
            Base::f1("hello ");
        }
        void exec2(){
            dispaly();
            say();
        }
};
int main(){
    Derived *a1=new Derived();
    Base *b1=a1;
    b1->f1("hello ");
    b1->f1(3);
    //derived 
    b1->func();
    cout<<"----------"<<endl;
    //base  base say
    b1->exec();//在调用子类函数 那么就相当于加了一个基类作用域
    //
    cout<<"=========="<<endl;
    //derived 
    a1->dispaly();
    //derivedd 
    a1->say();
    a1->f1(3,5);
    //derived func
    a1->func();
    cout<<"----------"<<endl;
    //derived derive 
    a1->exec2();
    cout<<"----------"<<endl;
    //base base 这个需注意，这儿有点不理解，就是a1调基类函数，在基类函数内部调用，
    //是不是天然的就加了一个基类的作用域，所以才会调用子类函数？感觉这样解释通
    a1->exec();
    cout<<"----------"<<endl;
    //base base
    a1->use_base_f1();
    /*
    Base f1(string)
    Base f1(int)
    DerivedA func()
    ----------
    Base virtual  display
    Base say
    ==========
    DerivedA diaplay()
    Derived say()
    DerivedA f1(int,int)
    DerivedA func()
    ----------
    DerivedA diaplay()
    Derived say()
    ----------
    Base virtual  display
    Base say
    ----------
    Base f1(int)
    Base f1(string)
    */



}
    /*
    考察一个函数是被子类还是基类调用时应该分以下几种情况
    1  该函数是虚函数并且被子类重写，如果是基类指针指向子类对象，调用该函数则引发多态机制，调用子类的虚函数
    2  如果该函数时虚函数并且没有被重写，那么无论调用的对象是基类指针还是子类对象，还是基类对象，
    还是子类指针都是调用基类的这个虚函数
    3  如果该函数不是虚函数，如果该函数被子类覆盖(子类重新定义了同名函数)，那么调用规则就是子类调用子类的该函数，
    基类调用该基类的函数。
    4  如果该函数不是虚函数，并且子类没有定义同名函数(没有覆盖基类同名函数)，那么无论是子类还是基类的指针或者对象，
    统一调用的是基类的函数。
    5  如果第4点里基类的函数(没有被子类覆盖)，但是内部调用了基类的虚函数，并且该虚函数被子类重写，这时内部这个虚函数调用规则
    就要看调用对象的实际类型，符合1的调用标准，多态就走子类，不是多态就走基类(此时符合2标准)
    6  如果第3点里基类的函数(被子类覆盖)，但是内部调用了基类的虚函数，并且该虚函数被子类重写，这时内部这个虚函数调用规则
    就要看调用对象的实际类型，符合1的调用标准，多态就走子类，不是多态就走基类(此时符合2标准)

    */
