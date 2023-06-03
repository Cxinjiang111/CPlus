#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>
using namespace std;
/*
条款26中指出有些容器成员函数只接受iterator作为参数，而不是const_iterator。那么，如果你只有一个
const_iterator，而你要在它所指向的容器位置上插入新元素呢？也就是如何把const_iterator转化为iterator呢？
因为正如条款26所解释的，并不存在从const_iterator到iterator之间的隐式转换，所以你必须成为这次行动的主
角。
*/
int main()
{
    typedef vector<int> intvec;
    typedef intvec::iterator intveciter;
    typedef intvec::const_iterator intvecconstiter; 
    intvec v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    intvecconstiter conit(v.begin());

    //intveciter i(conit);//error 不存在这种转化 const->非const

    //intveciter i(const_cast<intveciter>(conit));//但是任然是error 这种const的强制转化也不行
/*
包含映射的代码不能通过编译的原因在于，对于这些容器而言，iterator和const_iterator是完全不同的类。它们
之间并不比string和complex<float>具有更多的血缘关系。在两个毫无关联的类之间进行const_cast映射是荒谬
的，所以reinterpret_cast、static_cast甚至C风格的映射也会导致同样的结果。

把const迭代器映射为迭代器是病态的 
*/

    intveciter i(v.begin());

    //advance(i,distance(i,conit));//error
    //这里因为 
    /* template<typename _InputIterator>
    typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last)
    所以上面distance对于输入的两个迭代器有要求一致， 这里可以把迭代器都向窄的方向发展即const
    */
    advance(i,distance<intvecconstiter>(i,conit));


    return 0;
}

