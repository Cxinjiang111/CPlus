#include"msgfolder.h"
#include<iostream>
using namespace std;
//将Message保存在指定Folder中
void Message::save(Folder& s){
     this->folders.insert(&s);//将文件夹f添加到msg的folders里
     s.addMsg(*this);//将本msg添加到folder中
}
void Message::remove(Folder&f){//从Folder中删除Message
    this->folders.erase(&f);//将文件夹从msg的folders里删除
    f.remMsg(*this);
}
void Folder::addMsg(Message&m){
    this->msgs.insert(make_pair(m.contents,&m));
}
void Folder::remMsg(Message&msg){
    this->msgs.erase(msg.contents);
}
void Message::add_to_Folders(const Message &msg){
    for(auto f:msg.folders){
        f->addMsg(*this);
    }
}
//拷贝构造函数将m的folders拷贝给自己
Message::Message(const Message &m){
    contents=m.contents;
    folders=m.folders;
    add_to_Folders(m);
}

void Message::remove_from_Folders(){
    for(auto f:folders){
        f->remMsg(*this);
    }
}
Message::~Message(){
    remove_from_Folders();
}
Message&Message::operator=(const Message &msg){
    remove_from_Folders();//删除this指针
    this->contents=msg.contents;
    this->folders=msg.folders;
    add_to_Folders(msg);//文件夹这边的信息也需更新以下
    return *this;
}
void Message::move_Folders(Message *m){
    this->folders=m->folders;
    for(auto f:folders){
        f->remMsg(*m);//将所有含本信息的全部删除，因为本信息只有一个副本
        f->addMsg(*this);//将权力从指向m变为指向自身，这样就实现move
    }
    m->folders.clear();//
}
Message::Message(Message&&m):contents(std::move(m.contents)){
    move_Folders(&m);
}
Message& Message::operator=(Message &&m){
    if(this!=&m){
        remove_from_Folders();//断掉与Folder之间的联系，这样就会让新的连接Folder
        contents=std::move(m.contents);//contents 权力的交接
        move_Folders(&m);//移动到新的文件夹
    }
    return *this;
}
void Message::printMsg(){
    cout<<"contents is" <<contents<<endl;
}
void swap(Message&lhs,Message&rhs){
     //将lhs从关联的folders中移除
    lhs.remove_from_Folders();
    rhs.remove_from_Folders();
    swap(lhs.contents,rhs.contents);
    swap(lhs.folders,rhs.folders);
     //重新将lhs添加到关联的folders中
    lhs.add_to_Folders(lhs);
    rhs.add_to_Folders(rhs);
}
Folder::Folder(const Folder &f){
    this->msgs=f.msgs;
    this->name=f.name;
    add_msgs(f);
}
//删除folder中的所有msgs
void Folder::remove_msgs(){
    for(auto msgit=this->msgs.begin();msgit!=this->msgs.end();){
        msgit->second->folders.erase(this);
        msgit=this->msgs.erase(msgit);
    }
}
// 将f中的msgs添加到本folder中
void Folder::add_msgs(const Folder&f){
    //将f的msgs添加到本folder
    for(auto mp:f.msgs){
        //将消息保存在本folder
        mp.second->save(*this);
    }
}
Folder::~Folder(){
    remove_msgs();
    msgs.clear();
}
Folder &Folder::operator=(const Folder&f){
    //删除与folder的连接，f需要来接管
    remove_msgs();
    this->name=f.name;
    this->msgs=f.msgs;
    //现在用f彻底来接管，使得message只有一个
    add_msgs(f);
    return *this;
}
void swap(Folder&lf,Folder&rf){
    //先解除lf的msg和其的联系
    lf.remove_msgs();
    //再解除rf的msg和其的联系
    rf.remove_msgs();
    //交换数据结构
    swap(lf.msgs, rf.msgs);
    swap(lf.name, rf.name);
    //最后各自绑定msg和其folder的联系
    lf.add_msgs(lf);
    rf.add_msgs(rf);
}

int main(){
    auto f1 = new Folder("folder1");
    auto msg1 = new Message("msg1");
    msg1->save(*f1);
    auto f2 = new Folder("folder2");
    auto msg2 = new Message("msg2");
    msg2->save(*f2);
    auto f3 = new Folder(*f1);
    *f3 = *f2;
    swap(f1, f2);
    delete (f1);
    delete (msg1);
    delete (f2);
    delete (msg2);
    delete (f3);
    auto msg4 = new Message("msg4");
    msg4->printMsg();
    auto msg3 = new Message("msg3");
    msg3->printMsg();
    *msg4 = std::move(*msg3);
    msg4->printMsg();
    delete msg4;
    delete msg3;
}






