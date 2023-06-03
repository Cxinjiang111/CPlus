#include<new>

class Base{
public:
    static void*operator new(std::size_t size)throw(std::bad_alloc);
};
class Derived:public Base{//这里继承了operator new

};
int main()
{   
    Derived *p=new Derived;//这里调用的是Base::operator new

}
void*Base::operator new(std::size_t size)throw(std::bad_alloc)
{
    if(size!=sizeof(Base))
    {
        return ::operator new(size);
    }
}







