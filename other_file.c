#include "header.h"
#include <linux/kernel.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");
void do_other_func(void)
{
    printk(KERN_INFO "Hamza Basharat\n");
    
}
