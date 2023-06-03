#include<vector>
using namespace std;

//    smallObjAllocator

class FixedAllocator;
class Chunk;
class POOL{
    vector<FixedAllocator> pool;
    FixedAllocator* pLastAlloc;
    FixedAllocator* pLastDealloc;
    size_t chunkSize;
    size_t maxObjectSize;
};
//FixedAllocator
class FixedAllocator:public Chunk{
    public:
    void *AllocateF();
    vector<Chunk> chunk;
    Chunk* allocChunk;
    Chunk* deallocChunk;
};
//Chunk
class Chunk{
    public:
    void *Allocate(std::size_t blockSize);
    void *Deallocate(void *p,std::size_t blockSize);
    unsigned  char* pData;
    unsigned char firstAvailableBlock;//位置
    unsigned char blocksAvailable;//块的数量
};
void *FixedAllocator::Chunk::Allocate(std::size_t blockSize)
{
    if(!blocksAvailable) return 0;//此块内存没有可利用的内存‘   
    unsigned char* pResult=
    pData+(firstAvailableBlock*blockSize);//(firstAvailableBlock_*blockSize)内存块的地址偏移
    //pData_块的首地址
    firstAvailableBlock=*pResult;
    --blocksAvailable;//可利用的分割的区块少了一小块
    return pResult;
}
void *FixedAllocator::Chunk::Deallocate(void *p,std::size_t blockSize)
{
    //这里传入的p就是需要释放释放块内存的地址
   unsigned char*toRelease=static_cast<unsigned char*>(p);
   *toRelease=firstAvailableBlock; 
   firstAvailableBlock=static_cast<unsigned char>((toRelease-pData)/blockSize);//这个得到的时块的索引
   ++blocksAvailable;//释放了一块，可利用的块数增加一块
}
void *FixedAllocator::AllocateF(){
    if(allocChunk==0||allocChunk->blocksAvailable==0)
    {
        Chunk::iterator i=chunk.begin();
        for(;;++i)
        {
            if(i==chunk.end())//卷了一圈，可利用的内存没有找到
            {
                chunk.push_back(Chunk());
                Chunk&newChunk=chunk.back();
                newChunk.Init(blockSize,numblock);
                allocChunk=&newChunk;
                deallocChunk=&chunk.font();
                break;
            }
            if(i->blocksAvailable>0)//发现了利用的区块
            {
                allocChunk=&*i;//去该区块所对应的地址
                break;
            }
        }
    }
    return allocChunk->Allocate(blockSize);
}

