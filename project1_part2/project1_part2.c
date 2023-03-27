#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Project1_Part2");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);

static int __init mymodule_init(void) {
    printk(KERN_INFO "Loading module...\n");

    struct birthday *person;
    int i;

    for (i = 0; i < 5; i++) 
    {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = i + 1;
        person->month = 3;
        person->year = 1997 + i;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
    }

    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) 
    {
        printk(KERN_INFO "Birthday: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}

static void __exit mymodule_exit(void) 
{
    printk(KERN_INFO "Unloading module...\n");

    struct birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list) 
    {
        printk(KERN_INFO "Removing birthday: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
    }
}

module_init(mymodule_init);
module_exit(mymodule_exit);
