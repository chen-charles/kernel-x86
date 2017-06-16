// Copyright 2016 Jianye Chen All Rights Reserved.

#ifndef _KLIB_WAITABLE_
#define _KLIB_WAITABLE_

#include	<klib_sl/type.h>

class Waitable
{
public:
    Waitable(uint64_t pID, bool isPrivate)
    {
        this->pID = pID;
        this->isPriv = isPrivate;
    }
    
    Waitable(): Waitable(0, false)
    {
        
    }
    
    ~Waitable()
    {
        
    }
    
    uint64_t getCreatorProcessID()
    {
        return this->pID;
    }
    
    bool isPrivate()
    {
        return this->isPriv;
    }
    
    virtual bool isTimeout() const = 0;
    virtual char* getName() //c-type str
    {
        return (char*)0;
    }    
    virtual bool isFinished() const = 0;
    virtual bool wait() = 0;        //should WaitForAnSingleObject return now ? true:false
private:
    uint64_t pID;
    bool isPriv;
    
protected:
    
};

#endif
