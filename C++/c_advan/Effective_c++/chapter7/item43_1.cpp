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
问题在于，当编译器遭遇classtemplate LoggingMsgSender定义式时，并不知道它继承什么样的class。
当然它继承的是MsgSender<Company>，但其中的Company 是个template参数，不到后来
（当LoggingMsgSender被具现化）无法确切知道它是什么。而如果不知道Company是什么，
就无法知道classMsgSender<Company>看起来像什么－－更明确地说是没办法知道它是否有个sendClear函数。
*/
class Companz{
public:
    void sendEncrypted(const std::string&msg);

};
/*
一般性的MsgSender template对CompanyZ并不合适，因为那个template提供了一个sendClear函数
（其中针对其类型参数Company调用了sendCleartext函数），而这对CompanyZ对象并不合理。
欲矫正这个问题，我们可以针对CompanyZ 产生一个MsgSender特化版：
*/
template<>
class MsgSender<Companz>
{
    public:
        void sendSecret(const MagInfo&info){

        }

};
/*
注意class定义式最前头的“template令＂语法象征这既不是template也不是 标准class,
而是个特化版的MsgSendertemplate,在template实参是CornpanyZ时 被使用。
这是所谓的模板全特化(totaltemplate specialization) : template MsgSender 
针对类型CompanyZ特化了，而且其特化是全面性的，也就是说一旦类型参数被定义为CompanyZ,
再没有其他template参数可供变化。
*/







