#include<iterator>
#include<hashtable.h>
#include<hash_fun.h>
#include<algorithm>
using namespace std;
template<typename T,typename CompareFunction=less<T> >
class hash_compare{
public:
    enum{
        bucket_size=4,
        min_buckets=8
    };
    size_t operator()(const T&)const;
    bool operator()(const T &,const T&)const;
};
template<typename T,typename HashingInfo=hash_compare<T,less<T>>,typename Allocator=allocator<T>>
class hash_container{};








