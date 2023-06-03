#include<new>
/*
placement new 允许我们将构建allocated memory中，
没有所谓placement delete，因为placement new根本没分配memory

*/
class Complex{
public:
    Complex(float x,float y):real(x),image(y){}
private:    
    float real;
    float image;
};
int main(){
    char *buf=new char[sizeof(Complex)*3];
    Complex*pc=new(buf)Complex(1,2); //不分配内存,仅仅在利用内存区域

    delete[] buf;// 这里不能delete pc
}
/*
编译器转化为如下代码
Complex *pc;
try{
    void*mem=operator new(sizeof(Complex),buf);分配内存
    pc=static_cast<Complex*>(mem); 指针转型
    pc->Complex::Complex(1,2); 调用构造函数
}


*/