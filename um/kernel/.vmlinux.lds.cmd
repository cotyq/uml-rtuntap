cmd_arch/um/kernel/vmlinux.lds := gcc -E -Wp,-MD,arch/um/kernel/.vmlinux.lds.d  -nostdinc -isystem /usr/lib/gcc/i686-linux-gnu/6/include -I./arch/um/include -I./arch/um/include/generated/uapi -I./arch/um/include/generated  -I./include -I./arch/um/include/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -I./arch/x86/um -I./arch/x86/include -I./arch/x86/include/uapi -I./arch/x86/include/generated -I./arch/x86/include/generated/uapi     -DSTART=0x8048000 -DELF_ARCH=i386 -DELF_FORMAT=elf32-i386 -Ui386 -P -C -Uum -D__ASSEMBLY__ -DLINKER_SCRIPT -o arch/um/kernel/vmlinux.lds arch/um/kernel/vmlinux.lds.S

source_arch/um/kernel/vmlinux.lds := arch/um/kernel/vmlinux.lds.S

deps_arch/um/kernel/vmlinux.lds := \
    $(wildcard include/config/kernel/stack/order.h) \
    $(wildcard include/config/ld/script/static.h) \
  arch/um/kernel/dyn.lds.S \
  include/asm-generic/vmlinux.lds.h \
    $(wildcard include/config/ld/dead/code/data/elimination.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/kprobes.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/syscalls.h) \
    $(wildcard include/config/serial/earlycon.h) \
    $(wildcard include/config/clksrc/of.h) \
    $(wildcard include/config/irqchip.h) \
    $(wildcard include/config/common/clk.h) \
    $(wildcard include/config/of/iommu.h) \
    $(wildcard include/config/of/reserved/mem.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/idle.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/kasan.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/pm/trace.h) \
    $(wildcard include/config/blk/dev/initrd.h) \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/trim/unused/ksyms.h) \
    $(wildcard include/config/unused/symbols.h) \
  arch/um/include/asm/page.h \
    $(wildcard include/config/3/level/pgtables.h) \
    $(wildcard include/config/64bit.h) \
    $(wildcard include/config/x86/32.h) \
  include/uapi/linux/const.h \
  arch/um/include/asm/common.lds.S \

arch/um/kernel/vmlinux.lds: $(deps_arch/um/kernel/vmlinux.lds)

$(deps_arch/um/kernel/vmlinux.lds):
