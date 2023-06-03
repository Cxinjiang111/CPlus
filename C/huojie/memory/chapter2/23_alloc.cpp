#include<iostream>
#include<vector>
using namespace std;
//本處完全模仿 SGI STL, G2.92 的 std::alloc  
//放在 namespace 中因此和 std 不衝突 
//此手法和 G4.92 ext\__pool_alloc.h 也完全相同.  
#define __THROW_BAD_ALLOC  cerr << "out of memory" << endl; exit(1)
//----------------------------------------------
// 第1級配置器。次要的，当第二级配置器无法分配内存时，进入第一级再次new_handler malloc分配一下，不断尝试
//----------------------------------------------
template <int inst>
class __malloc_alloc_template {
private:
  static void* oom_malloc(size_t);
  static void* oom_realloc(void *, size_t);
  static void (*__malloc_alloc_oom_handler)();

public:
  static void* allocate(size_t n)
  {
    void *result = malloc(n);   //直接使用 malloc()
    if (0 == result) result = oom_malloc(n);//没有分配到内存，这时需要调用系统函数重新刷新内存再次寻找内存
    return result;
  }
  static void deallocate(void *p, size_t /* n */)
  {
    free(p);                    //直接使用 free()
  }
  static void* reallocate(void *p, size_t /* old_sz */, size_t new_sz)
  {
    void * result = realloc(p, new_sz); //直接使用 realloc()
    if (0 == result) result = oom_realloc(p, new_sz);
    return result;
  }
  static void (*set_malloc_handler(void (*f)()))()
  { //類似 C++ 的 set_new_handler().
    void (*old)() = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = f;
    return(old);
  }
};
//----------------------------------------------
template <int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template <int inst>
void* __malloc_alloc_template<inst>::oom_malloc(size_t n)
{
  void (*my_malloc_handler)();//定义void *()类型的指针函数 名称为my_malloc_handler
  void* result;
  //不断的寻找分配
  for (;;) {    //不斷嘗試釋放、配置、再釋放、再配置…
    my_malloc_handler = __malloc_alloc_oom_handler;//这个__malloc_alloc_oom_handler应该是个寻找内存的过程函数
    if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }//抛出异常 仅仅打印而已
    (*my_malloc_handler)();    //呼叫處理常式，企圖釋放記憶體
    result = malloc(n);        //再次嘗試配置記憶體
    if (result) return(result);
  }
}

template <int inst>
void * __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
{
  void (*my_malloc_handler)();
  void* result;

  for (;;) {    //不斷嘗試釋放、配置、再釋放、再配置…
    my_malloc_handler = __malloc_alloc_oom_handler;
    if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
    (*my_malloc_handler)();    //呼叫處理常式，企圖釋放記憶體。
    result = realloc(p, n);    //再次嘗試配置記憶體。
    if (result) return(result);
  }
}
//----------------------------------------------

typedef __malloc_alloc_template<0>  malloc_alloc;

template<class T, class Alloc>
class simple_alloc {
public:
  static T* allocate(size_t n)
    { return 0 == n? 0 : (T*)Alloc::allocate(n*sizeof(T)); }
  static T* allocate(void)
    { return (T*)Alloc::allocate(sizeof(T)); }
  static void deallocate(T* p, size_t n)
    { if (0 != n) Alloc::deallocate(p, n*sizeof(T)); }
  static void deallocate(T *p)
    { Alloc::deallocate(p, sizeof(T)); }
};
//----------------------------------------------
//第二級配置器
//----------------------------------------------
enum {__ALIGN = 8};                        //小區塊的上調邊界 对齐
enum {__MAX_BYTES = 128};                  //小區塊的上限
enum {__NFREELISTS = __MAX_BYTES/__ALIGN}; //free-lists 個數

//本例中兩個 template 參數threads线程 ，inst完全沒有派上用場
template <bool threads, int inst>
class __default_alloc_template {
private:
  //實際上應使用 static const int x = N
  //取代 enum { x = N }, 但目前支援該性質的編譯器不多
  //向上取整 至8的倍数
  static size_t ROUND_UP(size_t bytes) {
    return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
  }

private:
  union obj { //内嵌指针 这里改为struct 也可以
    union obj* free_list_link;//形成空闲区域链表的连接 
  };

private:
  static obj* volatile free_list[__NFREELISTS];
  static size_t FREELIST_INDEX(size_t bytes) {
    return (((bytes) + __ALIGN-1)/__ALIGN - 1);
  }//计算第几号链表来管理你所需的内存

