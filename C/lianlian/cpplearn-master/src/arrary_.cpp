#include "../inc/arrary_.h"
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

constexpr int get_size()
{
    return 42;
}

void arrary_init()
{
    //不是常量表达式
    unsigned cnt = 42;
    //常量表达式
    constexpr unsigned sz = 42;
    //常量表达式
    const unsigned usz = 42;
    //包含10个整数
    int arr[10];
    //含有42个整形指针的数组
    int *parr[sz];
    //含有42个string的数组
    string strvec[usz];
    //含有42个int的数组
    string invec[get_size()];
    // 编译报错,因为cnt不是常量表达式
    // string bad[cnt];
    const unsigned msz = 3;
    //含有3个元素的数组，元素值分别为0,1,2
    int ia1[msz] = {0, 1, 2};
    //维度是3的数组
    int a2[] = {0, 1, 2};
    //等价于a3[] = {0,1,2,0,0}
    int a3[5] = {0, 1, 2};
    //等价于a4[] = {"hi","bye",""}
    string a4[3] = {"hi", "bye"};
    //错误，初始值过多
    // string a5[2] = {0, 1, 2};
}

void array_error()
{
    // 错误用法，不允许用数组初始化数组
    //含有3个整数的数组
    // int a[] = {0,1,2};
    //不允许用一个数组初始化另一个数组
    // int a2[] = a;
    //不能把一个数组直接赋值给另一个数组
    // a2 = a;
}

void dif_array()
{
    // ptrs是含有10个整形指针的数组
    int *ptrs[10];
    //不存在引用的数组
    // int &refs[10] = /*?*/;
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // 数组的引用 arrRef是arr的引用
    int(&arrRef)[10] = arr;
    // Parray指向一个含有10个整数的数组
    int(*Parray)[10] = &arr;
}

void visit_array()
{
    //以10分为一个分数段统计成绩，0~9，10~19...，90~99,100
    // 11 个分数段，全部初始化为0
    unsigned scores[11] = {};
    unsigned grade;
    while (cin >> grade)
    {
        if (grade <= 100)
        {
            ++scores[grade / 10];
        }
    }

    //通过for range 遍历打印
    for (auto i : scores)
    {
        cout << i << " ";
    }
    cout << endl;
}

void pointer_array()
{
    //数组的元素是string元素
    string nums[] = {"one", "two", "three"};
    // p指向nums的第一个元素
    string *p = &nums[0];
    // ia是一个含有10个整数的数组
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // ia2是一个整数型指针，指向ia第一个元素
    auto ia2(ia);
    //错误：ia2是一个指针，不能用int值给指针赋值
    // ia2 = 42;
    // ia2是int*类型
    // auto ia2(&ia[0]);
    // ia3是一个含有10个整数的数组
    decltype(ia) ia3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *pint = nullptr;
    //错误，不能用整形指针给数组赋值
    // ia3 = pint;
    //正确，可以对数组的元素赋值
    ia3[4] = 1024;
}

void pointer_op()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p = arr;      // p指向arr的第一个元素
    ++p;               // p指向arr[1]
    int *e = &arr[10]; //指向arr尾元素的下一个位置的指针
    for (int *b = arr; b != e; ++b)
        cout << *b << endl;

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        cout << arr[i] << endl;
    }

    // beg指向arr第一个元素
    int *beg = begin(arr);
    // last指向arr最后一个元素的下一个位置
    int *last = end(arr);
    while (beg != last)
    {
        cout << *beg << endl;
        beg++;
    }
    //等价于int *p = &arr[0]
    int *ip = arr;
    //等价于ip2指向arr的第四个元素
    int *ip2 = ip + 4;
    int length = last - beg;
    cout << length << endl;
}

void c_string()
{
    const char cal1[] = "A string example";
    const char cal2[] = "A different string";
    if (strcmp(cal1, cal2) < 0)
    {
        cout << "cal1 is less than cal2" << endl;
    }
    else
    {
        cout << "cal2 is less than cal1" << endl;
    }

    const int total_len = strlen(cal1) + strlen(cal2) + 1;
    //开辟total_len字节的空间
    char *total_str = new char(total_len);
    //将空间清空为0
    memset(total_str, 0, total_len);
    //将cal1 copy 到 total_str
    strcpy(total_str, cal1);
    //将total_str和cal2连接
    strcat(total_str, cal2);
    //输出total_str 的值
    cout << "total_str is " << total_str << endl;
    //最后释放内存
    if (total_str != nullptr)
    {
        delete total_str;
        total_str = nullptr;
    }

    string strcpp = "CPP";
    const char *strc = strcpp.c_str();
}

