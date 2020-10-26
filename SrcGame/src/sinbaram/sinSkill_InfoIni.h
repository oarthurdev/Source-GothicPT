
#include <Windows.h>
#include <stdio.h>

struct MECH_INFO{

	int size, code;

	
	int E_Shield_BlockRate[10];
	int E_Shield_UseTime[10];
	int E_Shield_UseMana[10];

	int Mechanic_Bomb_Damage[10][2];
	int Mechanic_Bomb_Attack_Range[10];
	int Mechanic_Bomb_UseMana[10];

	int P_Absorb[10][2];
	int P_Absorb_UseTime[10];
	int P_Absor_bUseMana[10];

	int PlusPoison[10];

	
	int G_Smash_Attack_Rate[10];
	int G_Smash_Attack_Rage[10];
	int G_Smash_UseMana[10];

	int Maximize_Damage[10];
	int Maximize_Weapon_Speed[10];
	int Maximize_Time[10];
	int Maximize_UseMana[10];

	int Automation_Damage[10];
	int Automation_Speed[10];
	int Automation_Time[10];
	int Automation_UseMana[10];

	int Spark_Damage[10][2];
	int Spark_Area[10];
	int Spark_UseMana[10];

	
	int Metal_Armor_Defense[10];
	int Metal_Armor_Time[10];
	int Metal_Armor_UseMana[10];

	int Grand_Smash_AttackRate[10];
	int Grand_Smash_Damage[10];
	int Grand_Smash_UseMana[10];

	int M_Weapon_Mastey[10];

	int Spark_Shield_Damage[10];
	int Spark_Shield_Defense[10];
	int Spark_Shield_Time[10];
	int Spark_Shield_UseMana[10];

	
	int Impulsion_LightingDamage[10][2];
	int Impulsion_Range[10];
	int Impulsion_LightingNum[10];
	int Impulsion_UseMana[10];

	int Compulsion_AddAbsorb[10];
	int Compulsion_Area[10];
	int Compulsion_Time[10];
	int Compulsion_UseMana[10];

	int Magnetic_Sphere_AddDamage[10][2];
	int Magnetic_Sphere_Area[10];
	int Magnetic_Sphere_AttackDelay[10];
	int Magnetic_Sphere_Time[10];
	int Magnetic_Sphere_UseMana[10];

	int Metal_Golem_Damage[10][2];
	int Metal_Golem_Hit[10];
	int Metal_Golem_Defense[10];
	int Metal_Golem_Life[10];
	int Metal_Golem_UseMana[10];
};

struct FIGHTER_INFO{
	

	int size, code;

	int Melee_Mastery_DamagePercent[10];

	int PlusFire[10];

	int Raving_Damage[10];
	int Ravind_Speed[10];
	float Raving_UseLife[10];
	int Raving_UseMana[10];

	int Impact_Attack_Rating[10];
	int Impact_Damage[10];
	int Impact_UseMana[10];

	
	int T_Impact_Damage[10];
	int T_Impact_Hit[10];
	int T_Impact_UseMana[10];

	int B_Swing_Damage[10];
	int B_Swing_Critical[10];
	int B_Swing_UseMana[10];

	int Roar_Range[10];
	int Roar_Time[10];
	int Roar_UseMana[10];

	int R_Zecram_Damage[10];
	int R_Zecram_UseMana[10];

	
	int Concentration_AttackRate[10];
	int Concentration_Time[10];
	int Concentration_UseMana[10];

	int A_Crash_Damage[10];
	int A_Crash_AttackRate[10];
	int A_Crash_UseMana[10];

	int Swift_Axe_Speed[10];
	int Swift_Axe_Time[10];
	int Swift_Axe_UseMana[10];

	int B_Crash_Damage[10];
	int B_Crash_DemonDamage[10];
	int B_Crash_UseMana[10];

	
	int Destoryer_DamagePercent[10];
	int Destoryer_AddCritical[10];
	int Destoryer_UseMana[10];

	int Berserker_AddAttack[10];
	int Berserker_SubAbsorb[10];
	int Berserker_Time[10];
	int Berserker_UseMana[10];

	int Cyclone_Strike_DamagePercent[10];
	int Cyclone_Strike_AreaDamage[10][2];
	int Cyclone_Strike_AttackNum[10];
	int Cyclone_Strike_Area[10];
	int Cyclone_Strike_UseMana[10];

