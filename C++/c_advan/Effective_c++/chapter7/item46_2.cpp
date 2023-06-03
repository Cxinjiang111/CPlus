/*模板参数推导并且检查任何explicit模板参数表现 时去寻找模板参数值
if both succeeds, the template arguments are used to synthesize 
declarations of the corresponding function template specializations, 
which are added to the candidate set, and such specializations 
are treated just like non-template functions except where specified
 otherwise in the tie-breaker rules;
如果两者都成功，则模板参数用于合成相应函数模板特化的声明，
这些声明被添加到候选集中，并且此类特化将被视为与非模板函数一样，除非在决胜规则中另有指定;
if argument deduction fails or the synthesized function template specialization 
would be ill-formed, no such function is added to the candidate set.
如果参数推导失败或合成函数模板特化将不成形，则不会将此类函数添加到候选集中。
If a name refers to one or more function templates and also to a 
set of overloaded non-template functions, those functions and the 
specializations generated from the templates are all candidates.
如果名称引用一个或多个函数模板以及一组重载的非模板函数，
则这些函数和从模板生成的特化都是候选项。
*/
class  B{
    public:
    B(){};
    void f(int);
};
struct A{
    operator B&();//重载类

};
int main()
{
    A a;
   // a.B::f();//error 用户定义的转换无法应用于隐式对象参数
   a.B::B();
}
