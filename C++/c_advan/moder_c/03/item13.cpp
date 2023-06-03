#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
#include<algorithm>
using namespace std;
void t1(){
    std::vector<int> vals{10,4,12,12};
    //我查找vector容器中是否存在一个数，没有这个数呢，我就加上，有就算了，下面没有用if去判断it的形式来决定是否添加元素
    std::vector<int>::iterator it=std::find(vals.begin(),vals.end(),10);
    //option 1
    if(it!=vals.end()){
         vals.insert(it,11);//找到之后这是可以插入的呀
    }
    //option 2
    vals.insert(it,11);//找到之后这是可以插入的呀
    //*it=20;
    for(auto &t:vals){
        cout<<t<<endl;
    }
}
void t2(){
    //编译没有报错 而且可以正常运行 可能是编译器做了处理
    typedef std::vector<int>::iterator iter;
    typedef std::vector<int>::const_iterator coniter;
    std::vector<int> vals{};

    coniter it=std::find(static_cast<coniter>(vals.begin()),static_cast<coniter>(vals.end()),11);

    vals.insert(static_cast<coniter>(it),15);// 可能⽆法通过编译，原因⻅下
    /*
    typedef不是强制的，但是可以让类型转换更好写。（你可能想知道为什么我使⽤typedef而不是Item
9提到的别名声明，因为这段代码在演⽰C++98做法，别名声明是C++11加⼊的特性）
之所以std::find的调⽤会出现类型转换是因为在C++98中values是⾮常量容器，没办法简简单单的从
⾮常量容器中获取const_iterator。严格来说类型转换不是必须的，因为⽤其他⽅法获取
const_iterator也是可以的（⽐如你可以把values绑定到常量引⽤上，然后再⽤这个变量代替
values），但不管怎么说，从⾮常量容器中获取const_iterator的做法都有点别扭。
当你费劲地获得了const_iterator，事情可能会变得更糟，因为C++98中，插⼊操作的位置只能由
iterator指定，const_iterator是不被接受的。这也是我在上⾯的代码中，将const_iterator转换为
iterat的原因，因为向insert传⼊const_iterator不能通过编译。
    ⽼实说，上⾯的代码也可能⽆法编译，因为没有⼀个可移植的从const_iterator到iterator的⽅法，即
使使⽤static_cast也不⾏。甚⾄传说中的⽜⼑reinterpret_cast也杀不了这条鸡。（它C++98的限
制，也不是C++11的限制，只是const_iterator就是不能转换为iterator，不管看起来对它们施以转换
是有多么合理。）不过有办法⽣成⼀个iterator，使其指向和const_iterator指向相同，但是看起来不
明显，也没有⼴泛应⽤，在这本书也不值得讨论。除此之外，我希望⽬前我陈述的观点是清晰的：
const_iterator在C++98中会有很多问题。这⼀天结束时，开发者们不再相信能加const就加它的教
条，而是只在实⽤的地⽅加它，C++98的const_iterator不是那么实⽤。
    */
    for(auto &t:vals){
        cout<<t<<endl;
    }
}
int main(){

    //t1();
    t2();

    return 0;
}