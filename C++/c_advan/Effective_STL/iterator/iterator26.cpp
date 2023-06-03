/*条款26：尽量用iterator代替const_iterator，reverse_iterator和const_reverse_iterator

正如你所知的，每个标准容器类都提供四种迭代器类型。对于container<T>而言，iterator的作用相当于T*，
而const_iterator则相当于const T*（你可能也见过T const*这样的写法：它们意思一样[1]）。增加一个iterator或
者const_iterator可以在一个从容器开头趋向尾部的遍历中让你移动到容器的下一个元素。reverse_iterator与
const_reverse_iterator同样相当于对应的T*和const T*，所不同的是，增加reverse_iterator或者
const_reverse_iterator会在从尾到头的遍历中让你移动到容器的下一个元素。
*/
#include<vector>
#include<iterator>
using namespace std;
int main()
{
    vector<int>v;
    vector<int>::iterator it;
    v.insert(it,5);
    v.erase(it);
    v.erase(it,it+5);
    /*
    iterator insert(iterator pos,const T&x);
    iterator erase(iterator pos);
    iterator erase(iterator rangebegin,iterator rangeend);
    很多这样的函数只接受迭代器类型，为了模板化，并且这些迭代器都是iterator，而不是const型 或const_reverse
    
    
图中显示了从iterator到const_iterator、从iterator到reverse_iterator和从reverse_iterator到const_reverse_iterator可以
进行隐式转换。并且，reverse_iterator可以通过调用其base成员函数转换为iterator。const_reverse_iterator也可以
类似地通过base转换成为const_iterator
宽权限可以向窄权限转化，相反则不能，这个对所有的转变都是一样的

可以避免潜在的bug 
● insert和erase的一些版本要求iterator。如果你需要调用这些函数，你就必须产生iterator，而不能用const或reverse iterators。
● 不可能把const_iterator隐式转换成iterator，我们将会在条款27中讨论从一个const_iterator产生一个iterator的技术并不普遍适用，而且不保证高效。
● 从reverse_iterator转换而来的iterator在转换之后可能需要相应的调整，在条款28中我们会讨论何时需要调整以及调整的原因。
    */


}









