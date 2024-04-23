	.file	"file-01.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "w\0"
.LC1:
	.ascii "\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
main:
	.seh_proc	main
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	call	__main
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	fopen
	movq	%rax, -8(%rbp)
	jmp	.L2
.L4	:
	cmpb	$13, -9(%rbp)
	jne	.L3
	movq	-8(%rbp), %rax
	movq	%rax, %rdx
	movl	$10, %ecx
	call	putc
	jmp	.L2
.L3:
	movsbl	-9(%rbp), %eax
	movq	-8(%rbp), %rdx
	movl	%eax, %ecx
	call	putc
.L2:
	call	getche
	movb	%al, -9(%rbp)
	cmpb	$27, -9(%rbp)
	jne	.L4
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	call	fclose
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r5) 13.2.0"
	.def	fopen;	.scl	2;	.type	32;	.endef
	.def	putc;	.scl	2;	.type	32;	.endef
	.def	getche;	.scl	2;	.type	32;	.endef
	.def	fclose;	.scl	2;	.type	32;	.endef
