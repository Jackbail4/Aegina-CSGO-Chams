#pragma once
#include "VirtualMethod.h"

class MaterialVar {
public:
        VIRTUAL_METHOD(void, setValue, 4, (float value), (this, value))
        VIRTUAL_METHOD(void, setVectorValue, WIN32_LINUX(11, 12), (float x, float y, float z), (this, x, y, z))
        VIRTUAL_METHOD(void, setVecComponentValue, 26, (float value, int component), (this, value, component))
};

enum MaterialVarFlag {
    NO_DRAW = (1 << 2),
    ZNEARER = (1 << 10),
    FLAT = (1 << 12),
    NOCULL = (1 << 13),
    NOFOG = (1 << 14),
    IGNOREZ = (1 << 15),
    HALFLAMBERT = (1 << 27),
};

class Material {
public:
        VIRTUAL_METHOD(const char*, getName, 0, (), (this))
        VIRTUAL_METHOD(const char*, getTextureGroupName, 1, (), (this))
        VIRTUAL_METHOD(MaterialVar*, findVar, 11, (const char* name, bool* found = nullptr, bool complain = true), (this, name, found, complain))
        VIRTUAL_METHOD(void, incrementReferenceCount, 12, (), (this))
        VIRTUAL_METHOD(void, decrementReferenceCount, 13, (), (this))
        VIRTUAL_METHOD(void, alphaModulate, 27, (float alpha), (this, alpha))
        VIRTUAL_METHOD(void, colorModulate, 28, (float r, float g, float b), (this, r, g, b))
        VIRTUAL_METHOD(void, setMaterialVarFlag, 29, (MaterialVarFlag flag, bool on), (this, flag, on))
        VIRTUAL_METHOD(int, getReferenceCount, 56, (), (this))
        VIRTUAL_METHOD(bool, isPrecached, 70, (), (this))
};
