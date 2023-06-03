
/*
现在已经很清楚为什么这种方法可能降低性能了。我们先默认构造一个Widget，然后我们立即赋给它新值。
如果用想要的值构造Widget比默认构造Widget然后进行赋值显然更高效，我们就应该用直截了当的insert调用
来替换operator[]的使用（包括它的构造加赋值）
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
typedef map<int,Widget> IntWidgetMap;
    m.insert(IntWidgetMap::value_type(1, 1.5));


/*
这与上面的那些代码有相同的最终效果，除了它通常节省了三次函数调用：一个建立临时的默认构造Widget
对象，一个销毁那个临时的对象和一个对Widget的赋值操作。那些函数调用越昂贵，你通过使用map-insert代
替map::operator[]就能节省越多。
*/

m.insert(IntWidgetMap::value_type(1,1.5)).first->second=1.5;//使用insert來把k的值更新為v
/*
语法本身也许会让你信服地支持operator[]，但在这里我们关注于效率，所以我们将忽略它。insert的调用需要
IntWidgetMap::value_type类型的实参（即pair<int, Widget>），所以当我们调用insert时，我们必须构造和析构
一个那种类型的对象。那耗费了一对构造函数和析构函数，也会造成一个Widget的构造和析构，因为
pair<int, Widget>本身包含了一个Widget对象，operator[]没有使用pair对象，所以没有构造和析构pair和
Widget。
*/

}