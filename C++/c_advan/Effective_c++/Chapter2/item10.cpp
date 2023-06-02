/*
令operator=返回一个reference to*this
*/

//x=y=z=A;
//z=A-->z 
//y=z-->y
//x=y-->z;
class Widget{
    //返回类型是个reference 指向当前对象
    Widget&operator=(const Widget&rhs)
    {
        return *this;//返回左侧对象
    }


};