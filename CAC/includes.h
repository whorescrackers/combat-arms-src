#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "XorStr.h"
#include "MinHook/MinHook.h"
#include "MinHook/buffer.h"
#include "MinHook/trampoline.h"

#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"

#include "Settings.h"
#include "SDK.h"
#include "PatternScanner.h"
#include "Renderer.h"