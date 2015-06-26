kernel version 2.6.24.4

Patch to arch/x86/kernel/time\_32.c

```
150a151,161
> u_int64_t kernel_tsf = 0;
> DEFINE_SPINLOCK(kernel_tsf_lock);
>
> void tsf_update(u_int64_t tsf)
> {
>       spin_lock_irq(kernel_tsf_lock);
>       kernel_tsf = tsf;
>       spin_unlock_irq(kernel_tsf_lock);
> }
> EXPORT_SYMBOL(tsf_update);
>
160a172,174
>       spin_lock_irq(kernel_tsf_lock);
>       kernel_tsf++;
>       spin_unlock_irq(kernel_tsf_lock);
```
in the madwifi driver, we can call the tsf\_update method to update the kernel tsf in driver tasklet.