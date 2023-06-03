#include<set>
#include<iostream>
#include<string>
using namespace std;
int main()
{
    //multiset<int,less_equal<int>> s;
    multiset<int> s;    
    s.insert(10);
    s.insert(10);

    for (auto &i : s)
    {
        cout<<i<<endl;
    }
/*
现在，s里有两个10的拷贝，因此我们期望如果我们在它上面做一个equal_range，我们将会得到一对指出包含
这两个拷贝的范围的迭代器。但那是不可能的。equal_range，虽然叫这个名字，但不是指示出相等的值的范
围，而是等价的值的范围。在这个例子中，s的比较函数说10A和10B是不等价的，所以不可能让它们同时出现
在equal_range所指示的范围内。
*/
    return 0;
}















