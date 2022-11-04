#include "CritHack.h"
#define MASK_SIGNED 0x7FFFFFFF

// i hate crithack

/* Returns whether random crits are enabled on the server */
bool CCritHack::AreRandomCritsEnabled()
{
	if (static auto tf_weapon_criticals = g_ConVars.FindVar("tf_weapon_criticals"); tf_weapon_criticals)
	{
		return tf_weapon_criticals->GetBool();
	}
	return true;
}

/* Returns whether the crithack should run */
bool CCritHack::IsEnabled()
{
	if (!Vars::CritHack::Active.Value) { return false; }
	if (!AreRandomCritsEnabled()) { return false; }
	if (!I::EngineClient->IsInGame()) { return false; }

	return true;
}

bool CCritHack::IsAttacking(const CUserCmd* pCmd, CBaseCombatWeapon* pWeapon)
{
	if (G::CurItemDefIndex == Soldier_m_TheBeggarsBazooka)
	{
		static bool bLoading = false;

		if (pWeapon->GetClip1() > 0)
		{
			bLoading = true;
		}

		if (!(pCmd->buttons & IN_ATTACK) && bLoading)
		{
			bLoading = false;
			return true;
		}
	}

	else
	{
		if (pWeapon->GetWeaponID() == TF_WEAPON_COMPOUND_BOW || pWeapon->GetWeaponID() == TF_WEAPON_PIPEBOMBLAUNCHER)
		{
			static bool bCharging = false;

			if (pWeapon->GetChargeBeginTime() > 0.0f)
			{
				bCharging = true;
			}

			if (!(pCmd->buttons & IN_ATTACK) && bCharging)
			{
				bCharging = false;
				return true;
			}
		}

		//pssst..
		//Dragon's Fury has a gauge (seen on the weapon model) maybe it would help for pSilent hmm..
		/*
		if (pWeapon->GetWeaponID() == 109) {
		}*/

		else
		{
			if ((pCmd->buttons & IN_ATTACK) && G::WeaponCanAttack)
			{
				return true;
			}
		}
	}

	return false;
}

