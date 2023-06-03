#ifndef __SCREEN_H__
#define __SCREEN_H__
#include <iostream>
using namespace std;
#include <string>
#include <vector>

class Screen
{
public:
    typedef std::string::size_type pos;
    //因为Screen有另一个构造函数
    //所以要实现一个默认构造函数
    Screen() = default;
    // cursor被初始化为0
    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}

    //读取光标处字符
    char get() const
    {
        //隐式内联
        return contents[cursor];
    }

    //显示内联
    inline char get(pos ht, pos wd) const;
    //能在之后被设为内联
    Screen &move(pos r, pos c);
    void some_member() const;
    Screen &set(char);
    Screen &set(pos, pos, char);

    const Screen &display(ostream &os) const;

    Screen &display(ostream &os);

    void do_display(ostream &os) const;
    // Window_mgr可以访问Screen类的私有部分
    friend class Window_mgr;

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    //即使在一个const对象里access_ctr也可被修改
    mutable size_t access_ctr;
};

class First
{
    int memi;
    int getMem();
};

struct Second
{
    int memi;
    int getMem();
};

class Link_screen
{
    Screen window;
    Link_screen *next;
    Link_screen *prev;
};

class Window_mgr
{
public:
    //窗口中每个屏幕的编号
    using ScreenIndex = std::vector<Screen>::size_type;
    //按照编号将指定的Screen重置为空白
    void clear(ScreenIndex);
    ScreenIndex addScreen(const Screen &);

private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

#endif