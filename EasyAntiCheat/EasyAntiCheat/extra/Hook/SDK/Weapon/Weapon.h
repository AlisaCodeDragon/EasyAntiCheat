#pragma once
#include<Windows.h>
#include<cstdint>

class Weapon
{
public:

	uintptr_t PrimaryWeaponAmmo(const uintptr_t moduleBase)
	{
		return *(uintptr_t*)(moduleBase + 0x0);
	}

	uintptr_t isPrimaryWeaponActive(const uintptr_t moduleBase)
	{
		return PrimaryWeaponAmmo(moduleBase) != NULL;
	}

	uintptr_t ModifyPrimaryWeaponAmmoCount(const uintptr_t moduleBase, int value)
	{
		return *(uintptr_t*)(moduleBase + 0x0) = value;
	}

}; Weapon* pWeapon;