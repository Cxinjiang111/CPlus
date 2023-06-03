#include<iostream>
#include<list>
#include<memory>
#include<stdio.h>
#include<string>
using namespace std;
/*
8.1定义
　　将对象组合成树形结构以表示“部分—整体”的层次结构，使得用户对单个对象和组合对象的使用具有一致性
8.2 优点
　　■ 高层模块调用简单。一棵树形机构中的所有节点都是 Component，
局部和整体对调用者来说没有任何区别，即高层模块不必关心自己处理的是单个对象还是整个组合结构，简化了高层模块的代码。
　　■ 节点自由增加。使用组合模式后，如果想增加一个树枝节点、树叶节点只需要找到其父节点即可。
8.3 缺点
　　■ 不易控制树枝构件的类型；
　　■ 不易使用继承的方法来增加新的行为。
8.4 使用场景
　　■ 需要描述对象的部分和整体的等级结构，如树形菜单、文件和文件夹管理。
　　■ 需要客户端忽略个体构件和组合构件的区别，平等对待所有的构件。组合模式也是应用广泛的一种设计模式。
*/
class Company{
public:
    virtual string getInfo()=0;
    virtual string getName(){
        return name;
    }
    virtual string getType()=0;
protected:
    string name;
    string position;
    int salary;
};

class ConcreteCompany:public Company{
public:
    ConcreteCompany(string name,string position,int salary){
        this->name=name;
        this->position=position;
        this->salary=salary;
    }
    void add(Company *company){
        shared_ptr<Company> temp(company);
        companylist.push_back(temp);
    }
    string getType(){
        return "Concrete company";
    }
    void remove(string companyName){
        list<shared_ptr<Company>>::iterator iter=companylist.begin();
        for(;iter!=companylist.end();iter++){
            if((*iter).get()->getName()==companyName){
                companylist.erase(iter);
                return ;
            }
        }
    }
    list<shared_ptr<Company>>getChild(){
        return companylist;
    }
    string getInfo(){
        string info="";
        info="名称："+this->name;
        info=info+"\t职位"+this->position;
        info=info+"\t薪水"+to_string(this->salary);
        return info;
    }
private:
    list<shared_ptr<Company>> companylist;
};

class Employ:public Company{
public:
    Employ(string name,string position,int salary){
        this->name=name;
        this->position=position;
        this->salary=salary;
    }
    string getType(){
        return "Employee";
    }
    string getInfo(){
        string info="";
        info="名称："+this->name;
        info=info+"\t职位"+this->position;
        info=info+"\t薪水"+to_string(this->salary);
        return info;
    }
};
void display(ConcreteCompany*root){
    cout<<root->getInfo()<<endl;
    list<shared_ptr<Company>>tmp=root->getChild();
    list<shared_ptr<Company>>::iterator iter=tmp.begin();
    for(;iter!=tmp.end();iter++){
        if((*iter).get()->getType()==string("Employee")){
            cout<<(*iter).get()->getInfo()<<endl;
        }
        else{
            display((ConcreteCompany*)(*iter).get());
        }
    } 
}
int main(){
    ConcreteCompany*root=new ConcreteCompany("张三","CEO",11000);
    ConcreteCompany *develop=new ConcreteCompany("张4","leader",11000);
    ConcreteCompany *sale=new ConcreteCompany("张5","saler",11000);
    Employ*e1=new Employ("A","develop",200);
    Employ*e2=new Employ("B","saler",300);
    Employ*e3=new Employ("C","develop",400);
    Employ*e4=new Employ("D","saler",500);

    root->add(develop);
    root->add(sale);
    develop->add(e1);
    develop->add(e3);
    sale->add(e2);
    sale->add(e4);
    display(root);
    develop->remove("A");
    display(root);
    delete root;
    root=NULL;
    /*
    root      [develop  sale]
    develop   [e1    e3]
    sale      [e2    e4]
    */
}