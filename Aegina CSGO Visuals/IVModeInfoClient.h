#include <Windows.h>
#include "VirtualMethod.h"

class IVModelInfoClient
{
public:
    VIRTUAL_METHOD(const char*, GetModelName, 3, (const void* Model),(this, Model))
};
