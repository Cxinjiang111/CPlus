//reference type
/*
从 “迭代器所指之物的内容是否允许改变” 的角度观之， 迭代器分为两种：
不允许改变 “所指对象之内容” 者，称为constant iterators,例如cons t int* pie;
 允许改变 ”所指对象之内容” 者， 称为mutable iterators, 例如int* pi。 当我们
对一个mutable iterators进行提领操作时，获得的不应该是一个右值(rvalue)，应
该是一 个左值(lvalue)， 因为右值不允许赋值操作(assignment)， 左值才允许：
*/
void fun(){
    int* pi=new int(5);
    const int*pci=new int(9);
    *pi=7;//对mutable iterator进行提领操作时，获得的应该是个左值，允许赋值
    *pci=1;//这个操作不允许，因为pci是入r- constant iterator,
        //提领pci所得结果，是个右值，不允许被赋值
}
/*
在C+＋中，函数如果要传回左值，都是以by reference的方式进行，所以当p是个mutable iterators时，
如果其value type是T，那么*p的型别不应该是T, 应该是T&。 将此道理扩充，
如果p是一个constant iterators, 其value type是T, 那么*p的型别不应该是const T,
而应该是const T&。 这里所讨论的*p的型别， 即所谓的reference type。 
*/