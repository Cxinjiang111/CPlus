//#include"template_1.h"
#include"template_2.h"
int main(){
    // Library *lib=new Library();
    // application *app=new application();
    // lib->step1();
    // if(app->step2()){
    //     lib->step3();
    // }
    // for(int i=0;i<4;i++){
    //     app->step4();
    // }
    // lib->step5();
/////使用模板类编程
   Library *lib=new application();
   lib->run();
    return 0;
}