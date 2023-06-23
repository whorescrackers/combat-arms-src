#pragma once
namespace CheatVisual
{
	void Handle(LPDIRECT3DDEVICE9 pDevice);

	void Chams();
	void Hp();
	void LegitRecoil();
	void speed();
	void jump();
	void fps();
	void nametag();

}

void CheatVisual::Handle(LPDIRECT3DDEVICE9 pDevice)
{
	Chams();
	Hp();
	LegitRecoil();
	speed();
	jump();
	nametag();
	fps();
	

}

void CheatVisual::speed()
{
	while (GetModuleHandleA(_xor_("cshell.dll").c_str()) == NULL) {}
	static BYTE bBackup[1] = { 0xCC };

	static uint32_t pAddress = 0x38389D60;

	if (bBackup[0] == 0xCC) {
		memcpy(&bBackup[0], (void*)pAddress, 1);
	}

	if (Settings::Visual::fps) {
		memcpy((void*)pAddress, (void*)(PBYTE)_xor_("\x90").c_str(), 1);
	}
	else {
		memcpy((void*)pAddress, &bBackup[0], 1);
	}
}

void CheatVisual::fps()
{
	while (GetModuleHandleA(_xor_("cshell.dll").c_str()) == NULL) {}
	JumpVolumeFX* pJumpVolumeFX = (JumpVolumeFX*)0x3838A614;
	pJumpVolumeFX->WalkVel = 70.0F + (Settings::Visual::speed * 100);
	pJumpVolumeFX->DuckVel = 50.0F + (Settings::Visual::speed * 100);
	pJumpVolumeFX->SRunVel = 285.0F + (Settings::Visual::speed * 100);
	pJumpVolumeFX->BRunVel = 285.0F + (Settings::Visual::speed * 100);
	pJumpVolumeFX->FRunVel = 285.0F + (Settings::Visual::speed * 100);
}

void CheatVisual::nametag()
{
	while (GetModuleHandleA(_xor_("cshell.dll").c_str()) == NULL) {}
	static BYTE bBackup[2] = { 0xCC, 0xCC };

	static uint32_t pAddress = 0x371229F4;

	if (bBackup[0] == 0xCC) {
		memcpy(&bBackup[0], (void*)pAddress, 2);
	}

	if (Settings::Visual::nametag) {
		memcpy((void*)pAddress, (void*)(PBYTE)_xor_("\x90\x90").c_str(), 2);
	}
	else {
		memcpy((void*)pAddress, &bBackup[0], 2);
	}
}

void CheatVisual::jump()
{
	while (GetModuleHandleA(_xor_("cshell.dll").c_str()) == NULL) {}
	JumpVolumeFX* pJumpVolumeFX = (JumpVolumeFX*)0x3838A614;
	pJumpVolumeFX->JumpVel = 330.0F + (Settings::Visual::jump * 70);
}

void CheatVisual::LegitRecoil()
{
	while (GetModuleHandleA(_xor_("cshell.dll").c_str()) == NULL) {}
	static BYTE Backup[4] = { 0xCC };
	static uint32_t Addr = 0x373EA368;

	if (Settings::Visual::lRecoil)
	{
		if (Backup[0] == 0xCC)
		{
			memcpy((void*)Backup, (void*)Addr, 4);
		}
		memcpy((void*)Addr, (void*)(PBYTE)_xor_("\x90\x90\x90\x90").c_str(), 4);
	}
	else {
		if (Backup[0] != 0xCC) {
			memcpy((void*)Addr, (void*)Backup, 4);
		}
	}
}

void CheatVisual::Chams()
{
	while (GetModuleHandleA(_xor_("cshell.dll").c_str()) == NULL) {}
	if (Settings::Visual::nxchams)
	{
		((void(__cdecl*)(const char* Key, float Value))(0x37465DA0))(_xor_("SkelModelStencil").c_str(), 2.0);
	}
	else
	{
		((void(__cdecl*)(const char* Key, float Value))(0x37465DA0))(_xor_("SkelModelStencil").c_str(), 0.0);
	}
}

void CheatVisual::Hp()
{
	while (GetModuleHandleA(_xor_("cshell.dll").c_str()) == NULL) {}
	cWeaponSet* pWeaponSet = (cWeaponSet*)0x3842B600;
	if (Settings::Visual::HpHack)
	{
		if (Settings::Visual::HpHack)
		{
			pWeaponSet->pModel->nZombie = 61;
		}
		else
		{
			pWeaponSet->pModel->nZombie = -1;//try please
		}
	}
}
