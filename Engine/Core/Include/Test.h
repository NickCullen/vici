#pragma once

#ifdef Core_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

class CORE_API Test
{
public:
    static void Hello();
};