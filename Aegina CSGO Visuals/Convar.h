#include <Windows.h>

#include "VirtualMethod.h"

struct ConVar {
        VIRTUAL_METHOD(int, getInt, WIN32_LINUX(13, 16), (), (this))
        VIRTUAL_METHOD(void, SetInt, WIN32_LINUX(16, 19), (int value), (this, value))
};


class Cvar {
public:
        VIRTUAL_METHOD(ConVar*, findVar, 15, (const char* name), (this, name))
};
