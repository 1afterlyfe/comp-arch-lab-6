KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

obj-m += hello1.o hello2.o

ccflags-y += -I$(PWD)/inc -g

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	cp hello1.ko hello1.ko.unstripped
	cp hello2.ko hello2.ko.unstripped
	strip -g hello1.ko
	strip -g hello2.ko

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f *.ko.unstripped
