#include "../Hooks.h"

MAKE_HOOK(CL_ReadPackets, g_Pattern.Find(L"engine.dll", L"55 8B EC 83 EC ? 8B 0D ? ? ? ? 53 33 DB 89 5D ? 89 5D ? 8B 41 ? 89 5D ? 89 5D ? 85 C0 74 ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 53 53 53 53 8D 4D ? 51 50 8B 40 ? FF D0 8B 45 ? 83 C4 ? 8B 0D ? ? ? ? 89 45 ? 8B 45 ? 89 45 ? 8B 59 ? 8B 0D ? ? ? ? 89 5D ? FF 15 ? ? ? ? 88 45 ? 84 C0 74 ? 8B 0D ? ? ? ? 6A ? 6A ? 68 ? ? ? ? 6A ? 68 ? ? ? ? FF 15 ? ? ? ? 8B 0D"), void, __cdecl, 
	bool bFinalTick)
{
	CGlobalVarsBase gBackup{};
	memcpy(&gBackup, I::GlobalVars, sizeof(CGlobalVarsBase));
	Hook.Original<FN>()(bFinalTick);
	memcpy(I::GlobalVars, &gBackup, sizeof(CGlobalVarsBase));
	I::GlobalVars->tickcount++;
}