#include <Windows.h>
#include <iostream>

#include "Hooks.h"

void Init(HMODULE hModule) {
	if (!Hooks::InitHooks())
		MessageBoxA(0, "Failed", "Hooks failed!", MB_OK);

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPARAM lParam) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Init, hModule, 0, nullptr));
	}
	return TRUE;
}