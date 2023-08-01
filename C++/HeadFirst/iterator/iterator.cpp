#include<iostream>
#include<string>
#include<vector>
using namespace std;
//菜单
class MenuItem
{
private:
    string m_name;
    string m_desription;
    bool   m_vegetarian;
    double m_price;
public:
    MenuItem() {}
    MenuItem(string name, string desription, bool vegetarian, double price):m_name(name),m_desription(desription),m_vegetarian(vegetarian),m_price(price) {}
    string getName() const { return m_name; }
    string getDesription() const { return m_desription; }
    bool isVegetarian() const { return m_vegetarian; }
    double getPrice() const { return m_price; }
};
//这是第一种菜单
class PancakeHouseMenu
{
private:
    //这里使用的是vector
    vector<MenuItem*> m_menuItems;//组合的形式 是一种vector
public:
    PancakeHouseMenu()
    {
        addItem("K&B","Pancakes with fried ",true,2.99);
        addItem("regular","Pancakes with egg ",true,2.99);
        addItem("blueberry","Pancakes with blueberries ",true,3.49);
        addItem("Waffles","Pancakes with strawberries ",true,3.59);
    }   
    void addItem(string name,string description,bool vegetarian,double price)
    {
        MenuItem *menuitem= new MenuItem(name,description,vegetarian ,price);
        m_menuItems.push_back(menuitem);
    }     
    vector<MenuItem*> getMenuItems()
    {
        return m_menuItems;
    }
};
//这是第二种菜单
class DinerMenu
{
   int MAX_ITEMS=6;
private:
    int m_numberOfItems=0;
    MenuItem* m_menuItems;//这个是数组

public:
    DinerMenu()
    {
        m_menuItems = new MenuItem[MAX_ITEMS];
        addItem("vegetarian BLT","Fakin",true,2.99);
        addItem("BLT","Bacon Fakin",false,2.99);
        addItem("soup","salad",false,3.29);
        addItem("hotdog","saukraut",false,3.05);
    }
    void addItem(string name,string description,bool vegan,double price)
    {
        MenuItem *menuitem= new MenuItem(name,description,vegan,price);
        if(m_numberOfItems>=MAX_ITEMS)
        {
            std::cout<<"sorry ,menu is full can't add item to menu"<<std::endl;
        }
        else{
            //不断添加菜单项到菜单中，
            m_menuItems[m_numberOfItems]=*menuitem;
                        m_numberOfItems++;
        }
    }
    MenuItem *getMenuItems()
    {
        return m_menuItems;
    }
};

//目的就在于实现一个同时使用这两个菜单的客户代码，
int main()
{
    PancakeHouseMenu *pPancakeHouseMenu= new PancakeHouseMenu();
    vector<MenuItem*> breakfastItems=pPancakeHouseMenu->getMenuItems();
    for(int i=0; i<breakfastItems.size(); i++) //这个是遍历vector
    {
        std::cout<<breakfastItems[i]->getName()<<std::endl;
    }
    std::cout<<"--------------------------------"<<std::endl;
    DinerMenu *pDinerMenu=new DinerMenu();
    MenuItem *pDinerMenuItem=pDinerMenu->getMenuItems();
    for(int i=0;i<6; i++) //这个是遍历数组
    {
        std::cout<<pDinerMenuItem[i].getName()<<std::endl;
    }
    //上述两种类型，需要两种遍历方式，所以需要改变统一的一个接口，只需要一个函数即可，这就是迭代器需要做的事情
    //所以遍历便是封装的部分，这里发生变化的是：由不同的集合类型所造成的遍历
    //所以看iterator1.cpp
    return 0;
}
//按照上面一种模型的话，再添加一种菜单的话，那么打印就会重复一次，而且必须自己重复写
//而且遍历的方式也各不相同