bool CCritHack::NoRandomCrits()
{
	switch (G::CurItemDefIndex)
	{
		// Scout
		case Scout_s_TheFlyingGuillotine:
		case Scout_s_TheFlyingGuillotineG:
		case Scout_s_BonkAtomicPunch:
		case Scout_s_MadMilk:
		case Scout_s_MutatedMilk:
		{
			return true;
			break;
		}

		// Soldier
		case Soldier_m_TheCowMangler5000:
		case Soldier_m_RocketJumper:
		case Soldier_s_TheBuffBanner:
		case Soldier_s_FestiveBuffBanner:
		case Soldier_s_TheBattalionsBackup:
		case Soldier_s_TheConcheror:
		case Soldier_s_TheBASEJumper:
		case Soldier_s_Gunboats:
		case Soldier_s_TheMantreads:
		case Soldier_t_TheMarketGardener:
		{
			return true;
			break;
		}

		// Pyro
		case Pyro_m_TheBackburner:
		case Pyro_m_FestiveBackburner:
		case Pyro_m_DragonsFury:
		case Pyro_s_TheManmelter:
		case Pyro_s_GasPasser:
		case Pyro_s_ThermalThruster:
		case Pyro_t_NeonAnnihilator:
		case Pyro_t_NeonAnnihilatorG:
		{
			return true;
			break;
		}

		// Demoman
		case Demoman_m_AliBabasWeeBooties:
		case Demoman_m_TheBootlegger:
		case Demoman_s_StickyJumper:
		case Demoman_s_TheCharginTarge:
		case Demoman_s_TheSplendidScreen:
		case Demoman_s_TheTideTurner:
		case Demoman_t_TheEyelander:
		case Demoman_t_FestiveEyelander:
		case Demoman_t_HorselessHeadlessHorsemannsHeadtaker:
		case Demoman_t_NessiesNineIron:
		case Demoman_t_TheClaidheamhMor:
		case Demoman_t_UllapoolCaber:
		case Demoman_t_TheHalfZatoichi:
		case Demoman_t_ThePersianPersuader:
		{
			return true;
			break;
		}

		// Heavy
		case Heavy_s_Sandvich:
		case Heavy_s_TheDalokohsBar:
		case Heavy_s_TheBuffaloSteakSandvich:
		case Heavy_s_Fishcake:
		case Heavy_s_RoboSandvich:
		case Heavy_s_SecondBanana:
		{
			return true;
			break;
		}

		// Engineer
		case Engi_m_TheFrontierJustice:
		case Engi_m_FestiveFrontierJustice:
		case Engi_s_TheShortCircuit:
		case Engi_s_TheWrangler:
		case Engi_s_FestiveWrangler:
		case Engi_s_TheGigarCounter:
		case Engi_t_TheGunslinger:
		case Engi_t_TheSouthernHospitality:
		{
			return true;
			break;
		}

		// Medic
		case Medic_s_MediGun:
		case Medic_s_SilverBotkillerMediGunMkI:
		case Medic_s_GoldBotkillerMediGunMkI:
		case Medic_s_RustBotkillerMediGunMkI:
		case Medic_s_BloodBotkillerMediGunMkI:
		case Medic_s_CarbonadoBotkillerMediGunMkI:
		case Medic_s_DiamondBotkillerMediGunMkI:
		case Medic_s_SilverBotkillerMediGunMkII:
		case Medic_s_GoldBotkillerMediGunMkII:
		case Medic_s_FestiveMediGun:
		case Medic_s_TheKritzkrieg:
		case Medic_s_TheQuickFix:
		case Medic_s_TheVaccinator:
		{
			return true;
			break;
		}

		// Sniper
		case Sniper_m_SniperRifle:
		case Sniper_m_SniperRifleR:
		case Sniper_m_BloodBotkillerSniperRifleMkI:
		case Sniper_m_CarbonadoBotkillerSniperRifleMkI:
		case Sniper_m_DiamondBotkillerSniperRifleMkI:
		case Sniper_m_FestiveSniperRifle:
		case Sniper_m_GoldBotkillerSniperRifleMkI:
		case Sniper_m_GoldBotkillerSniperRifleMkII:
		case Sniper_m_RustBotkillerSniperRifleMkI:
		case Sniper_m_SilverBotkillerSniperRifleMkI:
		case Sniper_m_SilverBotkillerSniperRifleMkII:
		case Sniper_m_TheAWPerHand:
		case Sniper_m_TheMachina:
		case Sniper_m_ShootingStar:
		case Sniper_m_TheBazaarBargain:
		case Sniper_m_TheHitmansHeatmaker:
		case Sniper_m_TheHuntsman:
		case Sniper_m_TheFortifiedCompound:
		case Sniper_m_TheClassic:
		case Sniper_m_TheSydneySleeper:
		case Sniper_s_Jarate:
		case Sniper_s_FestiveJarate:
		case Sniper_s_TheSelfAwareBeautyMark:
		case Sniper_s_CozyCamper:
		case Sniper_s_TheRazorback:
		case Sniper_s_DarwinsDangerShield:
		case Sniper_t_TheBushwacka:
		{
			return true;
			break;
		}

		// Spy
		case Spy_m_TheEnforcer:
		case Spy_m_TheAmbassador:
		case Spy_m_FestiveAmbassador:
		case Spy_m_TheDiamondback:
		case Spy_s_Sapper:
		case Spy_s_FestiveSapper:
		case Spy_s_SapperR:
		case Spy_s_TheRedTapeRecorder:
		case Spy_s_TheRedTapeRecorderG:
		case Spy_s_TheApSapG:
		case Spy_s_TheSnackAttack:
		case Spy_d_DisguiseKitPDA:
		case Spy_t_Knife:
		case Spy_t_KnifeR:
		case Spy_t_TheBlackRose:
		case Spy_t_FestiveKnife:
		case Spy_t_TheWangaPrick:
		case Spy_t_TheSharpDresser:
		case Spy_t_TheBigEarner:
		case Spy_t_ConniversKunai:
		case Spy_t_TheSpycicle:
		case Spy_t_YourEternalReward:
		case Spy_t_SilverBotkillerKnifeMkI:
		case Spy_t_GoldBotkillerKnifeMkI:
		case Spy_t_RustBotkillerKnifeMkI:
		case Spy_t_BloodBotkillerKnifeMkI:
		case Spy_t_CarbonadoBotkillerKnifeMkI:
		case Spy_t_DiamondBotkillerKnifeMkI:
		case Spy_t_SilverBotkillerKnifeMkII:
		case Spy_t_GoldBotkillerKnifeMkII:
		case Spy_w_InvisWatch:
		case Spy_w_InvisWatchR:
		case Spy_w_TheCloakandDagger:
		case Spy_w_TheDeadRinger:
		case Spy_w_EnthusiastsTimepiece:
		case Spy_w_TheQuackenbirdt:
		{
			return true;
			break;
		}
		default: break;
	}
	return false;
}

