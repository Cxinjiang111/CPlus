/*条款35：通过mismatch或lexicographical比较实现简单的忽略大小写字符串比较*/
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<string>
#include<functional>
using namespace std;

int ciCharCompare(char c1,char c2)
{
    //tolower的参数和返回值类型是int
    //在C和C++中，char可能或可能不是有符号的（依赖于实现），当char
    //有符号时，唯一确认它的值可以表现为unsigned char的方式是在调用tolower之前转换一下
    int Ic1=tolower(static_cast<unsigned char>(c1));
    int Ic2=tolower(static_cast<unsigned char>(c2));
    if(Ic1<Ic2) return -1;
    if(Ic1>Ic2) return 1;
    return 0;
//它基于mismatch算法，因为mismatch确定了两个区间中第一个对应的不相同的值的位置。
}
int ciStringCompareImpl(const string&s1,const string&s2)
{
/*
inline pair<_InputIterator1, _InputIterator2>
mismatch(_InputIterator1 __first1,  _InputIterator1 __last1,  _InputIterator2  __first2,   _BinaryPredicate __binary_pred)
*/

    typedef pair<string::const_iterator,string::const_iterator> PSCI;
    //not2(ptr_fun(ciCharCompare))这个有点难记。。。。。
    PSCI p=mismatch(s1.begin(),s1.end(),s2.begin(),not2(ptr_fun(ciCharCompare)));
    //如果为真，s1等于s2或者s1比s2短
    if(p.first==s1.end())
    {

        if(p.second==s2.end())
            return 0;
        else
            return -1;
    }

    return ciCharCompare(*p.first,*p.second);//真正区比较第一个遇到不同的字母的排序问题

}
/*
幸运的是，注释把所有东西都弄清楚了。基本上，一旦你知道了字符串中第一个不同字符的位置，就可以很
容易决定哪个字符串, 如果有的话，在另一个前面。唯一可能感到奇怪的是传给mismatch的判断式，也就是
not2(ptr_fun(ciCharCompare))。当字符匹配时这个判断式返回true，因为当判断式返回false时mismatch会停
止。我们不能为此使用ciCharCompare，因为它返回-1、1或0，而当字符匹配时它返回0，就像strcmp。如果我
们把ciCharCompare作为判断式传给mismatch，C++会把ciCharCompare的返回类型转换为bool，而当然bool中
零的等价物是false，正好和我们想要的相反！同样的，当ciCharCompare返回1或-1，那会被解释成true，因
为，就像C，所有非零整数值都看作true。这再次和我们想要的相反。要修正这个语义倒置，我们在
ciCharCompare前面放上not2和ptr_fun，而且我们都会一直很快乐地生活。
*/
int ciStringCompare(const string&s1,const string&s2)
{
    //首先比较大小 不能比较为空
    if(s1.size()<=s2.size())return ciStringCompareImpl(s1,s2);
    else return -ciStringCompareImpl(s2,s1);//
}





