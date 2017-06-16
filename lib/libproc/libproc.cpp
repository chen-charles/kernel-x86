#include "libproc.hpp"



/*
startup context
esp-> valid stack space, minimun 1024 bytes
*/
static const int nTickRefresh = 10;
typedef struct _kProcQueueHead
{
    uint32_t nEntries;
    uint32_t offset;
    ProcessContextInfo * queue;
}
kProcQueueHead;

int kpcProcMgr_main(Mutex* kProcQueueRead, Mutex* kProcQueueWrite)
{
    // procMgr refreshes kProcQueue every 10 ticks

    // create kProcQueue
    kProcQueueHead* kProcQueue = (kProcQueueHead*)malloc(sizeof(kProcQueueHead)+sizeof(ProcessContextInfo)*nTickRefresh);
    kProcQueue->nEntries = 0;
    kProcQueue->offset = 0;
    while(1)
    {
        
    }

    return 0;
}
