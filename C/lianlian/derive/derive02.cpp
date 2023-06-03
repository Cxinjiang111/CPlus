#include<iostream>
using namespace std;
class Base{
    public:
        Base():m_nbase(0),m_nbase2(m_nbase+100){}
        Base(int n):m_nbase(n),m_nbase2(m_nbase+100){
            cout<<"this is base construct"<<endl;
        }
        virtual ~Base(){
            cout<<" this is Base destruct"<<endl;
        }
        virtual void printData(){
            cout<<"this is virtual Base printData"<<endl;
            cout<<" data is"<<m_nbase<<endl;
        }
        void printData2(){
            cout<<"base2 data is"<<m_nbase2<<endl;
        }
        int Sizeof(char p[]){
            return sizeof(p);
        }
        int Sizeof2(char *p){
            return sizeof(p);
        }
    private:
        int m_nbase;
        int m_nbase2;
};
class Derive:public Base{
    public:
        Derive(int n):Base(n),m_nderive(n){
            cout<<"this is Derive construct"<<endl;
        }
         ~Derive(){
            cout<<"this Derived  destruct"<<endl;
        }
        void printData(){
            cout<<"this is Derive printData"<<endl;
        }
    private:
        int m_nderive;
};
int main(){
    // Base *b1=nullptr;//没有构造出对象 访问空指针
    // //Segmentation fault 
    // b1->printData2();
    // b1->printData();

    char carry[100]="hello world";
    cout << "sizeof(carry)  " << sizeof(carry) << endl;
    cout<<"-----------------------"<<endl;
    char *pstr = "Hello World";
    cout << "sizeof(pstr)   " << sizeof(pstr) << endl;//测的是指针
    cout << "sizeof(*pstr)  " << sizeof(*pstr) << endl;//这个解应用为单个字符
    cout<<"-----------------------"<<endl;
    Base b1;
    cout<<"b1.Sizeof(carry)"<<b1.Sizeof(carry)<<endl;//carry作为一个指针传递，因此大小按指针大小计算
    cout<<"b1.Sizeof(carry)"<<b1.Sizeof2(carry)<<endl;//carry作为一个指针传递，因此大小按指针大小计算
}