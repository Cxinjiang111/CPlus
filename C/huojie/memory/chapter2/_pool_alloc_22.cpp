#include <cstddef>
#include <memory>				 //內含 std::allocator  
#include <ext/pool_allocator.h>	 //欲使用 std::allocator 以外的 allocator, 就得自行 #include <ext/...> 
#include <ext/mt_allocator.h>
#include <ext/debug_allocator.h>
#include <ext/bitmap_allocator.h>
#include <ext/malloc_allocator.h>
#include <ext/throw_allocator.h>
#include <ext/new_allocator.h>  //這其實已被 <memory> included, 它就是 std:allocator 的 base class 
#include <list>
#include <deque>
#include <vector>
#include <iostream>
using namespace std;
template <class T>
struct custom_allocator {
  	typedef T value_type;
  	custom_allocator() noexcept {}
  	template <class U> custom_allocator (const custom_allocator<U>&) noexcept {}
//! T* allocate (size_t n) { return static_cast<T*>(::new(n*sizeof(T))); }  
//     	編譯報錯，new 的語法是 new Type; 不是 new N; 改如下. josuttis 2/e 也如下.  
  	T* allocate (size_t n) { return static_cast<T*>(::operator new(n*sizeof(T))); }  
//	void deallocate (T* p, size_t n) { ::delete(p); }	 
//		編譯沒報錯，但我認為應使用 operator delete. 改如下. josuttis 2/e 也如下.
  	void deallocate (T* p, size_t n) { ::operator delete(p); }
};

//以下的 operator== 和 operator!= 原例有,但此處也許因是簡例,即使 mark 起來也 ok.(目前)  
//josuttis 2/e 中的 custom allocator 也有寫以下二個 operators  
template <class T, class U>
constexpr bool operator== (const custom_allocator<T>&, const custom_allocator<U>&) noexcept
{return true;}

template <class T, class U>
constexpr bool operator!= (const custom_allocator<T>&, const custom_allocator<U>&) noexcept
{return false;}	


/*
template<typename Alloc> 
void cookie_test(Alloc&& alloc, size_t n)	//由於呼叫時以 temp obj (Rvalue) 傳入，所以這兒使用 &&. 只是隨意之下的搭配
                                            //使用 &&，那麼呼叫時就不能以 Lvalue 傳入.  
*/                                            
//上述, pass by Rvalue reference 是 OK 的. 
//但我不想那麼標新立異, 就改用 pass by value 吧 
template<typename Alloc> 
void cookie_test(Alloc alloc, size_t n)                                                                                
{
    typename Alloc::pointer p1, p2, p3;		//需有 typename 
  	p1 = alloc.allocate(n); 		//allocate() and deallocate() 是 non-static, 需以 object 呼叫之. 
  	p2 = alloc.allocate(n);   	
  	p3 = alloc.allocate(n);  

  	cout << "p1= " << p1 << '\t' << "p2= " << p2 << '\t' << "p3= " << p3 <<"\t"<<p1-p2<< '\n';

        
    //自定义怎么释放    
  	alloc.deallocate(p1,sizeof(typename Alloc::value_type)); 	//需有 typename 
  	alloc.deallocate(p2,sizeof(typename Alloc::value_type));  	//有些 allocator 對於 2nd argument 的值無所謂  	
  	alloc.deallocate(p3,sizeof(typename Alloc::value_type)); 	
}