  // Returns an object of size n, and optionally adds to size n free list.
  static void *refill(size_t n);

  // Allocates a chunk for nobjs of size "size".  nobjs may be reduced
  // if it is inconvenient to allocate the requested number.
  static char *chunk_alloc(size_t size, int &nobjs);

  // Chunk allocation state.
  static char*  start_free;
  static char*  end_free;
  static size_t heap_size;

public:

  static void * allocate(size_t n)  //n must be > 0
  {
    obj* volatile *my_free_list;    //obj** my_free_list;
    obj* result;
  //申请的超过最大的内存块了，是不是内存池的大小 所以就寻找系统内存了 调用malloc函数
    if (n > (size_t)__MAX_BYTES) {
        return(malloc_alloc::allocate(n));
    }
  //寻找在那个内存链表 空闲区域 free_list链表的首地址
    my_free_list = free_list + FREELIST_INDEX(n);
    result = *my_free_list;//得到指向空闲区域的首地址 
    if (result == 0) {
        void* r = refill(ROUND_UP(n));//返回一个起始地址
        return r;
    }//若往下进行表示list内已有可用区块
    *my_free_list = result->free_list_link;//实际空闲区块的内存地址
    return (result);
  }
//回收到单向链表
  static void deallocate(void *p, size_t n)  //p may not be 0
  {
    obj* q = (obj*)p;
    obj* volatile *my_free_list;   //obj** my_free_list;
  //看看当初分配的内存是否在内存中，不在则是在外部申请的，外部释放
    if (n > (size_t) __MAX_BYTES) {
        malloc_alloc::deallocate(p, n);//调用第一级分配器
        return;
    }
    //这里仅仅移动指针，内存池中的内存安排是怎么样的？？？？，不需要标记吗那块是否被用，那块空闲吗？？ 不太懂
    //寻找空间链表的位置
    my_free_list = free_list + FREELIST_INDEX(n);
    q->free_list_link = *my_free_list;//空闲内存区域
    *my_free_list = q;
  }

