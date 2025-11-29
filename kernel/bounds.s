	.file	"bounds.c"
# GNU C11 (GCC) version 15.2.1 20251112 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 15.2.1 20251112, GMP version 6.3.0, MPFR version 4.2.2, MPC version 1.3.1, isl version isl-0.27-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -mno-sse4a -m32 -msoft-float -mregparm=3 -mpreferred-stack-boundary=2 -march=i686 -Os -std=gnu11 -fshort-wchar -funsigned-char -fno-common -fno-strict-aliasing -fcf-protection=none -fno-pcc-struct-return -fno-pic -ffreestanding -fno-asynchronous-unwind-tables -fno-delete-null-pointer-checks -fno-allow-store-data-races -fno-stack-protector -fomit-frame-pointer -ftrivial-auto-var-init=zero -fzero-init-padding-bits=all -fno-stack-clash-protection -fmin-function-alignment=4 -fstrict-flex-arrays=3 -fno-strict-overflow -fstack-check=no -fconserve-stack -fno-builtin-wcslen
	.text
	.section	.text.startup,"ax",@progbits
	.align 4
	.globl	main
	.type	main, @function
main:
# kernel/bounds.c:19: 	DEFINE(NR_PAGEFLAGS, __NR_PAGEFLAGS);
#APP
# 19 "kernel/bounds.c" 1
	
.ascii "->NR_PAGEFLAGS $21 __NR_PAGEFLAGS"	#
# 0 "" 2
# kernel/bounds.c:20: 	DEFINE(MAX_NR_ZONES, __MAX_NR_ZONES);
# 20 "kernel/bounds.c" 1
	
.ascii "->MAX_NR_ZONES $2 __MAX_NR_ZONES"	#
# 0 "" 2
# kernel/bounds.c:24: 	DEFINE(SPINLOCK_SIZE, sizeof(spinlock_t));
# 24 "kernel/bounds.c" 1
	
.ascii "->SPINLOCK_SIZE $0 sizeof(spinlock_t)"	#
# 0 "" 2
# kernel/bounds.c:29: 	DEFINE(LRU_GEN_WIDTH, 0);
# 29 "kernel/bounds.c" 1
	
.ascii "->LRU_GEN_WIDTH $0 0"	#
# 0 "" 2
# kernel/bounds.c:30: 	DEFINE(__LRU_REFS_WIDTH, 0);
# 30 "kernel/bounds.c" 1
	
.ascii "->__LRU_REFS_WIDTH $0 0"	#
# 0 "" 2
# kernel/bounds.c:35: }
#NO_APP
	xorl	%eax, %eax	#
	ret	
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20251112"
	.section	.note.GNU-stack,"",@progbits
