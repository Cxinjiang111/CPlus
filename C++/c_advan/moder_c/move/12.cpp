/*
std::forward
template<typename Func,typename T>
auto invoke1(Func f,T &&arg){
    return f(std::forward<T>(arg));
}
std::forward<T&>(x) return an lvaule reference which produces an lvalue
std::forward<T>(x) where T is not a reference ,return an rvalue reference
which produces an rvalue
in this case itis equivalue to std::move(x) 

template<typename Func,typename T>
auto invoke1(Func f,T &&arg){
    return (std::foeward<Func>(f))(std::forward<T>(arg));
}

*/