#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int ia[9]={0,1,2,7,8,9,3,5,6};
    vector<int> ivec(ia,ia+9);
    make_heap(ivec.begin(),ivec.end());
    for(int i=0;i<ivec.size();i++){
        cout<<ivec[i]<<" ";
    }
    cout<<endl;
    ivec.push_back(7);
    push_heap(ivec.begin(),ivec.end());
    for(int i=0;i<ivec.size();i++){
        cout<<ivec[i]<<" ";
    }
    cout<<endl;
    pop_heap(ivec.begin(),ivec.end());
    for(int i=0;i<ivec.size();i++){
        cout<<ivec[i]<<" ";
    }
    cout<<endl;
    sort_heap(ivec.begin(),ivec.end());
    for(int i=0;i<ivec.size();i++){
        cout<<ivec[i]<<" ";
    }
    cout<<endl;

}