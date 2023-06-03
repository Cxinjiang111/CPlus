#include<iostream>
using namespace std;
//业务操作
class Stream{
public:
    virtual void Read()=0;
    virtual void Seek()=0;
    virtual ~Stream(){}
};
//主体类
class FileStream: public Stream{
public:
    virtual void Read(){
        cout<<"FileStream: public Stream Read"<<endl;      
    }
    virtual void Seek(){
        cout<<"FileStream: public Stream Seek"<<endl; 
    }
};
class NetworkStream :public Stream{
public:
    virtual void Read(){
        cout<<"NetworkStream :public Stream Read"<<endl; 
    }
    virtual void Seek(){
        cout<<"NetworkStream :public Stream Seek"<<endl; 
    }
};
class MemoryStream :public Stream{
public:
    virtual void Read(){
       cout<<"MemoryStream :public Stream Read"<<endl; 
    }
    virtual void Seek(){
          cout<<"MemoryStream :public Stream Seek"<<endl; 
    }
};
//扩展操作
class CryptoStream { //这种结果和加继承是一样的
//class CryptoStream: public Stream { //
    
    Stream* stream;//...
public:
    CryptoStream(Stream* stm):stream(stm){   
    }
    virtual void Read(){     
        cout<<"CryptoStream: public Stream  Read"<<endl;
        stream->Read();//读文件流
    }
    virtual void Seek(){
         cout<<"CryptoStream: public Stream  Seek"<<endl;
        stream->Seek();//定位文件流
        //额外的加密操作...
    }
};
class BufferedStream {
//class BufferedStream : public Stream{
 Stream* stream;//...
public:
    BufferedStream(Stream* stm):stream(stm){  
    }
    virtual void Read(){     
         cout<<"BufferedStream : public Stream  read"<<endl;
        stream->Read();//读文件流
    }
    virtual void Seek(){
        cout<<"BufferedStream : public Stream  Seek"<<endl;
        stream->Seek();//定位文件流
        //额外的加密操作...
    }
};
void Process(){
    //运行时装配
    FileStream* s1=new FileStream();
    CryptoStream* s2=new CryptoStream(s1);
    BufferedStream* s3=new BufferedStream(s1);
   // BufferedStream* s4=new BufferedStream(s2);
    s2->Read();
    s2->Seek();
    s3->Read();
    s3->Seek();
   
}
int main(){
    Process();
    return 0;
}