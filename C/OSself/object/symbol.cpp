int func(int );
float func(float);
class C{
    int  func(int);
};
namespace N{
    int func(int);
    class C{
        int func(int);
    };
}
//以上6个函数不会冲突
func(float);
// func(int);
// C::func(int);
// N::func(int);
// N::C::func(int);
