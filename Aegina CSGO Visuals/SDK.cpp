#include "SDK.h"

void* SDK::Init::GetInterface(const char* DllName, const char* InterfaceName) {
    tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandleA(DllName), "CreateInterface");
    return CreateInterface(InterfaceName, nullptr);
}

bool SDK::Init::SetupSDK(void) {
    ClientDllAddr = (void*)GetModuleHandleA("client.dll");
    pIClientEntityList = (IClientEntityList*)GetInterface("client.dll", "VClientEntityList003");
    pIVEngineClient013 = (IVEngineClient013*)GetInterface("engine.dll", "VEngineClient014");
    pMaterialSystem = (MaterialSystem*)GetInterface("materialsystem.dll", "VMaterialSystem080");
    pIVModelInfoClient = (IVModelInfoClient*)GetInterface("engine.dll", "VModelInfoClient004");
    pIVModelRender = (IVModelRender*)GetInterface("engine.dll", "VEngineModel016");
    pCvar = (Cvar*)GetInterface("vstdlib.dll", "VEngineCvar007");
    return true;
}

float SDK::Helper::GetDistance(IClientEntity* Entity) {
    return (float)(sqrt(
        ((Entity->getAbsOrigin().x - SDK::Helper::GetLocalPlayer()->getAbsOrigin().x) *
            (Entity->getAbsOrigin().x - SDK::Helper::GetLocalPlayer()->getAbsOrigin().x) +
            ((Entity->getAbsOrigin().y - SDK::Helper::GetLocalPlayer()->getAbsOrigin().y) *
                (Entity->getAbsOrigin().y - SDK::Helper::GetLocalPlayer()->getAbsOrigin().y)) +
            ((Entity->getAbsOrigin().z - SDK::Helper::GetLocalPlayer()->getAbsOrigin().z) *
                (Entity->getAbsOrigin().z - SDK::Helper::GetLocalPlayer()->getAbsOrigin().z))
            )));
}

const char* SDK::Helper::GetName(IClientEntity* Entity) {
    static player_info_s playerInfo;
    SDK::pIVEngineClient013->getPlayerInfo(Entity->index(), playerInfo);

    return playerInfo.name;
}

bool SDK::Helper::WorldToScreen(Vec3 Pos3D, ImVec2& Pos2D) {
    Matrix4x4 matrix= SDK::pIVEngineClient013->worldToScreenMatrix();
    float w = matrix._41 * Pos3D.x + matrix._42 * Pos3D.y + matrix._43 * Pos3D.z + matrix._44;
    if (w < 0.001f)
        return false;

    Pos2D.x = ImGui::GetIO().DisplaySize.x / 2.0f;
    Pos2D.y = ImGui::GetIO().DisplaySize.y / 2.0f;
    Pos2D.x *= 1.0f + (matrix._11 * Pos3D.x + matrix._12 * Pos3D.y + matrix._13 * Pos3D.z + matrix._14) / w;
    Pos2D.y *= 1.0f - (matrix._21 * Pos3D.x + matrix._22 * Pos3D.y + matrix._23 * Pos3D.z + matrix._24) / w;
    return true;
}

IClientEntity* SDK::Helper::GetLocalPlayer() {
   return *(IClientEntity**)((uintptr_t)SDK::ClientDllAddr + 0xDB35EC);
}

bool SDK::Helper::isValidPlayer(IClientEntity* Entity) {
    if (Entity->isDormant())
        return false;
    if (!Entity->isPlayer())
        return false;
    if (!Entity->isAlive())
        return false;

    return true;
}

bool SDK::Helper::isValidEntity(IClientEntity* Entity){
    if (Entity == nullptr)
        return false;
    if (Entity == GetLocalPlayer())
        return false;

    return true;
}

bool SDK::Convar::InitConvar(void){
    WeaponGlow = pCvar->findVar("mp_weapons_glow_on_ground");
    GrenadePreview = pCvar->findVar("cl_grenadepreview");
    PlayerUfo = pCvar->findVar("cl_ragdoll_gravity");
    ShowPlayerInfo = pCvar->findVar("cl_showpos");

    GrenadePreview->SetInt(SDK::Convar::bGrenadePreview);
    WeaponGlow->SetInt(SDK::Convar::bWeaponGlow);
    ShowPlayerInfo->SetInt(SDK::Convar::bShowPlayerInfo);
    SDK::Convar::bPlayerUfo ? PlayerUfo->SetInt(-700) : PlayerUfo->SetInt(200);

    return true;
}