	int Boost_Health_Life[10];
};

struct PIKE_INFO{

	int size, code;

	
	int Pike_Wind_Damage[10][2];
	int Pike_Wind_Push_Lenght[10];
	int Pike_Wind_Throw_Height[10];
	int Pike_Wind_UseMana[10];

	int PlusIce[10];

	int Critical_Hit_Critical[10];
	int Critical_Hit_UseMana[10];

	int Jumping_Crash_UseMana[10];
	int Jumping_Crash_Attack_Rating[10];
	int Jumping_Crash_Damage[10];

	
	int G_Pike_Damage[10][2];
	int G_Pike_Range[10];
	int G_Pike_UseMana[10];
	int G_Pike_Time[10];

	int Tornado_Damage[10];
	int Tornado_Stun[10];
	int Tornado_Range[10];
	int Tornado_UseMana[10];

	int W_D_Mastery_Block[10];

	int Expansion_Size[10];
	int Expansion_UseMana[10];
	int Expansion_Damage[10];

	
	int VenomSpear_Damage[10][2];
	int VenomSpear_Num[10];
	int VenomSpear_Time[10];
	int VenomSpear_Range[10];
	int VenomSpear_UseMana[10];

	float Vanish_Speed[10];
	int Vanish_Damage[10];
	int Vanish_Range[10];
	int Vanish_Time[10];
	int Vanish_UseMana[10];

	int Critical_Mastery_Critical[10];

	int Chain_Lance_Damage[10];
	int Chain_Lance_UseMana[10];

	
	int Assassin_Eye_AddCritical[10];
	int Assassin_Eye_M_SubCritical[10];
	int Assassin_Eye_Time[10];
	int Assassin_Eye_UseMana[10];

	int Charging_Strike_DamagePercent[10];
	int Charging_Strike_CharingDamagePercent[10];
	int Charging_Strike_Time[10];
	int Charging_Strike_UseMana[10];

	int Vague_EvasionPercent[10];
	int Vague_Time[10];
	int Vague_UseMana[10];

	int Shadow_Master_DamagePercent[10];
	int Shadow_Master_AddHit[10];
	int Shadow_Master_ShadowNum[10];
	int Shadow_Master_UseMana[10];
};

struct ARCHER_INFO{

	int size, code;

	
	int Scout_Hawk_Attack_Rate[10];
	int Scout_Hawk_UseTime[10];
	int Scout_Hawk_UseMana[10];

	int S_Mastery_DamagePercent[10];

	int Wind_Arrow_Speed[10];
	int Wind_Arrow_Damage[10];
	int Wind_Arrow_UseMana[10];

	int Perfect_Aim_Attack_Rate[10];
	int Perfect_Aim_Damage[10];
	int Perfect_Aim_Damage_LV[10];
	int Perfect_Aim_UseMana[10];

	
	int D_Eye_Attack_Rate[10];

	int Falcon_Damage[10][2];
	int Falcon_Time[10];
	int Falcon_UseMana[10];

	int A_Rage_ArrowNum[10];
	int A_Rage_Damage[10];
	int A_Rage_Area[10];
	int A_Rage_UseMana[10];

	int Avalanche_Speed[10];
	int Avalanche_Damage[10];
	int Avalanche_ArrowNum[10];
	int Avalanche_UseMana[10];

	
	int Elemental_Shot_Ice[10][2];
	int Elemental_Shot_Fire[10][2];
	int Elemental_Shot_Lightning[10][2];
	int Elemental_Shot_UseMana[10];

	int Golden_Falcon_Damage[10];
	float Golden_Falcon_LifeRegen[10];
	int Golden_Falcon_Time[10];
	int Golden_Falcon_UseMana[10];

	int BombShot_Damage[10];
	int BombShot_DemonDamage[10];
	int BombShot_AddDamage[10][2];
	int BombShot_Area[10];
	int BombShot_UseMana[10];

	int Perforation_Damage[10];
	int Perforation_Critical[10];
	int Perforation_UseMana[10];
	int Perforation_Attack_Range[10];

	
	int Recall_Wolverin_Damage[10][2];
	int Recall_Wolverin_Hit[10];
	int Recall_Wolverin_Defense[10];
	int Recall_Wolverin_Life[10];
	int Recall_Wolverin_UseMana[10];

	int Evasion_Mastery_AddPercent[10];

