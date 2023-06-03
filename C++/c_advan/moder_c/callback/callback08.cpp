#include<iostream>
#include<functional>
#include<map>
using namespace std;
void testfun(string str)
{
    cout<<str<<endl;
}
using tTask=std::function<void(std::string)>;
class ThreadObject{
public:
    ThreadObject();
    ~ThreadObject();
public:
    void setTask(tTask task)
    {
        m_task=task;
    }
    void run()
    {
        m_task("okok");
    }
private:
    tTask m_task;//functional
};
ThreadObject::ThreadObject()
{

}
ThreadObject::~ThreadObject()
{

}

int main()
{
    tTask t1=testfun;
    ThreadObject obj;

    //obj.setTask(t1);
    obj.setTask(bind(&testfun,std::placeholders::_1));//记住这种方式
    obj.run();


}
