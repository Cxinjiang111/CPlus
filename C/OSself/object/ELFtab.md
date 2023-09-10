typedef struct
{
    Elf32_Word st_name;
    Elf32_Addr st_value;
    Elf32_Word st_size; 
    unsigned char st_info; 符号类型和绑定信息
    unsigned char st_other; 
    Elf32_Half  st_shndx; 符号所在的段
}Elf32_Sym;


