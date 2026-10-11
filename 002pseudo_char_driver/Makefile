obj-m := pcd.o
ARCH=arm
CROSS_COMPILE=arm-linux-gnueabihf-
KERN_DIR=~/Desktop/Temp/linux/
HOST_KERN_DIR=/lib/modules/$(shell uname -r)/build/

all:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(CURDIR) modules
clean:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(CURDIR) clean
help:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(CURDIR) help
host:
	$(MAKE) ARCH=$(shell uname -m) CROSS_COMPILE= -C $(HOST_KERN_DIR) M=$(CURDIR) modules

