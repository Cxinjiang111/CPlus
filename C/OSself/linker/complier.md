# 编译
处理词法 语法 语义 以及优化后产生的汇编代码


# t: gcc -s hello.c -o hello.s 

array[index]=(index+4)*(2+6)
# 词法分析
产生的记号一般可分为如下几类，关键词，标识符，自变量，和特殊符号。
词法分析器 lex 
# 语法分析
产生语法树，整个分析过程采用上下文无关语法与自动机， 生成抽象语法书，也就是以表达式为节点的树
语法分析器：yacc
# 语义分析
使得整个语句有了意义 整个语法树的表达式都被标识了类型，每个字符串有了实体意义
# 中间语言生成
 源码级别优化往往将整个语法树转换成中间代码， 他一般根目标机器和运行环境无关 比如它不包含数据的尺寸，变量地址和寄存器的名字，
 比较常见的有：三地址码
 x = y op z
 t1= 2+6  ==> 8
 t2= index+ 4  ==>((index)+4)*8
t3= t1*t2
 array[index]=t3;
 中间代码使得编译器分为前端和后端。
 前端负责产生机器无关代码的中间代码，后端负责将中间代码转换成目标机器代码

 # 目标代码生成与优化
 属于后端，后端主要包括代码生成器和目标代码优化器
 movl index,%eax
 addl $4 ,%ecx
 mull $8,%ecx
movl index,%eax
movel %ecx.array(,index,4)
# add.c 
#include<stdio.h>
#define indexsum 2
int main()
{

    int array[indexsum];
    int index=1;
    array[index]=(index+4)*(2+6);

    return 0;
}
# gcc -S add.c -o add.s
# ###############################
add.s 反汇编文件
	.file	"add.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1, -20(%rbp)
	movl	-20(%rbp), %eax   => index
	addl	$4, %eax          => index+4
	leal	0(,%rax,8), %edx   => (index+4)*8
	movl	-20(%rbp), %eax    =>array[index]=(index+4)*8
	cltq
	movl	%edx, -16(%rbp,%rax,4)
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:



