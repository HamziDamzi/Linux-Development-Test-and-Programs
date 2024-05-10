#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hamza ");
MODULE_DESCRIPTION(" QUESTION NO 2 SECONDARY FILE");
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
 
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
extern int etx_count;
void etx_share_function(void); 
 
static int __init etx_driver_init(void)
{
      
        if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev2")) <0)
        {
                pr_err("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
       etx_share_function();
       pr_info(" %d shared function is called in Secondary file\n", etx_count);
   
        pr_info("Device Driver 2 Insert\n");
        return 0;
 
}
static void __exit etx_driver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver 2 Remove\n");
}
module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
