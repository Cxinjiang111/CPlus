/*避免原地修改set和multiset的键
*/
#include<set>
#include<iostream>
#include<string>
using namespace std;
/*set或multiset里的元素不是常数开始
*/
class Employee{
public:
    const string&name()const;       // 获取雇员名
    void setName(const string&name);// 设置雇员名
    const string&getTitle()const;   // 获取雇员头衔
    void setTitle(string&title);    // 设置雇员头衔
    int idNumber()const;            // 获取雇员ID号
    void setID(int id1);
private:
    int ID;
    string str;
};
int Employee::idNumber()const            // 获取雇员ID号
{
    return this->ID;
}
void Employee::setID(int id1)
{
    this->ID=id1;
}
//很顯然按照雇员ID号排序

struct IDNumberLess :public binary_function<Employee,Employee,bool>{
    bool operator()(const Employee &lhs,const Employee &rhs)const{
        return lhs.idNumber()<rhs.idNumber();
    }
};
typedef set<Employee,IDNumberLess> EmpIDSet;
int main()
{
    EmpIDSet s1;
    Employee e1;
    e1.setID(10);
    Employee e2;
    e2.setID(11);
    Employee e3;
    e3.setID(9);
    string s2("hello");
    e3.setTitle(s2);

    s1.insert(e1);
    s1.insert(e2);
    s1.insert(e3);

    EmpIDSet::iterator i=s1.begin();
    for(;i!=s1.end();++i)
    {
        
        //i->setTitle(s2); error 
        static_cast<Employee>(*i).setTitle(s2);
        //((Employee)(*i).getTitle(s2)); 這二者等價 強轉
        //cout<<i->idNumber()<<endl;


        Employee tempCopy(*i);//*i拷貝到tempCopy
        tempCopy.setTitle(s2);//修改tempCopy
    
    }

    return 0;
}
int main()
{
    EmpIDSet se;
    Employee e1;
    e1.setID(10);
    Employee e2;
    e2.setID(11);
    Employee e3;
    e3.setID(9);
    string s2("hello");
    e3.setTitle(s2);
    se.insert(e1);
    se.insert(e2);
    se.insert(e3);
    EmpIDSet::iterator i=se.begin();
    for(;i!=se.end();++i)
    { 
        Employee e(*i);
        se.erase(i++);// 第二步：拷贝这个元素
        string tmps("hello");// 第三步：删除这个元素；自增这个迭代器以保持它有效
        e.setTitle(tmps);// 第四步：修改这个副本
        se.insert(i,e);// 第五步：插入新值；提示它的位置和原先元素的一样
    }

    return 0;


}





