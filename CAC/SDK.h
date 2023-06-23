#pragma once
class cWeaponSet
{
public:
    char pad_0000[568];
    class cCharModelInfoMgr* pModel;
    char pad_023C[1604];
};

class cCharModelInfoMgr
{
public:
    char pad_0000[724];
    int32_t nZombie;
    char pad_02D8[364];
};

class JumpVolumeFX
{
public:
	char pad_0000[132]; //0x0000
	float ActivisionDistance; //0x0084
	char pad_0088[176]; //0x0088
	float WalkVel; //0x0138
	char pad_013C[32]; //0x013C
	float SRunVel; //0x015C
	char pad_0160[32]; //0x0160
	float BRunVel; //0x0180
	char pad_0184[32]; //0x0184
	float FRunVel; //0x01A4
	char pad_01A8[32]; //0x01A8
	float JumpVel; //0x01C8
	char pad_01CC[32]; //0x01CC
	float DuckVel; //0x01EC
	char pad_01F0[80]; //0x01F0
}; //Size: 0x0240