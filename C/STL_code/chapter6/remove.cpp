/*
remove移除但不删除 erase才是删除内容
*/
template<class ForwwardIterator,class T>
ForwwardIterator remove(ForwwardIterator first,ForwwardIterator last,const T&value)
{
    first=find(first,last,value);//寻找第一个可覆盖的位置
    ForwwardIterator next=last;
    return first=last?first:remove_copy(++next,last,first,value);
}







