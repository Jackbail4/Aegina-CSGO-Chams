#include "Esp.h"

bool Esp::DrawBox(IClientEntity* Entity, ImColor Color) {
	ImVec2 Head2D, Pos2D;
	if (!SDK::Helper::WorldToScreen(Vec3{ Entity->getAbsOrigin().x, Entity->getAbsOrigin().y ,Entity->GetBonePosition(8).z + 10 }, Head2D)) return false;
	if (!SDK::Helper::WorldToScreen(Entity->getAbsOrigin(), Pos2D)) return false;

	float height = Head2D.y - Pos2D.y;
	height /= 3.5;

	ImVec2 tl, br;
	tl = ImVec2{ Head2D.x - height, Head2D.y };
	br = ImVec2{ Pos2D.x + height, Pos2D.y };
	
	ImGui::GetBackgroundDrawList()->AddRect(tl, br, Color);
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2{ tl.x + 1, tl.y + 1 }, ImVec2{ br.x + 1, br.y + 1 }, ImColor{ 0,0,0 });

	return true;
}

bool Esp::DrawHealth(IClientEntity* Entity) {
	ImVec2 Head2D, Pos2D;
	if (!SDK::Helper::WorldToScreen(Vec3{ Entity->getAbsOrigin().x, Entity->getAbsOrigin().y ,Entity->GetBonePosition(8).z + 10 }, Head2D))return false;
	if (!SDK::Helper::WorldToScreen(Entity->getAbsOrigin(), Pos2D)) return false;

	float height = Head2D.y - Pos2D.y;
	float DrawAmount = height / 100 * Entity->health();
	height /= 2.5;

	ImVec2 bl = ImVec2{ Pos2D.x - height, Pos2D.y };

	float g = Entity->health() / 100.f, r = 1.f - g;

	ImGui::GetBackgroundDrawList()->AddLine(bl, ImVec2{ bl.x, bl.y + DrawAmount }, ImColor{ r, g,0.f }, 2.f);
	ImGui::GetBackgroundDrawList()->AddLine(bl, ImVec2{ bl.x + 2, bl.y + DrawAmount + 2}, ImColor{ 0,0,0 }, 1.f);

	ImGui::GetBackgroundDrawList()->AddText(ImVec2{ bl.x, bl.y + DrawAmount - 10 }, ImColor{ 255,255,255 }, std::to_string(Entity->health()).c_str());
	return true;
}

bool Esp::DrawName(IClientEntity* Entity, ImColor Color) {
	ImVec2 Head2D, Pos2D;
	if (!SDK::Helper::WorldToScreen(Vec3{ Entity->getAbsOrigin().x, Entity->getAbsOrigin().y ,Entity->GetBonePosition(8).z + 10 }, Head2D))return false;
	if (!SDK::Helper::WorldToScreen(Entity->getAbsOrigin(), Pos2D)) return false;

	float height = Head2D.y - Pos2D.y;
	height /= 4;
	ImVec2 tl, tr;
	tl = ImVec2{ Head2D.x - height, Head2D.y };
	tr = ImVec2{ Head2D.x + height, Head2D.y };

	int TextSize = (0.0254f / SDK::Helper::GetDistance(Entity)) * (SDK::pIVEngineClient013->worldToScreenMatrix()._12 / ImGui::GetIO().DisplaySize.x);

	ImGui::GetBackgroundDrawList()->AddText(ImVec2{ tr.x, tr.y - 25 }, Color, SDK::Helper::GetName(Entity));
	ImGui::GetBackgroundDrawList()->AddText(ImVec2{ tr.x + 1, tr.y - 24 }, ImColor{ 0,0,0 }, SDK::Helper::GetName(Entity));
	return true;
}

