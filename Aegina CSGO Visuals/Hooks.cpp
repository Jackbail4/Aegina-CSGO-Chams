#include "Hooks.h"

bool Hooks::InitHooks(void){
	hwnd = FindWindowA(0, "Counter-Strike: Global Offensive - Direct3D 9");

	oWndProc = (WNDPROC)SetWindowLongPtrA(hwnd, GWL_WNDPROC, (LONG_PTR)WndProc);

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	IDirect3DDevice9* pDevice = nullptr;
	D3DPRESENT_PARAMETERS D3Dparams;
	D3Dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3Dparams.hDeviceWindow = hwnd;
	D3Dparams.Windowed = true;
	HRESULT Device = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3Dparams.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3Dparams, &pDevice);
	if (Device != S_OK) {
		D3Dparams.Windowed = false;
		pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3Dparams.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3Dparams, &pDevice);
		if (Device != S_OK)
			return false;
		
	}

	void** vTable = *(void***)(pDevice);

	pDevice->Release();
	pD3D->Release();

	SDK::Init::SetupSDK();

	pEndScene = (tEndScene)DetourFunction((PBYTE)vTable[42], (PBYTE)hkEndScene);
	oDrawModelExecute = (tDrawModelExecute)DetourFunction((*(PBYTE**)(SDK::pIVModelRender))[21], (PBYTE)hkDrawModelExecute);

	SDK::pIVEngineClient013->clientCmdUnrestricted("say discord.gg/dExJ9Sck7n <3");

	return true;
}

bool Hooks::RemoveHooks(void){
	DetourRemove((PBYTE)pEndScene, (PBYTE)hkEndScene);
	DetourRemove((PBYTE)oDrawModelExecute, (PBYTE)hkDrawModelExecute);
	return true;
}

static void __fastcall Hooks::hkDrawModelExecute(void* _this, int edx, void* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld){
	if (pInfo.pModel) {
		const char* modelName = SDK::pIVModelInfoClient->GetModelName(pInfo.pModel);

		if (Esp::Opt::Wpn::Chams) {
			if (std::strstr(modelName, "weapon") && !std::strstr(modelName, "arms")) {
				Material* mat = SDK::pMaterialSystem->findMaterial("debug/debugambientcube");

				mat->colorModulate(Esp::Opt::Wpn::Col[0], Esp::Opt::Wpn::Col[1], Esp::Opt::Wpn::Col[2]);
				mat->alphaModulate(1.f);

				SDK::pIVModelRender->ForcedMaterialOverride(mat);
				oDrawModelExecute(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);

				SDK::pIVModelRender->ForcedMaterialOverride(nullptr);
				return;
			}
		}

		IClientEntity* Entity = SDK::pIClientEntityList->GetClientEntity(pInfo.entity_index);
		if (SDK::Helper::isValidEntity(Entity)) {
			if (SDK::Helper::isValidPlayer(Entity)) {
				if (std::strstr(modelName, "player")) {
					if (Esp::Opt::Enm::Chams::Chams) {
						if (Entity->getTeamNumber() != SDK::Helper::GetLocalPlayer()->getTeamNumber()) {
							Material* mat = SDK::pMaterialSystem->findMaterial(Esp::Opt::Enm::Chams::SelectedStyle);

							mat->setMaterialVarFlag(MaterialVarFlag::IGNOREZ, true);

							mat->colorModulate(Esp::Opt::Enm::Chams::Col[0], Esp::Opt::Enm::Chams::Col[1], Esp::Opt::Enm::Chams::Col[2]);
							mat->alphaModulate(1.f);

							SDK::pIVModelRender->ForcedMaterialOverride(mat);
							oDrawModelExecute(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);

							SDK::pIVModelRender->ForcedMaterialOverride(nullptr);
							return;
						}
					}
					if (Esp::Opt::Frn::Chams::Chams) {
						if (Entity->getTeamNumber() == SDK::Helper::GetLocalPlayer()->getTeamNumber()) {
							Material* mat = SDK::pMaterialSystem->findMaterial(Esp::Opt::Frn::Chams::SelectedStyle);

							mat->setMaterialVarFlag(MaterialVarFlag::IGNOREZ, true);

							mat->colorModulate(Esp::Opt::Frn::Chams::Col[0], Esp::Opt::Frn::Chams::Col[1], Esp::Opt::Frn::Chams::Col[2]);
							mat->alphaModulate(1.f);

							SDK::pIVModelRender->ForcedMaterialOverride(mat);
							oDrawModelExecute(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);

							SDK::pIVModelRender->ForcedMaterialOverride(nullptr);
							return;
						}
					}
				}
			}
		}
	}
	oDrawModelExecute(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);
}

static HRESULT __stdcall Hooks::hkEndScene(IDirect3DDevice9* pDevice){
	if (!init) {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Arial.ttf", 20.f, 0, io.Fonts->GetGlyphRangesJapanese());
		ImGuiStyle* style = &ImGui::GetStyle();
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX9_Init(pDevice);
		D3DXCreateTextureFromFileInMemory(pDevice, Texture::LogoRaw, sizeof(Texture::LogoRaw), &Texture::Logo);
		init = true;
	}

	ImGui_ImplDX9_Init(pDevice);
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ShowMenu) {
		ImGui::Begin("Aegina CSGO Visuals", &ShowMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::Image((ImTextureID)Texture::Logo, ImVec2{ 25,25 });
		ImGui::SameLine();
		ImGui::Text("Project: https://github.com/Jackbail4/Aegina-CSGO-Visuals");
		ImGui::Separator();
		Esp::Menu();
		if (ImGui::BeginTabItem("Other")) {
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Checkbox("Weapon Glow", &SDK::Convar::bWeaponGlow);
			ImGui::Checkbox("Grenade preview", &SDK::Convar::bGrenadePreview);
			ImGui::Checkbox("UFO", &SDK::Convar::bPlayerUfo);
			ImGui::Checkbox("Show player info", &SDK::Convar::bShowPlayerInfo);
			ImGui::Checkbox("Weapon Chams", &Esp::Opt::Wpn::Chams);
			ImGui::ColorEdit3("###Color", Esp::Opt::Wpn::Col, ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSidePreview);
			ImGui::Text("Current Map: %s", SDK::pIVEngineClient013->getLevelName());
			if (ImGui::Button("Quit", ImVec2{ 200,50 })) {
				ExitProcess(EXIT_SUCCESS);
			}
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
		ImGui::End();
	}

	if (SDK::Helper::GetLocalPlayer() != nullptr) {
		Esp::RunESP();
		SDK::Convar::InitConvar();
	}


	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	if (GetAsyncKeyState(VK_F11)) {
		RemoveHooks();
	}
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		ShowMenu = !ShowMenu;
	}

	return pEndScene(pDevice);
}

inline LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProcA(Hooks::oWndProc, hWnd, uMsg, wParam, lParam);
}
