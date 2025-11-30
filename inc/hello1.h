#ifndef HELLO1_H
#define HELLO1_H

#include <linux/ktime.h>
#include <linux/list.h>

struct hello_event {
  struct list_head list;
  ktime_t t_start;
  ktime_t t_end;
};

void print_hello(void);

#endif
