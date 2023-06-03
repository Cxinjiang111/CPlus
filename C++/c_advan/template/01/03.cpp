#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;
int main()
{
    vector<string> v;
    string tmp;
    while (getline(cin,tmp))
    {
        v.push_back(tmp);
    }
    sort(v.begin(),v.end());
    copy(v.begin(),v.begin(),ostream_iterator<string>(cout,"\n"));
}