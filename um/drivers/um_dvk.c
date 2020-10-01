/*
 * Copyright (C) 2019 Pablo Pessolani
 * Licensed under the GPL
 * in linux-4.9.88/arch/um/drivers
 */ 
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <init.h>
#include <os.h>
  
#define DVKDBG		1

#ifdef CONFIG_UML_DVK
#include <kern_util.h>

#define DVK_GLOBAL_HERE		1
#include "um_dvk.h"
#include "glo_dvk.h"

#ifdef CONFIG_DVKIPC
#undef CONFIG_DVKIPC
#endif // CONFIG_DVKIPC

#include "/usr/src/dvs/dvk-lib/stub_dvkcall.c"

extern int userspace_pid[];
int module_dvk;

#define DVK_HELP \
"    This is used to specify the host dvk device to the dvk driver.\n" \
"    The default is \"" UML_DVK_DEV "\".\n\n"

module_param(dvk_dev, charp, 0644);
MODULE_PARM_DESC(dvk_dev, DVK_HELP);


#ifndef MODULE
static int set_dvk(char *name, int *add)
{
	DVKDEBUG(DBGPARAMS,"name=%s\n",name);
	dvk_dev = name;
	return 0;
}
__uml_setup("dvk_dev=", set_dvk, "dvk_dev=<dvk_device>\n" DVK_HELP);
#endif //MODULE

static DEFINE_MUTEX(uml_dvk_mutex);

/* /dev/dvk file operations */
static long uml_dvk_ioctl(struct file *file,
			   unsigned int cmd, unsigned long arg)
{
	int rcode;
	void *ptr; 

	kernel_param_lock(THIS_MODULE);
	int lnx_pid = os_getpid();
	int us_pid = userspace_pid[0];
	int uml_pid = get_current_pid();
	DVKDEBUG(DBGPARAMS,"lnx_pid=%d us_pid=%d uml_pid=%d cmd=%X arg=%X\n", 
		lnx_pid, us_pid, uml_pid, cmd, arg);
	kernel_param_unlock(THIS_MODULE);
	
	DVKDEBUG(INTERNAL,"rcode=%d\n",rcode);
	return rcode;
}

static int uml_dvk_open(struct inode *inode, struct file *file)
{
	int rcode;
	int ep;
	dvs_usr_t *dvsu_ptr;
	dc_usr_t *dcu_ptr;
	proc_usr_t *proc_ptr;

	kernel_param_lock(THIS_MODULE);
	mutex_lock(&uml_dvk_mutex);
	
	DVKDEBUG(DBGPARAMS,"dvk_dev=%s\n",dvk_dev);

	mutex_unlock(&uml_dvk_mutex);
	kernel_param_unlock(THIS_MODULE);

	return 0;
}

static int uml_dvk_release(struct inode *inode, struct file *file)
{
	DVKDEBUG(DBGPARAMS,"dvk_dev=%s\n",dvk_dev);
	return 0;
}


/* kernel module operations */
static const struct file_operations uml_dvk_fops = {
	.owner          = THIS_MODULE,
	.unlocked_ioctl	= uml_dvk_ioctl,
	.mmap           = NULL,
	.open           = uml_dvk_open,
	.release        = uml_dvk_release,
};

MODULE_AUTHOR("Pablo Pessolani - UTN FRSF");
MODULE_DESCRIPTION("Distributed Virtualization Kernel for UML");
MODULE_LICENSE("GPL");

static int __init uml_dvk_init_module(void)
{
	int kpid, ktid;

	printk("UML Distributed Virtualization Kernel (host dvk_dev = %s)\n",dvk_dev);

	kernel_param_lock(THIS_MODULE);
	DVKDEBUG(INTERNAL, "UML Distributed Virtualization Kernel (host dvk_dev = %s)\n",dvk_dev);
	kernel_param_unlock(THIS_MODULE);
	
	kpid = os_getpid();
	ktid = os_getpid();
	DVKDEBUG(INTERNAL, "UML-kernel PID=%d  UML-kernel TID=%d\n", kpid, ktid);

	module_dvk = register_chrdev(DVK_MAJOR, DEVICE_NAME, &uml_dvk_fops);
	if (module_dvk < 0) {
		printk(KERN_ERR "dvk: couldn't register DVK device!\n");
		return -ENODEV;
	}

	return 0;
}

static void __exit uml_dvk_cleanup_module (void)
{
	unregister_chrdev(DVK_MAJOR, DEVICE_NAME);
}

module_init(uml_dvk_init_module);
module_exit(uml_dvk_cleanup_module);

#endif // CONFIG_UML_DVK
