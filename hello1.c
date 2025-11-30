#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("hello1: storage & timing, exports print_hello()");
MODULE_VERSION("1.0");

static LIST_HEAD(events);

static int call_id;

void print_hello(void)
{
    struct hello_event *ev;

    call_id++;

    ev = kmalloc(sizeof(*ev), GFP_KERNEL);
    if (call_id == 5) {
        pr_warn("hello1: simulated kmalloc() failure on call %d\n", call_id);
        ev = NULL;
    }

    BUG_ON(!ev);

    ev->t_start = ktime_get();
    pr_info("Hello, world!\n");
    ev->t_end = ktime_get();

    list_add_tail(&ev->list, &events);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    pr_info("hello1: loaded\n");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct hello_event *ev, *tmp;
    int i = 0;

    list_for_each_entry_safe(ev, tmp, &events, list) {
        s64 ns = ktime_to_ns(ktime_sub(ev->t_end, ev->t_start));
        pr_info("hello1: print #%d took %lld ns\n", i, (long long)ns);
        list_del(&ev->list);
        kfree(ev);
        i++;
    }
    pr_info("hello1: unloaded, freed %d events\n", i);
}

module_init(hello1_init);
module_exit(hello1_exit);
