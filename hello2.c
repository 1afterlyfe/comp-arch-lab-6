#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "hello1.h"
#include <linux/bug.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("hello2: param + calls print_hello() from hello1");
MODULE_VERSION("1.0");

static unsigned int hello_count = 1;
module_param(hello_count, uint, 0444);
MODULE_PARM_DESC(hello_count,
    "Number of times to call print_hello() "
    "(0 or 5..10 -> warning; >10 -> error -EINVAL)");

static int __init hello2_init(void)
{
    unsigned int i;

    BUG_ON(hello_count > 10);

    if (hello_count == 0 || (hello_count >= 5 && hello_count <= 10))
        pr_warn("hello2: strange hello_count=%u\n", hello_count);

    for (i = 0; i < hello_count; i++)
        print_hello();

    pr_info("hello2: loaded, hello_count=%u\n", hello_count);
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("hello2: unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
