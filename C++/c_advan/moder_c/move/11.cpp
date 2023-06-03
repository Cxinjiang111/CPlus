//forward argument 
/*
some function need to forward the arguments to another function 
std::invoke(f,x,y,z);
std::vector<Type> v;
v.emplace_back(x,y,z);
std::invoke(f,arg...)call f(args...)
v.emplace_back(args...)constructs the element by calling the constructor Type(args...)
    it is different from v.push_back(Type(args...))in that it does copy the object

value categories must be preserved
std::string some_value();
std::vector<std::string> vs;
std::string s=some_value();
vs.emplace_back(s);
vs.emplace_back(some_value());

cv_qualifications must be preserved
struct Widget{
    Widget(const std::string&);//copy
    Widget(Std::string &);//move 
};
std::vector<Widget> vw;
vw.emplace_back(s);//Widget(Std::string &)
vw.emplace_back("abc");//Widget(const std::string&)
*/
/*


*/
