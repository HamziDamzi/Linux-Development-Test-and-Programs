 #include<linux/init.h>
#include<linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hamza Basharat");
MODULE_DESCRIPTION("KMalloc Allocation");

void *ptr;
static int kmalloc_init(void) 
{
      size_t size = 1024; 
      ptr = (void *) kmalloc(size,GFP_KERNEL); 

if(ptr == (void *) 0)
{
      printk("memory allocation failed\n");
      return 0;
}

else
      printk("Memory allocated successfully\n");

return 0;
}

static void kmalloc_exit(void) 
{

    kfree(ptr); 
    printk("Memory freed\n");

}
module_init(kmalloc_init);
module_exit(kmalloc_exit);
