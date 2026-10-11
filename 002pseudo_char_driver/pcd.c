#define pr_fmt(fmt) "%s : " fmt, __func__

#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/version.h>

#define DEV_MEM_SIZE 512
// peseudo device's memory
char device_buffer[DEV_MEM_SIZE];
// this holds the device number
dev_t device_number;

// Cdev variable
struct cdev pcd_cdev;

static loff_t pcd_lseek(struct file *filp, loff_t off, int whence)
{
    pr_info("lseek requested\n");
    return 0;
}

static ssize_t pcd_read(struct file *filp, char __user *buff,
                 size_t count, loff_t *f_pos)
{
    pr_info("read requested for %zu bytes\n", count);
    return 0;
}

static ssize_t pcd_write(struct file *filp, const char __user *buff,
                  size_t count, loff_t *f_pos)
{
    pr_info("write requested for %zu bytes\n", count);
    return 0;
}

static int pcd_open(struct inode *inode, struct file *filp)
{
    pr_info("open requested\n");
    return 0;
}

static int pcd_release(struct inode *inode, struct file *filp)
{
    pr_info("release requested\n");
    return 0;
}
// file operation of the driver
static const struct file_operations pcd_fops = {
    .owner = THIS_MODULE,
    .open = pcd_open,
    .release = pcd_release,
    .read = pcd_read,
    .write = pcd_write,
    .llseek = pcd_lseek,
};
struct class *class_pcd;
struct device *device_pcd;

static int __init pcd_driver_init(void) {
	//1. dynamically allocate a device number
	alloc_chrdev_region(&device_number,0,1,"pcd_device");
    pr_info("major = %d, minor = %d\n", MAJOR(device_number), MINOR(device_number));

	// 2.init the cdev struct with fops
	cdev_init(&pcd_cdev,&pcd_fops);

	//3.register a device (cdev struct) with VFS
	pcd_cdev.owner=THIS_MODULE;
	cdev_add(&pcd_cdev, device_number,1);

    // 4. create device class under /sys/class
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    class_pcd = class_create("pcd_class");
#else
    class_pcd = class_create(THIS_MODULE,"pcd_class");
#endif

    // 5. poplate the sysfs with device information
    device_pcd = device_create(class_pcd,NULL,device_number,NULL,"pcd");
    pr_info("module loaded successfully\n");
	return 0;
}
static void __exit pcd_driver_cleanup(void)
{
    device_destroy(class_pcd,device_number);
    class_destroy(class_pcd);
    cdev_del(&pcd_cdev);
    unregister_chrdev_region(device_number,1);
    pr_info("module unloaded successfully\n");
}

module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Amin");
MODULE_DESCRIPTION("A pseudo character driver");
