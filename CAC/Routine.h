#pragma once
#include "CheatVisual.h"

namespace Routine
{
	void Handle(LPDIRECT3DDEVICE9 pDevice);
}

void Routine::Handle(LPDIRECT3DDEVICE9 pDevice)
{
	// Call cheat handle
	CheatVisual::Handle(pDevice);
}