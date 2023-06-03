/*明智而审慎地使用private继承
*/
class Person{};
class Student:private Person{};
void eat(const Person&p);
void study(const Student&s);
int main()
{
    Person p;
    Student s;
    eat(p);
    study(s);
    eat(s);//error 继承类的不能够退化为基类使用
}
/*
如果classes之间的继承关系是private，编译器不会自动将一个derived classs对象转换为
一个base class对象，
由private base class继承而来的所有成员，在derived class 中都会变成private 
 
private继承意味只有实现部分被继承，接口部分应略去
*/