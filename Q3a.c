#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hamza ");
MODULE_DESCRIPTION("First Module");

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
 
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
void etx_shared_func(void);                           
int etx_count = 0;              

void etx_share_function(void)
{
        pr_info("hello world !\nFuncton is getting called from first module \n");
   
        etx_count++;
}

void etx_share_module(void)
{
        pr_info("hello world\n Module is loaded \n");
      
}


EXPORT_SYMBOL(etx_share_function);
EXPORT_SYMBOL(etx_count);
EXPORT_SYMBOL(etx_share_module);
static int __init etx_driver_init(void)
{
       
        if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev1")) <0)
        {
                pr_err("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 

        pr_info("Device Driver 1 Insert\n");
        return 0;
 
}

static void __exit etx_driver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver 1 Remove\n");
}
module_init(etx_driver_init);
module_exit(etx_driver_exit);

