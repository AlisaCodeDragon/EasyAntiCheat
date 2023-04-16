#pragma once
#include"../extra/Thread/Thread.h"
#include"../extra/Hook/hook.h"

VOID WINAPI Bytes(const HINSTANCE hInstance, LPVOID hBytes)
{
	try
	{
		CreateHook->hkGameEngine<uintptr_t>((uintptr_t)_HASH(GetModuleHandleA).get()(xorstr_("")));
		CreateHook->hkInterface<DWORD>("", 450, 500);
	}
	catch (std::exception& error_msg) {
		_HASH(MessageBoxA).get()(NULL, xorstr_("Failed"), xorstr_("Failed"), NULL);
		_HASH(FreeLibraryAndExitThread).get()(hInstance, 0);
	}
	
	while (!_HASH(GetAsyncKeyState).get()(VK_END))
		std::this_thread::sleep_for(std::chrono::seconds(420));

	if (_HASH(GetAsyncKeyState).get()(VK_END))
	{
		_HASH(FreeLibraryAndExitThread).get()(hInstance, 0);
	}
}

VOID WINAPI call_hook()
{
	pThread->NtWindowCreateThreadEx((LPTHREAD_START_ROUTINE)Bytes, NULL, NULL);
}

auto APIENTRY DllMain(const HINSTANCE hInstance, DWORD lpReasons, LPVOID hBuffer) -> BOOL
{
	if (lpReasons == DLL_PROCESS_ATTACH)
	{
		_HASH(DisableThreadLibraryCalls).get()(hInstance);
		call_hook();
	}

	return TRUE;
}