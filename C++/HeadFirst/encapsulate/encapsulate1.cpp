#include<iostream>
#include<vector>
using namespace std;
//
class Compareble
{
private:
    int m_weight;
public:
    Compareble(int weight):m_weight(weight){}
    ~Compareble(){}
    bool compareTo(const Compareble *other)
    {
        if(m_weight>other->m_weight)
            return true;
        else
            return false;
    }
    int getWeight(){return m_weight;}
    void swap(Compareble *later)
    {
        int i=this->m_weight;
        this->m_weight=later->m_weight;
        later->m_weight=i;
    }
};
template<typename T>
static void merge_sort(vector<T>&v, vector<T>&v2,int low,int high)
{
    for(int i=low; i<high; i++)
    {
        for(int j=i;j<high;j++)
        {
            if(v[j]->compareTo(v[i]))
                v[j]->swap(v[i]);
        }
    }
}

class Duck:public Compareble
{
public:
    Duck(int weight):Compareble(weight){}
    ~Duck(){}
};
int main()
{
    vector<Duck*> v;
    Duck *d1=new Duck(5);
    Duck *d2=new Duck(6);
    Duck *d3=new Duck(4);
    Duck *d4=new Duck(3);
    Duck *d5=new Duck(1);
    v.push_back(d1);
    v.push_back(d2);
    v.push_back(d3);
    v.push_back(d4);
    v.push_back(d5);
    merge_sort(v,v,0,v.size());
    for(int i=0;i<v.size();i++)
    {
        std:cout<<v[i]->getWeight()<<std::endl;
    }
    return 0;
}
