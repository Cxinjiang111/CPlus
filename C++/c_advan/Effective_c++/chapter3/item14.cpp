/*
在资源管理类中小心copying行为
*/
#include<mutex>
#include<thread>
#include<memory>
class Lock{
public:
    explicit Lock(std::mutex*pm):mutexPtr(pm){
        std::lock(mutexPtr);//获得资源
    }
    ~Lock(){
        std::unlock();//释放资源
    }
private:
    //std::mutex *mutexPtr; 
    std::shared_ptr<std::mutex> mutexPtr;//代替raw pointer
};
std::mutex m;

class Lock{
public:
    explicit Lock(std::mutex*pm):mutexPtr(pm){
        std::lock(mutexPtr);//获得资源
    }
private:
//这里没必要再写析构函数了 由shared_ptr会调用自己的删除器，
    std::shared_ptr<std::mutex> mutexPtr;//代替raw pointer
};
