/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,linux.intel}.com)
 * Licensed under the GPL
 */

#include <linux/netdevice.h>
#include <linux/init.h>
#include <linux/skbuff.h>
#include <asm/errno.h>
#include <net_kern.h>
#include "rtuntap.h"

struct rtuntap_init {
	char *dev_name;
	char *gate_addr;
};

static void rtuntap_init(struct net_device *dev, void *data)
{
	struct uml_net_private *pri;
	struct rtuntap_data *tpri;
	struct rtuntap_init *init = data;

	pri = netdev_priv(dev);
	tpri = (struct rtuntap_data *) pri->user;
	tpri->dev_name = init->dev_name;
	tpri->fixed_config = (init->dev_name != NULL);
	tpri->gate_addr = init->gate_addr;
	tpri->fd = -1;
	tpri->dev = dev;

	printk(KERN_INFO "RTUN/TAP backend - ");
	if (tpri->gate_addr != NULL)
		printk(KERN_CONT "IP = %s", tpri->gate_addr);
	printk(KERN_CONT "\n");
}

static int rtuntap_read(int fd, struct sk_buff *skb, struct uml_net_private *lp)
{
	return net_read(fd, skb_mac_header(skb),
			skb->dev->mtu + ETH_HEADER_OTHER);
}

static int rtuntap_write(int fd, struct sk_buff *skb, struct uml_net_private *lp)
{
	return net_write(fd, skb->data, skb->len);
}

const struct net_kern_info rtuntap_kern_info = {
	.init			= rtuntap_init,
	.protocol		= eth_protocol,
	.read			= rtuntap_read,
	.write 			= rtuntap_write,
};

int rtuntap_setup(char *str, char **mac_out, void *data)
{
	struct rtuntap_init *init = data;

	*init = ((struct rtuntap_init)
		{ .dev_name 	= NULL,
		  .gate_addr 	= NULL });
	if (tap_setup_common(str, "rtuntap", &init->dev_name, mac_out,
			    &init->gate_addr))
		return 0;

	return 1;
}

static struct transport rtuntap_transport = {
	.list 		= LIST_HEAD_INIT(rtuntap_transport.list),
	.name 		= "rtuntap",
	.setup  	= rtuntap_setup,
	.user 		= &rtuntap_user_info,
	.kern 		= &rtuntap_kern_info,
	.private_size 	= sizeof(struct rtuntap_data),
	.setup_size 	= sizeof(struct rtuntap_init),
};

static int register_rtuntap(void)
{
	register_transport(&rtuntap_transport);
	return 0;
}

late_initcall(register_rtuntap);
