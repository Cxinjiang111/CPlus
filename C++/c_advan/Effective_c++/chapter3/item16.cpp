/* 成对使用new 和delete时要采取相同形式

*/
#include<string>
typedef std::string AddressLines[4];
int main()
{
    std::string *stringArray=new std::string[100];
    //delete stringArray;//error 可能还有很多内存没有被删除
    delete[] stringArray;

    std::string pal=new AddressLines;//error 尽量不要对数组形式做typedef动作
    delete []pal;

}

