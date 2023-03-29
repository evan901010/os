#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("Kernel module 1");
MODULE_AUTHOR("Harry");
MODULE_LICENSE("GPL");

static int load_module(void){
    printk(KERN_INFO "Load Module\n");
    return 0;
}

static void exit_module(void){
    printk(KERN_INFO "Remove Module\n");
}
module_init(load_module);
module_exit(exit_module);