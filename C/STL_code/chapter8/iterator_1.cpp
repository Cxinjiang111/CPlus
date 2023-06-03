#include<iterator>
#include<deque>
#include<algorithm>
#include<iostream>
using namespace std;
int main(){
    //输出迭代器
    ostream_iterator<int>  outite(cout," ");
    int ia[]={0,1,2,3,4,5};
    deque<int> id(ia,ia+6);
     
    // copy(id.begin(),id.end(),outite);//将所有元素拷贝到outite 也就是cout
    // cout<<endl;

    // copy(ia+1,ia+2,front_inserter(id));//头插，
    // copy(id.begin(),id.end(),outite);
    
    deque<int>::iterator ite=find(id.begin(),id.end(),5);
    copy(ia+0,ia+3,inserter(id,ite));
    copy(id.begin(),id.end(),outite);
    cout<<endl;

}