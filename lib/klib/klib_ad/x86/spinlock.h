#ifndef _KLIB_SPINLOCK_H
#define _KLIB_SPINLOCK_H

#include <klib_sl/type.h>
#include <klib_sl/c/klib_sl.h>

/*
Spinlocks

spinlock is an un-named synchronization primitive shared globally (within a shared memory space, ofc.)
spinlocks are volatile
spinlocks does not have ownership, and does not check for validity. (use FLock/FCriticalSection instead)
*/

typedef volatile struct
{
    uintptr_t Data;    // arch. dependent atomic xchg operand
}
FSpinlock;

void spinlock_create(FSpinlock* spinlock);
void spinlock_destroy(FSpinlock* spinlock);

static inline bool spinlock_try_acquire(FSpinlock* spinlock)
{
    volatile register uintptr_t TargetValue = 1;

    __asm__ volatile ("xchg %1, %0" : "+r"(TargetValue), "+m"(spinlock->Data) :: "memory");

    return TargetValue == 0;
}

void spinlock_acquire(FSpinlock* spinlock);

void spinlock_release(FSpinlock* spinlock);

#endif