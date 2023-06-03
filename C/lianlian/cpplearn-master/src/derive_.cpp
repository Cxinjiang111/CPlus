#include "../inc/derive_.h"
#include <cfloat>
void derive_test()
{
    // Base b1(1);
    //  b1.printData();
    // Base b2(2);
    // b2.printData();
    // cout << " ................." << endl;
    //  Derive d1(2);
    //  d1.printData();
    // cout << " ................." << endl;
    // Base *b1 = new Derive(2);
    // // b1->printData();
    // delete b1;
    // cout << " +++++++" << endl;
    // Base b1;
    // b1.printData();

    //空指针崩溃
    // Base *b1 = nullptr;
    // b1->printData2();
    // b1->printData();
    // char carry[100] = "Hello World";
    // cout << "sizeof(carry)  " << sizeof(carry) << endl;
    // char *pstr = "Hello World";
    // cout << "sizeof(pstr)   " << sizeof(pstr) << endl;
    // cout << "sizeof(*pstr)  " << sizeof(*pstr) << endl;
    // Base b1;
    // cout << "b1.SizeOf(carry)  " << b1.SizeOf(carry) << endl;
    // cout << "b1.SizeOf2(carry) " << b1.SizeOf2(carry) << endl;

    float f1 = 0.1;
    if (f1 <= FLT_EPSILON && f1 >= -FLT_EPSILON)
    {
        cout << "this is float 0" << endl;
    }
    else
    {
        cout << "this is not float 0" << endl;
    }

    double d1 = 0.0;
    if (d1 <= DBL_EPSILON && d1 >= -DBL_EPSILON)
    {
        cout << "this is double 0" << endl;
    }
    else
    {
        cout << "this is not double 0" << endl;
    }
}

/**********************
 *  有一个连续的int数组，数组中的数据升序排序
 * 数组中的数据不唯一，有重复数据
 * 要求在数组中查找指定值为target的数据
 * 返回target最小的下标，如果找到返回其最小的下标
 * 如果没有找到，返回-1
 * 举例 数组nums = [0,1,1,3,3,4]
 * 查找target为1的数据最小的下标
 * 返回1
 * 如果查找target为100，则返回-1
 * 要求时间复杂度为Olog(n),空间复杂度为O(1)
 * 用二分查找的方式解决上述问题
 **********************/

int binary_search(int nums[], int begin, int end, int target)
{
    //只要有一个越界就是没找到
    if (begin < 0 || begin > end || end < 0)
    {
        return -1;
    }

    //找到中间值比较
    int mid = (begin + end) / 2;
    // cout << "mid is " << mid << endl;
    //要找到的target在右半部分
    if (target > nums[mid])
    {
        return binary_search(nums, mid + 1, end, target);
    }

    //要找到的target在左半部分
    if (target < nums[mid])
    {
        return binary_search(nums, begin, mid - 1, target);
    }
    // cout << "nums[mid] is " << nums[mid] << endl;
    //如果找到target相等的元素，需要向左移动找到最小索引
    for (int i = mid; i > begin; i--)
    {
        if (target == nums[mid])
        {
            continue;
        }
        //   cout << "i is " << endl;
        return i + 1;
    }
}
