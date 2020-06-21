#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;	
};

struct list_head birthday_list;

struct birthday *createBirthday(int day, int month, int year) {
	struct birthday *person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
	person->day = day;
	person->month = month;
	person->year = year;
	return person;
}

void printInfo(char *str) {
	printk(KERN_INFO "OS Module: %s", str);
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
	printInfo("Loading Module\n");
	
	LIST_HEAD(birthday_list);

        struct birthday *person = createBirthday(13, 4, 1987);
	list_add_tail(&person->list, &birthday_list);
	person = createBirthday(14, 1, 1964);
	list_add_tail(&person->list, &birthday_list);
	person = createBirthday(2, 6, 1964);
	list_add_tail(&person->list, &birthday_list);
	person = createBirthday(13, 8, 1986);
	list_add_tail(&person->list, &birthday_list);
	person = createBirthday(10, 6, 1990);
	list_add_tail(&person->list, &birthday_list);

	struct birthday *ptr;

	list_for_each_entry(ptr, &birthday_list, list) {
		printk(KERN_INFO "OS Module: Day %d.%d.%d\n", ptr->day, ptr->month, ptr->year);
	}

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printInfo("Removing Module\n");

	struct birthday *tmp;
	struct list_head *ptr, *next;

	if (list_empty(&birthday_list)) {
		printInfo("List is empty");
		return;
	}

	list_for_each_safe(ptr, next, &birthday_list){
		tmp = list_entry(ptr, struct birthday, list);
		printk(KERN_INFO "OS Module: Removing %d.%d.%d\n", tmp->day, tmp->month, tmp->year);
		list_del(ptr);
		kfree(tmp);
	}

	printInfo("Module removed\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Mikhail Polgun");
