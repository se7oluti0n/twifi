http://www.howtoforge.com/kernel_compilation_ubuntu

```
1 Preliminary Note
apt-get update

2 Install Required Packages For Kernel Compilation

apt-get install kernel-package libncurses5-dev fakeroot wget bzip2

3 Download The Kernel Sources

4 Apply Patches To The Kernel Sources (Optional)

5 Configure The Kernel

cp /boot/config-`uname -r` ./.config
make menuconfig

6 Build The Kernel

make-kpkg clean
fakeroot make-kpkg --initrd --append-to-version=-custom kernel_image kernel_headers

7 Install The New Kernel

dpkg -i linux-image-2.6.18.1-custom_2.6.18.1-custom-10.00.Custom_i386.deb
dpkg -i linux-headers-2.6.18.1-custom_2.6.18.1-custom-10.00.Custom_i386.deb

vi /boot/grub/menu.lst 

You may need to change the device to /dev/hda1, causing the default kernel using hda for hard disk.

title           Ubuntu, kernel 2.6.18.1-custom
root            (hd0,0)
kernel          /boot/vmlinuz-2.6.18.1-custom root=/dev/sda1 ro quiet splash
initrd          /boot/initrd.img-2.6.18.1-custom
savedefault
boot

title           Ubuntu, kernel 2.6.18.1-custom (recovery mode)
root            (hd0,0)
kernel          /boot/vmlinuz-2.6.18.1-custom root=/dev/sda1 ro single
initrd          /boot/initrd.img-2.6.18.1-custom
boot


```