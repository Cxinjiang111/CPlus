#ifndef __FUNC_H__
#define __FUNC_H__
#include <string>
using namespace std;
extern size_t count_calls();
extern void nochange(int a);
extern void change(int *p);
extern void change(int &ra);
extern bool isShorter(const string &s1, const string &s2);
extern void print_array(const int ia[], size_t size);
extern char &get_val(string &str, string::size_type ix);
#endif