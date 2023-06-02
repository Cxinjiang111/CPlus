/*
以独立语句将newed对象置入智能指针
*/
#include<memory>
#include<string>
class Widget{

};
int priority();
void processWidget(std::shared_ptr<Widget> pw,int priority);


int main()
{
    //processWidget(new Widget,priority());//目前编译器不允许转换
    processWidget(std::shared_ptr<Widget> (new Widget),priority());//这样可能会发生内存泄漏
    //原因时1. new Widget 2.priority() 3. shared_ptr构造函数 三个发生的顺序未知，那么new 后，priority发生异常之后，new 的资源就算泄漏了

    //以下就强制性规定了申请和管理资源能够得到保证
    std::shared_ptr<Widget> pw(new Widget);
    processWidget(pw,priority());
}