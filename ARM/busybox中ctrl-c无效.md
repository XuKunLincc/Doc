#### ARM Linux中Ctrl-C无效
原因如下：

    Hi John, Jim
    I had the same problem, but with an embedded Linux system. I found the solution on BusyBox, the write under FAQWhy do I keep getting "sh: can't access tty; job control turned off" errors? Why doesn't Control-C work within my shell?Job control will be turned off since your shell can not obtain a controlling terminal. This typically happens when you run your shell on /dev/console. The kernel will not provide a controlling terminal on the /dev/console device. Your should run your shell on a normal tty such as tty1 or ttyS0 and everything will work perfectly. If you REALLY want your shell to run on /dev/console, then you can hack your kernel (if you are into that sortof thing) by changing drivers/char/tty_io.c to change the lines where it sets "noctty = 1;" to instead set it to "0". I recommend you instead run your shell on a real console...There is also a lot of information about "job control turned off " in their mailing list.
    I hope this helps.
    
    从上面我们可以知道，在busybox环境下，如果我们使用的是/dev/console，我们就会出现这样的情况，而我们的真正的终端是通过Uboot传进来的，是ttymxc0


解决方案：
在系统初始化完毕后设置终端为ttymxc0即可：
修改etc/inittab
::respawn:/sbin/getty 115200 ttymxc0