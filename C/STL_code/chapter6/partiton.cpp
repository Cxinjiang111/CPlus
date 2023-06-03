template<class BidirectionanlIterator,class Predicate>
BidirectionanlIterator partition(BidirectionanlIterator first,BidirectionanlIterator last,Predicate pred)
{
    while(true)
    {
        while(true)
        {
            if(first=last)
                return first;
            if(pred(*first))
            {
                ++first;

            }else{
                break;
            }
            --last;
        }
        while(true)
        {
            if(pred(*last))
            {
                --last;
                
            }else{
                break;
            }
            ++first;
        }
    }
}