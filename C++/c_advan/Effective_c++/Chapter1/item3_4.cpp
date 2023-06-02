/* 在const和non-const成员函数中避免重复
对千 “ bitwise-constness非我所欲＂的问题，mutable是个解决办法， 
但它不 能解决所有的const相关难题。举个例子，假设TextBlock（和CTextBlock)内的operator[]
不单只是返回一个reference指向某字符， 也执行边界检验(bounds checking)、 志记访问信息(logged access info.)、
 甚至可能进行数据完善性检验。把所有这些同时放进const和non-const operator[］中， 
 导致这样的怪物（暂且 不管那将会成为一个 “长度颇为可议” 的隐喻式inline函数一见条款30) : 
*/
#include<iostream>
#include<string>
#include<string.h>
using namespace std;
class TextBlock1{
public:
    TextBlock1(std::string t):text(t){}
//我有时想用const 又是又想用非const 但是代码基本完全一样，代码就会重复很多
    const char&operator[](std::size_t position)const{
                            //边界检验(bounds checking) 
                            //志记数据访问<log access data) 
                            //检验数据完整性(verify data integrity)
        return text[position];
    }
    // char&operator[](std::size_t position){


    //     return text[position];
    // }

private:
    std::string text;
};

class TextBlock{
public:
    TextBlock(std::string t):text(t){}
//我有时想用const 又是又想用非const 但是代码基本完全一样，代码就会重复很多
    const char&operator[](std::size_t position)const{
                            //边界检验(bounds checking) 
                            //志记数据访问<log access data) 
                            //检验数据完整性(verify data integrity)
        cout<<" const"<<endl;  
        return text[position];
    }
    char&operator[](std::size_t position){
        cout<<"非 const"<<endl;
        //这个得记住就行了
        return const_cast<char&>(static_cast<const TextBlock&>(*this)[position]); 
    }
private:
    std::string text;
};

int main()
{
    // TextBlock b("hello");
    // cout<<b[0]; //这个非const调用const 
    // //b[0]='x';//error 但是不具有修改这个特性

    const TextBlock b("hello");
    b[0]; //这个非const调用const 
    //b[0]='x';//但是不具有修改这个特性
    cout<<"========"<<endl;
    TextBlock b1("hello");
    //这个非const调用const 
    b1[0]='x';//调用1.  b1[0] 调用2.static_cast<const TextBlock&>(*this)[position] 
/*
const
========
非 const
const
*/
    return 0;
}
/*
如你所见， 这份代码有两个转型动作， 而不是一个。 我们打算让non-const operator[]调用其const兄弟， 
但non-constoperator[］内部若只是单纯调用perator[］，会递归调用自己。那会大概……唔……进行一百万次。
 为了避免无穷递归， 我们必须明确指出调用的是const operator [], 但C++缺乏直接的语法可 以那么做。
  因此这里将 ＊this从其原始类型TextBloc胚转型为 const TextBlock&。 
  是的， 我们使用转型操作为它加上const！所以这里共有两次转型：
第一次用来为*this添加const（这使接下来调用 operator[］时得以调用const
第二次则是从const operator[］的返回值中移除const。

添加const的那一次转型强迫进行了一次安全转型（将non-const对象转为 const对象），所以我们使用 static—cast。
移除const的那个动作只可以藉由const_cast完成，没有其他选择（就技术而言其实是有的；一个C-style转型也行 得通，
但一如我在条款 27所说，那种转型很少是正确的抉择。如果你不熟悉static_cast或constcast,条款27提供了一份概要）。



更值得了解的是， 反向做法一一令const版本调用non-const版本以避免重 一并不是你该做的事。 
记住， const成员函数承诺绝不改变其对象的逻辑状态(logical state), non-con st成员函数却没有这般承诺。 如
果在const函数内调用non-const函数， 就是冒了这样的风险：你曾经承诺不改动的那个对象被改动了。
这就是为什么 “const成员函数调用non-const成员函数 ” 是一种错误行为： 因为 对象有可能因此被改动。
 实际上若要令这样的代码通过编译， 你必须使用一个 const_cast将＊this身上的const性质解放掉，这是乌云罩顶的清晰前兆。
 反向调 用（也就是我们先前使用的那个）才是安全的：non-canst成员函数本来就可以对 其对象做任何动作， 
 所以在其中调用一个const成员函数并不会带来风险。 这就 是为什么本例以static_cast作用于＊this的原因：这里并不存在const相关危险。

*/