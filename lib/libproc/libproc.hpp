/*
library Process --- C++ Process Management
Copyright (C) 2016  Jianye Chen
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIB_PROC
#define LIB_PROC

#include	<stdbool.h>
#include	<stdint.h>
#include	<stddef.h>

#include    "type.h"

#ifndef STL_ENABLED
#include    "Vector.h"
#else
#include    <vector>
#define Vector vector
#endif


/*
library Process

libproc abstracts the process interface
however, due to architecture differences, context switch requires additional handling from the kernel
for example, not every architecture requires fxsave/fxrstor

scheduler is provided for process scheduling
every call to the scheduler will be counted as a time slice change
which means a context switch should happen right after such call

context switching on different platforms are completely different
libproc will use the following modal:

interrupt timer tick
-> scheduler tick (libproc) -> return ContextSwitchInformation(current_ctx*, next_ctx*)
-> store current_ctx* (kernel)
-> setup next_ctx* (kernel)
interrupt cleanup
interrupt return

libproc will not handle the underlying context switching mechanics 

synchronization objects are supplied in libproc as well
they are built with an required accessor to SYSTEM_INTERNAL_TIME
that is, the real time being counted

Waitable: Timer(oneshot/periodic), Mutex
WaitForASingleObject(Waitable) puts the process into an idle state if the Waitable is not ready yet
WaitForASingleObject(Timer) puts the wake up time into a queue, then idle the current process

libproc comes with a vector implementation, since under most situations, you won't have the STL supplied (maybe not even libupc++)
you can, however, uses the STL vector implementation if you can supply, by defining STL_ENABLED

*/



/* BEGIN REQUIRED INTERFACE */

extern "C"
{
    uint64_t SYSTEM_INTERNAL_TIME();
}

/* END REQUIRED INTERFACE */



/* BEGIN INITIALIZATION */

/* END INITIALIZATION */

/* BEGIN SYNC */

class Waitable
{
public:
    Waitable(uint64_t pID, bool isPrivate)
    {
        this->pID = pID;
        this->isPriv = isPrivate;
    }
    
    Waitable(): Waitable(0, false) {}
    ~Waitable() {}
    
    uint64_t getCreatorProcessID() { return this->pID; }
    bool isPrivate() { return this->isPriv; }
    
    virtual bool isTimeout() const = 0;
    virtual char* getName() { return (char*)0; } // c-type str

    virtual bool isFinished() const = 0;
    virtual bool wait() = 0;        // should WaitForAnSingleObject return now ? true:false

private:
    uint64_t pID;
    bool isPriv;
    
protected:
    
};

class Timer: public Waitable
{
public:
    
    enum TimerMode
    {
        MOD_ONESHOT, MOD_PERIODIC, UNSPECIFIED
    };
    
    
    Timer(uint64_t pID, bool isPrivate): Waitable(pID, isPrivate)
    {
        mode = Timer::TimerMode::UNSPECIFIED;
        this->isTurnFinished = true;
    }
    
    Timer(): Waitable()
    {
        mode = Timer::TimerMode::UNSPECIFIED;
        this->isTurnFinished = true;
    }
    
    void setTimer(Timer::TimerMode mode, int interval)
    {
        this->mode = mode;
        this->interval = interval;
    }
    
    void start()
    {
        isTurnFinished = false;
        startTime = SYSTEM_INTERNAL_TIME();
    }
    
    void end() { isTurnFinished = true; }
    
    bool isFinished() const { return this->isTurnFinished; }
    
    bool isTimeout() const { return false; }
    
    bool wait()
    {
        if (mode == Timer::TimerMode::UNSPECIFIED) return false;
        if (isTurnFinished) return false;
        
        switch (mode)
        {
        case MOD_ONESHOT:
            if (startTime+interval >= SYSTEM_INTERNAL_TIME())
            {
                isTurnFinished = true;
                return true;
            }
            break;
        case MOD_PERIODIC:
            if (startTime+interval >= SYSTEM_INTERNAL_TIME())
            {
                startTime = SYSTEM_INTERNAL_TIME();
                return true;
            }
            break;
        }
        return false;
    }
    
    ~Timer() {}
    
private:
    TimerMode mode;
    bool isTurnFinished;
    int interval;
    int startTime;
};

class Mutex: public Waitable
{
public:
    Mutex(uint64_t pID, bool isPrivate): Waitable(pID, isPrivate) { this->startTime = 0; this->timeout = (uint32_t)(-1); }
    
    Mutex(): Waitable() { this->startTime = 0; this->timeout = (uint32_t)(-1); }
    
    bool open(int timeout)
    {
        this->startTime = SYSTEM_INTERNAL_TIME();
        this->timeout = timeout;
        if (!this->isInUse) 
        {
            this->isInUse = true;
            return true;
        }
        else
        {
            //call system routine(fetch process id, then add waitable, then set state)
            //using the dumb way here
            while(!wait());
            if (!isTimeout()) 
            {
                isInUse = true;
                return true;
            }
            else return false;
        }
    }
    
