#include <Windows.h>
#include "VirtualMethod.h"

class IVModelInfoClient
{
public:
    VIRTUAL_METHOD(void*, GetModel, 1, (int Index), (this, Index))
    VIRTUAL_METHOD(int, GetModelIndex, 2, (const char* Filename),(this, Filename))
    VIRTUAL_METHOD(const char*, GetModelName, 3, (const void* Model),(this, Model))
};