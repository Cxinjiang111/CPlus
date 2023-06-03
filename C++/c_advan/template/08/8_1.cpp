/*
是一种能以一般得函数调用调用语法来调用得对象，所有具备
operator() member function 的object，指向
nonstatic member function的指针就不是function object 但是可以通过bind函数来绑定
Functi on objects和adaptable functi on objects之间有一个重要而有点微妙的差异。 
一般而言， function objects的引数型别受到限制。 型别限制不 一定是很单纯的， 
例如operator(）可能被重载， 也可能 是个member template, 亦或两者都是。
 对程序而言， 决定引数型别的方式不必局限千一种。
Adap七ablefunction object可以指定引数及返回值型别， 而且可以包含嵌套型别(nested type)声明， 
好让这些型别可以被命名以及被程序使用。 如果type FO是Adaptable Generator的一个model, 
那么它必须定义嵌套型别FO::result＿七ype。 同样道理如果Fl是Adaptable Unary Generator的一个
 model,那么它必须定义嵌套型别Fl: :argument_type和Fl:: resul 仁type;
 如果F2是Adaptable Binary Generator的一个 model, 那么它必须定义嵌套型别 F2:: firSt＿argurnent_type、
  F2: :second_argument_type和F2::result_type。
Adaptable function objects之所以称为 “adaptable"， 是因为它们可用千function object adapter, 
它们是「能够被转换为或被用来操作其他function objects」的一种function objects。 
STL定义了很多不同的 function object adapters, 包括unary_negate、 unary_compose、 bind1st、 bind2nd。
*/
/*
Generator 
是一种不需要任何引数的函数对象
Result type  调用Generator后， 返回值的型别
所谓Generator的“range”，意指其可能返回值所形成的集合

函数调用
f()
返回型别：Result
语义：返回型别为Result的某值。注意，调用f两次可能会返回不同的结果。
        Generator可能会参考局部状态(localstate)或执行1/0动作...…表达式f()
    甚至可以改变f的状态一也就是说oprea七or(）不必是个constmember function。
    例如f可以扮演「伪乱数生成器(pseudo-randomnumber generator)」 的角色。
必然结果：返回值位于f的range之中。
Model
凡一个函数能够返回某值，而且不需任何引数，它便是一个Generator。例如型别如下的函数指针便是
Generator的个model。
int(*)();
*/