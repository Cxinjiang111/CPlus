#include "../inc/cincout.h"
#include <string>
void cin_func()
{
    string input;
    cout << "input your words " << endl;
    cin >> input;
    cout << "your input is " << endl;
    cout << input << endl;
}

void var_func()
{
    //整形，4字节
    int a = 100;
    // ll整形, 8字节
    long long lla = 1000;
    //长整型， 4 字节
    long la = 1024;
    //短整型,2 字节
    short sa = 200;
    //带符号字符型,
    //字符型使用时最好指示带符号还是不带符号
    //因为在不同的机器上不指明char符号可能会有问题
    signed char sc = 'a';
    //无符号字符型
    unsigned char uc = 'm';
    // bool类型
    bool bt = true;
}

//类型转换
void convert_func()
{
    bool b = 42;          // b为true
    int i = b;            // i 为1
    i = 3.14;             // i 为3
    double pi = i;        // pi为3.0
    unsigned char c = -1; //
}

//字面值
void const_func()
{
    //宽字符型字面值
    L'a';
    // utf-8字符串常量
    u8"hello world";
    //无符号整形字面值
    42ULL;
    //单精度浮点字面值
    1E-3F;
    //扩展精度浮点字面值
    3.14159L;
}
namespace cincout
{
    //定义a
    int a = 100;
    //声明并定义j
    int j = 20;
    //定义
    extern string m = "Hello";
}

//引用
void refe_func()
{
    int j = 20;
    // i 是j的引用
    int &i = j;
    j = 200;
    cout << i << " " << j << endl;
}

//指针
void piont_func()
{
    int age = 18;
    int *page = &age;
    *page += 2;
    cout << age << "" << page << endl;
}

//指向指针的引用
void poinref_func()
{
    int i = 42;
    // p是一个指针
    int *p;
    // r 是一个对p的引用
    int *&r = p;
    // 令r指向了一个指针p
    //给r赋值为&i,就是p指向了i
    r = &i;
    //解引用r得到i,也就是p指向的对象，将i的值修改为0
    *r = 0;
}

int get_size()
{
    return 1024;
}

//常量
void const_func2()
{
    // 常量定义一定要初始化赋值，否则编译报错
    const int bufSize = 512;
    //修改bufSize的值会报错
    //编译器提示表达式必须是可修改的左值
    // bufSize = 222;
    //运行时初始化
    const int i = get_size();
    //编译时初始化
    const int j = 43;
    //如果定义const变量不初始化也会报错
    // const int k;
    //利用一个常量初始化另一个常量
    const int cj = j;
    // const引用,引用及其对应的对象都是const
    const int &r1 = cj;
    //不可以修改r1的值
    // r1 = 42;
    //不可以用非常量引用指向一个常量对象
    // int &r2 = ci;
    int iv = 42;
    //允许将const int&绑定到一个普通int对象上
    // const int &r1 = iv;
    //正确, r2是一个常量引用
    const int &r2 = 42;
    //正确, r3是一个常量引用
    const int &r3 = r1 * 2;
    //错误, r4 是一个普通非常量的引用
    // int &r4 = r1 * 2;
}

//指针和常量
void pconst_func()
{
    //指向常量的指针
    const double pi = 3.14;
    //不可以用普通指针指向常量
    // double *ptr = &pi;
    //用常量指针指向常量
    const double *cptr = &pi;
    //不能给*cptr赋值因为cptr指向的是常量
    // *cptr = 42;
    //指向常量的指针指向非常量
    double dval = 3.14;
    cptr = &dval;
    //常量指针
    //常量指针的值初始化后就不允许修改
    int errNumb = 0;
    // curErr将一直指向errNumb
    int *const curErr = &errNumb;
    //不允许修改curErr的指向
    int rightNumb = 1;
    //编译报错，提示=左侧必须为可修改的左值
    // curErr = &rightNumb;
    const double pi2 = 3.14159;
    // pip是一个指向常量对象的常量指针
    const double *const pip = &pi2;
}

constexpr int size()
{
    return 42;
}

void constexpr_func()
{
    // 20是一个常量表达式
    constexpr int mf = 20;
    // mf + 1是一个常量表达式
    constexpr int limit = mf + 1;
    // size是一个constexpr函数
    constexpr int sizen = size();
}

int j = 0;
// i 的类型是整型常量
constexpr int i = 42;

void pointer_constexpr()
{
    // p是一个指向整形常量的指针,p可以修改，但是*P不可修改
    const int *p = nullptr;
    // q是一个指向整形变量的常量指针,q不可修改,但是*q可以修改
    constexpr int *q = nullptr;
    // np是一个指向整数的常量指针，其中为空
    constexpr int *np = nullptr;
    // i和j必须定义在函数体之外，否则报错，提示p访问运行时存储
    //因为constexpr要求表达式为常量，在编译时展开
    //  p是常量指针，指向整形常量i
    constexpr const int *p2 = &i;
    // p1是常量指针，指向整数j
    constexpr int *p1 = &j;
}

void const_pointer()
{
    int i = 0;
    //不能改变p1的值，因为他是顶层const
    int *const p1 = &i;
    //不能改变ci的值，因为ci是顶层const
    const int ci = i;
    //可以改变p2的值，p2是底层const
    const int *p2 = &ci;
    //*右侧的const是顶层const，左侧的是底层const
    const int *const p3 = p2;
    //用于声明引用的const都是底层const
    const int &r = ci;
}

void typedef_func()
{
    // wages是double的同义词
    typedef double wages;
    // base是double的同义词， p 是double*的同义词
    typedef wages base, *p;
    // C11用法
    using newd = double;
    newd dd = 3.14;
    typedef char *pstring;
    // pstring是一个指向char的常量指针
    const pstring cstr = 0;
    // ps 是一个指针，其对象是指向char的常量指针
    const pstring *ps;
    char b = 'H';
    //不可修改
    // cstr = &b;
    ps = &cstr;
    const pstring cstr2 = &b;
    ps = &cstr2;
    //不可修改*ps的值
    // *ps = cstr;
}

void auto_func()
{
    int a = 100;
    int b = 1024;
    const int ci = 111;
    // c被推导为int类型
    auto c = a + b;
    auto i = 0, *p = &i;
    //一条声明语句只能有一个基本数据类型
    //不同类型编译器会报错
    // auto sz = 0, pi = 3.14;
    const int ma = 1;
    // auto会忽略顶层const
    //可以通过const明确指出，此时f为const int类型
    const auto f = ma;
    // auto配合引用类型
    auto &g = a;
    // 不能为非常量引用绑定字面值
    // auto &h = 42;
    //指明const 引用绑定字面值
    const auto &j = 42;
    // k是int类型，l是int的引用
    // auto 忽略了顶层const
    auto k = ci, &l = i;
    // m是int常量的引用，p是指向int常量的指针
    // auto保留了底层const
    auto &m2 = ci, *p2 = &ci;
    // 错误 i的类型是int， ci的类型是 const int
    // auto &n = i, *p2 = &ci;
}

void decltype_func()
{
    decltype(size()) sum;
    const int ci = 0, &cj = ci;
    // x的类型是const int
    decltype(ci) x = 0;
    // y的类型是 const int& , y绑定到变量x
    decltype(cj) y = x;
    //错误，z是一个引用，必须初始化
    // decltype(cj) z;
    int i = 42, *p = &i, &r = i;
    // b1 是一个int类型的引用
    decltype(r) b1 = i;
    // r+0 通过decltype返回int类型
    decltype(r + 0) b2;
    //错误，必须初始化,c是int&类型
    // decltype(*p) c;
}