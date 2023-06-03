#include<thread>
#include<chrono>
#include<future>
#include<iostream>
using namespace std;
void print(int a){
    for(unsigned i=a;i<a+10;i++){
        cout<<i<<endl;
    }
}
void t1(){
     int n=10;
    auto fut1=std::async(print,10);
    std::thread t1(print,30);
    fut1.get();
    t1.join();
}
void f(){
    
}
int main(){
   
    return 0;

}