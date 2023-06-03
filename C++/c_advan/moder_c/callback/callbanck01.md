对std::function最简单的理解就是：std::function实现了函数的存储，即先将可调用实体保存起来，在需要的时候再调用。
关于可调用对象转换为std::function对象需要遵守以下两条原则：
转换后的std::function对象的参数能转换为可调用对象的参数；
可调用对象的返回值能转换为std::function对象的返回值。

std::bind函数定义在头文件<functional>中，是一个函数模板，它就像一个函数适配器，接受一个可调用对象（callable object），生成一个新的可调用对象来“适应”原对象的参数列表。

使用std::bind可以将可调用对象和参数一起绑定，绑定后的结果使用std::function进行保存，并延迟调用到任何我们需要的时候，所以经常用来实现回调函数。
将可调用对象与参数一起绑定为另一个std::function供调用
将 n 元可调用对象转成 m(m < n) 元可调用对象，绑定一部分参数，这里需要使用std::placeholders

std::bind函数有两种函数原型，定义如下：
template <class Fn, class... Args>
bind (Fn&& fn, Args&&... args);

template <class Ret, class Fn, class... Args>
bind (Fn&& fn, Args&&... args);
基于参数fn返回一个函数对象，并且以args参数绑定为函数对象的参数。
每个参数要么绑定一个参数值，要么绑定为一个std::placeholders（占位符，如 _1, _2, ..., _n）。
如果参数绑定成一个值，那么返回的函数对象将总使用绑定的参数值做为调用参数，即调用传入参数将不起作用；如果参数绑定为std::placeholders，那么返回的函数对象在被调用时需要传入实时参数，参数填充的位置即由placeholder指定的序号。

2. 函数模板参数说明

fn：可调用的函数对象，比如函数对象、函数指针、函数引用、成员函数或者数据成员函数。
args：需要绑定的函数的参数列表，使用命名空间占位符std::placeholders::_1，std::placeholders::_2标志参数，其中std::placeholders::_1标志为参数列表中的第一个参数，std::placeholders::_2标志参数列表中的第二个参数，std::placeholders::_3标志参数列表中的第三个参数，以此类推。
3. 函数模板返回值说明

返回一个函数对象，该函数在调用时使用参数列表args来调用fn。如果fn是指向类的成员函数，则返回函数第一个参数应该是该类的成员、或者成员对象的引用、或者是成员对象的指针。