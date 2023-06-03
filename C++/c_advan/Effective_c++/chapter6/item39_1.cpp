/*
*/
class Timer{
public:
    Timer(){};
    explicit Timer(int tickFrequency);
    virtual void onTick()const;//定时器每滴答一次
                                //此函数就 被自动调用一次

};
class Widget:private Timer{
public:
    Widget();
private:
    virtual void onTick()const;
};
Widget::Widget()
{

}
int main()
{
    Widget w;
    return 0;
};