bool CCritHack::ShouldCrit()
{
	static KeyHelper critKey{ &Vars::CritHack::CritKey.Value };
	if (critKey.Down()) { return true; }
	if (G::CurWeaponType == EWeaponType::MELEE && Vars::CritHack::AlwaysMelee.Value) { return true; }

	//Check if auto melee crit is enabled and player is using melee
	if (Vars::CritHack::AutoMeleeCrit.Value && G::CurWeaponType == EWeaponType::MELEE)
	{
		//Base melee damage
		int MeleeDamage = 65;

		//Could be missing weapons or reskins
		switch (G::CurItemDefIndex)
		{
		case Scout_t_SunonaStick:
		{
			//The Sun on a Stick has a -25% melee damage stat
			MeleeDamage = 26;
			break;
		}
		case Scout_t_TheFanOWar:
		{
			//The Fan O'War has a -75% melee damage stat
			MeleeDamage = 9;
			break;
		}
		case Scout_t_TheWrapAssassin:
		{
			//The Wrap Assassin has a -65% melee damage stat
			MeleeDamage = 12;
			break;
		}
		case Soldier_t_TheDisciplinaryAction:
		case Engi_t_TheJag:
		{
			//The Disciplinary Action and The Jag have a -25% melee damage stat
			MeleeDamage = 49;
			break;
		}
		case Soldier_t_TheEqualizer:
		{
			//The Equalizer does more damage the lower the local player's health is
			break;
		}
		case Pyro_t_HotHand:
		{
			//The Hot Hand has a -20% melee damage stat
			MeleeDamage = 28;
			break;
		}
		case Pyro_t_SharpenedVolcanoFragment:
		case Medic_t_Amputator:
		{
			//The Sharpened Volcano Fragment and The Amputator have a -20% melee damage stat
			MeleeDamage = 52;
			break;
		}
		case Pyro_t_TheBackScratcher:
		{
			//The Back Scratcher has a +25% melee damage stat
			MeleeDamage = 81;
			break;
		}
		case Demoman_t_TheScotsmansSkullcutter:
		{
			//The Scotsmans Skullcutter has a +20% melee damage stat
			MeleeDamage = 78;
			break;
		}
		case Heavy_t_WarriorsSpirit:
		{
			//The Warriors Spirit has a +30% melee damage stat
			MeleeDamage = 85;
			break;
		}
		case Sniper_t_TheTribalmansShiv:
		{
			//The Tribalmans Shiv has a -50% melee damage stat
			MeleeDamage = 37;
			break;
		}
		case Sniper_t_TheShahanshah:
		{
			//The Shahanshah has a -25% melee damage stat when above half health and a +25% when below half health
			//81 if below half health
			//49 if above half health

			// this is currently not coded in, not sure why
			break;
		}
		default: break;
		}

		CBaseEntity* Player;
		if ((Player = I::ClientEntityList->GetClientEntity(G::CurrentTargetIdx)))
		{
			if (G::CurItemDefIndex == Heavy_t_TheHolidayPunch)
			{
				if (Player->OnSolid())
					return true;
			}

			if (MeleeDamage <= Player->GetHealth())
				return true;
		}
	}

	return false;
}

int CCritHack::LastGoodCritTick(const CUserCmd* pCmd)
{
	int retVal = -1;
	bool popBack = false;

	for (const auto& tick : CritTicks)
	{
		if (tick >= pCmd->command_number)
		{
			retVal = tick;
		}
		else
		{
			popBack = true;
		}
	}

	if (popBack)
	{
		CritTicks.pop_back();
	}

	return retVal;
}

