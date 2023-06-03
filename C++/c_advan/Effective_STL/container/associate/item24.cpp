/*当关乎效率时应该在map::operator[]和map-insert之间仔细选择
*/
#include<map>
using namespace std;
class Widget{
public:
    Widget();
    Widget(double weight);
    Widget&operator=(double weight);
};
int main()
{  //map<K  , V>
    map<int,Widget> m;
    m[1]=1.5;
      m[1]=1.5;  
    m[1]=1.5;
    /*
    operator[]返回一個與k關聯的值對象的引用，然後v賦值給所引用的對象
当要更新一个已存在的键的关联值时很直接，因为已经有operator[]可以用来返回引用的值对象。但是
如果k还不在map里，operator[]就没有可以引用的值对象。那样的话，它使用值类型的默认构造函数从头开始
建立一个，然后operator[]返回这个新建立对象的引用。 
表达式m[1]是m.operator[](1)的简化，所以这是一个map::operator[]的调用。那个函数必须返回一个Widget的
引用，因为m 的映射类型是Widget。在这里，m里面还没有任何东西，所以键1在map里没有入口。因此
operator[]默认构造一个Widget来作为关联到1的值，然后返回到那个Widget的引用。最后，Widget成为赋值目
标：被赋值的值是1.50。
    */
m[1]=1.5;
typedef map<int,Widget> IntWidgetMap;
pair<IntWidgetMap::iterator,bool> result=m.insert(IntWidgetMap::value_type(1,Widget()));
result.first->second=1.5;//result.first：IntWidgetMap::iterator
//result.first->second：IntWidgetMap::iterator->second：value值 true 就新構造出這個函數


}
/*
map的operator[]函数是个奇怪的东西。它与vector、deque和string的operator[]函数无关，也和内建的数组
operator[]无关。
*/