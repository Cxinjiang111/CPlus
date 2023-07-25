#include<iostream>
using namespace std;
class Iterator
{
public:
    virtual void hasNext();
    virtual void next();
    virtual void remove();
};
class Enumeration
{
public:
    bool hasMoreElements();
    void nextElement();
};
bool Enumeration::hasMoreElements(){}
void Enumeration::nextElement(){}
class EnumerationIterator:public Iterator
{
private:
    Enumeration *m_enum;
public:
    //EnumerationIterator(Enumeration *enum):m_enum(enum) {}
    bool hasNext() const { return m_enum->hasMoreElements(); };
    void next() { m_enum->nextElement(); };   
};