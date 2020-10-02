/*
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and
 * James Leu (jleu@mindspring.net).
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,linux.intel}.com)
 * Copyright (C) 2001 by various other people who didn't put their name here.
 * Licensed under the GPL.
 */

#include <linux/init.h>
#include <linux/netdevice.h>
#include <net_kern.h>
#include "rmteth.h"

struct rmteth_init {
	char *sock_type;
	char *ctl_sock;
};

static void rmteth_init(struct net_device *dev, void *data)
{
	struct uml_net_private *pri;
	struct rmteth_data *dpri;
	struct rmteth_init *init = data;

	pri = netdev_priv(dev);
	dpri = (struct rmteth_data *) pri->user;
	dpri->sock_type = init->sock_type;
	dpri->ctl_sock = init->ctl_sock;
	dpri->fd = -1;
	dpri->control = -1;
	dpri->dev = dev;
	/* We will free this pointer. If it contains crap we're burned. */
	dpri->ctl_addr = NULL;
	dpri->data_addr = NULL;
	dpri->local_addr = NULL;

	printk("rmteth backend (uml_switch version %d) - %s:%s",
	       SWITCH_VERSION, dpri->sock_type, dpri->ctl_sock);
	printk("\n");
}

static int rmteth_read(int fd, struct sk_buff *skb, struct uml_net_private *lp)
{
	return net_recvfrom(fd, skb_mac_header(skb),
			    skb->dev->mtu + ETH_HEADER_OTHER);
}

static int rmteth_write(int fd, struct sk_buff *skb, struct uml_net_private *lp)
{
	return rmteth_user_write(fd, skb->data, skb->len,
				 (struct rmteth_data *) &lp->user);
}

static const struct net_kern_info rmteth_kern_info = {
	.init			= rmteth_init,
	.protocol		= eth_protocol,
	.read			= rmteth_read,
	.write			= rmteth_write,
};

static int rmteth_setup(char *str, char **mac_out, void *data)
{
	struct rmteth_init *init = data;
	char *remain;

	*init = ((struct rmteth_init)
		{ .sock_type 		= "unix",
		  .ctl_sock 		= "/tmp/uml.ctl" });

	remain = split_if_spec(str, mac_out, &init->sock_type, &init->ctl_sock,
			       NULL);
	if (remain != NULL)
		printk(KERN_WARNING "rmteth_setup : Ignoring data socket "
		       "specification\n");

	return 1;
}

static struct transport rmteth_transport = {
	.list 		= LIST_HEAD_INIT(rmteth_transport.list),
	.name 		= "rmteth",
	.setup  	= rmteth_setup,
	.user 		= &rmteth_user_info,
	.kern 		= &rmteth_kern_info,
	.private_size 	= sizeof(struct rmteth_data),
	.setup_size 	= sizeof(struct rmteth_init),
};

static int register_rmteth(void)
{
	register_transport(&rmteth_transport);
	return 0;
}

late_initcall(register_rmteth);
