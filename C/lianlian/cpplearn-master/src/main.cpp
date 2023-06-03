#include <iostream>
using namespace std;
#include "../inc/cincout.h"
#include "../inc/string_.h"
#include "../inc/vector_.h"
#include "../inc/iterator_.h"
#include "../inc/arrary_.h"
#include "../inc/treetolist.h"
#include "../inc/func_.h"
#include <string>
#include "../inc/screen.h"
#include "../inc/money_c.h"
#include "../inc/class_.h"
#include "../inc/lru_.hpp"
#include "../inc/stl_.h"
#include "../inc/numeric_.h"
#include "../inc/stl_iter_.h"
#include "../inc/map_.h"
#include "../inc/pointer_.h"
#include "../inc/new_allocator_.h"
#include "../inc/text_query_.h"
#include "../inc/mystring_.h"
#include "../inc/singleton_.h"
#include "../inc/msgfolder.h"
#include "../inc/strvec.h"
#include "../inc/rightrf.h"
#include "../inc/derive_.h"
#include "../inc/single_2.h"
#include "../inc/lambda_.h"
#include "../inc/basederive.h"
#include "../inc/template_.h"
#include "../inc/derive_base.h"
#include "../inc/vitrual_table.h"
int main()
{
    // cin_func();
    // refe_func();
    // piont_func();
    // auto_func();
    // opstr_func();
    // str11_func();
    // vector_init();
    // vector_push();
    // iterator_func();
    // arrary_init();
    // pointer_op();
    // c_string();
    // vector_init2();
    // multi_index();
    // Test();
    // for (size_t i = 0; i != 10; ++i)
    // {
    //     cout << count_calls() << endl;
    // }
    // int m = 6;
    // nochange(m);
    // cout << m << endl;
    // change(&m);
    // cout << m << endl;
    // change(m);
    // cout << m << endl;
    // int j[] = {0, 1};
    // print_array(j, end(j) - begin(j));
    // string s("a value");
    // cout << s << endl; //输出a value
    //将s的第一个字母修改为A
    // get_val(s, 0) = 'A';
    // Screen::pos row = 3;
    // Screen::pos col = 4;
    // Screen screen(row, col, 'c');
    // screen.get();
    // screen.display(cout).move(2, 3).set('#');
    // const Screen cscreen(2, 1, ' ');
    // cscreen.display(cout);
    // Screen *psc = &screen;
    // psc->get();

    // First obj1;
    //编译报错，obj1和obj2不是一个类型
    // Second obj2 = obj1;
    // Sales_data sa;
    // auto sb = sa.combine(string("good luck"));
    // Data val2 = {0, "zack"};
    // auto lru = LRU(3);
    // lru.insert(4);
    // lru.insert(3);
    // lru.insert(2);
    // lru.print();
    // lru.insert(100);
    // lru.print();
    // lru.insert(10);
    // lru.print();
    //保留当前cin状态
    // auto old_state = cin.rdstate();
    // //使cin有效
    // cin.clear();
    // //将cin置为原有状态
    // cin.setstate(old_state);
    // //所有输出操作都立即刷新缓冲区
    // cout << unitbuf;
    // //恢复到正常模式
    // cout << nounitbuf;
    // //将cin和cout绑定在一起
    // cin.tie(&cout);
    // // old_tie指向当前关联到cin的流(如果有的话)
    // // cin不再与其他流关联
    // ostream *old_tie = cin.tie(nullptr);
    // //将cin和cerr关联
    // //读取cin会刷新cerr
    // cin.tie(&cerr);
    // //重建cin和cout的关联
    // cin.tie(old_tie);
    // use_stl();
    // use_numeric();
    // erase_dup();
    // use_predicate();
    // use_lambda();
    // cout << "count is " << use_bigger(3) << endl;
    // cout << "count is " << use_bigger(5) << endl;
    // cout << "count is " << use_bigger(10) << endl;
    // lambda_catch_r();
    // use_bigger2(cout, ' ', 2);
    // mutalble_lam();
    // rt_lambda();
    // calsize_count();
    // use_bigger3(cout, ' ', 2);
    // use_inserter();
    // use_istreamiter();
    // use_ostreamiter();
    // use_reverseiter();
    // use_map();
    // use_multiset();
    // insert_map();
    // find_map();
    // use_unorderd_map();
    // use_pointer();
    // use_sharedptr();
    // test_StrBlob();
    // shared_ptrnew();
    // bad_use_sharedptr();
    // reset_shared();
    // execption_shared();
    // delfunc_shared();
    // use_uniqueptr();
    // use_weakptr();
    // new_array();
    // unique_array();
    // use_shared_array();
    // use_allocator();
    // std::ifstream file("./config/text_query.txt");
    // runQueries(file);
    // use_mystr();
    // test_single();
    // test_thread_single();
    // test_share();
    // int a = 100, b = 200;
    // swap_int(a, b);
    // cout << "a is " << a << endl;
    // cout << "b is " << b << endl;
    // use_mystr();
    // test_msgfolder();
    //  test_strvec();
    // right_references();
    // derive_test();
    // int nums[] = {0, 1, 1, 3, 3, 4};
    // cout << sizeof(nums) / sizeof(int) << endl;
    // int find = binary_search(nums, 0, sizeof(nums) / sizeof(int) - 1, 3);
    // cout << "find is " << find << endl;
    // int find2 = binary_search(nums, 0, sizeof(nums) / sizeof(int) - 1, 4);
    // cout << "find is " << find2 << endl;
    // int find3 = binary_search(nums, 0, sizeof(nums) / sizeof(int) - 1, 0);
    // cout << "find is " << find3 << endl;
    // test_single2();
    // test_single2hungry();
    // test_single2hungry();
    // test_singleDangours();
    // test_singlelazy();
    // test_singleauto();
    // test_singleautosafe();
    // test_singlenet();
    // use_mystr_1();
    // use_lambda2();
    //  use_lambda3();
    // use_bind();
    // use_base_static();
    // use_derive_to_base();
    // use_derive_param();
    // use_probase();
    // use_hiddenbase();
    // use_template();
    // use_classtemp();
    // use_tempmove();
    //  use_ftemp();
    // use_printtemp();
    // test_strvectmp();
    // testcompare();
    // use_ftemp();
    // use_lambda_old();
    // use_ref();
    // derive_base_test1();
    // destructVirtualTable();
    // useVitualTable();
    // deriveTable();
    aligneTest();
    system("pause");
    return 0;
}