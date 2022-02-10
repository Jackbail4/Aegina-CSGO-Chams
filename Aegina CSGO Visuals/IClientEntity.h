#pragma once
#include "VirtualMethod.h"
#include "Vectors.h"

class IClientEntity {
public:
    VIRTUAL_METHOD(const void*, getModel, 8, (), (this + sizeof(uintptr_t)))
    VIRTUAL_METHOD(bool, isDormant, 9, (), (this + sizeof(uintptr_t) * 2))
    VIRTUAL_METHOD(int, index, 10, (), (this + sizeof(uintptr_t) * 2))

    VIRTUAL_METHOD(const Vec3&, getAbsOrigin, WIN32_LINUX(10, 12), (), (this))
    VIRTUAL_METHOD(void, setModelIndex, WIN32_LINUX(75, 111), (int index), (this, index))
    VIRTUAL_METHOD(int, getTeamNumber, WIN32_LINUX(88, 128), (), (this))
    VIRTUAL_METHOD(int, health, WIN32_LINUX(122, 167), (), (this))
    VIRTUAL_METHOD(bool, isAlive, WIN32_LINUX(156, 208), (), (this))
    VIRTUAL_METHOD(bool, isPlayer, WIN32_LINUX(158, 210), (), (this))
    VIRTUAL_METHOD(bool, isWeapon, WIN32_LINUX(166, 218), (), (this))
    VIRTUAL_METHOD(IClientEntity*, getActiveWeapon, WIN32_LINUX(268, 331), (), (this))
    VIRTUAL_METHOD(int, getWeaponType, WIN32_LINUX(455, 523), (), (this))

    Vec3 GetBonePosition(int boneId) {
        uintptr_t BoneMatrix = *(uintptr_t*)(this + 0x26A8);
        Vec3 pos;
        pos.x = *(float*)(BoneMatrix + 0x30 * boneId + 0x0C);
        pos.y = *(float*)(BoneMatrix + 0x30 * boneId + 0x1C);
        pos.z = *(float*)(BoneMatrix + 0x30 * boneId + 0x2C);
        return pos;
    }
    int GetArmor(void) {
        return *(int*)(this + 0x117CC);
    }
    int GetFlags(void) {
        return *(int*)(this + 0x104);
    }
};
