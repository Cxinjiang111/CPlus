//move from local variable and parameter
/*
when an object being retunrned is declaered
    in the function body 
    as a parameter of the function
the overload resolution to select the constructor to use for 
initialization of the returned value is performed twice:
    first as if the object were an rvalue 
    and if the first overload resolution failed ,then overload 
        resolution is preformed as usual,with the object considered
        as an lvalue
    尝试右值，右值不行，那就只能左值引用咯 拷贝构造
*/
/*
强制取消拷贝赋值
returning a pravlue of the same class type as the function return-type
std::string f(){
    return std::string(10,'c);//move 不会先拷贝一份相同的内存再赋值返回 而是直接move 
}
std::string s=f();//move 


*/