  static void * reallocate(void *p, size_t old_sz, size_t new_sz);

};
//----------------------------------------------
// We allocate memory in large chunks in order to
// avoid fragmentingthe malloc heap too much.
// We assume that size is properly aligned.
// We hold the allocation lock. 
//当分配的内存发现申请的内存由他来负责，但他又是空的（比如他管理的时64*20时，但是之前没有申请过64的块，所以他为空），这时需要申请内存，当他的指针指向他应该管理的内存区块
//----------------------------------------------
template <bool threads, int inst>
char*
__default_alloc_template<threads, inst>::
chunk_alloc(size_t size, int& nobjs)
{
  char* result;
  size_t total_bytes = size * nobjs;
  size_t bytes_left = end_free - start_free;
  //
  if (bytes_left >= total_bytes) {
    //单个内存块内存完全够所需申请的内存 比如每次不够预申请的16*20 而size*nobjs
      result = start_free;
      start_free += total_bytes;
      return(result);
  } else if (bytes_left >= size) { 
    //bytes_left >= size&&bytes_left <= total_bytes
    // 这个和上面的有什么区别吗
      nobjs = bytes_left / size;
      total_bytes = size * nobjs;
      result = start_free;
      start_free += total_bytes;
      return(result);
  } else {
    //既然不够 ，那就计算需要申请多少内存
      size_t bytes_to_get =
                 2 * total_bytes + ROUND_UP(heap_size >> 4);
      // Try to make use of the left-over piece.
      if (bytes_left > 0) {
        //计算内存池内可申请的内存是多少 ，并把位置计算出去
          obj* volatile *my_free_list =
                 free_list + FREELIST_INDEX(bytes_left);

          ((obj*)start_free)->free_list_link = *my_free_list;
          *my_free_list = (obj*)start_free;//更新链表头 my_free_list更新有什么意义？？他已经失效了
      }
      start_free = (char*)malloc(bytes_to_get);
      if (0 == start_free) { //外部没有 申请到内存
          int i;
          obj* volatile *my_free_list, *p;

          //Try to make do with what we have. That can't
          //hurt. We do not try smaller requests, since that tends
          //to result in disaster on multi-process machines.
          //这个实在能用的区块一个一个对齐的字节数向前挪动的申请，直到完全耗完
          for (i = size; i <= __MAX_BYTES; i += __ALIGN) {
              my_free_list = free_list + FREELIST_INDEX(i);
              p = *my_free_list;
              if (0 != p) {
                  *my_free_list = p -> free_list_link;
                  start_free = (char*)p;
                  end_free = start_free + i;
                  return(chunk_alloc(size, nobjs));//者岂不是递归向下 可能返回之后在这里返回出函数
                  //Any leftover piece will eventually make it to the
                  //right free list.
              }
          }
          //for循环走到这里说明内存一直没有 即if (0 == p)一直存在 
          end_free = 0;       //In case of exception.
          start_free = (char*)malloc_alloc::allocate(bytes_to_get);//这个和上面的malloc有什么区别，既然没有那么为什么要两个先后分配内，
          //This should either throw an exception or
          //remedy the situation. Thus we assume it
          //succeeded.
      }
      heap_size += bytes_to_get;//malloc了申请的堆的内存区域大小继续增加，更新该区域，这个是不是申请到的算到内存池里面去？？
      end_free = start_free + bytes_to_get;
      return(chunk_alloc(size, nobjs));
  }
}
//----------------------------------------------
// Returns an object of size n, and optionally adds
// to size n free list.We assume that n is properly aligned.
// We hold the allocation lock.
//----------------------------------------------
template <bool threads, int inst>
void* __default_alloc_template<threads, inst>::
refill(size_t n)//n 时要求的对齐的字节数
{
    int nobjs = 20;
    char* chunk = chunk_alloc(n,nobjs);
    obj* volatile *my_free_list;   //obj** my_free_list;
    obj* result;
    obj* current_obj;
    obj* next_obj;
    int i;

    if (1 == nobjs) return(chunk);
    my_free_list = free_list + FREELIST_INDEX(n);
//在chunk内建立free list 做切割，建立内存区块之间的链表
    //Build free list in chunk
    result = (obj*)chunk;//此种类型块的内存区域的首地址
    *my_free_list = next_obj = (obj*)(chunk + n);//最后一个区块
    for (i=1;  ; ++i) {
      current_obj = next_obj;
      next_obj = (obj*)((char*)next_obj + n);//每隔 对齐的数量的内存区域形成空闲区域的链表
      if (nobjs-1 == i) {
          current_obj->free_list_link = 0;
          break;
      } else {
          current_obj->free_list_link = next_obj;
      }
    }
    return(result);
}
//----------------------------------------------
template <bool threads, int inst>
char *__default_alloc_template<threads,inst>::start_free = 0;

template <bool threads, int inst>
char *__default_alloc_template<threads,inst>::end_free = 0;

template <bool threads, int inst>
size_t __default_alloc_template<threads,inst>::heap_size = 0;

template <bool threads, int inst>
typename __default_alloc_template<threads, inst>::obj* volatile
__default_alloc_template<threads, inst>::free_list[__NFREELISTS]
     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
//----------------------------------------------
//令第2級配置器的名稱為 alloc
typedef __default_alloc_template<false,0> alloc;


//**********************************

int main()
{
	cout << "\n\n\ntest_global_allocator_with_16_freelist().......... \n";
	//这个还需要仔细调试
void*	p1 = alloc::allocate(120);
void* 	p2 = alloc::allocate(72);	
void* 	p3 = alloc::allocate(60);	//不是 8 倍數 

    cout << p1 << ' ' << p2 << ' ' << p3 << endl;

	alloc::deallocate(p1,120);
	alloc::deallocate(p2,72);
	alloc::deallocate(p3,60);	
	
//以下, 不能搭配容器來測試, 因為新版 G++ 對於 allocator 有更多要求 (詢問更多 typedef 而 alloc 都無法回答) 
//它其實就是 G4.9 __pool_alloc，所以讓 G4.9容器使用 __pool_alloc 也就等同於這裡所要的測試 

	// vector<int, simple_alloc<int,alloc>> v;
	// for(int i=0; i< 1000; ++i)
	// 	v.push_back(i);
	// for(int i=700; i< 720; ++i)
	// 	cout << v[i] << ' ';

			
	cout << endl;	
}
