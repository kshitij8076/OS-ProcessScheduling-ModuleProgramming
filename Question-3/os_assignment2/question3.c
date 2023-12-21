#include <linux/init.h>        
#include <linux/module.h>     
#include <linux/sched.h>     
#include <linux/kernel.h>      
#include <linux/syscalls.h>  

MODULE_LICENSE("GPL");
MODULE_AUTHOR("roshan_kshitij");
MODULE_DESCRIPTION("this kernel program  list task kernel program");

static int process_running(void) {
    struct task_struct *task;
    int totalprocess_count = 0;
    for_each_process(task) {
        if (task->__state == TASK_RUNNING) {
            printk(KERN_INFO "Task name: %s, PID: %d\n", task->comm, task->pid);
            totalprocess_count++;
        }
    }
    printk(KERN_INFO "total number of runnig process : %u\n", totalprocess_count);
    return 0;
}

static int __init list_taskfunction(void) {
    printk(KERN_INFO "task list_kernel module uploaded \n");
    process_running();
    return 0;
}

static void __exit exit_taskfunction(void) {
    printk(KERN_INFO "task list_kernel module unloaded\n");
}

module_init(list_taskfunction);
module_exit(exit_taskfunction);
