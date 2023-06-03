/*学习处理模板化基类内的名称
*/
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

