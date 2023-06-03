#include<hash_set>
#include<iostream>
using namespace std;
int main(){
    __gnu_cxx::hashtable<int,int, hash<int>,_Identity<int>,equal_to<int>,allocator<int>>
    iht(50,hash<int>(),equal_to<int>());

    cout<<iht.size()<<endl;
    cout<<iht.bucket_count()<<endl;
    cout<<iht.max_bucket_count()<<endl;
    //=========
    iht.insert_unique(59);
    iht.insert_unique(63);
    iht.insert_unique(108);
    iht.insert_unique(2);
    iht.insert_unique(53);
    iht.insert_unique(55);
    cout << iht.size() << endl;
    cout<<"==========="<<endl;
    // 遍历所有buckets，如果节点个数不为0则打印
    for (int i = 0; i < iht.bucket_count(); ++i) {
        int n = iht.elems_in_bucket(i);
        if (n!=0) 
            cout << "bucket[" << i << "] has " << n << " elems." << endl;
    }
    /*
bucket[0] has 1 elems.
bucket[2] has 3 elems.
bucket[6] has 1 elems.
bucket[10] has 1 elems.
    */

}