void Esp::Menu(void) {
	if (ImGui::BeginTabBar("Menu")) {
		if (ImGui::BeginTabItem("Enemy")) {
			ImGui::Text("ESP");
			ImGui::Separator();

			ImGui::Checkbox("Box", &Opt::Enm::Esp::Box);
			ImGui::Checkbox("Name", &Opt::Enm::Esp::Name);
			ImGui::Checkbox("Lines", &Opt::Enm::Esp::Lines);
			ImGui::ColorEdit3("Color", Opt::Enm::Esp::Col, ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox("Health", &Opt::Enm::Esp::Health);
			ImGui::Checkbox("Armour", &Opt::Enm::Esp::Armour);

			ImGui::Text("Chams");
			ImGui::Separator();

			ImGui::Checkbox("Chams", &Opt::Enm::Chams::Chams);
			ImGui::ColorEdit3("##Color", Opt::Enm::Chams::Col, ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview);


			if (ImGui::BeginCombo("combo", Opt::Enm::Chams::SelectedStyle)) {
				for (int n = 0; n < IM_ARRAYSIZE(ChamsStyles); n++) {
					bool is_selected = (Opt::Enm::Chams::SelectedStyle == ChamsStyles[n]);
					if (ImGui::Selectable(ChamsStyles[n], is_selected)) {
						Opt::Enm::Chams::SelectedStyle = ChamsStyles[n];
					}
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Friendly")) {
			ImGui::Text("ESP");
			ImGui::Separator();

			ImGui::Checkbox("Box", &Opt::Frn::Esp::Box);
			ImGui::Checkbox("Name", &Opt::Frn::Esp::Name);
			ImGui::Checkbox("Lines", &Opt::Frn::Esp::Lines);
			ImGui::ColorEdit3("Color", Opt::Frn::Esp::Col, ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Checkbox("Health", &Opt::Frn::Esp::Health);
			ImGui::Checkbox("Armour", &Opt::Frn::Esp::Armour);

			ImGui::Text("Chams");
			ImGui::Separator();

			ImGui::Checkbox("Chams", &Opt::Frn::Chams::Chams);
			ImGui::ColorEdit3("##Color", Opt::Frn::Chams::Col, ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview);


			if (ImGui::BeginCombo("##combo", Opt::Frn::Chams::SelectedStyle)) {
				for (int n = 0; n < IM_ARRAYSIZE(ChamsStyles); n++) {
					bool is_selected = (Opt::Frn::Chams::SelectedStyle == ChamsStyles[n]);
					if (ImGui::Selectable(ChamsStyles[n], is_selected)) {
						Opt::Frn::Chams::SelectedStyle = ChamsStyles[n];
					}
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::EndTabItem();
		}
	}
}

bool Esp::DrawLine(IClientEntity* Entity, ImColor Color){
	ImVec2 Pos2D;
	if (!SDK::Helper::WorldToScreen(Vec3{Entity->getAbsOrigin()}, Pos2D))return false;

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2{ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y }, Pos2D, Color, 1.f);
	return true;
}

bool Esp::DrawWeaponName(IClientEntity* Entity, ImColor Color){
	ImVec2 Pos2D;
	if (!SDK::Helper::WorldToScreen(Vec3{ Entity->getAbsOrigin() }, Pos2D)) return false;

	const char* WeaponName = "Error";
	switch (Entity->getWeaponType()) {
	case 0:
		WeaponName = "Knife";
		break;
	case 1:
		WeaponName = "Pistol";
		break;
	case 2:
		WeaponName = "Sub-machine Gun";
		break;
	case 3:
		WeaponName = "Rifle";
		break;
	case 4:
		WeaponName = "Shotgun";
		break;
	case 5:
		WeaponName = "Sniper Rifle";
		break;
	case 6:
		WeaponName = "Machine Gun";
		break;
	case 7:
		WeaponName = "Bomb";
		break;
	case 9:
		WeaponName = "Throwable";
		break;
	}

	ImGui::GetBackgroundDrawList()->AddText(0, 13.f, Pos2D, ImColor{ 255,255,255 }, WeaponName);

	return true;
}

bool Esp::DrawArmour(IClientEntity* Entity){
	ImVec2 Head2D, Pos2D;
	if (!SDK::Helper::WorldToScreen(Vec3{ Entity->getAbsOrigin().x, Entity->getAbsOrigin().y ,Entity->GetBonePosition(8).z }, Head2D)) return false;
	if (!SDK::Helper::WorldToScreen(Vec3{ Entity->getAbsOrigin().x, Entity->getAbsOrigin().y ,Entity->getAbsOrigin().z - 5 }, Pos2D)) return false;

	float height = Head2D.y - Pos2D.y;
	height /= 4;
	ImVec2 bl, br;
	bl = ImVec2{ Pos2D.x - height, Pos2D.y };
	br = ImVec2{ Pos2D.x + height, Pos2D.y };

	float DrawAmount = (bl.x - br.x) / 100 * Entity->GetArmor();

	ImGui::GetBackgroundDrawList()->AddLine(bl, ImVec2{ bl.x - DrawAmount,bl.y }, ImColor{ 0,0,255 });
	return true;
}

void Esp::RunESP(void) {
	for (int i = 0; i != SDK::pIClientEntityList->GetHighestEntityIndex(); i++) {
		IClientEntity* Entity = SDK::pIClientEntityList->GetClientEntity(i);
		if (!SDK::Helper::isValidEntity(Entity))
			continue;

		if (Entity->isWeapon())
			if (Opt::Wpn::Name)
				DrawWeaponName(Entity, Float3ToImColor(Opt::Wpn::Col));

		if (SDK::Helper::isValidPlayer(Entity)) {
			if (Entity->getTeamNumber() != SDK::Helper::GetLocalPlayer()->getTeamNumber()) {
				if (Opt::Enm::Esp::Box)
					DrawBox(Entity, Float3ToImColor(Opt::Enm::Esp::Col));
				if (Opt::Enm::Esp::Name)
					DrawName(Entity, Float3ToImColor(Opt::Enm::Esp::Col));
				if (Opt::Enm::Esp::Health)
					DrawHealth(Entity);
				if (Opt::Enm::Esp::Armour)
					DrawArmour(Entity);
				if (Opt::Enm::Esp::Lines)
					DrawLine(Entity, Float3ToImColor(Opt::Enm::Esp::Col));

			}
			else if (Entity->getTeamNumber() == SDK::Helper::GetLocalPlayer()->getTeamNumber()) {
				if (Opt::Frn::Esp::Box)
					DrawBox(Entity, Float3ToImColor(Opt::Frn::Esp::Col));
				if (Opt::Frn::Esp::Name)
					DrawName(Entity, Float3ToImColor(Opt::Frn::Esp::Col));
				if (Opt::Frn::Esp::Health)
					DrawHealth(Entity);
				if (Opt::Frn::Esp::Armour)
					DrawArmour(Entity);
				if (Opt::Frn::Esp::Lines)
					DrawLine(Entity, Float3ToImColor(Opt::Frn::Esp::Col));
			}
		}
	}
}