void vector_init2()
{
    vector<int> v1 = {1, 3, 5, 7, 9};
    vector<int> v2(v1);
    for (auto v : v2)
    {
        cout << v << endl;
    }

    int a[] = {2, 4, 6, 8, 10};
    vector<int> v3(begin(a), end(a));

    for (auto v : v3)
    {
        cout << v << endl;
    }
}

void multi_array()
{
    //大小为3的数组，每个元素是含有4个整数的数组
    int ia[3][4];
    //大小为10的数组,他的每个元素都是大小为20的数组
    //这些数组的元素是含有30个整数的数组
    int arr[10][20][30] = {0};
}

void multi_init()
{
    //三个元素，每个元素大小都是4的数组
    int ia[3][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11}};
    //可以用一个花括号初始化二维数组
    int ib[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    //显示初始化每行的首元素
    int ic[3][4] = {{0}, {4}, {8}};
    //显示初始化第一行,其他元素被初始化为0
    int id[3][4] = {0, 3, 4, 6};
}

void multi_index()
{
    int arr[3][3][3] = {
        0,
        1,
        2,
    };
    //用arr的首元素为ia最后一行的最后一个元素赋值
    int ia[3][4] = {0};
    ia[2][3] = arr[0][0][0];
    // row是一个ia第二个元素数组的引用，包含四个元素
    int(&row)[4] = ia[1];
    //遍历
    constexpr size_t rowCnt = 3, colCnt = 4;
    for (size_t i = 0; i != rowCnt; ++i)
    {
        //对于行内的每一列
        for (size_t j = 0; j != colCnt; ++j)
        {
            //将元素的位置索引作为他的值
            ia[i][j] = i * colCnt + j;
        }
    }

    size_t cnt = 0;
    for (auto &row : ia)
    {
        for (auto &col : row)
        {
            col = cnt++;
        }
    }

    for (auto &row : ia)
    {
        for (auto col : row)
        {
            cout << col << endl;
        }
    }
}

void multi_pointer()
{
    //大小为3的数组，每个元素是含有4个整数的数组
    int ia[3][4];
    // p指向含有4个整数的数组
    int(*p)[4] = ia;
    // p指向ia的尾元素
    p = &ia[2];
    //整数指针的数组
    int *ib[4];
    //指向含有4个整数的数组
    // int(*ib)[4];

    // p指向一个含有4个整数的数组
    for (auto p = ia; p != ia + 3; ++p)
    {
        // q指向4个整数数组的首元素，也就是说q指向一个整数
        for (auto q = *p; q != *p + 4; q++)
        {
            cout << *q << ' ';
        }
        cout << endl;
    }

    // p指向ia的第一个数组
    for (auto p = begin(ia); p != end(ia); p++)
    {
        // q指向内层数组的首元素
        for (auto q = begin(*p); q != end(*p); q++)
        {
            //输出q所指的整数
            cout << *q << ' ';
        }

        cout << endl;
    }
}

void typedef_pointer()
{
    // C11新标准定义类型别名
    // int_array 是一个包含四个元素的整形数组类型
    using int_array = int[4];
    //等价的typedef声明
    // int_array_same 是一个包含四个元素的整形数组类型
    typedef int int_array_same[4];
    //如果不会用typedef定义数组类型，可以先定义一个数组变量
    int int_array_inst[4];
    //然后加上typedef即可,
    //此时int_array_inst就是一个大小为4的整形数组类型
    // typedef int int_array_inst[4];
    int ia[3][4];
    //输出ia中每个元素的值，每个内层数组各占一行
    for (int_array *p = ia; p != ia + 3; p++)
    {
        for (int *q = *p; q != *p + 4; q++)
        {
            cout << *q << ' ';
        }
        cout << endl;
    }
}