class File{
public:
    virtual void file()=0;
};
class InputFile:public File{
public:
    virtual void file();
};
class OutputFile:public File{
public:
    virtual void file();
};
class IOFile:public InputFile,public OutputFile
{
    void file();
};
//尽量不要使用多继承，