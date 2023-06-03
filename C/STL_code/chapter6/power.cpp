template<class T,class Integer>
T power(T x,Integer n)
{
    return power(x,n,multiplies<T>());
}
template<class T,class Integer,class MonoidOperation>
T power(T x,Integer n,MonoidOperation op)
{
    if(n==0){
        return identity_element(op);
    }else{
        while((n&1)==0){
            n>>=1;
            x=op(x,x);
        }
        return x;
    }

}
