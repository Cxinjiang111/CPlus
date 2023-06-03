#include<iostream>
#include<vector>
#include<string>
using namespace std;
/*
17.1 定义
　　提供一种方法访问一个容器对象中各个元素，而又不需暴露该对象的内部细节
17.2 优点
　　■它支持以不同的方式遍历一个聚合对象。
　　■迭代器简化了聚合类。
　　■在同一个聚合上可以有多个遍历。
　　■在迭代器模式中，增加新的聚合类和迭代器类都很方便，无须修改原有代码。
17.3 缺点
　　■由于迭代器模式将存储数据和遍历数据的职责分离，增加新的聚合类需要对应增加新的迭代器类，
    类的个数成对增加，这在一定程度上增加了系统的复杂性。
17.4 使用场景
　　■访问一个聚合对象的内容而无须暴露它的内部表示。
　　■需要为聚合对象提供多种遍历方式。
　　■为遍历不同的聚合结构提供一个统一的接口
*/
//抽象迭代角色：该角色负责定义访问和遍历元素的接口。
class Iterator{
public:
    Iterator(){}
    virtual ~Iterator(){};
    virtual string First()=0;
    virtual string Next()=0;
    virtual string GetCur()=0;
    virtual bool IsEnd()=0;
};
//抽象聚合角色：该角色提供创建迭代器角色的接口。 
class Aggregate{
public:
    virtual int Count()=0;
    virtual void Push(const string&strValue)=0;
    virtual string Pop(const int cnt)=0;
};
//具体迭代角色：该角色实现Iterator接口，完成容器元素的遍历。
class ConcreteIterator:public Iterator{
public:
    ConcreteIterator(Aggregate*p_aggregate):m_aggregate(p_aggregate),m_cnt(0){}
    string First(){
        return m_aggregate->Pop(0);
    }
    string Next(){
        string str;
        m_cnt++;
        if(m_cnt<m_aggregate->Count()){
            str=m_aggregate->Pop(m_cnt);
        }
        return str;
    }
    string GetCur(){
        return m_aggregate->Pop(m_cnt);
    }
    bool IsEnd(){
        return m_cnt>=m_aggregate->Count()?true:false;
    }
    ~ConcreteIterator(){}
private:
    Aggregate *m_aggregate;
    int m_cnt;
};
class ConcreteAggregate:public Aggregate{
public:
    ConcreteAggregate(){
        m_vecItem.clear();
    }
    ~ConcreteAggregate(){
    }
    int Count(){
        return m_vecItem.size();
    }
    void Push(const string &strValue){
        m_vecItem.push_back(strValue);
    }
    string Pop(const int cnt){
        string str;
        if(cnt<Count()){
            str=m_vecItem[cnt];
        }
        return str;
    }
private:
    vector<string> m_vecItem;
};
int main(){
    ConcreteAggregate*pName=NULL;
    pName=new ConcreteAggregate();
    if(NULL!=pName){
        pName->Push("hello");
        pName->Push("word");
        pName->Push("cxue");
    }
    Iterator *iter=new ConcreteIterator(pName);
    if(NULL!=iter){
        string strItem=iter->First();
        while(!iter->IsEnd()){
            cout<<iter->GetCur()<<"is ok"<<endl;
            iter->Next();
        }
    }
    delete iter;
    iter=NULL;
    system("pause");
    return 0;
}