	int Phoenix_Shot_DamagePercent[10];
	int Phoenix_Shot_Time[10];
	int Phoenix_Shot_UseMana[10];

	int Force_Of_Nature_AddDamage[10];
	int Force_Of_Nature_AddHit[10];
	int Force_Of_Nature_FalconAddDamage[10];
	int Force_Of_Nature_Time[10];
	int Force_Of_Nature_UseMana[10];
};

struct KINA_INFO{

	int size, code;

	
	int Sword_Blast_UseMana[10];
	int Sword_Blast_Damage[10][2];
	int Sword_Blast_ShootingRange[10];

	int HolyBody_UseMana[10];
	int HolyBody_Absorb[10];
	int HolyBody_Time[10];

	int P_Traning_Stamina[10];

	int D_Crash_UseMana[10];
	int D_Crash_Damage[10];
	int D_Crash_Critical[10];

	
	int Holy_Valor_Damage[10];
	int Holy_Valor_Time[10];
	int Holy_Valor_Mana[10];

	int Brandish_Range[10];
	int Brandish_Damage[10];
	int Brandish_Mana[10];

	int Piercing_Damage[10];
	int Piercing_Attack_Rating[10];
	int Piercing_Mana[10];

	int Drastic_Spirit_Defense[10];
	int Drastic_Spirit_Time[10];
	int Drastic_Spirit_Mana[10];

	
	int Sword_Mastery_DamagePercent[10];

	int D_Inhalation_Life[10];
	int D_Inhalation_Block[10];
	int D_Inhalation_Time[10];
	int D_Inhalation_UseMana[10];

	int H_Incantation_Success[10];
	int H_Incantation_AddLife[10];
	int H_Incantation_Time[10];
	int H_Incantation_UseMana[10];

	int Grand_Cross_Damage[10];
	int Grand_Cross_AttackRate[10];
	int Grand_Cross_UndeadDamage[10];
	int Grand_Cross_UseMana[10];

	
	int Divine_Piercing_DamagePercent[10];
	int Divine_Piercing_AddHit[10];
	int Divine_Piercing_AttackNum[10];
	int Divine_Piercing_UseMana[10];

	int Godly_Shield_AbsorbPercent[10];
	int Godly_Shield_Time[10];
	int Godly_Shield_UseMana[10];

	int God_Bless_AddDamage[10];
	int God_Bless_Time[10];
	int God_Bless_UseMana[10];

	int Sword_Of_Justice_DamagePercent[10];
	int Sword_Of_Justice_Area[10];
	int Sword_Of_Justice_UseMana[10];

	///TIER5
	int Soul_Breaker_DamagePercent[10];
	int Soul_Breaker_AttackRate[10];
	int Soul_Breaker_UseMana[10];
};

struct ATA_INFO{

	int size, code;

	
	int S_Strike_UseMana[10];
	int S_Strike_Damage[10][2];

	int Farina_UseMana[10];
	int Farina_Speed[10];
	int Farina_AttackRate[10];

	int T_Mastery_Damage[10];

	int V_Spear_UseMana[10];
	int V_Spear_Damage[10][2];

	
	int Windy_Attack_Rating[10];
	int Windy_Time[10];
	int Windy_Mana[10];

	int Twist_Javelin_Damage[10];
	int Twist_Javelin_Attack_Rating[10];
	int Twist_Javelin_Mana[10];

	int Soul_Sucker_Absorb[10];
	int Soul_Sucker_Mana[10];

	int Fire_Javelin_Damage[10][2];
	int Fire_Javelin_Mana[10];

	
	int Split_Javelin_AttackNum[10];
	int Split_Javelin_Damage[10];
	int Split_Javelin_AttackRate[10];
	int Split_Javelin_UseMana[10];

	int T_Of_Valhalla_Damage[10];
	int T_Of_Valhalla_Time[10];
	int T_Of_Valhalla_UseMana[10];

	int Lightning_Javelin_Damage[10][2];
	int Lightning_Javelin_UseMana[10];

	int Storm_Javelin_Damage[10];
	int Storm_Javelin_UseMana[10];

	
	int Hall_Of_Valhalla_AddEvation[10];
	int Hall_Of_Valhalla_Time[10];
	int Hall_Of_Valhalla_UseMana[10];

	int X_Rage_DamagePercent[10];
	int X_Rage_Area[10];
	int X_Rage_UseMana[10];

