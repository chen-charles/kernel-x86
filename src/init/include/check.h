#ifndef _KINIT_CHECK_
#define _KINIT_CHECK_

#include "panic.h"

/*
Assertions

There are cases where we cannot continue executions due to critical errors. 
This could be as simple as a NULL pointer, or as complicated as a potential kernel vulnerability. 

At kernel level, we provide the three types of assertion mechanisms.
1. check(pred), checkf(pred, format, ...), checkNoEntry()
    checks are debug-time assertions, they will only be compiled when DO_CHECK is set.
2. verify(pred), verifyf(pred, format, ...)
    verifys are assertions that must be satisfied even in shipping builds, we cannot possibly recover from such failures.
3. ensure(pred)
    ensure points fire a "int 3" upon failure
*/

/* verifys */
#define _verifyf_impl(pred, pred_str, format, ...) if (!pred) panic("verify failed at %s(%s:%d).\nPredicate (%s) evaluates to false.\nEnclosed message: " # format, __func__, __FILE__, __LINE__, pred_str, ## __VA_ARGS__)
#define verifyf(pred, format, ...) _verifyf_impl(pred, #pred, format, ## __VA_ARGS__)
#define verify(pred) verifyf(pred, "None")

/* checks: enabled by DO_CHECK=1 */
#if DO_CHECK
#define _checkf_impl(pred, pred_str, format, ...) if (!pred) panic("check failed at %s(%s:%d).\nPredicate (%s) evaluates to false.\nEnclosed message: " # format, __func__, __FILE__, __LINE__, pred_str, ## __VA_ARGS__)
#else
#define _checkf_impl(...) 
#endif

#define checkf(pred, format, ...) _checkf_impl(pred, #pred, format, ## __VA_ARGS__)
#define check(pred) checkf(pred, "None")

#define checkNoEntry() checkf(false, "checkNoEntry: this subroutine should never got executed.")

/* ensures: enabled by DO_CHECK=1 */
#define ensure(pred) __asm__ volatile ( "int 3" )

#endif
