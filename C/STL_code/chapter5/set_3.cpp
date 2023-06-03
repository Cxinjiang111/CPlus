#include<set>
#include<iostream>
using namespace std;
int main(){
    int i;
    int ia[5]={0,1,2,3,4};
    set<int> iset(ia,ia+5);
    cout<<"size="<<iset.size()<<endl;
    cout<<"3 cout"<<iset.count(3)<<endl;
    iset.insert(3);
    cout<<"size="<<iset.size()<<endl;
    cout<<"3 cout"<<iset.count(3)<<endl;
    iset.erase(1);
    cout<<"size="<<iset.size()<<endl;
    cout<<"1 cout"<<iset.count(1)<<endl;

    set<int>::iterator it=iset.begin();
    set<int>::iterator it2=iset.end();
    for(;it!=it2;it++){
        cout<<*it;
    }
    cout<<endl;

}