#include<iostream>
#include<cstdlib>
#include<functional>
using namespace std;
typedef int(*fcmp)(const int*elem1,const int*elem2) ; 
int main(){
    int ia[10]={1,3,45,6,35,12,14,42,13,34};
    qsort(ia,sizeof(ia)/sizeof(int),sizeof(int),fcmp);//我怎么忘了函数指针
    for(auto & s:ia){
        cout<<s<<"\t";
    }
}
int fcmp(const int*elem1,const int*elem2){
    const int* i1=(const int*)elem1;
    const int* i2=(const int*)elem2;
    if(*i1<*i2){
        return -1;
    }
    else if(*i1==*i2){
        return 0;
    }
    else{
        return 1;
    }
}




