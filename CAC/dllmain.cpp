#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"
#include "Menu.h"

BOOL DllEntry()
{
    AllocConsole();
    freopen(_xor_("CONIN$").c_str(), _xor_("r").c_str(), stdin);
    freopen(_xor_("CONOUT$").c_str(), _xor_("w").c_str(), stdout);
    freopen(_xor_("CONOUT$").c_str(), _xor_("w").c_str(), stderr);

    if (MH_OK != MH_Initialize()) {
        printf(_xor_("Unable to initialize hook!\n").c_str());
        return false;
    }

    if (!HooksD3D::PlaceHooks())
    {
        printf(_xor_("Unable to hook D3D scenes\n").c_str());
        return false;
    }

    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		HMODULE hMod;
		GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_PIN, _xor_(L"binkw32.dll").c_str(), &hMod);
		return DllEntry();
	}
	return true;
}