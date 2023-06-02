/*
若不想使用编译器自动生成的 函数，就该明确拒绝
申明为private 并不是一个较好的方法， 毕竟friend还是可以调用它
*/
class HomeForSale{
public:
    HomeForSale(){}

    //HomeForSale(const HomeForSale&)=delete;
    //HomeForSale& operator=(const HomeForSale&)=delete;
private:
    HomeForSale(const HomeForSale&);
    HomeForSale& operator=(const HomeForSale&);
};

int main2()
{
    HomeForSale h1;
    HomeForSale h2;
    //HomeForSale h3(h1);// 不希望存在复制这种现象，为了防止编译器自己生成这种函数，明确拒绝 使用delete
   // h1=h2;//将其申明为private依然会报错，编译器依然会
   return 0;
}
//可以专门设计一个阻止copying动作而设计的base class类
class Uncopyable{
protected:
    Uncopyable(){}
    ~Uncopyable(){}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable&operator=(const Uncopyable&);
};
class HomeForSale1:public Uncopyable{
public:
    HomeForSale1();
};
int main()
{
    HomeForSale1 h1;
    HomeForSale1 h2;
    HomeForSale1 h3(h1);//通过基类形式化的 可以避免
    h1=h2;//
}