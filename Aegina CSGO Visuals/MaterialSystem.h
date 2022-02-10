#include "Vectors.h"
#include "VirtualMethod.h"
#include "Material.h"

class MaterialSystem {
public:
        VIRTUAL_METHOD(Material*, findMaterial, 84, (const char* materialName, const char* textureGroupName = nullptr, bool complain = true, const char* complainPrefix = nullptr), (this, materialName, textureGroupName, complain, complainPrefix))
        VIRTUAL_METHOD(short, firstMaterial, 86, (), (this))
        VIRTUAL_METHOD(short, nextMaterial, 87, (short handle), (this, handle))
        VIRTUAL_METHOD(short, invalidMaterial, 88, (), (this))
        VIRTUAL_METHOD(Material*, getMaterial, 89, (short handle), (this, handle))
};
