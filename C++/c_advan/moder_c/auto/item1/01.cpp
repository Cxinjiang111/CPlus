template<typename T>
void f(const T* Param);
void t1(){
    int x=0;
    int *x1=&x;
    f(x1);
}
