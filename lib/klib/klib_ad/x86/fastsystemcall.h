#ifndef _KLIB_FSC_H_
#define _KLIB_FSC_H_

// Fast System Call
//
// Arguments
// ecx: r3 esp
// edx: nxt instruction eip
// eax: fastsyscall_info*
//
// Returns
// eax: fastsyscall_return*
//

#include "type.h"
#include "global.h"
#include "string.h"

/* MSR for enabling this feature */
#define FSC_CS_MSR     0x00000174
#define FSC_ESP_MSR    0x00000175
#define FSC_EIP_MSR    0x00000176


typedef struct __fastsyscall_info
{
    uint8_t     Version;        /* klib fastsyscall version, a kernel could choose to allow multiple versions of fastsyscall protocols */
    uint32_t    FunctionID;     /* requested sys function ID */
    uint32_t    CallerProcessID;    /* caller identification */
    uint32_t    nArgs;          /* number of arguments required by the requested sys function, MUST MATCH */
    uint32_t    pArgs;          /* a pointer to the provided arguments; ignored if nArgs == 0 */
}fastsyscall_info;

typedef struct __fastsyscall_return
{
    uint8_t     VersionCheckSum;    /* if requested version is available; a failed chksum indicates the requested function is not called and this result structure should be ignored */
    uint32_t    FunctionID;         /* requested sys function ID; must match the function id used to enter fastsyscall; otherwise this structure should be ignored */
    uint32_t    CallerProcessID;    /* caller identification, always matches the value from info */
    uint32_t    Result;             /* result of the fast system call, value differs by functions */
    uint32_t    extraInfo;          /* extra information returned from the fast system call */
}fastsyscall_return;


int enable_fastsyscall(void* __fastsyscall_entrance, void* __fastsyscall_stacktop);

fastsyscall_return fsc_ret;
fastsyscall_return* fastsyscall_handler(fastsyscall_info* info);    //eax-> ptr for info

#endif
