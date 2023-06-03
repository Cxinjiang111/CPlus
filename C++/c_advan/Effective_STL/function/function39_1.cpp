#include <iostream>
#include <vector> 
#include <algorithm> 
#include <iterator>
using namespace std;
/*这个还是没有看懂 还需研究研究*/
class BadValue : public unary_function<int, bool>
{
public:
	BadValue(){}

	// bool operator()(const int&)
	// {
	// 	return ++timesCalled == 3;
	// }
    bool operator()(const int&) const
    {
        static int timesCalled = 0; 
        return ++timesCalled == 3;
    }

private:
	int timesCalled {0};	
}; 


int main()
{
	typedef vector<int> IntVec;
	typedef vector<int>::iterator IntIter;
	
	IntVec v;
	
	for(int index = 0; index < 10; ++index)
	{
		v.push_back(index + 1);
	}
	
	v.erase(remove_if(v.begin(), v.end(), BadValue()));
	
	for(IntIter it = v.begin(); it != v.end(); ++it)
	{
		cout << *it << " "; // 1 2 4 5 7 8 9 10 10
	}
	
	return 0;
}
