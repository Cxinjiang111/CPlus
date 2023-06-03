/*将成员变量申明为private
切记将成员变量声明为private，这可赋予客服访问数据 的一致性，
可细微划分访问控制，允诺约束条件获得保证，并提供class作者以充分的实现弹性

*/
class AccessLevels
{
public:
    int getReadOnly()const{return readOnly;}
    void setReadWrite(int value){readWrite=value;}
    int getReadWrite()const {return readWrite;}
    void setWriteOnly(int value){writeOnly=value;}
private:
    int noAccess;
    int readOnly;
    int readWrite;
    int writeOnly;
};


