cmd_arch/um/kernel/config.c := sed -e '/CONFIG/{' -e 's/"CONFIG"//' -e 'r arch/um/kernel/config.tmp' -e 'a \' -e '""' -e '}' arch/um/kernel/config.c.in > arch/um/kernel/config.c
