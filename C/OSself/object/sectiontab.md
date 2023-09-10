typedef struct
{
    ELF32_Word   sh_name
    ELF32_Word   sh_type
    ELF32_Word   sh_flags   标志位
    ELF32_Addr   sh_addr  段虚拟地址
    ELF32_Off    sh_offset
    ELF32_Word   sh_size
    ELF32_Word   sh_link
    ELF32_Word   sh_info
    ELF32_Word   sh_addralign
    ELF32_Shdr   sh_entsize
}

可重定位表

字符串表
由于ELF文件中很多字符串的长度不固定，用固定的结构来表示比较困难，将其存放到一个表中，在ELF文件中也以段的形式保存，常见的段名为".strtab"  ".shstrtab"
.shstrtab 段表字符串表 也是ELF段文件中一个普通的段 



