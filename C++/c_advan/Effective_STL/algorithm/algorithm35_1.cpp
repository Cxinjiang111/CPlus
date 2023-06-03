/*
我们的第二个方法ciStringCompare是产生一个合适的STL判断式：可以在关联容器中用作比较函数的函数。这
个实现很短也很好，因为我们需要做的是把ciCharCompare修改为一个有判断式接口的字符比较函数，然后把
进行字符串比较的工作交给STL中名字第二长的算法——lexicographical_compare：
*/
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<string>
#include<functional>
using namespace std;
bool ciCharLess(char c1,char c2)
{
    return tolower(static_cast<unsigned char>(c1))<tolower(static_cast<unsigned char>(c2));
}
bool ciStringCompare(const string&s1,const string &s2)
{
    return lexicographical_compare(s1.begin(),s1.end(),s2.begin(),s2.end(),ciCharLess);
}
/*
在上面的调用中，lexicographical_compare用来寻找s1和s2第一个不同的位置，基于调用ciCharLess的结果。如
果，使用那个位置的字符，ciCharLess返回true，lexicographical_compare也是；如果，在第一个字符不同的位
置，从第一个字符串来的字符先于对应的来自第二个字符串的字符，第一个字符串就先于第二个。就像
strcmp，lexicographical_compare认为两个相等值的区间是相等的，因此它对于这样的两个区间返回false：第一
个区间不在第二个之前。也像strcmp，如果第一个区间在发现不同的对应值之前就结束了，
lexicographical_compare返回true：一个先于任何区间的前缀是一个前缀。
*/
int main()
{
    string s1="abcDmoip";
    string s2="abcde";
    if(ciStringCompare(s1,s2))
        cout<<"ok s1>s2"<<endl;
    else
        cout<<" no s1<s2"<<endl;
    return 0;
}



