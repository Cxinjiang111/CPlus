#ifndef __MAP_H__
#define __MAP_H__
#include <string>
using namespace std;
extern void use_map();
extern void use_multiset();
extern void use_defkey();
extern void insert_map();
extern void find_map();
extern void use_unorderd_map();
class BookData
{
public:
    BookData() = default;
    BookData(string nm, string au, string is) : name(nm), author(au), isbn(is) {}
    string name;
    string author;
    string isbn;
};
#endif