//While compiling this ..kernel crashes everytime...unstable behavious
//Kernel crashed and BUG: unable to handle kernel NULL pointer dereference has been logged


#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hamza Basharat");
MODULE_DESCRIPTION("Dereferncing a null pointer");


static int __init null_init(void)
{
    struct inode
     {
        int i_ino;
    };
    struct dentry
    {
        struct inode *d_inode;
    }; 
    struct dentry *f_dentry;
    f_dentry = NULL;
    struct inode * p = f_dentry->d_inode;
    return 0; 
}

static void __exit nullpointer_exit(void)
{ 
        printk("Goodbye world\n");
}


module_init(null_init);
module_exit(nullpointer_exit);
