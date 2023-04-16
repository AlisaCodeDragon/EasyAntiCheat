#pragma once
#include"../Protection/global.h"

typedef struct
{
	DWORD64 dwEP;
	PVOID pParam;
}CALL_FUNC, * PCALL_FUNC;
typedef DWORD(*_Function)(VOID* p);

void WINAPI MyFunctionThread(PCALL_FUNC pCMF)
{
	if (pCMF != NULL && pCMF->dwEP != NULL)
	{
		_Function Function = (_Function)pCMF->dwEP;
		Function(pCMF->pParam);
	}
}

class Thread
{
public:
	
	DWORD GetImageSize(DWORD64 Image)
	{
		IMAGE_NT_HEADERS nt_headers = { 0 };
		IMAGE_DOS_HEADER dos_header = { 0 };
		dos_header = *(IMAGE_DOS_HEADER*)Image;
		nt_headers = *(IMAGE_NT_HEADERS*)(Image + dos_header.e_lfanew);
		return nt_headers.OptionalHeader.SizeOfImage;
	}

	HANDLE NtWindowCreateThreadEx(LPTHREAD_START_ROUTINE lpEntryAddr, LPVOID lpParam, LPDWORD lpThreadId)
	{
		const HINSTANCE hModule = _HASH(GetModuleHandleA).get()(xorstr_("ntdll.dll"));
		
		if (hModule)
		{
			DWORD dwImageSize = GetImageSize((DWORD64)hModule);
			BYTE* pImageBytes = (BYTE*)hModule + dwImageSize - 0x400;

			if (pImageBytes)
			{
				DWORD dwProtect;
				_HASH(VirtualProtect).get()(pImageBytes, 0x100, PAGE_EXECUTE_READWRITE, &dwProtect);
				CALL_FUNC* pCMF = (CALL_FUNC*)_HASH(VirtualAlloc).get()(NULL, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
				pCMF->dwEP = (DWORD64)(lpEntryAddr);
				pCMF->pParam = lpParam;
				memcpy((LPVOID)pImageBytes, (LPVOID)MyFunctionThread, 0x100);
				const HANDLE hRemoteThread = _HASH(CreateRemoteThread).get()(GetCurrentProcess(), NULL, 0, (LPTHREAD_START_ROUTINE)pImageBytes, pCMF, NULL, lpThreadId);
				return hRemoteThread;
			}
		}

		return 0;
	}
}; Thread* pThread;

