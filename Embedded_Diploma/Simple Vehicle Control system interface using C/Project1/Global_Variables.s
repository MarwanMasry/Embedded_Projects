	.file	"Global_Variables.c"
	.text
	.globl	VCS_selection
	.bss
VCS_selection:
	.space 1
	.globl	SS_selection
SS_selection:
	.space 1
	.globl	My_Vehicle
	.data
	.align 32
My_Vehicle:
	.long	0
	.long	0
	.long	0
	.space 4
	.long	0
	.long	0
	.long	0
	.long	1077149696
	.long	0
	.long	1079410688
	.ident	"GCC: (GNU) 11.1.0"
