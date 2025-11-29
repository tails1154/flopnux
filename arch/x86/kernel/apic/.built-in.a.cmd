savedcmd_arch/x86/kernel/apic/built-in.a := rm -f arch/x86/kernel/apic/built-in.a;  printf "arch/x86/kernel/apic/%s " hw_nmi.o | xargs ar cDPrST arch/x86/kernel/apic/built-in.a
