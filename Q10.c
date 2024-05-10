 // After Make run this command to input the values : sudo insmod Q10.ko number=23 string="hamza" array=10,12,104,19  

#include<linux/kernel.h>
#include<linux/moduleparam.h>
#include<linux/init.h>
#include<linux/module.h>
  
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hamza Basharat");
MODULE_DESCRIPTION("Scanf in Kernel Module");
 
int number; 
int array[4];
char *string;
int callval = 0;
 
module_param(number, int, S_IRUSR|S_IWUSR);                      
module_param(string, charp, S_IRUSR|S_IWUSR);                     
module_param_array(array, int, NULL, S_IRUSR|S_IWUSR);    
 
int notify_param(const char *val, const struct kernel_param *kp)
{
        int check = param_set_int(val, kp); 
        if(check==0)
       	{

                printk(KERN_INFO "Call back function called...\n");
                printk(KERN_INFO "New value of CallVall = %d\n", callval);
                return 0;
        }
        return -1;
}
 
const struct kernel_param_ops my_param_ops = 
{
        .set = &notify_param, 
        .get = &param_get_int, 
};
 
module_param_cb(callval, &my_param_ops, &callval, S_IRUGO|S_IWUSR );

static int __init hello_world_init(void)
{                                             
        int i;
        printk(KERN_INFO "Value = %d  \n", number);
        printk(KERN_INFO "CallVal = %d  \n", callval);
        printk(KERN_INFO "String = %s \n", string);
        for (i = 0; i < (sizeof array / sizeof (int)); i++) 
        {
                printk(KERN_INFO "Array[%d] = %d\n", i, array[i]);
        }
        printk(KERN_INFO "Kernel Module Inserted\n");
    return 0;
}

static void __exit hello_world_exit(void)
{
    printk(KERN_INFO "Kernel Module Removed\n");
}
 
module_init(hello_world_init);
module_exit(hello_world_exit);

