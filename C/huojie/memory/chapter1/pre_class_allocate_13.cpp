#include<cstddef>
#include<iostream>
using namespace std;
class Airplane{
private:
    struct AirplaneRep{
        unsigned long miles;
        char type;
    };
private:
    union{
        AirplaneRep rep;
        Airplane *next;
    };
public:
    unsigned long getMiles(){return rep.miles;}
    void *operator new(size_t size);
    void operator delete(void *deadObject,size_t size);    
    char getType(){return rep.type;}
    void set(unsigned long m,char t)
    {
        rep.miles=m;
        rep.type=t;
    }
public:
    static const int BLOCK_SIZE;
    static Airplane*headOfFreeList;
};
const int Airplane::BLOCK_SIZE=512;
Airplane *Airplane::headOfFreeList;//这是个static 全局有效，谁都可以改
void *Airplane::operator new(size_t size)
{
    if(size!=sizeof(Airplane))
    {
        return ::operator new(size);
    }
    Airplane *p=headOfFreeList;
    //这时是p不为空，指向一篇有效的区域
    if(p)
    {
        headOfFreeList=p->next;
    }else{
        //预申请的数量的对象用完了，delete中可看出每次销毁一个对象先是指针向后移动，等移动到空，在释放，
        //此时你在使用对象也就是headOfFreeList指向为空时，申请默认的BLOCK_SIZE的大小提供使用，虽然你在
        //调用new，但不一定真的在执行new 相当于一个内存池提供使用，而不是简单的申请size大小的内存对象
        //申请一段内存
        Airplane*newBlock=static_cast<Airplane*>
        (::operator new(BLOCK_SIZE*sizeof(Airplane)));
        //把申请的512个类对象的内存给连起来,这里不是从0开始，
        for(int i=1;i<BLOCK_SIZE-1;++i)
        {
            newBlock[i].next=&newBlock[i+1];
        }
        newBlock[BLOCK_SIZE-1].next=0;//末尾的这个赋为空
        p=newBlock;
        headOfFreeList=&newBlock[1];
    }
    return p;
}
void Airplane::operator delete(void *deadObject,size_t size)
{
    if(deadObject==0) return ;
    if(size!=sizeof(Airplane))
    {
        ::operator delete(deadObject);
        return ;
    }
    //size==sizeof(Airplane) 使用512个对象 中的几个，接下来继续向下使用
    Airplane *carcass=static_cast<Airplane*>(deadObject);
    carcass->next=headOfFreeList;
    headOfFreeList=carcass;
}
int main()
{
	cout << "\ntest_per_class_allocator_2().......... \n";		
	
  	cout << sizeof(Airplane) << endl;    //8

size_t const N = 100;
Airplane* p[N];	

   	for (int i=0; i< N; ++i)
   	     p[i] = new Airplane;     
			
    
    //隨機測試 object 正常否 
  	p[1]->set(1000,'A'); 	
  	p[5]->set(2000,'B');
  	p[9]->set(500000,'C');
  	cout << p[1] << ' ' << p[1]->getType() << ' ' << p[1]->getMiles() << endl;
  	cout << p[5] << ' ' << p[5]->getType() << ' ' << p[5]->getMiles() << endl;
  	cout << p[9] << ' ' << p[9]->getType() << ' ' << p[9]->getMiles() << endl; 
  	
	//輸出前 10 個 pointers, 用以比較其間隔 
   	for (int i=0; i< 10; ++i)  	   
		cout << p[i] << endl; 		 
	 
   	for (int i=0; i< N; ++i)
   	     delete p[i]; 
    /*
test_per_class_allocator_2().......... 
16
0x13d92d0 A 1000
0x13d9310 B 2000
0x13d9350 C 500000

0x13d92c0
0x13d92d0
0x13d92e0
0x13d92f0
0x13d9300
0x13d9310
0x13d9320
0x13d9330
0x13d9340
0x13d9350
    */	
//相差16字节
cout<<sizeof(Airplane)<<endl;//16 
    return 0;
}