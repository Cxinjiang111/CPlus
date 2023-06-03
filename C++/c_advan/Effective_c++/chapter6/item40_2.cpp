#include<string>
class IPerson{ //抽象基类
public:
    virtual ~IPerson();
    virtual std::string name()const=0;
    virtual std::string birthDate()const=0;
};
class DatabaseID{};
class PersonInfo{
public:
    explicit PersonInfo(DatabaseID pid);
     virtual ~PersonInfo();
     virtual const char*theName()const;
     virtual const char*theBirthDate()const;
};
class CPerson:public IPerson,private PersonInfo{
public:
    std::string name()const{
        return PersonInfo::theName();
    }
};




