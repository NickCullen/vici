#pragma once

// Credit: https://github.com/marcmo/delegates/
// Modified to follow engine style

/**
 * specialization for member functions
 *
 * \tparam T            class-type of the object who's member function to call
 * \tparam R            return type of the function that gets captured
 * \tparam params       variadic template list for possible arguments
 *                      of the captured function
 */
template <typename T, typename R, typename... Params>
class VDelegate<R (T::*)(Params...)>
{
public:
    typedef R (T::*func_type)(Params...);

	VDelegate(func_type func, T& callee)
        : callee_(callee)
        , func_(func)
    {}

    R operator()(Params... args) const
    {
        return (callee_.*func_)(args...);
    }

    bool operator==(const VDelegate& other) const
    {
        return (&callee_ == &other.callee_) && (func_ == other.func_);
    }
    bool operator!= (const VDelegate& other) const
    {
        return !((*this) == other);
    }

private:
    T& callee_;
    func_type func_;
};

/**
 * specialization for const member functions
 */
template <typename T, typename R, typename... Params>
class VDelegate<R (T::*)(Params...) const>
{
public:
    typedef R (T::*func_type)(Params...) const;

	VDelegate(func_type func, const T& callee)
        : callee_(callee)
        , func_(func)
    {}

    R operator()(Params... args) const
    {
        return (callee_.*func_)(args...);
    }

    bool operator==(const VDelegate& other) const
    {
        return (&callee_ == &other.callee_) && (func_ == other.func_);
    }
    bool operator!= (const VDelegate& other) const
    {
        return !(*this == other);
    }

private:
    const T& callee_;
    func_type func_;
};

/**
 * specialization for free functions
 *
 * \tparam R            return type of the function that gets captured
 * \tparam params       variadic template list for possible arguments
 *                      of the captured function
 */
template <typename R, typename... Params>
class VDelegate<R (*)(Params...)>
{
public:
    typedef R (*func_type)(Params...);

	VDelegate(func_type func)
        : func_(func)
    {}

    R operator()(Params... args) const
    {
        return (*func_)(args...);
    }

    bool operator==(const VDelegate& other) const
    {
        return func_ == other.func_;
    }
    bool operator!= (const VDelegate& other) const
    {
        return !((*this) == other);
    }

private:
    func_type func_;
};

/**
 * function to deduce template parameters from call-context
 */
template <typename F, typename T>
VDelegate<F> MakeDelegate(F func, T& obj)
{
    return VDelegate<F>(func, obj);
}

template <typename T>
VDelegate<T> MakeDelegate(T func)
{
    return VDelegate<T>(func);
}

// a little backward compatilbility layer
#define DELEGATE MakeDelegate
#define DELEGATE_CONST MakeDelegate
#define DELEGATE_FREE MakeDelegate
