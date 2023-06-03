// 迭代器是一种智能指针
//迭代器最重要的工作就是operator* 和operator->进行重载
// void func(){
//     //ps是原生指针指向型别为string
//     auto_ptr<string> ps(new string("hello"));
// } 
template<class T>
class auto_ptr{
public:
    explicit auto_ptr(T*p=nullptr):pointee(p){}
    template<class U>
    auto_ptr(auto_ptr<U>&rhs):pointee(rhs.release()){}
    ~auto_ptr(){delete pointee;}

    template<class U>
    auto_ptr<T>&operator=(auto_ptr<U> &rhs){
        if(this!=&rhs){
            reset(rhs.release());
        }
        return *this;  
    }
    //迭代器最重要的连个函数 取迭代器中的值，
    T&operator*()const{return *pointee;}
    T*operator->()const {return pointee;}
    T*get()const {return pointee;}
private:
    T*pointee;
};

