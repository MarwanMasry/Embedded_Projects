	.file	"Project_Functions.c"
	.text
	.def	scanf;	.scl	3;	.type	32;	.endef
	.seh_proc	scanf
scanf:
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
	movl	$0, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rbx, %r8
	movq	32(%rbp), %rdx
	movq	%rax, %rcx
	call	__mingw_vfscanf
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
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
	.section .rdata,"dr"
	.align 8
.LC0:
	.ascii "\12/////////////////////////////////////////////////////////////////\12\12\0"
	.align 8
.LC1:
	.ascii "<Vehicle Control System List>\12\0"
	.align 8
.LC2:
	.ascii "a. Turn on the vehicle engine \12\0"
	.align 8
.LC3:
	.ascii "b. Turn off the vehicle engine \12\0"
.LC4:
	.ascii "c. Quit the system \12\12\0"
	.text
	.globl	print_Vehicle_Control_system_List
	.def	print_Vehicle_Control_system_List;	.scl	2;	.type	32;	.endef
	.seh_proc	print_Vehicle_Control_system_List
print_Vehicle_Control_system_List:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC5:
	.ascii "Please enter your selection [a or b or c] ?  \0"
.LC6:
	.ascii " %c\0"
	.text
	.globl	taking_Input_VCS_List
	.def	taking_Input_VCS_List;	.scl	2;	.type	32;	.endef
	.seh_proc	taking_Input_VCS_List
