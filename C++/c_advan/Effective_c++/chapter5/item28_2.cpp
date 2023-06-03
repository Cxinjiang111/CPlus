#include<memory>
#include<string>

class IMother
{
   virtual std::string GetName() const = 0;

};

class Mother: public IMother
{
   // Implementation of IMother and other stuff

};


class Family {
public:

     Mother mother() { return Mother(_motherName, _motherBirthDate); }

     void mother(Mother m) {
         _motherName = m.name();
         _motherBirthDate = m.birthDate();
     }

private:
     std::string _motherName;
     int _motherBirthDate;
};
//--------------------

/*
如果Mother接口很大，可能会很无聊，但这可能是设计问题（好的接口应具有3-5-7个成员），这将使您以更好的方式进行重新设计。

在第二种情况下，您仍然需要返回整个对象。 有两个问题：

封装分解（最终用户代码将取决于Mother定义）
所有权问题（悬空的指针/引用）
要解决问题1，请使用接口而不是特定的类；要解决问题2，请使用共享或弱所有权：
*/

class Family
{
   std::shared_ptr<IMother> GetMother() const { return mommy; }
   std::weak_ptr<IMother> GetMotherWeakPtr() const { return mommy; }


private:
   std::shared_ptr<Mother> mommy;
};