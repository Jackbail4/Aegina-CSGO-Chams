#pragma once
#include <Windows.h>
#include <string>

#include "SDK.h"
#include "ImGui/imgui.h"

#define Float3ToImColor(Col) ImColor{Col[0], Col[1], Col[2]}

namespace Esp {
	inline const char* ChamsStyles[] = {
		"debug/debugdrawflat",
		"debug/debugambientcube",
		"models/inventory_items/cologne_prediction/cologne_prediction_glass",
		"models/inventory_items/service_medal_2016/glass_lvl4",
		"models/inventory_items/trophy_majors/gold", 

	};
	namespace Opt {
		namespace Enm {
			namespace Esp{
				static bool Box = false;
				static bool Name = false;
				static bool Lines = false;
				static bool Health = false;
				static bool Armour = false;
				static float Col[3] = {
					1.f,1.f,1.f
				};
			}
			namespace Chams {
				inline bool Chams = false;
				inline float Col[3] = {
					1.f,1.f,1.f
				};
				inline const char* SelectedStyle = "debug/debugdrawflat";
			}
		}
		namespace Frn {
			namespace Esp {
				static bool Box = false;
				static bool Name = false;
				static bool Lines = false;
				static bool Health = false;
				static bool Armour = false;
				static float Col[3] = {
					1.f,1.f,1.f
				};
			}
			namespace Chams {
				inline bool Chams = false;
				inline float Col[3] = {
					1.f,1.f,1.f
				};
				inline const char* SelectedStyle = "debug/debugdrawflat";
			}
		}
		namespace Wpn {
			inline bool Name = false;
			inline bool Chams = false;
			inline float Col[3] = {
					0.f,0.f,1.f
			};
		}
	}

	bool DrawBox(IClientEntity* Entity, ImColor Color);
	bool DrawHealth(IClientEntity* Entity);
	bool DrawName(IClientEntity* Entity, ImColor Color);
	bool DrawArmour(IClientEntity* Entity);
	bool DrawLine(IClientEntity* Entity, ImColor Color);
	bool DrawWeaponName(IClientEntity* Entity, ImColor Color);
	void RunESP(void);
	void Menu(void);
}