	int Frost_Javelin_IceAddDamage[10][2];
	int Frost_Javelin_SpeedSubPercent[10];
	int Frost_Javelin_IceTime[10];
	int Frost_Javelin_Time[10];
	int Frost_Javelin_UseMana[10];

	int Vengeance_DamagePercent[10];
	int Vengeance_AddCritical[10];
	int Vengeance_Range[10];
	int Vengeance_UseMana[10];
};

struct SACER_INFO{

	int size, code;

	
	int Healing_UseMana[10];
	int Healing_Heal[10][2];

	int HolyBolt_UseMana[10];
	int HolyBolt_Damage[10];

	int M_Spark_UseMana[10];
	int M_Spark_Damage[10];
	int M_Spark_Num[10];

	int HolyMind_UseMana[10];
	int HolyMind_DecDamage[10];
	int HolyMind_Time[10];

	
	float Meditation_Regen[10];

	int Divine_Lightning_Damage[10];
	int Divine_Lightning_Num[10];
	int Divine_Lightning_Mana[10];

	int Holy_Reflection_Return_Damage[10];
	int Holy_Reflection_Time[10];
	int Holy_Reflection_Mana[10];

	int Grand_Healing[10][2];
	int Grand_Healing_Range[10];
	int Grand_Healing_Mana[10];

	
	int Vigor_Ball_Damage[10];
	int Vigor_Ball_UseMana[10];

	int Resurrection_Percent[10];
	int Resurrection_Exp[10];
	int Resurrection_UseMana[10];

	int Extinction_Percent[10];
	int Extinction_Amount[10];
	int Extinction_UseMana[10];

	int Virtual_Life_Percent[10];
	int Virtual_Life_Time[10];
	int Virtual_Life_UseMana[10];

	
	int Glacial_Spike_Damage[10];
	int Glacial_Spike_Area[10];
	int Glacial_Spike_UseMana[10];

	float Regeneration_Field_LifeRegen[10];
	float Regeneration_Field_ManaRegen[10];
	int Regeneration_Field_Time[10];
	int Regeneration_Field_Area[10];
	int Regeneration_Field_UseMana[10];

	int Chain_Lightning_Damage[10];
	int Chain_Lightning_Num[10];
	int Chain_Lightning_Range[10];
	int Chain_Lightning_UseMana[10];

	int Summon_Muspell_Damage[10][2];
	int Summon_Muspell_Attack_Delay[10];
	int Summon_Muspell_UndeadAbsorbPercent[10];
	int Summon_Muspell_BlockPercent[10];
	int Summon_Muspell_Time[10];
	int Summon_Muspell_UseMana[10];
};

struct MAGE_INFO{

	int size, code;

	
	int Agony_UseMana[10];
	int Agony_ConvLife[10];

	int FireBolt_UseMana[10];
	int FireBolt_Damage[10];

	int Zenith_UseMana[10];
	int Zenith_Element[10];
	int Zenith_Time[10];

	int FireBall_UseMana[10];
	int FireBall_Damage[10];
	int FireBall_Range[10];
	int FireBall_Area[10];

	
	int Mental_Mastery_Mana[10];

	int Watornado_Damage[10];
	int Watornado_Range[10];
	int Watornado_Mana[10];
	int Watornado_Area[10];

	int Enchant_Weapon_Damage_Ice[10][2];
	int Enchant_Weapon_Damage_Fire[10][2];
	int Enchant_Weapon_Damage_Lightning[10][2];
	int Enchant_Weapon_Time[10];
	int Enchant_Weapon_Mana[10];

	int Dead_Ray_Damage[10];
	int Dead_Ray_Range[10];
	int Dead_Ray_Mana[10];

	
	int Energy_Shield_DecDamage[10];
	int Energy_Shield_Time[10];
	int Energy_Shield_UseMana[10];

	int Diastrophism_Damage[10];
	int Diastrophism_Area[10];
	int Diastrophism_UseMana[10];

	float Spirit_Elemental_RegenMana[10];
	int Spirit_Elemental_Damage[10];
	int Spirit_Elemental_Time[10];
	int Spirit_Elemental_UseMana[10];

	int Dancing_Sword_IceDamage[10][2];
	int Dancing_Sword_FireDamage[10][2];
	int Dancing_Sword_AttackDelay[10];
	int Dancing_Sword_Time[10];
	int Dancing_Sword_UseMana[10];

	
	int Fire_Elemental_Damage[10][2];
	int Fire_Elemental_Hit[10];
	int Fire_Elemental_Life[10];
	int Fire_Elemental_UseMana[10];