void CCritHack::ScanForCrits(const CUserCmd* pCmd, int loops)
{
	static int previousWeapon = 0;
	static int previousCrit = 0;
	static int startingNum = pCmd->command_number;

	const auto& pLocal = g_EntityCache.GetLocal();
	if (!pLocal) { return; }

	const auto& pWeapon = pLocal->GetActiveWeapon();
	if (!pWeapon) { return; }

	if (G::IsAttacking || IsAttacking(pCmd, pWeapon)/* || pCmd->buttons & IN_ATTACK*/)
	{
		return;
	}

	const bool bRescanRequired = previousWeapon != pWeapon->GetIndex();
	if (bRescanRequired)
	{
		startingNum = pCmd->command_number;
		previousWeapon = pWeapon->GetIndex();
		CritTicks.clear();
	}

	if (CritTicks.size() >= 256)
	{
		return;
	}

	//CritBucketBP = *reinterpret_cast<float*>(pWeapon + 0xA54);
	ProtectData = true; //	stop shit that interferes with our crit bucket because it will BREAK it
	const int seedBackup = MD5_PseudoRandom(pCmd->command_number) & MASK_SIGNED;
	for (int i = 0; i < loops; i++)
	{
		const int cmdNum = startingNum + i;
		*I::RandomSeed = MD5_PseudoRandom(cmdNum) & MASK_SIGNED;
		if (pWeapon->WillCrit())
		{
			CritTicks.push_back(cmdNum); //	store our wish command number for later reference
		}
	}
	startingNum += loops;
	ProtectData = false; //	we no longer need to be protecting important crit data

	//*reinterpret_cast<float*>(pWeapon + 0xA54) = CritBucketBP;
	*reinterpret_cast<int*>(pWeapon + 0xA5C) = 0; //	dont comment this out, makes sure our crit mult stays as low as possible
	//	crit mult can reach a maximum value of 3!! which means we expend 3 crits WORTH from our bucket
	//	by forcing crit mult to be its minimum value of 1, we can crit more without directly fucking our bucket
	//	yes ProtectData stops this value from changing artificially, but it still changes when you fire and this is worth it imo.

	*I::RandomSeed = seedBackup;
}

void CCritHack::Run(CUserCmd* pCmd)
{
	if (!IsEnabled()) { return; }

	const auto& pWeapon = g_EntityCache.GetWeapon();
	if (!pWeapon || !pWeapon->CanFireCriticalShot(false)) { return; }

	ScanForCrits(pCmd, 50); //	fill our vector slowly.

	const int closestGoodTick = LastGoodCritTick(pCmd); //	retrieve our wish
	if (IsAttacking(pCmd, pWeapon)) //	is it valid & should we even use it
	{
		if (ShouldCrit())
		{
			if (closestGoodTick < 0) { return; }
			pCmd->command_number = closestGoodTick; //	set our cmdnumber to our wish
			pCmd->random_seed = MD5_PseudoRandom(closestGoodTick) & MASK_SIGNED; //	trash poopy whatever who cares
		}
		else if (Vars::CritHack::AvoidRandom.Value) //	we don't want to crit
		{
			for (int tries = 1; tries < 25; tries++)
			{
				if (std::find(CritTicks.begin(), CritTicks.end(), pCmd->command_number + tries) != CritTicks.end())
				{
					continue; //	what a useless attempt
				}
				pCmd->command_number += tries;
				pCmd->random_seed = MD5_PseudoRandom(pCmd->command_number) & MASK_SIGNED;
				break; //	we found a seed that we can use to avoid a crit and have skipped to it, woohoo
			}
		}
	}
}

