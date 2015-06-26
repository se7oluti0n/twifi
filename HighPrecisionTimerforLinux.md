# PIT (Programmable Interval Timer) #
change the timer frequency to 1000HZ

make menuconfig
Processor type and features --> Timer frequency = 1000HZ

I try the method as follow, but there are some problems
  * using an 8254 CMOS chip ath the 0x40-0x43 port
  * clock signal frequency is about 1000.15 Hz
  * default tick is roughly 10 milliseconds by setting the HZ 100. We can change it to 1000 in linux/include/asm-x86/param.h. So we can get a 1 milliseconds tick.

#define HZ 100
==>
#define HZ 1000


# HPET (High Precision Event Timer) #

  * frequency must be at least 10MHz; therefore, the tick is at least 100 nanoseconds.

# Timer Interrupt Handler #

  * timer\_interrupt() located on arch\x86\kernel\time\_32.c or time\_64.c
  * do\_timer\_interrupt\_hook() located on include/asm-i386/mach-default/do\_timer.h
  * global\_clock\_event located on  linux/arch/i386/kernel/i8253.c

# Kernel Timer #

> The kernel cannot ensure that timer functions will start right at their expiration times. It can only ensure that they are executed either at the proper time or after with a delay of up to a few hundreds of milliseconds. For this reason, timers are not appropriate for real-time applications.


useful function:
  * init\_timer
  * add\_timer
  * mod\_timer
  * del\_timer

# Delay Function #

useful function:
  * udelay
  * ndelay