#pragma once
#include "Routine.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
long __stdcall DrawMenu(LPDIRECT3DDEVICE9 pDevice);

HWND hWND;
WNDPROC oWndProc;

bool init;
bool show;

namespace HooksD3D {
    namespace Defs {
        typedef long(__stdcall* BeginScene_t)(IDirect3DDevice9*);
        typedef long(__stdcall* EndScene_t)(IDirect3DDevice9*);
        typedef long(__stdcall* Present_t)(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
        typedef long(__stdcall* Reset_t)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
    }

    namespace Origs {
        Defs::BeginScene_t oBeginScene;
        Defs::EndScene_t oEndScene;
        Defs::Present_t oPresentScene;
        Defs::Reset_t oReset;
        LONG_PTR oWndProc;
    }

    HRESULT __stdcall BeginScene(IDirect3DDevice9* pDevice);
    HRESULT __stdcall EndScene(IDirect3DDevice9* pDevice);
    HRESULT __stdcall Present(IDirect3DDevice9* pDevice, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion);
    HRESULT __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
    LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    BOOL bHooksPlaced = false;

    BOOL PlaceHooks();
}

HRESULT __stdcall HooksD3D::BeginScene(IDirect3DDevice9* pDevice)
{
    static BOOL bIsImguiInitialized = false;

    if (!bIsImguiInitialized) {
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        D3DDEVICE_CREATION_PARAMETERS params = { 0 };
        pDevice->GetCreationParameters(&params);
        ImGui_ImplWin32_Init(params.hFocusWindow);
        ImGui_ImplDX9_Init(pDevice);
        pDevice->GetCreationParameters(&params);
        oWndProc = (WNDPROC)SetWindowLongPtr(params.hFocusWindow, GWL_WNDPROC, (LONG_PTR)WndProc);

        bIsImguiInitialized = true;
    }

    return HooksD3D::Origs::oBeginScene(pDevice);
}

HRESULT __stdcall HooksD3D::EndScene(IDirect3DDevice9* pDevice)
{
    return HooksD3D::Origs::oEndScene(pDevice);
}

HRESULT __stdcall HooksD3D::Present(IDirect3DDevice9* pDevice, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion)
{
    // Menu
    DrawMenu(pDevice);

    return HooksD3D::Origs::oPresentScene(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT __stdcall HooksD3D::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return HooksD3D::Origs::oReset(pDevice, pPresentationParameters);
}

LRESULT __stdcall HooksD3D::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) && show) {
        return true;
    }
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL HooksD3D::PlaceHooks() {
    if (!bHooksPlaced) {
        DWORD dwD3DBase = (DWORD)GetModuleHandleA(_xor_("d3d9.dll").c_str());
        if (!dwD3DBase) return false;

        DWORD dwD3DDevice = PatternScan(dwD3DBase, _xor_("C7 06 ? ? ? ? 89 86 ? ? ? ? 89 86").c_str(), false);
        if (!dwD3DDevice) return false;

        PDWORD dwD3DvTable = (PDWORD)(*(PDWORD)(dwD3DDevice + 2));
        if (!dwD3DvTable) return false;

        if (MH_OK != MH_CreateHook((LPVOID)dwD3DvTable[42], (PVOID)EndScene, (LPVOID*)&Origs::oEndScene)) {
            printf(_xor_("unable to hook endscene\n").c_str());
        }

        if (MH_OK != MH_CreateHook((LPVOID)dwD3DvTable[41], (PVOID)BeginScene, (LPVOID*)&Origs::oBeginScene)) {
            printf(_xor_("unable to hook beginscene\n").c_str());
        }

        if (MH_OK != MH_CreateHook((LPVOID)dwD3DvTable[16], (PVOID)Reset, (LPVOID*)&Origs::oReset)) {
            printf(_xor_("unable to hook reset\n").c_str());
        }

        if (MH_OK != MH_CreateHook((LPVOID)dwD3DvTable[17], (PVOID)Present, (LPVOID*)&Origs::oPresentScene)) {
            printf(_xor_("unable to hook present\n").c_str());
        }

        if (MH_OK != MH_EnableHook(MH_ALL_HOOKS)) {
            printf(_xor_("Unable to enable D3D hooks\n").c_str());
            return false;
        }

        hWND = FindWindowW(_xor_(L"Combat_Arms").c_str(), _xor_(L"CombatArms").c_str());
        if (!hWND) {
            printf(_xor_("Unable to find window\n").c_str());
            return false;
        }

        bHooksPlaced = true;
    }
    return bHooksPlaced;
}