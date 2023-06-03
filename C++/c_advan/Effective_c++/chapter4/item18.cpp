/*
让接口容易被正确使用，不易被误用

*/
class Date1{
public:
    Date1(int month,int  day,int year);
private:
    int month;
    int day;
    int year;
};
//类型全部是int 那么很容易出错。至少没法却分三者 因此区分三者，就是让它类型不一致

struct Day
{
    explicit Day(int d):val(d){}
    int val;
};
struct Month
{
    static Month Jan(){return Month(1);}
    explicit Month(int d):val(d){}
    int val;
};
struct Year
{
    explicit Year(int d):val(d){}
    int val;
};
class Date{
public:
//这样正确类型就能定位
    Date(Month month1,Day  day1,Year year1):month(month1),day(day1),year(year1){};
private:
    Month month;
    Day day;
    Year year;
};
int main()
{

    Date d(Month(3),Day(30),Year(1995));//ok
    //Date d2(Day(2),Month(3),Year(555));//error
}