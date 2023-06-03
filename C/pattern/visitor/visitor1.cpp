#include<iostream>
#include<string>
using namespace std;
/*
23.1定义
　　封装一些作用于某种数据结构中的各元素的操作，它可以在不改变数据结构的前提下定义作用于这些元素的新的操作
23.2 优点
　　■ 访问者模式使得增加新的操作变得很容易，增加新的操作只需要增加新的访问者类。
　　■ 访问者模式将有关的行为集中到一个访问者对象中，而不是分散到一个个元素类中。
　　■ 访问者模式可以跨过几个类的等级结构访问属于不同等级结构的成员类。
　　■ 累积状态。每一个单独的访问者对象都集中了相关的行为，从而也就可以在访问的过程中将执行操作的状态积累在自己内部，
而不是分散到很多的元素对象中，益于系统的维护。
22.3 缺点
　　■ 增加新的元素类变得很困难。每增加一个新的元素类都意味着要在抽象访问者角色中增加一个新的抽象操作，
并在每一个具体访问者类中增加相应的具体操作。
　　■ 破坏封装。访问者模式要求访问者对象访问并调用每一个元素对象的操作，这隐含了一个对所有元素对象的要求，
即必须暴露一些自己的操作和内部状态，否则访问者的访问就变得没有意义。由于访问者对象自己会积累访问操作所需的状态，
从而使得这些状态不再存储在元素对象中，破坏了类的封装性。
　　■ 违背了依赖倒置原则。访问者依赖的是具体的元素，而不是抽象的元素，这破坏了依赖倒置的原则，特别是在面向对象的编程中，
抛弃了对接口的依赖，而直接依赖实现类，扩展比较难。
22.4 使用场景
　　■ 一个对象结构包含很多类对象，它们有不同的接口，当对这些对象实施依赖于具体类的操作时，
即使用迭代器模式不能胜任的场景下，可以采用访问者模式。
　　■ 需要对一个对象结构中的对象进行很多不同并且不相关的操作，避免操作污染类。
　　■ 业务规则要求遍历多个不同的对象，这本身也是访问者模式的出发点，迭代器模式只能访问同类或同接口的数据，
而访问者模式是对迭代器模式的扩充，可以遍历不同的对象，执行不同的操作。
*/
class Hardware;
class ComputerVisitor;
class CPU;
class Harddisk;
class Hardware {
protected:
    string type;
public:
    Hardware() {
    }
    Hardware(string type) {
        this->type = type;
    }
    string getType() {
        return type;
    }
    virtual void run() = 0;
    virtual void accept(ComputerVisitor* computerVisitor) = 0;
};
class ComputerVisitor {
public:
    virtual void vistCpu(CPU* cpu)=0;
    virtual void vistHarddisk(Harddisk* harddisk) = 0;
};
class CPU :public Hardware {
public:
    CPU(string type) {
        this->type = type;
    }
    void run() {
        cout << "CPU型号为" << this->type << "正在运行" << endl;
    }
    void accept(ComputerVisitor* computerVisitor) {
        computerVisitor->vistCpu(this);
    }
};
class Harddisk :public Hardware {
public:
    Harddisk(string type) {
        this->type = type;
    }
    void run() {
        cout << "Harddisk型号为" << this->type<<"正在运行" << endl;
    }
    void accept(ComputerVisitor* computerVisitor) {
        computerVisitor->vistHarddisk(this);
    }
};
class TypeVisitor:public ComputerVisitor {
public:
    void vistCpu(CPU* cpu) {
        cout << "CPU型号为" << cpu->getType() << endl;
    }
    void vistHarddisk(Harddisk* harddisk) {
        cout << "Harddisk型号为" << harddisk->getType() << endl;
    }

};
class RunVisitor :public ComputerVisitor {
public:
    void vistCpu(CPU* cpu) {
        cpu->run();
    }
    void vistHarddisk(Harddisk* harddisk) {
        harddisk->run();
    }
};
class Computer {
private:
    Hardware* cpu;
    Hardware* harddisk;
public:
    Computer() {
        this->cpu = new CPU("aa");
        this->harddisk = new Harddisk("bb");
    }
    void accept(ComputerVisitor* computerVistor) {
        cpu->accept(computerVistor);
        harddisk->accept(computerVistor);
    }
};
int main() {
    Computer* computer = new Computer();
    ComputerVisitor* typeVisitor = new TypeVisitor();
    ComputerVisitor* runVisitor = new RunVisitor();
    computer->accept(typeVisitor);
    computer->accept(runVisitor);
}