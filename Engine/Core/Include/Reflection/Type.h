#pragma once

#include "CoreAPI.h"
#include "VString.h"

namespace Core
{
    enum class CORE_API EValueType
    {    
        None,
        Boolean,   
        Integer,    
        Real,       
        String,     
        Enum,       
        Array,      
        User        
    };  


    class VType
    {
    private:
        EValueType ValueTypeCode;

    public:
        VType()
            : ValueTypeCode(EValueType::None)
            {}
                
        VType(EValueType ValueType)
            : ValueTypeCode(ValueType)
            {}

        inline EValueType GetTypeCode()
        {
            return ValueTypeCode;
        }
    };

     
    template<typename T> struct ValueTypeMapper { static const EValueType Value = EValueType::User;};
    template<> struct ValueTypeMapper<bool> { static const EValueType Value = EValueType::Boolean;};
    template<> struct ValueTypeMapper<int> { static const EValueType Value = EValueType::Integer;};
    template<> struct ValueTypeMapper<float> { static const EValueType Value = EValueType::Real;};
    template<> struct ValueTypeMapper<VString> { static const EValueType Value = EValueType::String;};
    
    #define typeof(t) VType(ValueTypeMapper<t>::Value)
}