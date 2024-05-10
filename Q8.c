#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h> 
#include<linux/uaccess.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hamza");
MODULE_DESCRIPTION("Read Write from file");
MODULE_VERSION("1.4");
#define mem_size 1024
dev_t dev =0;

static struct class *dev_class;
static struct cdev device_cdev;
uint8_t *kernel_buffer;

static int __init device_driver_init(void);
static void __exit device_driver_exit(void);

static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *filp, char __user *buf, size_t
len,loff_t * off);
static ssize_t device_write(struct file *filp, const char *buf, size_t len,
loff_t * off);

static struct file_operations fops =
{
 .owner = THIS_MODULE,
 .read = device_read,
 .write = device_write,
 .open = device_open,
 .release = device_release,
};

static int device_open(struct inode *inode, struct file *file)
{
 pr_info("Device File Opened...!!!\n");
 return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
 pr_info("Device File Closed...!!!\n");
 return 0;
}

static ssize_t device_read(struct file *filp, char __user *buf, size_t len,
loff_t *off)
{
 //Copy the data from the kernel space to the user-space
 if( copy_to_user(buf, kernel_buffer, mem_size) )
 {
 pr_err("Data Read : Err!\n");
 }
 pr_info("Data Read : Done!\n");
 return mem_size;
}

static ssize_t device_write(struct file *filp, const char __user *buf, size_t
len, loff_t *off)
{
 //Copy the data to kernel space from the user-space
 if( copy_from_user(kernel_buffer, buf, len) )
 {
 pr_err("Data Write : Err!\n");
 }
 pr_info("Data Write : Done!\n");
 return len;
}

static int __init device_driver_init(void)
{
 /*Allocating Major number*/
 if((alloc_chrdev_region(&dev, 0, 1, "device_Dev")) <0){
 pr_info("Cannot allocate major number\n");
 return -1;
 }
 pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 /*Creating cdev structure*/
 cdev_init(&device_cdev,&fops);
 /*Adding character device to the system*/
 if((cdev_add(&device_cdev,dev,1)) < 0){
 pr_info("Cannot add the device to the system\n");
 goto r_class;
 }
 /*Creating struct class*/
 if((dev_class = class_create(THIS_MODULE,"device_class")) == NULL){
 pr_info("Cannot create the struct class\n");
 goto r_class;
 }
 /*Creating device*/
 if((device_create(dev_class,NULL,dev,NULL,"etx_device")) == NULL){
 pr_info("Cannot create the Device 1\n");
 goto r_device;
 }

 /*Creating Physical memory*/
 if((kernel_buffer = kmalloc(mem_size , GFP_KERNEL)) == 0){
 pr_info("Cannot allocate memory in kernel\n");
 goto r_device;
 }

 strcpy(kernel_buffer, "Hello_World");

 pr_info("Device Driver Insert...Done!!!\n");
 return 0;
r_device:
 class_destroy(dev_class);
r_class:
 unregister_chrdev_region(dev,1);
 return -1;
}
static void __exit device_driver_exit(void)
{
kfree(kernel_buffer);
 device_destroy(dev_class,dev);
 class_destroy(dev_class);
 cdev_del(&device_cdev);
 unregister_chrdev_region(dev, 1);
 pr_info("Device Driver Remove...Done!!!\n");
}

module_init(device_driver_init);
module_exit(device_driver_exit);
