#include<iostream>
#include<map>
using namespace std;
/*
软件系统采用纯粹对象方案的问题在于大量细粒度的对象会很快充斥在系统中
从而带来很高的运行时代价主要指内存需求方面的代价
采用共享的方法来降低系统中对象的个数，从而降低细粒度对象给系统带来的内存压力
*/
class Font{
private:
    string key;
public:
    Font(const string &key){

    }
};
//通过构建一个内存池，所有的都可以访问
class FontFactory{
private:
    map<string ,Font*> fontpool;
public:
    Font *GetFont(const string &key){
        map<string,Font*>::iterator it=fontpool.find(key);
        if(it!=fontpool.end()){
            return fontpool[key];
        }
        else {
            Font *font=new Font(key);
            fontpool[key]=font;
            return font;
        }       
    }
};




