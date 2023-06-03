/*谨慎使用多重继承
*/
#include<iostream>
using namespace std;
class BorrowableItem{
public:
    BorrowableItem();
    void checkout();
};
BorrowableItem::BorrowableItem()
{

}

void BorrowableItem::checkout()
{
    cout<<"BorrowableItem::checkout()"<<endl;
}

class ElectronGadget{
public:
    ElectronGadget();
private:
    bool checkout()const;
};
ElectronGadget::ElectronGadget()
{

}
bool ElectronGadget::checkout()const
{
    cout<<"ElectronGadget::checkout"<<endl;
}
class MP3Player:public BorrowableItem,public ElectronGadget {
public:
    MP3Player(BorrowableItem &b,ElectronGadget &e):MP3Player::BorrowableItem(b),MP3Player::ElectronGadget(e){}; //error 两个重载
};

int main()
{
    BorrowableItem b;
    ElectronGadget e;
    MP3Player m(b,e);
    m.checkout();//error  checkout’ is ambiguous 编译器直接报错 存在歧义 
    return 0;
}