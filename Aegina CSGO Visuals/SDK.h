#include <Windows.h>

#include "Vectors.h"
#include "ImGui/imgui.h"

#include "IClientEntity.h"
#include "IClientEntityList.h"
#include "cdll_int.h"
#include "MaterialSystem.h"
#include "IVModeInfoClient.h"
#include "IVModelRender.h"
#include "Convar.h"

typedef void* (__cdecl* tCreateInterface)(const char* name, int* returnCode);

namespace SDK {
	namespace Init {
		static void* GetInterface(const char* DllName, const char* InterfaceName);
		bool SetupSDK(void);
	}
	namespace Helper {
		float GetDistance(IClientEntity* Entity);
		const char* GetName(IClientEntity* Entity);
		bool WorldToScreen(Vec3 Pos3D, ImVec2& Pos2D);
		IClientEntity* GetLocalPlayer();
		bool isValidPlayer(IClientEntity* Entity);
		bool isValidEntity(IClientEntity* Entity);
	}
	namespace Convar {
		bool InitConvar(void);
		inline bool bWeaponGlow = false;
		inline bool bGrenadePreview = false;
		inline bool bPlayerUfo = false;
		inline bool bShowPlayerInfo = false;
		inline ConVar* WeaponGlow = nullptr;
		inline ConVar* GrenadePreview = nullptr;
		inline ConVar* PlayerUfo = nullptr;
		inline ConVar* ShowPlayerInfo = nullptr;
	}
	inline void* ClientDllAddr;
	inline IClientEntityList* pIClientEntityList;
	inline IVEngineClient013* pIVEngineClient013;
	inline MaterialSystem* pMaterialSystem;
	inline IClientEntity* LocalPlayer;
	inline IVModelInfoClient* pIVModelInfoClient;
	inline IVModelRender* pIVModelRender;
	inline Cvar* pCvar;
}
