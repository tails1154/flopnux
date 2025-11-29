savedcmd_vmlinux := objcopy --set-section-flags .modinfo=noload vmlinux.unstripped vmlinux; objcopy --remove-section=.modinfo vmlinux
