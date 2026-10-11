# Custom Linux Device Driver

A collection of small Linux kernel modules for learning device driver development,
with host builds and ARM cross-compilation for the BeagleBone Black.

## Examples

| Directory | Description |
| --- | --- |
| `001hello_world` | A basic module that logs messages when loaded and unloaded. |
| `002pseudo_char_driver` | A pseudo character driver that registers a device number, character device, and `/dev/pcd` device node. |

The character driver's `open`, `release`, `read`, `write`, and `llseek` callbacks
currently log requests. Data transfer and seek behavior are not implemented yet;
the declared 512-byte buffer is not used by these callbacks.

## Requirements

- GNU Make and a C compiler.
- Kernel headers or a configured kernel build tree matching the target kernel.
- For ARM builds, an ARM cross-compiler such as `arm-linux-gnueabihf-gcc`.
- Root privileges to load and unload modules.

## Build

Run these commands from either example directory.

Build for the running host kernel:

```sh
make host
```

Cross-compile for ARM using your configured target kernel tree:

```sh
make KERN_DIR=/path/to/linux ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
```

The Makefiles default to `~/Desktop/Temp/linux/` for the ARM kernel tree and
`/lib/modules/$(uname -r)/build/` for host headers. Override `KERN_DIR` or
`HOST_KERN_DIR` if your build tree is elsewhere.

## Load and unload

For the hello-world example, run from `001hello_world` on the target machine:

```sh
sudo insmod main.ko
sudo dmesg | tail
sudo rmmod main
```

For the character driver, run from `002pseudo_char_driver` on the target machine:

```sh
sudo insmod pcd.ko
ls -l /dev/pcd
sudo dmesg | tail
sudo rmmod pcd
```

Load each module on a machine running the kernel it was built for. Device node
creation depends on the target's device management setup, such as udev/devtmpfs.

## Clean

Clean an ARM build with the same kernel tree used to build it:

```sh
make clean KERN_DIR=/path/to/linux ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
```

Clean a host build directly through the kernel build system:

```sh
make -C /lib/modules/$(uname -r)/build M="$PWD" clean
```

Generated kernel module build files are excluded from Git by `.gitignore`.
