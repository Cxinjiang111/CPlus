#include<iostream>
#include<string>
#include<vector>
using namespace std;
//迭代器是提供所有一个流程类
class Iterator_
{
public:
    virtual Iterator_* next();
    virtual bool hasNext();
};
Iterator_* Iterator_::next() { return nullptr; }
bool Iterator_::hasNext() { return false; }
//这个是生成所有菜单共有的属性 实体
class MenuItem :public Iterator_
{
private:
    string m_name;
    string m_desription;
    bool   m_vegetarian;
    double m_price;
public:
    MenuItem() {}
    MenuItem(string name, string desription, bool vegetarian, double price) :
        m_name(name), m_desription(desription), m_vegetarian(vegetarian), m_price(price) {}
    string getName() const {
        std::cout << "getName: " << m_name << std::endl;
        return m_name;
    }
    string getDesription() const { return m_desription; }
    bool isVegetarian() const { return m_vegetarian; }
    double getPrice() const { return m_price; }
    virtual Iterator_* next()override;
    virtual bool hasNext()override;
};
Iterator_* MenuItem::next() { return nullptr; }
bool MenuItem::hasNext() { return false; }
//这个则是提供每种菜单特有的iterator的功能
class DinerMenuIterator :public Iterator_
{
private:
    MenuItem** m_menuItems;//这个是数组
    int m_position = 0;
public:
    DinerMenuIterator(MenuItem** menuitem)//
    {
        this->m_menuItems = menuitem;
    }
    MenuItem** getMenuItems()
    {
        return m_menuItems;
    }
    MenuItem* next()
    {
     std::cout<<"m_position:  "<<m_position<<std::endl;
        MenuItem* item = m_menuItems[m_position];
        m_position++;
        return item;
    }
    bool hasNext()
    {
        //std::cout << "position : " << m_position << std::endl;
        if (6<= m_position || m_menuItems[m_position] == nullptr)
            return false;
        else
            return true;
    }
};
//餐厅代码
class DinerMenu
{
private:
    int MAX_ITEMS = 6;
    int m_numberOfItems = 0;
    MenuItem* m_menuItems[6]; //m_menuItems[i]=(MenuItem)
public:
    Iterator_* creatorIterator()
    {
        return new DinerMenuIterator(m_menuItems);//通过拿到的menu资源来new了指向继承DinerMenuIterator一个迭代器 但指针是基类
    }
    //
    DinerMenu()
    {
        addItem("one BLT", "Fakin", true, 2.99);
        addItem("two BLT", "Bacon Fakin", false, 2.99);
        addItem("three soup", "salad", false, 3.29);
        addItem("four hotdog", "saukraut", false, 3.05);
        addItem("five hotdog", "saukraut", false, 3.05);
        addItem("six hotdog", "saukraut", false, 3.05);
    }
    void addItem(string name, string description, bool vegan, double price)
    {
        MenuItem* menuitem = new MenuItem(name, description, vegan, price);
        //不断添加菜单项到菜单中，
        m_menuItems[m_numberOfItems] = menuitem;
        m_numberOfItems++;
    }
};
//这个则是提供每种菜单特有的iterator的功能
class PancakeIterator :public Iterator_
{
private:
    vector<MenuItem*> m_menuItems;//这个是数组
    int m_position = 0;
public:
    PancakeIterator(vector<MenuItem*>& menuitem)//
    {
        for(int i = 0; i < menuitem.size();++i)
        {
            m_menuItems.push_back(menuitem[i]);
        }
        std::cout<<m_menuItems.size()<<std::endl;
    }
    vector<MenuItem*> getMenuItems()
    {
        return m_menuItems;
    }
    MenuItem* next()
    {
        std::cout<<"m_position:  "<<m_position<<std::endl;
        MenuItem* item = m_menuItems[m_position];
        m_position++;
        return item;
    }
    bool hasNext()
    {
        std::cout << "hasNext  m_menuItems.size() : " << m_menuItems.size() << std::endl;
        if ((m_menuItems.size()-1)<m_position||m_menuItems.size()<1)
            return false;
        else
            return true;
    }
};
//餐厅代码
class PancakeHouseMenu
{
private:
    vector<MenuItem*> m_menuItems; //m_menuItems[i]=(MenuItem)
public:
    Iterator_* creatorIterator()
    {
        return new PancakeIterator(m_menuItems);//通过拿到的menu资源来new了指向继承DinerMenuIterator一个迭代器 但指针是基类
    }
    PancakeHouseMenu()
    {
        addItem("one vector BLT", "Fakin", true, 2.99);
        addItem("two vector BLT", "Bacon Fakin", false, 2.99);
        addItem("three vector soup", "salad", false, 3.29);
        addItem("four vector hotdog", "saukraut", false, 3.05);
        addItem("five vector tdog", "saukraut", false, 3.05);
        addItem("six vector hotdog", "saukraut", false, 3.05);
    }
    void addItem(string name, string description, bool vegan, double price)
    {
        MenuItem* menuitem = new MenuItem(name, description, vegan, price);
        //不断添加菜单项到菜单中，
        m_menuItems.push_back(menuitem);
    }
};




class Waitress {
private:
    DinerMenu* m_dinerMenu;
    PancakeHouseMenu* m_PancakeMenu;
public:
    Waitress(DinerMenu* menu,PancakeHouseMenu* rootMenuList)
    {
        this->m_dinerMenu = menu;//拿取菜单资源
        this->m_PancakeMenu=rootMenuList;
    }
    void printMenu()
    {
        // Iterator_* piteratordiner = m_dinerMenu->creatorIterator();//拿一个临时迭代器
        // printMenu(piteratordiner);
        std::cout << "================"<<std::endl;
        Iterator_ *piteatorpanck= m_PancakeMenu->creatorIterator();
        printMenu(piteatorpanck);

    }
    void printMenu(Iterator_* iterator)
    {
        while (iterator->hasNext())
        {
            MenuItem* pmenuiterator = (MenuItem*)(iterator->next());
            std::cout << pmenuiterator->getName() << std::endl;
        }  
    }
};
//目的就在于实现一个同时使用这两个菜单的客户代码，
int main()
{
    DinerMenu* pdinermenu = new DinerMenu();//生成m_menu实体
    PancakeHouseMenu *pancakeHouseMenu = new PancakeHouseMenu();
    Waitress* pwaitress = new Waitress(pdinermenu,pancakeHouseMenu);//
    
    pwaitress->printMenu();
    return 0;
}