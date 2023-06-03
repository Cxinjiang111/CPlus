//STL 还有其他数个函数对象适配器，(1)   binder1st   (2) binder2nd 可以将Adaptable Binary Function 转换Unary Function 
//(2)mem_fun_t adapter 及其变形，他们除了作用于member function 而非全局函数之外，极类似于pointer_to_unary_function
//（3）unary_compose 能将两个function objects f和 g转换成单一一个函数对象 h 使得h(x)=f(g(x))