    void release() { this->isInUse = false; }
    
    bool isTimeout() const { return startTime+timeout >= SYSTEM_INTERNAL_TIME(); }

    bool isFinished() const { return false; }
    
    bool wait()
    {
        if (isTimeout()) return true;
        else
        {
            if (!isInUse) return true;
            else return false;
        }
    }
    
private:
    bool isInUse = false;
    int timeout;
    int startTime;
};

/* END SYNC */



/* BEGIN PUBLIC INTERFACE */

enum class RuntimeStatus { IDLING, RUNNING, PENDING };
enum class Privilege { KERNEL, DRIVER, SERVICE, USER };

/* memory pointer to actural context supplied by kernel */
typedef memblock ProcessContextInfo;

class Process
{
public:
    Process(){}
    Process(uint64_t priority, ProcessContextInfo ctx, Privilege priv)
    {
        rt_status = RuntimeStatus::PENDING;
        this->priority = priority;
        this->max_priority = priority;
        this->ctx = ctx;
        this->priv = priv;
    }
    ~Process(){}

    void wait(Waitable* pBlockingWaitable)
    {
        pBlockingWaitable->getCreatorProcessID();   // runtime failure if the pointer passed in is wrong
        if (pBlockingWaitable != nullptr) rt_status = RuntimeStatus::PENDING;
        this->pBlockingWaitable = pBlockingWaitable;
    }

    /*
    Runtime status: IDLING, RUNNING, PENDING
    idling: waiting for a system event to activate the process (IO idling ... )
    running: currently using the time slice
    pending: waiting to use the time slice
    */
    RuntimeStatus rt_status;
    ProcessContextInfo ctx;
    Privilege priv;
    uint64_t max_priority;  // actural process priority, max priority: 0

    // scheduler runtime
    uint64_t priority;  // dynamic priority
    uint64_t tick = 0;  // ticker
    Waitable *pBlockingWaitable = nullptr;
};

class Scheduler
{
public:
    Scheduler()
    {
        vec_p = new Vector<Process*>();
        prev = next = nullptr;
    }
    
    Process* CreateProcess(uint64_t priority, ProcessContextInfo ctx, Privilege priv)
    {
        vec_p->push_back(new Process(priority, ctx, priv));
        return vec_p->back();
    }
    
    Process* prevProc()
    {
        return prev;
    }

    Process* nextProc()
    {
        return next;
    }

    ProcessContextInfo* prevCtx()
    {
        if (prev != nullptr)
            return &(prev->ctx);
        return nullptr;
    }

    ProcessContextInfo* nextCtx()
    {
        return &(next->ctx);
    }

    /*
    Scheduler.tick()

    Return:
    true: if a context switch is required (possible nullptr for prev)
    false: no ctx switch required, either no PENDING processes or next=prev (possible nullptr for both prev and next)

    Result:
    * must check for nullptr
    this->prevProcess() returns the previous running process
    this->nextProcess() returns the next running process

    */
    bool tick()
    {
        if (vec_p->size() > 0)
        {
            if (this->running != 0) 
            {
                prev = (this->running);
                if (this->running->rt_status == RuntimeStatus::RUNNING)
                    this->running->rt_status = RuntimeStatus::PENDING;
            }
            else
            {
                prev = nullptr;
            }
            
            this->running = vec_p->at(0);
            for (int i=0; i<vec_p->size(); i++)
            {
                if (vec_p->at(i)->rt_status == RuntimeStatus::IDLING)
                {
                    if (vec_p->at(i)->pBlockingWaitable != nullptr && vec_p->at(i)->pBlockingWaitable->wait())
                    {
                        vec_p->at(i)->rt_status = RuntimeStatus::PENDING;
                        vec_p->at(i)->pBlockingWaitable = nullptr;
                    }
                }
                
                if (vec_p->at(i)->priority < this->running->priority && vec_p->at(i)->rt_status == RuntimeStatus::PENDING)
                {
                    this->running = vec_p->at(i);
                }
            }
            
            if (this->running->rt_status != RuntimeStatus::PENDING)
            {
                next = nullptr;
                return false;
            }
            else
            {
                this->running->rt_status = RuntimeStatus::RUNNING;
            }
            
            uint64_t past_pri = this->running->priority;
            
            for (int i=0; i<vec_p->size(); i++)
            {
                if (past_pri > vec_p->at(i)->priority)
                {
                    vec_p->at(i)->priority = 0;
                }
                else
                {
                    vec_p->at(i)->priority -= past_pri;
                }
            }
            
            this->running->priority = this->running->max_priority;
            this->running->tick ++;
            next = (this->running);

            if (next == prev)   // no hardware ctx switch required
                return false;
            return true;
        }
        else
        {
            next = prev = nullptr;
            return false;
        }
    }
    
    ~Scheduler()
    {
        delete vec_p;
    }
    
// private:
    Vector<Process*>* vec_p = nullptr;
    Process* prev = nullptr;
    Process* next = nullptr;
    Process* running = nullptr;

};


/* END PUBLIC INTERFACE*/

#endif
