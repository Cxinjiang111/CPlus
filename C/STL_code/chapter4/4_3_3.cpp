#include<list>
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int i;
    list<int> ilist;
    cout<<"size="<<ilist.size()<<endl;
    for(int j=0;j<5;j++){
        ilist.push_back(j);
    }
    cout<<"size="<<ilist.size()<<endl;

    list<int>::iterator ite;
    for(ite=ilist.begin();ite!=ilist.end();ite++){
        cout<<*ite<<" ";
    }
    cout<<endl;
    cout<<"========================="<<endl;
    ite=find(ilist.begin(),ilist.end(),3);
    if(ite!=ilist.end()){
        ilist.insert(ite,10);
    }
    for(ite=ilist.begin();ite!=ilist.end();ite++){
        cout<<*ite<<" ";
    }
    cout<<endl;
    cout<<"========================="<<endl;
    ite=find(ilist.begin(),ilist.end(),1);
    if(ite!=ilist.end()){
        cout<<*(ilist.erase(ite))<<endl;
    }
    cout<<"========================="<<endl;
    for(ite=ilist.begin();ite!=ilist.end();ite++){
        cout<<*ite<<" ";
    }
    cout<<endl;
}