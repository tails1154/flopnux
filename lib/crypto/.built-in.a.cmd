savedcmd_lib/crypto/built-in.a := rm -f lib/crypto/built-in.a;  printf "lib/crypto/%s " chacha.o blake2s.o blake2s-generic.o sha256.o x86/built-in.a | xargs ar cDPrST lib/crypto/built-in.a
