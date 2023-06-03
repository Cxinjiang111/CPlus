#include<string>
class CompanyA{
public:
    void sendCleartext(const std::string&msg);
    void sendEncrypted(const std::string&msg);
};
class CompanyB{
public:
    void sendCleartext(const std::string&msg);
    void sendEncrypted(const std::string&msg);
};
class MagInfo{};//这个class用来保存信息，以备将来产生信息
template<typename Company> //不用的类调用不同类中的函数
class MsgSender{
public:
    void sendClear(const MagInfo&info)
    {
        std::string msg;
        Company c;
        c.sendCleartext(msg);
    }
    void sendSecret(const MsgInfo&info)
    {
    }
};
class Companz{
public:
    void sendEncrypted(const std::string&msg);

};
template<>
class MsgSender<Companz>
{
    public:
        void sendSecret(const MagInfo&info){

        }
};
template<typename Company>
class LoggingMsgSender:public MsgSender<Company>
{
public:
    void sendClearMsg(const MsgInfo&info)
    {
        //将传送前的信息写至log
        sendClear(info);//调用这个函数 调用base class 函数 这段代码无法通过编译
        //将传送后的信息写至log
    }
};
/*
正如注释所言，当base class被指定为MsgSender<CompanyZ>时这段代码不合法，
因为那个class并未提供sendClear函数！那就是为什么C+＋拒绝这个调用的原因：
它知道base class templates有可能被特化，而那个特化版本可能不提供和一般性template相同的接口。
因此它往往拒绝在templatizedbase classes（模板化基类，本例的MsgSender<Company>）
内寻找继承而来的名称（本例的SendClear)。就某种意义而言，
当我们从Object Oriented C+＋跨进Template C++（见条款1)继承就不像以前那般畅行无阻了。
*/
/*
为了重头来过， 我们必须有某种办法令C++ “ 个进入templatized base classes 观察 ＂ 的行为失效。
有三个办法， 第一是在base class函数调用动作之前加上 "this->": 
*/
template<typename Company>
class LoggingMsgSender:public MsgSender<Company>
{
public:
    void sendClearMsg(const MsgInfo&info)
    {
        //将传送前的信息写至log
        this->sendClear(info);// 成立，假设sendClear将被继承
        //将传送后的信息写至log
    }
};
/*
第二是使用using声明式。如果你已读过条款33,这个解法应该会令你感到熟悉。
条款33描述using声明式如何将“被掩盖的baseclass名称“带入一个derived class作用域内。
我们可以这样写下sendClearMsg:
*/
template<typename Company>
class LoggingMsgSender:public MsgSender<Company>
{
public:
    using MsgSender<Company>::sendClear;//添加作用域 限制的成分是适应基类的成员
    void sendClearMsg(const MsgInfo&info)
    {
        //将传送前的信息写至log
        sendClear(info);// 成立，假设sendClear将被继承
        //将传送后的信息写至log
    }
};
/*
（虽然using声明式在这里或在条款33都可有效运作，但两处解决的问题其实不相同。
这里的情况并不是baseclass名称被derivedclass名称遮掩，而是编译器 不进入baseclass作用域内查找，
于是我们通过using告诉它，请它那么做。）
*/
/*第三个做法是，明白指出被调用的函数位于baseclass内：*/
template<typename Company>
class LoggingMsgSender:public MsgSender<Company>
{
public:
    void sendClearMsg(const MsgInfo&info)
    {
        //将传送前的信息写至log
        MsgSender::sendClear(info);//OK,假设sendClear将被继承下来。
        //但这往往是最不让人满意的一个解法，因为如果被调用的是virtual函数，
        //上述 的明确资格修饰(explicitqualification)会关闭“virtual绑定行为"。
        //将传送后的信息写至log
    }
};
/*
从名称可视点(visibilitypoint)的角度出发，上述每一个解法做的事情都相同：
对编译器承诺“baseclass template的任何特化版本都将支持其一般（泛化）版本所提供的接口”。
这样一个承诺是编译器在解析(parse)像LoggingMsgSender这样 的derivedclass template时需要的。
但如果这个承诺最终未被实践出来，往后的编译最终还是会还给事实一个公道。 举个例子，如果稍后的源码内含这个：
*/
int main()
{
    LoggingMsgSender<Companz> zmsSender;
    MagInfo msgData;
    zmsSender.sendClearMsg(msgData);
/*
其中对sendClearMsg的调用动作将无法通过编译， 因为在那个点上， 编译器知道base class是个template特化版本MsgSender<CompanyZ>， 
而且它们知道那个 class不提供sendClear函数， 而后者却是sendClearMsg尝试调用的 函数。
根本而言，本条款探讨的是，面对 ”指涉base class members” 之无效references,编译器的诊断时间可能发生在早期
（当解析derived class template的定义式时），也可能发生在晚期（当那些templates被特定之template实参具现化时）。 
C++的政策是宁愿较早诊断，这就是为什么“ 当base classes从templates中被具现化时“它假设它对那些base classes的内容毫无所悉的缘故。
*/

}
