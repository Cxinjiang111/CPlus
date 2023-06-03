#include<iostream>
#include<set>
#include<unordered_map>
class Folder;
class Message{
    friend class Folder;//以便访问私有成员
    public:
        //folder被隐式初始化为空集合
        explicit Message(const std::string &str=""):contents(str){}
        //拷贝控制成员，用来管理指向本Message的指针
        Message(const Message&);
        //拷贝赋值运算符
        Message &operator=(const Message&);
        ~Message();
        Message(Message&&m);  //右值
        Message&operator=(Message&&m);
        //将Message保存在指定Folder中
        void save(Folder&);
        //从Folder中删除Message
        void remove(Folder&);
        bool operator<(const Message *msg){return this->contents< msg->contents;}
        friend void swap(Message &lhs,Message &rhs);
        //j将m的FOlder交接给本类对象
        //并且实现FOlder和本类对象的关联,解除Folder和m的关联
        void move_Folders(Message *m);
        void printMsg();
    private:
        std::string contents;//消息内容
        std::set<Folder*> folders;//消息所属文件夹
        void add_to_Folders(const Message&msg);//将本Message添加到参数msg的folder
        void remove_from_Folders();//从folder中的每个Folfer删除本Message
};
//--------------------------Folder----------------------
class Folder{
    friend class Message;
    public:
        explicit Folder(const std::string &nm=""):name(nm){}
        Folder(const Folder&);//拷贝控制成员
        Folder &operator=(const Folder&);//拷贝赋值运算符
        ~Folder();
        void addMsg(Message&);//保存指定的msg
        void remMsg(Message&);//移除制定的msg
        bool operator<(const Folder*folder){return this->name<folder->name;}
        friend void swap(Folder &lf,Folder&rf);
    private:
        void remove_msgs();//删除folder中的所有的msg
        void add_msgs(const  Folder&f);//将f中的msg添加本folder中 多个
        std::string name;//文件夹名字
        std::unordered_map<std::string,Message*>msgs;//包含的消息列表
};