void CCritHack::Draw()
{
	if (!Vars::CritHack::Indicators.Value) { return; }
	if (!IsEnabled() || !G::CurrentUserCmd) { return; }

	const auto& pLocal = g_EntityCache.GetLocal();
	if (!pLocal || !pLocal->IsAlive()) { return; }

	const auto& pWeapon = pLocal->GetActiveWeapon();
	if (!pWeapon) { return; }

	const int x = Vars::CritHack::IndicatorPos.c;
	int currentY = Vars::CritHack::IndicatorPos.y;

	const float bucket = *reinterpret_cast<float*>(pWeapon + 0xA54);
	const int seedRequests = *reinterpret_cast<int*>(pWeapon + 0xA5C);

	int longestW = 40;

	if (Vars::Debug::DebugInfo.Value)
	{
		g_Draw.String(FONT_INDICATORS, x, currentY += 15, { 255, 255, 255, 255, }, ALIGN_CENTERHORIZONTAL, tfm::format("%x", reinterpret_cast<float*>(pWeapon + 0xA54)).c_str());
	}
	// Are we currently forcing crits?
	if (ShouldCrit() && NoRandomCrits() == false)
	{
		if (CritTicks.size() > 0)
		{ 
			g_Draw.String(FONT_INDICATORS, x, currentY += 15, { 0, 255, 0, 255 }, ALIGN_CENTERHORIZONTAL, "Forcing Crits");
		}
	}
	//Can this weapon do random crits?
	if (NoRandomCrits() == true)
	{
		g_Draw.String(FONT_INDICATORS, x, currentY += 15, { 255, 95, 95, 255 }, ALIGN_CENTERHORIZONTAL, L"No Random Crits");
	}
	if (CritTicks.size() == 0 && NoRandomCrits() == false)
	{
		g_Draw.String(FONT_INDICATORS, x, currentY += 15, { 255,0,0,255 }, ALIGN_CENTERHORIZONTAL, L"Crit Banned");
	}
	static auto tf_weapon_criticals_bucket_cap = g_ConVars.FindVar("tf_weapon_criticals_bucket_cap");
	const float bucketCap = tf_weapon_criticals_bucket_cap->GetFloat();
	const std::wstring bucketstr = L"Bucket: " + std::to_wstring(static_cast<int>(bucket)) + L"/" + std::to_wstring(static_cast<int>(bucketCap));
	if (NoRandomCrits() == false)
	{
		g_Draw.String(FONT_INDICATORS, x, currentY += 15, { 181, 181, 181, 255 }, ALIGN_CENTERHORIZONTAL, bucketstr.c_str());
	}
	int w, h;
	I::VGuiSurface->GetTextSize(g_Draw.m_vecFonts.at(FONT_INDICATORS).dwFont, bucketstr.c_str(), w, h);
	if (w > longestW)
	{
		longestW = w;
	}
	if (Vars::Debug::DebugInfo.Value && NoRandomCrits() == false)
	{
		const std::wstring seedText = L"m_nCritSeedRequests: " + std::to_wstring(seedRequests);
		const std::wstring FoundCrits = L"Found Crit Ticks: " + std::to_wstring(CritTicks.size());
		const std::wstring commandNumber = L"cmdNumber: " + std::to_wstring(G::CurrentUserCmd->command_number);
		g_Draw.String(FONT_INDICATORS, x, currentY += 15, { 181, 181, 181, 255 }, ALIGN_CENTERHORIZONTAL, seedText.c_str());
		I::VGuiSurface->GetTextSize(g_Draw.m_vecFonts.at(FONT_INDICATORS).dwFont, seedText.c_str(), w, h);
		if (w > longestW)
		{
			longestW = w;
		}
		g_Draw.String(FONT_INDICATORS, x, currentY += 15, { 181, 181, 181, 255 }, ALIGN_CENTERHORIZONTAL, FoundCrits.c_str());
		I::VGuiSurface->GetTextSize(g_Draw.m_vecFonts.at(FONT_INDICATORS).dwFont, FoundCrits.c_str(), w, h);
		if (w > longestW)
		{
			longestW = w;
		}
		g_Draw.String(FONT_INDICATORS, x, currentY += 15, { 181, 181, 181, 255 }, ALIGN_CENTERHORIZONTAL, commandNumber.c_str());
		I::VGuiSurface->GetTextSize(g_Draw.m_vecFonts.at(FONT_INDICATORS).dwFont, commandNumber.c_str(), w, h);
		if (w > longestW)
		{
			longestW = w;
		}
	}
	IndicatorW = longestW * 2;
	IndicatorH = currentY;
}
