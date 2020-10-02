/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,linux.intel}.com)
 * Licensed under the GPL
 */

#ifndef __RMTETH_H__
#define __RMTETH_H__

#include <net_user.h>

#define SWITCH_VERSION 3

struct rmteth_data {
	char *sock_type;
	char *ctl_sock;
	void *ctl_addr;
	void *data_addr;
	void *local_addr;
	int fd;
	int control;
	void *dev;
};

extern const struct net_user_info rmteth_user_info;

extern int rmteth_user_write(int fd, void *buf, int len,
			     struct rmteth_data *pri);

#endif
