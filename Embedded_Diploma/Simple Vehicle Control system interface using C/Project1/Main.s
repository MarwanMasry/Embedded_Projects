	.file	"Main.c"
	.text
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	48(%rsp), %rbp
	.seh_setframe	%rbp, 48
	.seh_endprologue
	movq	%rcx, 32(%rbp)
	movq	%rdx, 40(%rbp)
	movq	%r8, 48(%rbp)
	movq	%r9, 56(%rbp)
	leaq	40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rbx
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rbx, %r8
	movq	32(%rbp), %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "Turning off the engine \12\0"
	.align 8
.LC1:
	.ascii "You entered undefined input ,Try again..\12\0"
	.align 8
.LC2:
	.ascii "Turning off the vehicle engine \12\0"
	.align 8
.LC3:
	.ascii "Quitting The System,Goodbye.....\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movl	$0, %r9d
	movl	$4, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	call	setvbuf
	movl	$2, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movl	$0, %r9d
	movl	$4, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	call	setvbuf
.L16:
	call	print_Vehicle_Control_system_List
	call	taking_Input_VCS_List
	movq	.refptr.VCS_selection(%rip), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	cmpl	$99, %eax
	je	.L4
	cmpl	$99, %eax
	jg	.L5
	cmpl	$97, %eax
	je	.L6
	cmpl	$98, %eax
	je	.L7
	jmp	.L5
.L6:
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	$1, (%rax)
.L14:
	call	Print_Sensors_set_menu
	call	taking_Input_SS_Menu
	movq	.refptr.SS_selection(%rip), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	cmpl	$100, %eax
	je	.L8
	cmpl	$100, %eax
	jg	.L9
	cmpl	$99, %eax
	je	.L10
	cmpl	$99, %eax
	jg	.L9
	cmpl	$97, %eax
	je	.L11
	cmpl	$98, %eax
	je	.L12
	jmp	.L9
.L11:
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	$0, (%rax)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	printf
	jmp	.L13
.L12:
	call	processing_traffic_light_color
	jmp	.L13
.L10:
	call	Processing_Room_Temperature_Data
	jmp	.L13
.L8:
	call	Processing_Engine_Temperature_Data
	jmp	.L13
.L9:
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	printf
	nop
.L13:
	movq	.refptr.SS_selection(%rip), %rax
	movzbl	(%rax), %eax
	cmpb	$97, %al
	jne	.L14
	jmp	.L15
.L7:
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	$0, (%rax)
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	printf
	jmp	.L15
.L4:
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	printf
	jmp	.L15
.L5:
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	printf
	nop
.L15:
	movq	.refptr.VCS_selection(%rip), %rax
	movzbl	(%rax), %eax
	cmpb	$99, %al
	jne	.L16
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 11.1.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	setvbuf;	.scl	2;	.type	32;	.endef
	.def	print_Vehicle_Control_system_List;	.scl	2;	.type	32;	.endef
	.def	taking_Input_VCS_List;	.scl	2;	.type	32;	.endef
	.def	Print_Sensors_set_menu;	.scl	2;	.type	32;	.endef
	.def	taking_Input_SS_Menu;	.scl	2;	.type	32;	.endef
	.def	processing_traffic_light_color;	.scl	2;	.type	32;	.endef
	.def	Processing_Room_Temperature_Data;	.scl	2;	.type	32;	.endef
	.def	Processing_Engine_Temperature_Data;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr.SS_selection, "dr"
	.globl	.refptr.SS_selection
	.linkonce	discard
.refptr.SS_selection:
	.quad	SS_selection
	.section	.rdata$.refptr.My_Vehicle, "dr"
	.globl	.refptr.My_Vehicle
	.linkonce	discard
.refptr.My_Vehicle:
	.quad	My_Vehicle
	.section	.rdata$.refptr.VCS_selection, "dr"
	.globl	.refptr.VCS_selection
	.linkonce	discard
.refptr.VCS_selection:
	.quad	VCS_selection
