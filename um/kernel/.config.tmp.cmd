cmd_arch/um/kernel/config.tmp := sed -e 's/"/\\"/g' -e 's/^/"/' -e 's/$$/\\n",/' .config > arch/um/kernel/config.tmp
