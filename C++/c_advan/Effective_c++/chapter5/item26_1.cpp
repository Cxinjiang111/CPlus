#include<string>

void encrypt(std::string&s);//在其中的适当的点对s加密
//这个函数延后encrypted的定义，知道需要它为止
std::string encryptPassword(const std::string&password){
    using namespace std;
    if (password.length()<MinimumPawordLength)
    {
        throw logic_error("password is too short");
    }
    string encrypted;//在上面抛出异常 这个对象就不用申请了，那么构造函数或者其他动作也无需必要了
            //如有必要加一段密码到encrypted
    encrypted=password;
    encrypt(encrypted);
    return encrypted;
}
//更受欢迎的做法是以password作为encrypted的初值，跳过毫无意义的default构造函数、

std::string encryptPassword(const std::string&password){
    using namespace std;
    if (password.length()<MinimumPawordLength)
    {
        throw logic_error("password is too short");
    }
    string encrypted(encrypted);//定义并完成初始化，
            //如有必要加一段密码到encrypted
    encrypt(encrypted);
    return encrypted;
}
/*
这让我们联想起本条款所谓 “尽可能延后” 的真正意义。 你不只应该延后变量 、
的定义，直到非得使用该变量的前一刻为止，甚至应该尝试延后这份定义直到能够 给它初值实参为止。
 如果这样， 不仅能够避免构造（和析构）非必要对象，还可以避免无意义的default构造行为。
 更深一层说， 以“具明显意义之初值“ 将变量初始 化， 还可以附带说明变量的目的。
*/

