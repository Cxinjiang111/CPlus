#include<iostream>
#include<mutex>
#include<atomic>
#include<memory>
mutex mt;
using namespace std;
/*
面向对象很好地解决了"抽象” 的问题，但是必不可免地要付出
一定的代价。 对千通常情况来讲，面向对象的成本大都可以忽略不计。
 但是某些情况，面向对象所带来的成本必须谨慎处理。
 在软件系统中，，经常有这样的的特殊类，必须保证它们在
 系统中只存在一个实例
 总结：
 Singleton模式中的实例构造器可以设置为protected以允许子类派生
 Singleton模式一般不要支持拷贝构造函数和CLONE接口，因为
 这有可能导致多个对象实例，
*/
class Signleton{
public:
    static Signleton*getInstance();
    static Signleton*m_instance;
private:
    Signleton();//构造函数
    Signleton(const Signleton&other);//拷贝构造函数
};
//单线程安全
Signleton*Signleton::m_instance=nullptr;
Signleton*Signleton::getInstance(){
    if(m_instance==nullptr){
        m_instance=new Signleton();
    }
    return m_instance;
}
//多线程安全版本  代价过高
Signleton*Signleton::getInstance(){
     mt.lock();
    if(m_instance==nullptr){
        m_instance=new Signleton();
    }
    mt.unlock();
    return m_instance;
}
//双检查锁，但由于内存读写reorder不安全
/*
不安全的原因式在 m_instance=new Signleton()时
理想分三步，申请内存，调用Signleton默认构造函数 将地址赋给m_instance
在指令级别为申请内存，地址赋给m_instance，调用默认构造函数
*/
Signleton*Signleton::getInstance(){
     if(m_instance==nullptr){
        mt.lock();
             if(m_instance==nullptr){
                m_instance=new Signleton();
        }
         mt.unlock();
     }
    return m_instance;
}
//申请
std::atomic<Signleton*> Singleton::m_instance;
std::mutex  Singleton::m_mutex;
//
Signleton*Signleton::getInstance(){
    Signleton*tmp=m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);;
    if(tmp==nullptr){
        std::lock_guard<std::mutex> lock(m_mutex);//加锁
        tmp=m_instance.load(std::memory_order_relaxed);
        if(tmp==nullptr){ //放置两线程都为空，此时智能进一个
            tmp=new Signleton;
            std::atomic_thread_fence(std::memory_order_release);//释放内存fence
            m_instance.store(tmp,std::memory_order_relaxed);
        }
    }
    return tmp;
}

