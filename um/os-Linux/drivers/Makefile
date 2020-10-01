# 
# Copyright (C) 2000, 2002 Jeff Dike (jdike@karaya.com)
# Licensed under the GPL
#

ethertap-objs := ethertap_kern.o ethertap_user.o
tuntap-objs := tuntap_kern.o tuntap_user.o
rtuntap-objs := rtuntap_kern.o rtuntap_user.o

obj-y = 
obj-$(CONFIG_UML_NET_ETHERTAP) += ethertap.o
obj-$(CONFIG_UML_NET_TUNTAP) += tuntap.o
obj-$(CONFIG_UML_NET_RTUNTAP) += rtuntap.o

include arch/um/scripts/Makefile.rules
