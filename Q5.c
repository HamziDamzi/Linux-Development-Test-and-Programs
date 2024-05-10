#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 
#include<linux/uaccess.h>             
#include <linux/kthread.h>             
#include <linux/sched.h>              
#include <linux/delay.h>
#include <linux/mutex.h>
 
 MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hamza Basharat");
MODULE_DESCRIPTION("Prinitng k thread 6 times");
MODULE_VERSION("1.3");
 
struct mutex etx_mutex;
unsigned long etx_global_variable = 0;
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
 
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
 
static struct task_struct *etx_thread1;
static struct task_struct *etx_thread2; 
 
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
 
int thread_function1(void *pv);
int thread_function2(void *pv);

int thread_function1(void *pv)
{
    int i=0;
    while(!kthread_should_stop()) 
    {
    if (i==6)
       {
           pr_info("\n 1 minutes is completed and the thread 1 has prinited 6 times\nGood Bye\n");
           kthread_stop(etx_thread1);
       }
    while(i<6)
    {
        mutex_lock(&etx_mutex);
        etx_global_variable++;
        pr_info("Thread Function1.....Printing Time:  %lu\n", etx_global_variable);
        mutex_unlock(&etx_mutex);
        msleep(10000);
        i++;
      }
    }
    return 0;
    
}
int thread_function2(void *pv)
{
int j=0;
    while(!kthread_should_stop()) 
    {
       if (j==6)
       {
           pr_info("\n 1 minutes is completed and the thread 2 has prinited 6 times\nGood Bye\n");
            kthread_stop(etx_thread2);
       }
        while(j<6)
        {
        mutex_lock(&etx_mutex);
        etx_global_variable++;
        pr_info("Thread Function2.....Printing TIme:  %lu\n", etx_global_variable);
        mutex_unlock(&etx_mutex);
        msleep(10000);   
        j++;  
        
        }
    }
    return 0;
    
}

static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .open           = etx_open,
        .release        = etx_release,
};

static int etx_open(struct inode *inode, struct file *file)
{
        pr_info("Device File Opened...!!!\n");
        return 0;
}

static int etx_release(struct inode *inode, struct file *file)
{
        pr_info("Device File Closed...!!!\n");
        return 0;
}

static int __init etx_driver_init(void)
{

        if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) <0)
        {
                pr_info("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        cdev_init(&etx_cdev,&fops);

        if((cdev_add(&etx_cdev,dev,1)) < 0)
        {
            pr_info("Cannot add the device to the system\n");
            
        }

        if((dev_class = class_create(THIS_MODULE,"etx_class")) == NULL){
            pr_info("Cannot create the struct class\n");
            
        }
   
        if((device_create(dev_class,NULL,dev,NULL,"etx_device")) == NULL){
            pr_info("Cannot create the Device \n");
         
        }
 
        mutex_init(&etx_mutex);
        
    
        etx_thread1 = kthread_run(thread_function1,NULL,"eTx Thread1");
        if(etx_thread1) 
        {
            pr_err("Kthread1 Created Successfully...\n");
        } 
        else 
        {
            pr_err("Cannot create kthread1\n");
         
        }
 
        etx_thread2 = kthread_run(thread_function2,NULL,"eTx Thread2");
        if(etx_thread2) 
        {
            pr_err("Kthread2 Created Successfully...\n");
        } 
        else 
        {
            pr_err("Cannot create kthread2\n");          
        }
        
        pr_info("Device Driver Insert Successfully\nRun Command Sudo dmesg after evert 10 Seconds to print\n");
        return 0;
}

static void __exit etx_driver_exit(void)
{
        kthread_stop(etx_thread1);
        kthread_stop(etx_thread2);
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!\n");
}
 
module_init(etx_driver_init);
module_exit(etx_driver_exit);
