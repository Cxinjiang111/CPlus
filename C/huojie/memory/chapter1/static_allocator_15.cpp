/*
当你受困于必须为不同的class重写一边几乎相同的member operator new和member operator delete时，
应该将一个总是分配特定尺寸的之区别块memory Allocator 概念包装起来，使之更容易使用，不同的Allocator object
维护不同的free-list
*/
#include<iostream>
#include <complex>
using namespace std;
class Allocator 
{
private:
  	struct obj {
    	struct obj* next;  //embedded pointer
  	};	
public:
    void* allocate(size_t);
    void  deallocate(void*, size_t);
    void  check();
    
private: 
    obj* freeStore = nullptr;
    const int CHUNK = 5; //小一點方便觀察 
};

void* Allocator::allocate(size_t size)
{
  	obj* p;

  	if (!freeStore) {
      	//linked list 是空的，所以攫取一大塊 memory
      	size_t chunk = CHUNK * size;
      	freeStore = p = (obj*)malloc(chunk);  
      
      	//cout << "empty. malloc: " << chunk << "  " << p << endl;
     
      	//將分配得來的一大塊當做 linked list 般小塊小塊串接起來
      	for (int i=0; i < (CHUNK-1); ++i)	{  //沒寫很漂亮, 不是重點無所謂.  
           	p->next = (obj*)((char*)p + size);
           	p = p->next;
      	}
      	p->next = nullptr;  //last       
  	}
  	p = freeStore;
  	freeStore = freeStore->next;
   
  	//cout << "p= " << p << "  freeStore= " << freeStore << endl;
  
  	return p;
}
void Allocator::deallocate(void* p, size_t)
{
  	//將 deleted object 收回插入 free list 前端
  	((obj*)p)->next = freeStore;
  	freeStore = (obj*)p;
}
void Allocator::check()
{ 
    obj* p = freeStore;
    int count = 0;
    
    while (p) {
        cout << p << endl;
		p = p->next;
		count++;
	}
    cout << count << endl;
}
//借鏡 MFC macros. 
// DECLARE_POOL_ALLOC -- used in class definition
#define DECLARE_POOL_ALLOC() \
public: \
    void* operator new(size_t size) { return myAlloc.allocate(size); } \
    void operator delete(void* p) { myAlloc.deallocate(p, 0); } \
protected: \
    static Allocator myAlloc; 

// IMPLEMENT_POOL_ALLOC -- used in class implementation file
#define IMPLEMENT_POOL_ALLOC(class_name) \
Allocator class_name::myAlloc; 


// in class definition file
class Foo {
   DECLARE_POOL_ALLOC()
public: 
	long L;
	string str;
public:
	Foo(long l) : L(l) {  }   
};
//in class implementation file
IMPLEMENT_POOL_ALLOC(Foo) 

//  in class definition file
class Goo {
   DECLARE_POOL_ALLOC()
public: 
	complex<double> c;
	string str;
public:
	Goo(const complex<double>& x) : c(x) {  }   
};
//in class implementation file
IMPLEMENT_POOL_ALLOC(Goo) 


int main()
{
	cout << "\n\n\ntest_static_Allocator().......... \n";	
    {
Foo* p[100];
 
	cout << "sizeof(Foo)= " << sizeof(Foo) << endl;
   	for (int i=0; i<23; ++i) {	//23,任意數, 隨意看看結果 
	   	p[i] = new Foo(i); 
	    cout << p[i] << ' ' << p[i]->L << endl;
	}
	//Foo::myAlloc.check();
	
   	for (int i=0; i<23; ++i) {
	   	delete p[i]; 
	}
    }	
	//Foo::myAlloc.check();
    {
    Goo* p[100];
 
	cout << "sizeof(Goo)= " << sizeof(Goo) << endl;
   	for (int i=0; i<17; ++i) {	//17,任意數, 隨意看看結果 
	   	p[i] = new Goo(complex<double>(i,i)); 
	    cout << p[i] << ' ' << p[i]->c << endl;
	}
	//Goo::myAlloc.check();
	
   	for (int i=0; i<17; ++i) {
	   	delete p[i]; 
	}	
	//Goo::myAlloc.check();	
    }
/*
test_static_Allocator().......... 
sizeof(Foo)= 40
0x6552c0 0
0x6552e8 1
0x655310 2
0x655338 3
0x655360 4
0x655390 5
0x6553b8 6
0x6553e0 7
0x655408 8
0x655430 9
0x655460 10
0x655488 11
0x6554b0 12
0x6554d8 13
0x655500 14
0x655530 15
0x655558 16
0x655580 17
0x6555a8 18
0x6555d0 19
0x655600 20
0x655628 21
0x655650 22
sizeof(Goo)= 48
0x6556d0 (0,0)
0x655700 (1,1)
0x655730 (2,2)
0x655760 (3,3)
0x655790 (4,4)
0x6557d0 (5,5)
0x655800 (6,6)
0x655830 (7,7)
0x655860 (8,8)
0x655890 (9,9)
0x6558d0 (10,10)
0x655900 (11,11)
0x655930 (12,12)
0x655960 (13,13)
0x655990 (14,14)
0x6559d0 (15,15)
0x655a00 (16,16)
//很牛逼 但是要利用在现实还需要深入思考内存，这种根据特定的环境分配比较特定的内存
块大小，很是有用，
*/
}




