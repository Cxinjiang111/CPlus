#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;
class line_iterator{
    istream *in;
    string line;
    bool is_valid;
    void read()
    {
        if(*in)
            getline(*in,line);
        is_valid=(*in)?true:false;
    }
public:
    /*对于任何类而言 都有一下5个typedef 具有泛型编程的部分思想*/
    typedef input_iterator_tag  iterator_category;
    typedef string              value_type;
    typedef ptrdiff_t           difference_type;
    typedef const string *      pointer;
    typedef const string&       reference;


    line_iterator():in(&cin),is_valid(false){}
    line_iterator(istream&s):in(&s){read();}
    reference operator*()const{return line;}
    pointer operator->()const{return &line;}  
    line_iterator operator++(){
        read();
        return *this;
    }
    line_iterator operator++(int){
        line_iterator tmp=*this;
        read();
        return tmp;
    }
    bool operator==(const line_iterator &i)const{
        return (in==i.in&&is_valid==i.is_valid)||
                (is_valid==false&&i.is_valid==false);
    }
    bool operator!=(const line_iterator &i)const{
        return !(*this==i);

    }
};
struct strtab_cmp{
typedef vector<char>::iterator strtab_iterator;
bool operator()(const pair<strtab_iterator,strtab_iterator>&x,
                const pair<strtab_iterator,strtab_iterator>&y)const{
                    return lexicographical_compare(x.first,x.second,y.first,y.second);
                }
};
struct strtab_print
{
   ostream&out;
   strtab_print(ostream&os):out(os){}
   typedef vector<char>::iterator strtab_iterator;
   void operator()(const pair<strtab_iterator,strtab_iterator>&s)const
   {
        copy(s.first,s.second,ostream_iterator<char>(out));
   }
};
int main()
{
    vector<char> strtab;
    char c;
    while (cin.get(c)&&c!='0')
    {
        strtab.push_back(c);
    }
    cout<<"======================"<<endl;
    typedef vector<char>::iterator strtab_iterator;
    vector<pair<strtab_iterator,strtab_iterator> >lines;
    strtab_iterator start=strtab.begin();
    while (start!=strtab.end())
    {
        strtab_iterator next=find(start,strtab.end(),'\n');
        if(next!=strtab.end())
        {
            ++next;
        }
        lines.push_back(make_pair(start,next));
        start=next;
    }
    sort(lines.begin(),lines.end(),strtab_cmp());
    for_each(lines.begin(),lines.end(),strtab_print(cout));    
}

