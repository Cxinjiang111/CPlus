#include<iostream>
#include<string>
#include<vector>
#include<tuple>
using namespace std;
bool isLuck(int number){
   cout<<"isLuck(int number)"<<endl;
   return true;  
}
bool isLuck(char number)=delete;
int main(){
    ///isLuck('1');//这样该函数就被明确的被禁止调用
     isLuck(true);

 return 0;   
}