/*
再重载new和delete的基础上可以自己写出很多不同的版本，但是再原基础上智能增加，，第一个参数是
size_t,
Foo *pf=new (10,'c)Foo;
但自写的operator delete()写出很多的版本，但他们绝不会被delete调用，只有当new所调用
的ctor抛出的expection，才会调用这些重载版本的delete（），主要用来归还未能完全创造成功
的object所占用的memory
*/
#include<iostream>
#include<exception>
#include<malloc.h>
#include<string>
using namespace std;
class Bad {
    Bad(){
        cout<<"Bad is here"<<endl;
    }
 };
class Foo
{
public:
  	Foo() { cout << "Foo::Foo()" << endl;  }
  	Foo(int) { 
	   			cout << "Foo::Foo(int)" << endl;  
	           	// throw Bad();  构造函数这里这里抛出异常，如果在内存没有完全的建立起来，这时抛出异常比较合适
			 }

  	//(1) 這個就是一般的 operator new() 的重載 
  	void* operator new(size_t size) {
		cout << "operator new(size_t size), size= " << size << endl;
    	return malloc(size);  
  	}

  	//(2) 這個就是標準庫已經提供的 placement new() 的重載 (形式)
	//    (所以我也模擬 standard placement new 的動作, just return ptr) 
  	void* operator new(size_t size, void* start) { 
	  	cout << "operator new(size_t size, void* start), size= " << size << "  start= " << start << endl;
    	return start;
  	}

  	//(3) 這個才是嶄新的 placement new 
  	void* operator new(size_t size, long extra) { 
	  	cout << "operator new(size_t size, long extra)  " << size << ' ' << extra << endl;
    	return malloc(size+extra);
  	}

  	//(4) 這又是一個 placement new 
  	void* operator new(size_t size, long extra, char init) { 
	  	cout << "operator new(size_t size, long extra, char init)  " << size << ' ' << extra << ' ' << init << endl;
    	return malloc(size+extra);
  	}
  	
   	//(5) 這又是一個 placement new, 但故意寫錯第一參數的 type (它必須是 size_t 以滿足正常的 operator new) 
//!  	void* operator new(long extra, char init) { //[Error] 'operator new' takes type 'size_t' ('unsigned int') as first parameter [-fpermissive]
//!	  	cout << "op-new(long,char)" << endl;
//!    	return malloc(extra);
//!  	} 	

    //以下是搭配上述 placement new 的各個 called placement delete. 
	//當 ctor 發出異常，這兒對應的 operator (placement) delete 就會被喚起. 
	//應該是要負責釋放其搭檔兄弟 (placement new) 分配所得的 memory.  
  	//(1) 這個就是一般的 operator delete() 的重載 
  	void operator delete(void* p,size_t)
  	{ cout << "operator delete(void*,size_t)  " << endl;  
        free(p) ; 
    }

	//(2) 這是對應上述的 (2)  
  	void operator delete(void*p,void*start)
  	{ cout << "operator delete(void*,void*)  " << endl; 
              free(p) ;  }

	//(3) 這是對應上述的 (3)  
  	void operator delete(void*p,long)
  	{
        cout << "operator delete(void*,long)  " << endl; 
        free(p);
    }
	//(4) 這是對應上述的 (4)  
	//如果沒有一一對應, 也不會有任何編譯報錯 
  	void operator delete(void*p,long,char)
  	{ 
        cout << "operator delete(void*,long,char)  " << endl; 
        free(p);
    }
  	
private:
  	int m_i;
};


//-------------	
int  main(){
	cout << "\n\n\ntest_overload_placement_new().......... \n";
	//这些指针该怎样释放才是最安全的呢
  	Foo start;  //Foo::Foo

  	Foo* p1 = new Foo;           //op-new(size_t)
      free(p1);
    cout<<"=======   p1    ======"<<endl;
  	Foo* p2 = new (&start) Foo;  //op-new(size_t,void*)
      free(p2);  //    
    cout<<"=======   p2    ======"<<endl;      
  	Foo* p3 = new (100) Foo;     //op-new(size_t,long)
        free(p3);
    cout<<"=======   p3    ======"<<endl;      
  	Foo* p4 = new (100,'a') Foo; //op-new(size_t,long,char)
        free(p4);
    cout<<"=======   p4    ======"<<endl;
  	Foo* p5 = new (100) Foo(1);     //op-new(size_t,long)  op-del(void*,long)
        free(p5);
    cout<<"=======   p5    ======"<<endl;      
  	Foo* p6 = new (100,'a') Foo(1); //
        free(p6);
    cout<<"=======   p6    ======"<<endl;      
  	Foo* p7 = new (&start) Foo(1);  //
        free(p7);
    cout<<"=======   p7    ======"<<endl;      
  	Foo* p8 = new Foo(1);           //
        free(p8);
  	//VC6 warning C4291: 'void *__cdecl Foo::operator new(unsigned int)'
  	//no matching operator delete found; memory will not be freed if
  	//initialization throws an exception
      //这个能申请但是不好释放
}