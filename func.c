// I have make scanf of function name using moduleparam. 
// to print func1 name, enter command sudo insmod Q7.ko string="func1"
// to print func2 name, enter command sudo insmod Q7.ko string="func2"

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hamza Basharat");
MODULE_DESCRIPTION("Character device drivers to print function names");

char *string;
module_param(string, charp, S_IRUSR|S_IWUSR);  
static int      __init Main_function(void);
static void     __exit etx_driver_exit(void);
char *string1="func1";
char *string2="func2";

void fun1(void)
{
	pr_info("Thank You for Calling Me.\nI am Called function is: %s\n",__func__);
}

void fun2(void)
{
	pr_info("Thank You for Calling Me.\nI am Called function is: %s\n",__func__);
}
static int __init Main_function(void)
{
        pr_info("Called function is: %s\n",__func__);
	pr_info("\nThere are Two Functions In this Program.\n1. func1 \n2. func2\n");
	pr_info("Enter the name of any one of them to call and get its name printed\n");
	
	if (strcmp(string,string1)==0)
	{
	fun1();
	}
	else if (strcmp(string,string2)==0)
	{
	fun2();
	}
	else 
	pr_info("\nDefault");
	
	return 0;    
}

static void __exit etx_driver_exit(void)
{
      
        pr_info("Device Driver Remove...Done!!!\n");
}

module_init(Main_function);
module_exit(etx_driver_exit);


