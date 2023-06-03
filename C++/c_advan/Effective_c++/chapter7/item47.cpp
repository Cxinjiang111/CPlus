/*请使用traits classe 表现类型信息
*/
#include<iterator>
template<typename IterT,typename DistT>
void advance(IterT &iter,DistT d)
{

}
struct input_iterator_tag{};
struct output_iterator_tag
{
    /* data */
};
struct forward_iterator_tag:public input_iterator_tag
{
    /* data */
};
struct bidrectional_iterator_tag:public forward_iterator_tag
{
    /* data */
};
struct random_access_iterator_tag:public bidrectional_iterator_tag
{
    /* data */
};
//重载 可以选择特定的函数
template<typename IterT,typename DistT>
void doAdvance(IterT&iter,DistT d,std::random_access_iterator_tag)
{

}
template<typename IterT,typename DistT>
void doAdvance(IterT&iter,DistT d,std::bidirectional_iterator_tag)
{
    
}
template<typename IterT,typename DistT>
void doAdvance(IterT&iter,DistT d,std::input_iterator_tag)
{
    
}

template<typename IterT,typename DistT>
void doAdvance(IterT&iter,DistT d)
{
    doAdvance(iter,d,typename std::iterator_traits<IterT>::iterator_category());
}