taking_Input_VCS_List:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC5(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.VCS_selection(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC6(%rip), %rax
	movq	%rax, %rcx
	call	scanf
	movq	.refptr.VCS_selection(%rip), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %ecx
	movq	__imp_tolower(%rip), %rax
	call	*%rax
	movl	%eax, %edx
	movq	.refptr.VCS_selection(%rip), %rax
	movb	%dl, (%rax)
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC7:
	.ascii "<Sensors Set Menu>\12\0"
.LC8:
	.ascii "a. Turn off the engine \12\0"
	.align 8
.LC9:
	.ascii "b. Set the traffic light color \12\0"
	.align 8
.LC10:
	.ascii "c. Set the room temperature (Temperature Sensor) \12\0"
	.align 8
.LC11:
	.ascii "d. Set the engine temperature (Engine Temperature Sensor) \12\12\0"
	.text
	.globl	Print_Sensors_set_menu
	.def	Print_Sensors_set_menu;	.scl	2;	.type	32;	.endef
	.seh_proc	Print_Sensors_set_menu
Print_Sensors_set_menu:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC7(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC8(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC9(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC10(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC11(%rip), %rax
	movq	%rax, %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC12:
	.ascii "Please enter your selection [a or b or c or d] ?  \0"
	.text
	.globl	taking_Input_SS_Menu
	.def	taking_Input_SS_Menu;	.scl	2;	.type	32;	.endef
	.seh_proc	taking_Input_SS_Menu
taking_Input_SS_Menu:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC12(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.SS_selection(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC6(%rip), %rax
	movq	%rax, %rcx
	call	scanf
	movq	.refptr.SS_selection(%rip), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %ecx
	movq	__imp_tolower(%rip), %rax
	call	*%rax
	movl	%eax, %edx
	movq	.refptr.SS_selection(%rip), %rax
	movb	%dl, (%rax)
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	check_Vehicle_Speed
	.def	check_Vehicle_Speed;	.scl	2;	.type	32;	.endef
	.seh_proc	check_Vehicle_Speed
check_Vehicle_Speed:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	16(%rax), %xmm0
	ucomisd	.LC13(%rip), %xmm0
	jp	.L15
	ucomisd	.LC13(%rip), %xmm0
	je	.L14
	jmp	.L15
.L14:
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	4(%rax), %eax
	testl	%eax, %eax
	jne	.L12
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	$1, 4(%rax)
.L12:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	24(%rax), %xmm1
	movsd	.LC14(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movsd	.LC15(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	%xmm0, 24(%rax)
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	jne	.L13
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	$1, 8(%rax)
.L13:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	32(%rax), %xmm1
	movsd	.LC14(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movsd	.LC15(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	%xmm0, 32(%rax)
.L15:
	nop
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC16:
	.ascii "<Vehicle State>\12\0"
.LC17:
	.ascii "ON\0"
.LC18:
	.ascii "OFF\0"
.LC19:
	.ascii "Engine state : %s \12\0"
.LC20:
	.ascii "AC : %s \12\0"
.LC21:
	.ascii "Vehicle Speed : %lf KM/H \12\0"
.LC22:
	.ascii "Room Temperature : %lf C\12\0"
	.align 8
.LC23:
	.ascii "Engine Temperature Controller State. : %s \12\0"
.LC24:
	.ascii "Engine Temperature : %lf C\12\12\0"
	.text
	.globl	Display_Vehicle_State
	.def	Display_Vehicle_State;	.scl	2;	.type	32;	.endef
	.seh_proc	Display_Vehicle_State
Display_Vehicle_State:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC16(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L17
	leaq	.LC17(%rip), %rax
	jmp	.L18
.L17:
	leaq	.LC18(%rip), %rax
.L18:
	movq	%rax, %rdx
	leaq	.LC19(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	4(%rax), %eax
	testl	%eax, %eax
	je	.L19
	leaq	.LC17(%rip), %rax
	jmp	.L20
.L19:
	leaq	.LC18(%rip), %rax
.L20:
	movq	%rax, %rdx
	leaq	.LC20(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	16(%rax), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %rdx
	movq	%rdx, %xmm0
	movapd	%xmm0, %xmm1
	movq	%rax, %rdx
	leaq	.LC21(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	24(%rax), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %rdx
	movq	%rdx, %xmm0
	movapd	%xmm0, %xmm1
	movq	%rax, %rdx
	leaq	.LC22(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	je	.L21
	leaq	.LC17(%rip), %rax
	jmp	.L22
.L21:
	leaq	.LC18(%rip), %rax
.L22:
	movq	%rax, %rdx
	leaq	.LC23(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	32(%rax), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %rdx
	movq	%rdx, %xmm0
	movapd	%xmm0, %xmm1
	movq	%rax, %rdx
	leaq	.LC24(%rip), %rax
	movq	%rax, %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC25:
	.ascii "\12Please Enter the Traffic Light Color [G or Y or R] ? \0"
	.align 8
.LC28:
	.ascii "You entered undefined input ,Try again..\12\0"
	.text
	.globl	processing_traffic_light_color
	.def	processing_traffic_light_color;	.scl	2;	.type	32;	.endef
	.seh_proc	processing_traffic_light_color
processing_traffic_light_color:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
.L30:
	leaq	.LC25(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	-1(%rbp), %rax
	movq	%rax, %rdx
	leaq	.LC6(%rip), %rax
	movq	%rax, %rcx
	call	scanf
	movzbl	-1(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %ecx
	movq	__imp_tolower(%rip), %rax
	call	*%rax
	movb	%al, -1(%rbp)
	movzbl	-1(%rbp), %eax
	movsbl	%al, %eax
	cmpl	$121, %eax
	je	.L24
	cmpl	$121, %eax
	jg	.L25
	cmpl	$103, %eax
	je	.L26
	cmpl	$114, %eax
	je	.L27
	jmp	.L25
.L26:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	.LC26(%rip), %xmm0
	movsd	%xmm0, 16(%rax)
	jmp	.L28
.L24:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	.LC13(%rip), %xmm0
	movsd	%xmm0, 16(%rax)
	jmp	.L28
.L27:
	movq	.refptr.My_Vehicle(%rip), %rax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, 16(%rax)
	jmp	.L28
.L25:
	leaq	.LC28(%rip), %rax
	movq	%rax, %rcx
	call	printf
	nop
.L28:
	movzbl	-1(%rbp), %eax
	cmpb	$103, %al
	je	.L29
	movzbl	-1(%rbp), %eax
	cmpb	$114, %al
	je	.L29
	movzbl	-1(%rbp), %eax
	cmpb	$121, %al
	jne	.L30
.L29:
	call	check_Vehicle_Speed
	call	Display_Vehicle_State
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC29:
	.ascii "\12Please Enter the Room Temperature : \0"
.LC30:
	.ascii " %lf\0"
	.text
	.globl	Processing_Room_Temperature_Data
	.def	Processing_Room_Temperature_Data;	.scl	2;	.type	32;	.endef
	.seh_proc	Processing_Room_Temperature_Data
Processing_Room_Temperature_Data:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
.L41:
	leaq	.LC29(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.My_Vehicle(%rip), %rax
	addq	$24, %rax
	movq	%rax, %rdx
	leaq	.LC30(%rip), %rax
	movq	%rax, %rcx
	call	scanf
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	24(%rax), %xmm1
	movsd	.LC31(%rip), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L32
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	24(%rax), %xmm0
	pxor	%xmm1, %xmm1
	comisd	%xmm1, %xmm0
	ja	.L34
.L32:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	24(%rax), %xmm0
	comisd	.LC13(%rip), %xmm0
	jbe	.L45
.L34:
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	$1, 4(%rax)
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	.LC32(%rip), %xmm0
	movsd	%xmm0, 24(%rax)
	jmp	.L37
.L45:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	24(%rax), %xmm0
	pxor	%xmm1, %xmm1
	comisd	%xmm1, %xmm0
	jbe	.L37
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	$0, 4(%rax)
.L37:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	24(%rax), %xmm1
	pxor	%xmm0, %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L39
	leaq	.LC28(%rip), %rax
	movq	%rax, %rcx
	call	printf
.L39:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	24(%rax), %xmm1
	pxor	%xmm0, %xmm0
	comisd	%xmm1, %xmm0
	ja	.L41
	call	check_Vehicle_Speed
	call	Display_Vehicle_State
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC33:
	.ascii "\12Please Enter the Engine Temperature : \0"
	.text
	.globl	Processing_Engine_Temperature_Data
	.def	Processing_Engine_Temperature_Data;	.scl	2;	.type	32;	.endef
	.seh_proc	Processing_Engine_Temperature_Data
Processing_Engine_Temperature_Data:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
.L56:
	leaq	.LC33(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	.refptr.My_Vehicle(%rip), %rax
	addq	$32, %rax
	movq	%rax, %rdx
	leaq	.LC30(%rip), %rax
	movq	%rax, %rcx
	call	scanf
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	32(%rax), %xmm1
	movsd	.LC26(%rip), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L47
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	32(%rax), %xmm0
	pxor	%xmm1, %xmm1
	comisd	%xmm1, %xmm0
	ja	.L49
.L47:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	32(%rax), %xmm0
	comisd	.LC34(%rip), %xmm0
	jbe	.L60
.L49:
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	$1, 8(%rax)
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	.LC35(%rip), %xmm0
	movsd	%xmm0, 32(%rax)
	jmp	.L52
.L60:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	32(%rax), %xmm0
	pxor	%xmm1, %xmm1
	comisd	%xmm1, %xmm0
	jbe	.L52
	movq	.refptr.My_Vehicle(%rip), %rax
	movl	$0, 8(%rax)
.L52:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	32(%rax), %xmm1
	pxor	%xmm0, %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L54
	leaq	.LC28(%rip), %rax
	movq	%rax, %rcx
	call	printf
.L54:
	movq	.refptr.My_Vehicle(%rip), %rax
	movsd	32(%rax), %xmm1
	pxor	%xmm0, %xmm0
	comisd	%xmm1, %xmm0
	ja	.L56
	call	check_Vehicle_Speed
	call	Display_Vehicle_State
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC13:
	.long	0
	.long	1077805056
	.align 8
.LC14:
	.long	0
	.long	1072955392
	.align 8
.LC15:
	.long	0
	.long	1072693248
	.align 8
.LC26:
	.long	0
	.long	1079574528
	.align 8
.LC31:
	.long	0
	.long	1076101120
	.align 8
.LC32:
	.long	0
	.long	1077149696
	.align 8
.LC34:
	.long	0
	.long	1080213504
	.align 8
.LC35:
	.long	0
	.long	1079984128
	.ident	"GCC: (GNU) 11.1.0"
	.def	__mingw_vfscanf;	.scl	2;	.type	32;	.endef
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr.My_Vehicle, "dr"
	.globl	.refptr.My_Vehicle
	.linkonce	discard
.refptr.My_Vehicle:
	.quad	My_Vehicle
	.section	.rdata$.refptr.SS_selection, "dr"
	.globl	.refptr.SS_selection
	.linkonce	discard
.refptr.SS_selection:
	.quad	SS_selection
	.section	.rdata$.refptr.VCS_selection, "dr"
	.globl	.refptr.VCS_selection
	.linkonce	discard
.refptr.VCS_selection:
	.quad	VCS_selection
