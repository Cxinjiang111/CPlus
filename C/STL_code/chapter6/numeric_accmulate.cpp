#include<numeric>
#include<vector>
#include<functional>
#include<iostream>
#include<iterator>
using namespace std;
void print(vector<int>& iv)
{
    for(int i=0;i<iv.size();i++)
    {
        cout<<iv[i]<<"\t";
    }
    cout<<endl;
}
int main()
{
    vector<int> iv{0,1,2,3,4};
    vector<int> iv2{4,5,6,7};
    cout<<accumulate(iv.begin(),iv.begin()+3,0)<<endl;// 0+1+2= 3 
    
    //minus<int>() x-y
    cout<<accumulate(iv.begin(),iv.end(),0,minus<int>())<<endl;// 0-0-1-2-3=-6
    // //                   first       end      first     sum 
    cout<<inner_product(iv.begin(),iv.end(),iv2.begin(),10)<<endl;//0*4+1*5+2*6+3*7+10=48
    //cout<<inner_product(iv.begin(),iv.end(),iv2.begin(),10,minus<int>(),plus<int>())<<endl;// 10-0+4-1+5-2+6-3+7=-18
    cout<<endl;
    ostream_iterator<int> oite(cout," ");
    partial_sum(iv.begin()+1,iv.begin()+4,oite);// 不包括4 尾区间 1 1+2  1+2+3 前缀和
    cout<<endl;
    partial_sum(iv.begin(),iv.end(),oite,minus<int>());//0-1 0-1-2 0-1-2-3 0-1-2-3-4

    // adjacent_difference(iv.begin(),iv.end(),oite);
    // adjacent_difference(iv.begin(),iv.end(),oite,plus<int>());


    return 0;
}