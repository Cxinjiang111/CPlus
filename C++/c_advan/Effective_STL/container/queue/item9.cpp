/*再刪除選項中仔細選擇
*/
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    vector<int> c;
    //這種方法連續内存容器時vector string 
    //儅c是list時，成員函數remove更高效，c.remove(1963);
    c.erase(remove(c.begin(),c.end(),1963),c.end());
    /*
    （1）erase是容器自带的成员函数，而remove是STL中的函数；
    （2）erase是真正的删除，而remove是虚假的删除。（下面会说明）
remove函数并不会“真正地”对特定元素进行删除，它只会移动指定区间中的元素直到所有
“不删除的”元素在区间的开头（相对位置不变），并返回此时的newEnd迭代器，newEnd后的元素值保持不变。
    */ 
   /*
   儅c是標準關聯容器時，使用任何叫做remove的東西都是錯的，破壞了容器 他們只需使用erase
   */   
}




