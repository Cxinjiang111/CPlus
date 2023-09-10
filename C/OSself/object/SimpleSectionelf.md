##  readelf -h SimpleSection.o > SimpleSectionelf.md
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              DYN (Position-Independent Executable file)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x1060
  程序头起点：          64 (bytes into file)
  Start of section headers:          14184 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 30

# ELF 的文件头中定义了ELF 魔数，文件 机器字节长度，数据存储方式，版本，运行平台，ABI版本，ELF重定位类型，硬件平台，入口地址，程序头入口和长度，段的数量

Magic：   7f 45 4c 46   02 01 01 00 00 00 00 00 00 00 00 00 

7f    45 4c 46 最开始的4个字节是所有ELF文件都必须相同的标识码
DEL      ASCII 
第一个字节对应ASCII里面的DEL控制符 
后面3个字节刚好ELF这3个字母的ASCII码
这种魔数用来确认文件的类型，操作系统在加载可执行文件的时候会确认魔术是否正确
02 01 01  
第5个字节表示系统位数      01 32位   02 64位
第6个字节表示字节序       01   小端
第7个字节表示系统主版本号  01  ELF主版本号
文件类型，e_type成员表示ELF 文件类型，每个文件类型对应一个常量，系统通过这个来判断ELF 的真正文件类型，而不是通过文件的扩展名

ET_REL    1  可重定位文件，一般为.o文件
ET_EXEC   2  可执行文件
ET_DYN    3  共享目标文件，一般为.so文件




