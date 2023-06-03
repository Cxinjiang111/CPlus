/*
假设我们正在撰写一个function template,它接受一个迭代器，而我们打算为该
迭代器指涉的对象做一份local复件（副本）temp。 我们可以这么写：
*/
#include<iterator>
template<typename IterT>
void workWithIterator(IterT iter)
{
    typename std::iterator_traits<IterT>::value_type temp(*iter);
}
/*别让std::iterator_traits<IterT>: :value_type惊吓了你， 那只不过是标准traits class
（见条款47)的一种运用，相当于说 “类型为IterT之对象所指之物的类型” 。这个语句声明一个local变量(temp)，
使用IterT对象所指物的相同类型，并将temp初始化为iter所指物。如果IterT是vector<int>::iterator, 
temp的类型就是int。如果IterT是list<string>:：iterator, temp的类型就是string。 
由于std::iterator_traits<IterT>::valuelue type是个嵌套从属类型名称Cvalue_type被嵌套于
iterator_traits<IterT>之内而IterT是个template 参数）， 所以我们必须在它之前放置typename。
*/

template<typename IterT>
void workWithIterator(IterT iter)
{
   typedef typename std::iterator_traits<IterT>::value_type value_type;
   value_type temp(*iter);
}






