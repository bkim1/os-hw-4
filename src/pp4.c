#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

#define MAX_BDAYS 5

struct birthday { 
    int day; 
    int month;
    int year;
    struct list_head list; 
}; 

LIST_HEAD(birthday_list);   


/* This function is called when the module is loaded. */
int pp4_init(void) {
    printk(KERN_INFO "Loading Module\n");
  
    // Create the Linked List of Birthdays
    int i;
    for (i = 0; i < MAX_BDAYS; i++) {
        struct birthday *person;
        
        person = (struct birthday *)kmalloc(sizeof(*person), GFP_KERNEL); 
        person->day = 11;
        person->month= 7;
        person->year = 1996; 
        INIT_LIST_HEAD(&person->list); 

        list_add_tail(&person->list, &birthday_list);
    }

    // Traverse Linked List and Output Info
    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) { 
        printk("Birthday: %i/%i/%i\n", ptr->month, ptr->day, ptr->year);
    }
    
    return 0;
}

/* This function is called when the module is removed. */
void pp4_exit(void) {
    printk(KERN_INFO "Removing Module\n");

    // Remove and Free each node in list
    struct birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list) { 
        list_del(&ptr->list); 
        kfree(ptr); 
    }

    printk("List has been removed\n");
}

/* Macros for registering module entry and exit points. */
module_init( pp4_init );
module_exit( pp4_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PP4 Module");
MODULE_AUTHOR("BKIM");

