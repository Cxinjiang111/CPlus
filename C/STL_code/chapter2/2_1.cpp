#include"jjalloc.h"
#include<vector>
#include<memory>
using namespace std;
int main(){
    //   居然能运行
    int ia[5]={1,2,3,4,5};
    unsigned int i;
    //vector<int,JJ::allocator<int> >iv(ia,ia+5); 
    vector<int,std::allocator<int>>iv(ia,ia+5);
    //vector<int,std::alloc>iv(ia,ia+5);error
    //   标准库
    //  template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    //class vector : protected _Vector_base<_Tp, _Alloc>
    for(i=0;i<iv.size();i++){
        cout<<iv[i]<<"\t";
    }
    cout<<endl;
    /*
allocator ::allocate
allocator ::construct
allocator ::construct
allocator ::construct
allocator ::construct
allocator ::construct
1       2       3       4       5
allocator ::deallocate

    */
   
    return 0;
}