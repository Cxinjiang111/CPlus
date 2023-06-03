#include<deque>
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    //deque<int,alloc,32> ideq(20,9};
    //其缓冲区大小为32 bytes, 并令其保留20个元素空间， 每个元素初值为9。 
    //为了指定deque的第三个template参数（缓冲区大小），我们必须将前两个参数 都指明出来（这是C丑· 语法规则），
     //因此必须明确指定alloc（第二章）为空间 配置器。现在，deque的情况如图4-12（该图并未显示每个元素的初值为9)所示。
    deque<int,allocator<int>> ideq(20,9); 
     cout << "size=" << ideq.size() << endl;

    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;

    for (int i = 0; i < 3; ++i)
        ideq.push_back(i);
    
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.push_back(3);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.push_front(99);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.push_front(98);
    ideq.push_front(97);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    deque<int, allocator<int>>::iterator itr;
    itr = find(ideq.begin(), ideq.end(), 99);
    cout << *itr << endl;
    cout << *(itr._M_cur) << endl;

    return 0;
}