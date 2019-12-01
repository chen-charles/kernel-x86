#include "spinlock.h"

// multi-process unsafe for now

void spinlock_create(FSpinlock* spinlock)
{
    spinlock->Data = 0;
}

void spinlock_destroy(FSpinlock* spinlock)
{

}

void spinlock_acquire(FSpinlock* spinlock)
{
    while (!spinlock_try_acquire(spinlock));
}

void spinlock_release(FSpinlock* spinlock)
{
    volatile register uintptr_t TargetValue = 0;
    __asm__ volatile ("xchg %1, %0" : "+r"(TargetValue), "+m"(spinlock->Data) :: "memory");

    // check(TargetValue == 1);
}
