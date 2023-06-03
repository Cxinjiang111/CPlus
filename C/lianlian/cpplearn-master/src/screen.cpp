#include "../inc/screen.h"
Screen &Screen::move(pos r, pos c)
{
    //计算行的位置
    pos row = r * width;
    //把光标移动到指定的列
    cursor = row + c;
    //以左值形式返回
    return *this;
}

char Screen::get(pos r, pos c) const
{
    //计算行的位置
    pos row = r * width;
    //返回给定的字符
    return contents[row + c];
}

void Screen::some_member() const
{ //在const函数中也可以修改access_ctr
    ++access_ctr;
}

Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}
Screen &Screen::set(pos r, pos col, char ch)
{
    //给定位置设置新值
    contents[r * width + col] = ch;
    return *this;
}

const Screen &Screen::display(ostream &os) const
{
    do_display(os);
    return *this;
}

void Screen::do_display(ostream &os) const
{
    os << "width is " << width << " "
       << "height is " << height << endl;
}

Screen &Screen::display(ostream &os)
{
    do_display(os);
    return *this;
}

void Window_mgr::clear(ScreenIndex i)
{
    // s是一个Screen的引用，指向我们想清空的屏幕
    Screen &s = screens[i];
    //清空屏幕
    s.contents = string(s.height * s.width, ' ');
}

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}
