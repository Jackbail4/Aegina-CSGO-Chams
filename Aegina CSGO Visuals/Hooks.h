#pragma once
#include <Windows.h>
#include <fstream>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

#include "Textures.h"

#include "Esp.h"

#include "detours.h"
#pragma comment(lib, "detours.lib")

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef HRESULT(__stdcall* tEndScene)(IDirect3DDevice9* pDevice);

typedef void(__fastcall* tDrawModelExecute)(void*, int, void* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hooks {
	static HWND hwnd;
	static WNDPROC oWndProc;
	static bool init = false;

	static tEndScene pEndScene;
	static tDrawModelExecute oDrawModelExecute;

	bool InitHooks(void);
	bool RemoveHooks(void);

	static bool ShowMenu = true;

	static void __fastcall hkDrawModelExecute(void* _this, int edx, void* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld);
	static HRESULT __stdcall hkEndScene(IDirect3DDevice9* pDevice);
}

inline LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);