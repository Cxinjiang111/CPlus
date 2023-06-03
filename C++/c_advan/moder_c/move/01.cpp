
std::string foo(){
    std::string s=some_value(); 
    return s;
}
std::string t=foo();
以上t为了得到some_value() 内存中进行了两次内存拷贝，
作为返回值，s创建了依次临时拷贝
t=foo()拷贝赋值 拷贝了一次

char some_char(int);
std::string fun1(int n){
    std::string s="";
    for(auto i=9;i!=n;i++){
        s+=some_char();
    }
    return s;
}
std::string fun2(int n){
    std::string s="";
    for(auto i=0;i!=n;i++){
        s=s+some_char(i);
    }
    return s;
}
//
s=s+some_char(i);
调用operator+  在调用operator= 实际进行了两次内存拷贝
O(n^2)



s+=some_char();
O(1)
相当于push_back(some_char(i)); 

a=b;
我们可能想要a b拥有独立的各自的资源
我们可能a改变但不影响b
但是有时我们想要拷贝的对象马上被销毁掉，于是我们让新对象去接管此对象
可能b之后马上被销毁，a存活
右值引用
int &r=42;//error
int &&rr=42; 
const int &cr=42;//常量左值引用 这是可以的 左值引用const绑定到右值
const int &&crr=42;//常量右值引用
int i=42;
int &&rr2=i; //error
int &r2=i*42;//error
const int &cr2=i*2;
int &&r3=i*42;
