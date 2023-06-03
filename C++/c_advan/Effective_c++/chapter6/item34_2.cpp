class Airport{

};
class Airplane{
public:
    virtual void fly(const Airport &destination)=0;
protected:
    void defaultFly(const Airport&destination);
};
void Airplane::defaultFly(const Airport&destination)
{
    //缺省行为，将飞机飞至指定的目的地
}
void Airplane::fly(const Airport &destination)
{

}
void Airplane::fly(const Airport &destination)
{

}
/*
请注意，Airplane: : fly已被改为一个purevirtual函数，只提供飞行接口。其
缺省行为也出现在Airplaneclass中，但此次系以独订函数defaultFly的姿态出现。
若想使用缺省实现（例如ModelA和ModelB)，可以在其fly函数中对defaultFly
做一个inline调用（但请注意条款30所言，inline函数和virtual闭数之间的交互关系）：
*/
class ModelA:public Airplane{
public:
    virtual void fly(const Airport&destination){
        defaultFly(destination);
    }

};
class ModelB:public Airplane{
    virtual void fly(const Airport&destination){
        defaultFly(destination);
    }
};
/*
现在ModelC class不可能意外继承不正确的fly实现代码了， 因为Airplane 
中的pure virtual函数迫使ModelC必须提供自己的fly版本：
*/
class ModelC:public Airplane{
public:
    virtual void fly(const Airport&destination);
};
void ModelC::fly(const Airport&destination)
{
    
}
/*
这个方案并非安全无虞，程序员还是可能因为剪贴(copy-and-paste)代码而招来麻烦， 
但它的确比原先的设计值得倚赖。 至千Airplane::defaultFly, 请注意 它现在成了protected,
因为它是Airplane及其derived classes的实现细目。乘客应该只在意飞机能不能飞，不在意它们怎么飞。

Airplane: :defaultFly是个non-virtual函数，这一点也很重要。因为没有任何一个derived class
应该重新定义此函数（见条款36)。 如果defaultFly是virtual 函数， 就会出现一个循环问题： 
万一某些derived class忘记重新定义defaultFly, 会怎样？
*/