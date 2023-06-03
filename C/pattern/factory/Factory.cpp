#include<iostream>
using namespace std;
/*
工厂方法模式（Factory Method Pattern）又叫虚拟构造函数（Virtual Constructor）模式或者多态性工厂（PolymorphicFactory）模式。
工厂方法模式的用意是定义一个创建产品对象的工厂接口，将实际创建性工作推迟到子类中，
即定义一个用于创建对象的接口，让子类决定实例化哪个类。工厂方法使一个类的实例化延迟到其子类。
*/
//定义产品类型
typedef enum{
    Product_Type_01,
    Product_Type_02
}Product_Type;
//定义抽象产品类
class Product{
public:
    virtual string getType()=0;
};
//具体产品类01
class Product01:public Product{
public:
    Product01():Product(),m_type("Product01"){}
    string getType(){ //
        cout<<m_type<<endl;
        return m_type; //
    }
private:
    string m_type;
};
// //抽象工厂类
// class ProductFactory{
// public:
//     virtual Product *creatProduct()=0;
// };
//具体创建工厂类
class Product01Factory{
public:
    virtual Product *creatProduct(){
        return new Product01();//Product01 称为产品 子类实例化对象
    }
};
// //具体产品类02
// class Product02:public Product{
// public:
//     Product02():Product(),m_type("Product02"){}
//     string getType(){
//         cout<<m_type<<endl;
//         return m_type;
//     }
// private:
//     string m_type;
// };
// //具体创建工厂类
// class Product02Factory{
// public:
//     virtual Product *creatProduct(){
//         return new Product02();//为什么能够返回Product01
//     }
// }; 
int main(){
    Product01Factory *factory01=new Product01Factory(); //创建工厂接口
    Product *product01=factory01->creatProduct();//子类
    product01->getType();//子类实现功能

    // Product02Factory *factory02=new Product02Factory();
    // Product *product02=factory02->creatProduct();
    // product02->getType();

    delete product01;
    product01=nullptr;
    delete factory01;
    factory01=nullptr;
    // delete product02;
    // product02=nullptr;
    // delete factory02;
    // factory02=nullptr;


}
/*
伪代码
// 创建者类声明的工厂方法必须返回一个产品类的对象。创建者的子类通常会提供
// 该方法的实现。
class Dialog is
    // 创建者还可提供一些工厂方法的默认实现。
    abstract method createButton():Button

    // 请注意，创建者的主要职责并非是创建产品。其中通常会包含一些核心业务
    // 逻辑，这些逻辑依赖于由工厂方法返回的产品对象。子类可通过重写工厂方
    // 法并使其返回不同类型的产品来间接修改业务逻辑。
    method render() is
        // 调用工厂方法创建一个产品对象。
        Button okButton = createButton()
        // 现在使用产品。
        okButton.onClick(closeDialog)
        okButton.render()


// 具体创建者将重写工厂方法以改变其所返回的产品类型。
class WindowsDialog extends Dialog is
    method createButton():Button is
        return new WindowsButton()

class WebDialog extends Dialog is
    method createButton():Button is
        return new HTMLButton()


// 产品接口中将声明所有具体产品都必须实现的操作。
interface Button is
    method render()
    method onClick(f)

// 具体产品需提供产品接口的各种实现。
class WindowsButton implements Button is
    method render(a, b) is
        // 根据 Windows 样式渲染按钮。
    method onClick(f) is
        // 绑定本地操作系统点击事件。

class HTMLButton implements Button is
    method render(a, b) is
        // 返回一个按钮的 HTML 表述。
    method onClick(f) is
        // 绑定网络浏览器的点击事件。


class Application is
    field dialog: Dialog

    // 程序根据当前配置或环境设定选择创建者的类型。
    method initialize() is
        config = readApplicationConfigFile()

        if (config.OS == "Windows") then
            dialog = new WindowsDialog()
        else if (config.OS == "Web") then
            dialog = new WebDialog()
        else
            throw new Exception("错误！未知的操作系统。")

    // 当前客户端代码会与具体创建者的实例进行交互，但是必须通过其基本接口
    // 进行。只要客户端通过基本接口与创建者进行交互，你就可将任何创建者子
    // 类传递给客户端。
    method main() is
        this.initialize()
        dialog.render()

*/

