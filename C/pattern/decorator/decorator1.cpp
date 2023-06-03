class Stream{
public:
    virtual char Read(int number)=0;
    virtual void Seek(int position)=0;
    virtual void Write(char data)=0;
    virtual ~Stream(){}
};
//不同流的继承
class FileStream:public Stream{
public:
    virtual char read(int number){
    }
    virtual void Seek(int position){
    }
    virtual void Write(char data){
    }
};
class NetStream:public Stream{
public:
    virtual char read(int number){
    }
    virtual void Seek(int position){
    }
    virtual void Write(char data){
    }
};
class MemoryStream:public Stream{
public:
    virtual char read(int number){
    }
    virtual void Seek(int position){
    }
    virtual void Write(char data){
    }
};
//复制扩展操作
class CryptoFileStream:public FileStream{
public:
    virtual char Read(int number){
    FileStream::Read(number);
    }
    virtual void Seek(int position){
        FileStream::Seek(position);
    }
    virtual void Write(char data){
        FileStream::Write(data);
    }
};
class CryptoNetStream:public NetStream{
public:
    virtual char Read(int number){
    NetStream::Read(number);
    }
    virtual void Seek(int position){
        NetStream::Seek(position);
    }
    virtual void Write(char data){
        NetStream::Write(data);
    }
};
class CryptoMemoryStream : public MemoryStream{
public:
    virtual char Read(int number){
        
        //额外的加密操作...
        MemoryStream::Read(number);//读内存流
    }
    virtual void Seek(int position){
        //额外的加密操作...
        MemoryStream::Seek(position);//定位内存流
        //额外的加密操作...
    }
    virtual void Write(char data){
        //额外的加密操作...
        MemoryStream::Write(data);//写内存流
        //额外的加密操作...
    }
};
class BufferedFileStream : public FileStream{
    //...
};

class BufferedNetworkStream : public NetStream{
    //...
};

class BufferedMemoryStream : public MemoryStream{
    //...
};