struct A{
int x;
int x1;
double y;
double y1;
double y2;
};
int main(){
  	cout << "\ntest_GNU_allocators().......\n";    	
	
  	//下例來自 http://www.cplusplus.com/reference/memory/allocator_traits/ 
  	vector<int,custom_allocator<int>> foo {10,20,30};
  	for (auto x : foo) cout << x << " ";		//10, 20, 30
  	cout << '\n';
	  
	  
	cout << sizeof(std::allocator<int>) << endl;			//1
    cout << sizeof(__gnu_cxx::new_allocator<int>) << endl;	//1. 
		//觀察 STL source 可知: new_allocator 是 std::allocator 的 base 
		//我們無法改變 std::allocator 的 base class, 那該如何使用其他的 GNU allocators ? 
		//是否要寫個 custom_allocator (像上面) 並為它加上我想要的 base (例如 __pool_alloc) ?
		//不，不必，就直接使用, 但需自行 #include <ext/...> 
		 
    				
	//從語法上試用各式各樣的 allocators										 
 	cout << sizeof(__gnu_cxx::malloc_allocator<int>) << endl;	//1. 大小 1者其實為 0, fields 都是 static. 
 	cout << sizeof(__gnu_cxx::__pool_alloc<int>) << endl;		//1
 	cout << sizeof(__gnu_cxx::__mt_alloc<int>) << endl;			//1
 	cout << sizeof(__gnu_cxx::bitmap_allocator<int>) << endl;	//1
 	cout << sizeof(__gnu_cxx::debug_allocator<std::allocator<double>>) << endl;	//16
//!	cout << sizeof(__gnu_cxx::throw_allocator<int>) << endl;	//只有 throw_allocator_base, throw_allocator_random, throw_allocator_limit, 沒有 throw_allocator !! 
		
 	//搭配容器 
 	list <int, __gnu_cxx::malloc_allocator<int>> list_malloc;  
 	deque <int, __gnu_cxx::debug_allocator<std::allocator<int>>> deque_debug;	
	vector<int, __gnu_cxx::__pool_alloc<int>> vector_pool;
//! vector<int, __pool_alloc<int>> vector_pool;   //如果沒加上 namespace : [Error] '__pool_alloc' was not declared in this scope 
   
    cout<<"test cookie"<<endl;
    //測試 cookie
	cout << "sizeof(int)=" << sizeof(int) << endl;			//4
	cout << "sizeof(double)=" << sizeof(double) << endl;	//8
	 
    cookie_test(std::allocator<int>(), 1);					//相距 20h (表示帶 cookie)
    cookie_test(__gnu_cxx::malloc_allocator<int>(), 1);    	//相距 20h (表示帶 cookie) 
    //内存池分配利用率较高
    cookie_test(__gnu_cxx::__pool_alloc<int>(), 1);			//相距 08h (表示不帶 cookie) 
    
    //以下將 int 改為 double 結果不變，意味上述 ints 間隔 8 (而非 4) 乃是因為 alignment. 
    cookie_test(std::allocator<double>(), 1);				//相距 20h (表示帶 cookie)
    cookie_test(__gnu_cxx::malloc_allocator<double>(), 1);  //相距 20h (表示帶 cookie) 
    //内存池分配利用率较高 适合比较小的   
    cookie_test(__gnu_cxx::__pool_alloc<double>(), 1);		//相距 08h (表示不帶 cookie)     
  
    

    //cout << "sizeof(array<int,3>) = " << sizeof(array<int,3>) << endl;	//12 ==> sizeof(_Alloc_block)=16=10h
    //cookie_test(__gnu_cxx::bitmap_allocator<array<int,3>>(), 1);		//相距 10h (表示不帶 cookie)  
//!    cookie_test(__gnu_cxx::bitmap_allocator<double>(), 1);				//相距 08h (不帶 cookie) 
    //  内存池分配最少
     std::cout<<"list begin"<<endl;
    list<A, std::allocator<A>> list_pool;
    A a;
    a.x=1;
    a.x1=1;
    a.y1=1;
    a.y1=2;
    a.y=3;
    for (int i=0; i<1000; ++i)
        list_pool.push_back(a);
    list<int, __gnu_cxx::malloc_allocator<int>> list_malloc1;
    for (int i=0; i<1000; ++i)
        list_malloc1.push_back(i);
    list<int, __gnu_cxx::__pool_alloc<int>> list_pool_alloc;
    for (int i=0; i<1000; ++i)
        list_pool_alloc.push_back(i);                
        
}
