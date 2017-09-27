#pragma once

class IWeakPtrBase
{
protected:
    bool bIsValid = false;

public:
    virtual void Validate()
    {
        bIsValid = true;
    }

    virtual void Invalidate()
    {
        bIsValid = false;
    }

    virtual ~IWeakPtrBase() 
    {
        
    }
};