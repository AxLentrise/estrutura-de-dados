	.file	"file-exercise.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "r\0"
.LC1:
	.ascii "file.txt\0"
.LC2:
	.ascii "Error opening file.\0"
.LC3:
	.ascii "\12\12N of char: %d\0"
.LC4:
	.ascii "\12N of word: %d\0"
.LC5:
	.ascii "\12N of line: %d\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	call	__main
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	fopen
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L3
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	$0, %ecx
	call	exit
.L9:
	movsbl	-25(%rbp), %eax
	movl	%eax, %ecx
	call	putchar
	cmpb	$10, -25(%rbp)
	je	.L4
	addl	$1, -8(%rbp)
.L4:
	cmpb	$32, -25(%rbp)
	jne	.L5
	cmpb	$10, -1(%rbp)
	je	.L5
	cmpb	$32, -1(%rbp)
	jne	.L6
.L5:
	cmpb	$10, -25(%rbp)
	jne	.L7
	cmpb	$10, -1(%rbp)
	je	.L7
	cmpb	$32, -1(%rbp)
	je	.L7
.L6:
	addl	$1, -16(%rbp)
.L7:
	cmpb	$10, -25(%rbp)
	jne	.L8
	addl	$1, -12(%rbp)
.L8:
	movzbl	-25(%rbp), %eax
	movb	%al, -1(%rbp)
.L3:
	movq	-24(%rbp), %rax
	movq	%rax, %rcx
	call	getc
	movb	%al, -25(%rbp)
	cmpb	$-1, -25(%rbp)
	jne	.L9
	cmpb	$10, -1(%rbp)
	je	.L10
	addl	$1, -12(%rbp)
.L10:
	cmpb	$-1, -1(%rbp)
	je	.L11
	addl	$1, -16(%rbp)
.L11:
	movl	-8(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	-16(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	-12(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC5(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	-24(%rbp), %rax
	movq	%rax, %rcx
	call	fclose
	movl	$0, %eax
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r5) 13.2.0"
	.def	fopen;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	exit;	.scl	2;	.type	32;	.endef
	.def	putchar;	.scl	2;	.type	32;	.endef
	.def	getc;	.scl	2;	.type	32;	.endef
	.def	fclose;	.scl	2;	.type	32;	.endef