	int Flame_Wave_FireDamage[10];
	int Flame_Wave_Area[10];
	int Flame_Wave_UseMana[10];

	int Distortion_SpeedSubPercent[10];
	int Distortion_DamageSubPercent[10];
	int Distortion_Area[10];
	int Distortion_Time[10];
	int Distortion_UseMana[10];

	int Meteo_Damage[10];
	int Meteo_Area[10];
	int Meteo_UseMana[10];
};

struct ASSASSIN_INFO
{
	int size, code;

	int Stinger_Damage[10];
	int Stingger_UseMana[10];
	int Double_Blow_Damage[10];
	int DoubleBlow_UseMana[10];
	int D_Mastery_DamagePercent[10];
	int Wisp_UseTime[10];
	int Wisp_Reduction[10];
	int Wisp_UseMana[10];
	int VenomThorn_Time[10];
	int VenomThorn_Chance[10];
	int VenomThorn_Damage[10];
	int VenomThorn_UseMana[10];
	int Alas_Time[10];
	int Alas_UseMana[10];
	int Alas_EvasionPercent[10];
	int SoulChock_Range[10];
	int SoulChock_Time[10];
	int SoulChock_UseMana[10];
	int A_Mastery_AddPercent[10];
	int A_Mastery_AddPercent2[10];
	int SoreSword_Damage[10];
	int SoreSword_UseMana[10];
	int BeatUp_Damage[10];
	int BeatUp_Area[10];
	int BeatUp_UseMana[10];
	int Inpes_Time[10];
	int Inpes_Speed[10];
	int Inpes_UseMana[10];
	int Blind_Time[10];
	int Blind_Damage[10];
	int Blind_Range[10];
	int Blind_UseMana[10];
	int FrostWind_Damage[10];
	int FrostWind_UseMana[10];
	int F_Mastery_Critical[10];
	int ViolenceStab_Damage[10];
	int ViolenceStab_UseMana[10];
	int PastingShadow_Damage[10];
	int PastingShadow_UseMana[10];
};

struct SHAMAN_INFO
{
	int size, code;

	int DarkBolt_Damage[10];
	int DarkBolt_UseMana[10];
	int InnerPeace_Add[10];
	int SoulManacle_Time[10];
	int SoulManacle_UseMana[10];
	int Haunt_Damage[10];
	int Haunt_UseMana[10];
	int Scratch_Damage[10];
	int Scratch_UseMana[10];
	int Judgement_Damage[10];
	int Judgement_Range[10];
	int Judgement_UseMana[10];
	int DarkWave_Damage[10];
	int DarkWave_Area[10];
	int DarkWave_Range[10];
	int DarkWave_UseMana[10];
	int CurseLazy_SpeedSubPercent[10];
	int CurseLazy_DamageSubPercent[10];
	int CurseLazy_Area[10];
	int CurseLazy_Time[10];
	int CurseLazy_UseMana[10];
	int SpiritualFlare_Damage[10];
	int SpiritualFlare_Area[10];
	int SpiritualFlare_Range[10];
	int SpiritualFlare_UseMana[10];
	int ChasingHunt_Time[10];
	int ChasingHunt_Area[10];
	int ChasingHunt_UseMana[10];
	int LandGhost_Damage[10];
	int LandGhost_Range[10];
	int LandGhost_UseMana[10];
	int MourningOfPray_Damage[10];
	int MourningOfPray_Range[10];
	int MourningOfPray_UseMana[10];
	int BloodyKnight_Damage[10][2];
	int BloodyKnight_Hit[10];
	int BloodyKnight_Defense[10];
	int BloodyKnight_Life[10];
	int BloodyKnight_UseMana[10];
	int BloodyKnight_Time[10];
	int AdventMigal_AttackRate[10];
	int AdventMigal_UseMana[10];
	int AdventMigal_Time[10];
	int RainMaker_Absorb[10];
	int RainMaker_UseMana[10];
	int RainMaker_Time[10];
	int AdventMidranda_UseMana[10];
	int AdventMidranda_Speed[10];
	int AdventMidranda_Time[10];
};

#include "sinLinkHeader.h"

int LoadSkillInfo();

int ReLoadSkillInfo(rsPLAYINFO *lpPlayInfo);
