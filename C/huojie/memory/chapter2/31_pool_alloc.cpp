
#include<iostream>
#include <vector>
#include <list>
#include <ext/pool_allocator.h> 
using namespace std;
//C++/11 alias template

//----------------------------------------------------
#include <cstdlib>	//malloc, free

void* myAlloc(size_t size)
{  return malloc(size); }

void myFree(void* ptr)
{  return free(ptr); }

//我要設計一個可以累計總分配量和總釋放量的 operator new() / operator delete().
//除非 user 直接使用 malloc/free, 否則都避不開它們, 這樣就可以累積總量. 
static long long countNew = 0;//内存量
static long long countDel = 0;//free的数量	    
static long long countArrayNew = 0;
static long long countArrayDel = 0;
static long long timesNew = 0;//次数

//小心，這影響無遠弗屆 
//它們不可被聲明於一個 namespace 內 
//以下是成功的, 但我暫時不想要它 (免得對我這整個測試程序帶來影響). 
/*
inline void* operator new(size_t size) 	 
{
    //cout << "jjhou global new(), \t" << size << "\t"; 
    countNew += size; 
    ++timesNew;  
    //void* p = myAlloc( size ); 
    //cout << p << endl; 
    //return p;
    
    return myAlloc( size ); 	    
}

inline void* operator new[](size_t size)  
{ 
    cout << "jjhou global new[](), \t" << size << "\t";
    countArrayNew += size; 				

    void* p = myAlloc( size ); 
    cout << p << endl; 
    return p;
    
    //return myAlloc( size ); 	    
}	

//天啊, 以下(1)(2)可以並存並由(2)抓住流程 (但它對我這兒的測試無用). 
//當只存在 (1) 時, 抓不住流程. 
//在 class members 中二者只能擇一 (任一均可) 
//(1) 
inline void  operator delete(void* ptr, size_t size)  
{  	
    cout << "jjhou global delete(ptr,size), \t" << ptr << "\t" << size << endl;	
    countDel += size;  	
    myFree( ptr ); 			
}
//(2)
inline void  operator delete(void* ptr)  
{  	
    //cout << "jjhou global delete(ptr), \t" << ptr << endl;	 	
    myFree( ptr ); 			
}	

//(1)
inline void  operator delete[](void* ptr, size_t size) 
{ 
    cout << "jjhou global delete[](ptr,size), \t" << ptr << "\t" << size << endl;
    countArrayDel += size; 
    myFree( ptr ); 			
}	
//(2)
inline void  operator delete[](void* ptr) 
{ 
    cout << "jjhou global delete[](ptr), \t" << ptr << endl;
    myFree( ptr ); 			
}
*/

template <typename T>
using listPool = list<T, __gnu_cxx::__pool_alloc<T>>; 	
//-------------	
int main()
{
	cout << "\n\n\ntest_overload_global_new().......... \n";

//***** 測試時, main() 中的其他測試全都 remark, 獨留本測試 *****
  { 
    cout << "::countNew= " << ::countNew << endl;		//0
    cout << "::countDel= " << ::countDel << endl;   	//0 
    cout << "::timesNew= " << ::timesNew << endl;   	//0 
    
    string* p = new string("My name is Ace");		//jjhou global new(), 4 	(註：這是 string size) 
    												//jjhou global new(), 27	(註：這是 sizeof(Rep)+extra) 
    delete p;		//jjhou global delete(ptr), 0x3e3e48
    				//jjhou global delete(ptr), 0x3e3e38
    
    cout << "::countNew= " << ::countNew << endl;	//31 ==> 4+27
    cout << "::timesNew= " << ::timesNew << endl;   //2
    cout << "::countDel= " << ::countDel << endl;	//0 <== 本測試顯然我永遠觀察不到我所要觀察的
	               									//      因為進不去 operator delete(ptr,size) 版 	               								
	    
	p = new string[3];		//jjhou global new[](), 16 (註：其中內含 arraySize field: 4 bytes, 
													  	//所以 16-4 = 12 ==> 4*3, 也就是 3 個 string 每個佔 4 bytes)
							//jjhou global new(), 13  	//Nil string
							//jjhou global new(), 13	//Nil string	
							//jjhou global new(), 13	//Nil string										
							
    delete [] p;			//jjhou global delete(ptr),   0x3e3e88
							//jjhou global delete(ptr),   0x3e3e70
							//jjhou global delete(ptr),   0x3e39c8
							//jjhou global delete[](ptr), 0x3e3978   
							
    cout << "::countNew= " << ::countNew << endl;			//70 ==> 4+27+13+13+13
    cout << "::timesNew= " << ::timesNew << endl;   		//5    
    cout << "::countArrayNew= " << ::countArrayNew << endl;	//16 (這個數值其實對我而言無意義)
	
	//測試: global operator new 也會帶容器帶來影響
	vector<int> vec(10);	//jjhou global new(), 	40  	0x3e3ea0  (註：10 ints)
							//註：vector object 本身不是 dynamic allocated. 
	vec.push_back(1); 		
	  		 				//jjhou global new(), 	80		0x3e3ed0
							//jjhou global delete(ptr), 	0x3e3ea0	
	vec.push_back(1); 		
	vec.push_back(1); 	
								
    cout << "::countNew= " << ::countNew << endl;	//190 ==> 70+40+80		
    cout << "::timesNew= " << ::timesNew << endl;   //7    
	
	list<int> lst;		//註：list object 本身不是 dynamic allocated. 	
	lst.push_back(1); 	//jjhou global new(), 	12	(註：每個 node是 12 bytes) 
	lst.push_back(1); 	//jjhou global new(), 	12
	lst.push_back(1); 	//jjhou global new(), 	12
    cout << "::countNew= " << ::countNew << endl;	//226 ==> 190+12+12+12		
    cout << "::timesNew= " << ::timesNew << endl;   //10  
			
	//jjhou global delete(ptr), 	0x3e3978
	//jjhou global delete(ptr), 	0x3e39c8
	//jjhou global delete(ptr), 	0x3e3e70
	//jjhou global delete(ptr), 	0x3e3ed0	
  }
	
  {
  	//reset countNew
	countNew = 0;
	timesNew = 0;	
	
  	//list<double, __gnu_cxx::__pool_alloc<double>> lst;	
	//上一行改用 C++/11 alias template 來寫 : 
	listPool<double> lst; 

  	for (int i=0; i< 1000000; ++i)
  	    lst.push_back(i);
    cout << "::countNew= " << ::countNew << endl;  	//16752832 (注意, node 都不帶 cookie)
    cout << "::timesNew= " << ::timesNew << endl;   //122	
  }
  
  {
  	//reset countNew
	countNew = 0;
	timesNew = 0;	
  	list<double> lst;
  	for (int i=0; i< 1000000; ++i)
  	    lst.push_back(i);
    cout << "::countNew= " << ::countNew << endl;	//16000000 (注意, node 都帶 cookie)
    cout << "::timesNew= " << ::timesNew << endl;   //1000000    
  }  										 
}