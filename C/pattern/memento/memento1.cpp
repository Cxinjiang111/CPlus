#include<iostream>
#include<vector>
using namespace std;
/*
19.1 定义
　　不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。
    这样，以后就可以将该对象恢复到原先保存的状态。
19.2 使用场景
　　■ 需要保存和恢复数据的相关状态场景。
　　■ 提供一个可回滚的操作。
　　■ 需要监控副本的场景。例如，监控一个对象的属性，但是监控又不应该作为系统的主业务来调用，
它只是边缘应用，即使出现监控不准、错误报警也影响不大，
因此一般做法是备份一个主线程中的对象，然后由分析程序来分析。
　　■ 数据库连接的事务管理使用的就是备忘录模式
*/
//恢复的状态
class Backup{
public:
    string content;//需要备份
    int version;//不需要备份
public:
    Backup(string content){
        this->content=content;
    }
};
//从需要备忘的文档得到的状态
class Document{
public:
    string content;
    string otherContent;
public:
    Backup *save(){
        cout<<"save memento"<<endl;
        return new Backup(content);
    }
    void resume(Backup*backup){//这里Backup*backup
        cout<<"resume memento"<<endl;
        content=backup->content;
    }
    string toString(){
        return "content"+content+",otherconter:"+otherContent;
    }
};
//维护备忘录的其中的状态 处于保存状态中的
class VersiosnControlSystem{
public:
    vector<Backup*>backups;//组合
    int nextVersion=0;
public:
    void add(Backup*backup){
        backup->version=++nextVersion;
        backups.push_back(backup);
    }
    Backup*get(int version){
        for(int i=0;i<backups.size();i++){
            if(backups[i]->version==version){
                return backups[i];
            }
        }
        return NULL;
    }
    Backup*getLastVersion(){
        int len=backups.size();
        if(len>0){
            return backups[len-1];
        }
        else{
            return NULL;
        }
    }
};
int main(){
    VersiosnControlSystem vcs;//建立一个备忘录对象
    Document document;//状态：文档

    document.content="content1";          
    document.otherContent="othercontent1";  
    vcs.add(document.save()); //添加状态
    cout<<document.toString()<<endl;      

    document.content="content2";
    document.otherContent="othercontent2";
    vcs.add(document.save());//添加状态
    cout<<document.toString()<<endl;

    document.resume(vcs.get(1));
    cout<<document.toString()<<endl;

    document.resume(vcs.getLastVersion());
    cout<<document.toString()<<endl;
}




