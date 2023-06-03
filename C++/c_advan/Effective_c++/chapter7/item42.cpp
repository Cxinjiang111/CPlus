/*了解typename 的双重意义

*/
template<class T>
class Widget;
template<typename T>
class Widget;
/*
答案： 没有不同。当我们声明template类型参数，class和typenarne的意义完全相同。
某些程序员始终比较喜欢class, 因为可以少打儿个字。其他人（包括 我）比较喜欢typename, 
因为它暗示参数并非一定得是个class类型。 少数开发人 员在接受任何类型时使用typenarne,
而在只接受用户自定义类型时保留旧式的class。然而从C廿的角度来看，声明template参数时，
不论使用关键字class或 typenarne, 意义完全相同。

然而C+＋并不总是把class和typename视为等价。 有时候你一定得使用 typename。
 为了解其时机， 我们必须先谈谈你可以在template内指涉(refer to)的 两种名称。
*/

template<typename C>
void print2nd(const C& container)
{
    if(container.size()>2)
    {
        C::const_iterator iter(container.begin());//const_iterator从属名称
        for(;iter!=container.end();++iter)
        {
            int value=*iter;// int 不依赖template 非从属名称 这里不一定基础类型，有可能*iter依然是个结构体
        }
    }
}
/*
我在代码中特别强调两个local 变量iter和value。iter的类型是
C: :const_iterator,实际是什么必须取决千template参数C。template内出现的名
称如果相依于某个template参数， 称之为从属名称(dependent names)。如果从属
名称在class内呈嵌套状，我们称它为嵌套从属名称(nested dependent name)。
C::const_iterator就是这样一个名称。实际上它还是个嵌套从属类型名称(nested
dependent typename)，也就是个嵌套从属名称 并且指涉某类型。
这一类名称的术语， 所以请和我一样， 眨眨眼睛然后顺从它吧。
*/




