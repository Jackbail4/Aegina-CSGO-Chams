#pragma once
#include <cstddef>

/*
https://github.com/danielkrupinski/Osiris/blob/master/Osiris/SDK/VirtualMethod.h
osiris <3
*/

template <typename T, std::size_t Idx, typename ...Args>
constexpr T VirtualMethodCall(void* classBase, Args... args) noexcept{
    return (*reinterpret_cast<T(__thiscall***)(void*, Args...)>(classBase))[Idx](classBase, args...);
}

#define VIRTUAL_METHOD(returnType, name, idx, args, argsRaw) \
returnType name args noexcept \
{ \
    return VirtualMethodCall<returnType, idx>argsRaw; \
}

#define WIN32_LINUX(win32, linux) win32