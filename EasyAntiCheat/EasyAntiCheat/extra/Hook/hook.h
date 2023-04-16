#pragma once
#include"../Protection/global.h"
#include"SDK/Weapon/Weapon.h"

class Hook
{
public:
	template<class HookEx>
	HookEx* hkGameEngine(const uintptr_t moduleBase)
	{
		while (true)
		{
			if (moduleBase)
			{
				if (pWeapon->isPrimaryWeaponActive(moduleBase))
				{
					pWeapon->ModifyPrimaryWeaponAmmoCount(moduleBase, 1024);
				}
			}
		}
		return nullptr;
	}

	template<class HookEx>
	HookEx* hkInterface(std::string title, int width, int height)
	{
		// start imgui here
		/*
		
		

		*/
		return nullptr;
	}

private:
	uintptr_t dwbase = 0;
	std::string& szWindowTitle;

}; Hook* CreateHook;
