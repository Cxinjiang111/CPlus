char *strchr(char *s,int c)
{
    while (*s!='\0'&&*s==c)
    {
        ++s;
    }
    return *s!=c? s:(char*)0;
}
char *find1(char *first,char *end,int c)
{
    while (*first!=c&&*first!=*end)
    {
        ++first;
    }
    return first==end?end:first;
}
/*
通过从first至last（但不包含last）的所有指针，进行查找。
*/

template<typename Inputiterator,typename T>
Inputiterator *find2(Inputiterator *first,Inputiterator *end,T c)
{
    while (*first!=c&&first!=end)
    {
        ++first;
    }
    return first==end?end:first;
}