/*
有些人反对以不同的函数分别提供接口和缺省实现， 像上述的 fly和 defaultFly那样。 
他们关心因过度雷同的函数名称而引起的class命名空间污染问 题。 但是他们也同意，
接口和缺省实现应该分开。 这个表面上看起来的矛盾该如何解决？唔， 
我们可以利用 “purevirtual函数必须在derived classes中重新声明， 
但它们也可以拥有自己的实现“ 这一事实。 下面便是Airplane继承体系如何给pure virtual函数一份定义：
*/
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
class ModelA:public Airplane{
public:
    virtual void fly(const Airport&destination){
        Airplane::fly(destination);
    }

};
class ModelB:public Airplane{
    virtual void fly(const Airport&destination){
        Airplane::fly(destination);
    }
};

class ModelC:public Airplane{
public:
    virtual void fly(const Airport&destination);
};
void ModelC::fly(const Airport&destination)
{
    
}
/*
儿乎和前一个设计一模一样，只不过purevirtual函数Airplane::fly替换了独欢函数Airplane::defaultFly。
本质上，现在的fly被分割为两个基本要素：其声明部分表现的是接口（那是derivedclasses必须使用的），
其定义部分则表现出缺省行为（那是derivedclasses可能使用的，但只有在它们明确提出申请时才是）。 
如果合并fly和defaultFly，就丧失了“让两个函数享有不同保护级别”的机会：
习惯上被设为protected的函数(defaultFly)如今成了public（因为它在fly之中）。

*/