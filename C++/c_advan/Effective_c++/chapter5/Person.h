#include<string>
#include<memory>
class Date
{
    public:
    Date(){};
};
class Address
{
    public:
        Address(){};
};
class PersonImpl
{
    public:
        PersonImpl(const std::string&name ,const Date &date,const Address&address):thename(name),thedate(date),thedaddress(address){};
    private:
        std::string thename;
        Date thedate;
        Address thedaddress;
    
};
class Person{
public:
    Person(const std::string &name,const Date&birthday,const Address&addr);
    std::string name()const;
    std::string birthDate()const;
    std::string address()const;
private:
    std::shared_ptr<PersonImpl>pImpl;
};