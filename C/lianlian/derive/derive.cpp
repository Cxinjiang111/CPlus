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
    // Base b1(1);
    // //  cout<<"this is virtual Base printData"<<endl;
    // //  cout<<" data is"<<m_nbase<<endl;
    // b1.printData();
    // Base b2(2);
    // // cout<<"this is Derive construct"<<endl;
    // //  cout<<"this is Derive printData"<<endl;
    // b2.printData();
    // cout<<"------------\n";
    // Derive d1(2);
    // //    cout<<"this is base construct"<<endl;
    // //    cout<<"this is Derive printData"<<endl;
    // d1.printData();
    // cout<<"------------\n";
    Base *pb1=new Derive(2); //这个看成是强转就行 申请了集成类的空间
    //   cout<<"this is Derive construct"<<endl;
    //  cout<<"this is Derive construct"<<endl;
    //   cout<<"Derive data is"<<m_nbase2<<endl;
    pb1->printData();
    cout<<"-------------\n";
/* 这个答案怎么这么奇怪
this Derived  destruct
this is Base destruct
*/
    delete pb1;
}