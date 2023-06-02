/*
为多态基类声明virtual析构函数
*/
class TimeKeeper{
public:
    TimeKeeper();
    virtual ~TimeKeeper();

};
class AtomicClock:public TimeKeeper{

};
class Waterlock:public TimeKeeper{

};
class WristWatch:public TimeKeeper{

};
int main()
{
    TimeKeeper *t=new AtomicClock();
    delete t;
}