/**
 * FileName: affinity_demo.c
 */

#include <stdint.h>
#include <stdio.h>
#include <sched.h>
#include <pthread.h>
#include <stdlib.h>

#include <unistd.h>


static inline void print_cpu_mask(cpu_set_t cpu_mask)
{
    unsigned char flag = 0;
    printf("Cpu affinity is ");
    for (unsigned int i = 0; i < sizeof(cpu_set_t); i ++)
    {
        if (CPU_ISSET(i, &cpu_mask))
        {
            if (flag == 0)
            {
                flag = 1;
                printf("%d", i);
            }
            else
            {
                printf(",%d", i);
            }
        }
    }
    printf(".\n");
}

static inline void get_cpu_mask(pid_t pid, cpu_set_t *mask)
{
    if (sched_getaffinity(pid, sizeof(cpu_set_t), mask) == -1)
    {
        perror("get cpu affinity failed.\n");
        abort();
    }
}

static inline void set_cpu_mask(pid_t pid, cpu_set_t *mask)
{
    if (sched_setaffinity(pid, sizeof(cpu_set_t), mask) == -1)
    {
        perror("set cpu affinity failed.\n");
        abort();
    }
}

int main(int argc, char *argv[])
{
    unsigned int dummy = 0;
    cpu_set_t cpu_mask;

    get_cpu_mask(0, &cpu_mask);
    print_cpu_mask(cpu_mask);

    CPU_ZERO(&cpu_mask);
    CPU_SET(0, &cpu_mask); // (activecpu, cpumask)
    CPU_SET(1, &cpu_mask);
    set_cpu_mask(0, &cpu_mask);

    get_cpu_mask(0, &cpu_mask);
    print_cpu_mask(cpu_mask);

    for(;;)
    {
        for (int i=0; i<100000; i++)
        {
            dummy = 1;
        }
        sleep(0.00001);
    }
    return 0;
}


