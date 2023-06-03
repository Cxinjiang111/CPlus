#ifndef _FARQ
#define _FARQ
#define _PDFT ptrdiff_t
#define _SIZT size_t
#endif 
template<class _Ty>
inline _Ty _FARQ*_Allocate(_PDFT _N,_Ty _FARQ *p)
{
    if(_N<0)_N=0;
    return ((_Ty _FARQ* )operator new ((_SIZT)_N*sizeof(_Ty)));
}
template<class _Ty>
class allocator{
public:
    typedef _SIZT size_type;
    typedef _PDFT different_type;
    typedef _Ty _FARQ*pointer;
    typedef _Ty value_type;
    pointer allocate(size_type _N,const void * p){
        return (_Allocate((different_type)_N,(pointer)0));
    }
    void deallocate(void _FARQ*_P,size_type)
    {
        operator delete(_P);
    }
};