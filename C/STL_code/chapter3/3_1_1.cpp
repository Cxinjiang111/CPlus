#include<vector>
#include<list>
#include<deque>
#include<algorithm>
#include<iostream>
using namespace std;
int main(){
    const int arraySize=7;
    int ia[arraySize]={1,2,3,4,5,6,7};
    vector<int> ivect(ia,ia+arraySize);//指向int型的指针此时是迭代器
    list<int>  ilist(ia,ia+arraySize);
    deque<int> iqueue(ia,ia+arraySize);
    vector<int>::iterator it=find(ivect.begin(),ivect.end(),4);
    if(it==ivect.end()){
        cout<<"ivect not find()"<<endl;
    }
    else{
        cout<<"ivect find()"<<endl;
    }
 list<int>::iterator it2=find(ilist.begin(),ilist.end(),4);
    if(it2==ilist.end()){
        cout<<"ilist not find()"<<endl;
    }
    else{
        cout<<"ilist find()"<<endl;
    }
 deque<int>::iterator it3=find(iqueue.begin(),iqueue.end(),4);
    if(it3==iqueue.end()){
        cout<<"iqueue not find()"<<endl;
    }
    else{
        cout<<" iqueue find()"<<endl;
    }

    return 0;

}

