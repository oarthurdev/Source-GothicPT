

#define SIN2_ATTACK_RATE		0
#define SIN2_DAMAGE				1
#define SIN2_DEFENSE			2
#define SIN2_ABSORB				3
#define SIN2_SPEED				4
#define SIN2_LIFE				5
#define SIN2_MANA				6 
#define SIN2_STAMINA			7 

#define USE_SKILL_MASTERY_COUNT	100



int RequireStateCheck(int Mana);
int ContinueSkillUse(sSKILL *pSkill, int Time);
void CheckContinueSkill();
void SwitchSkill(sSKILL *pSkill);

int F_Stingger();
int F_R_Hit();
int F_Wisp();
int F_V_Throne();
int F_Alas();
int F_S_Shock();
int F_S_Sword();
int F_BeatUp();
int F_Inpes();
int F_Blind();
int F_FrostWind();
int F_ViolenceStab();
int F_PastingShadow();

int F_Extreme_Shield();
int F_Mechanic_Bomb();
int F_Physical_Absorption();
int F_Poison_Attribute();

int F_Great_Smash();
int F_Maximize();
int F_Automation();
int F_Spark();

int F_Metal_Armor();
int F_Grand_Smash();
int F_M_W_Mastery();
int F_Spark_Shield();


int F_Impulsion();
int F_Compulsion();
int F_Magnetic_Sphere();
int F_Metal_Golem();


int F_Melee_Mastery();
int F_Fire_Attribute();
int F_Raving();
int F_Impact();

int F_Triple_Impact();
int F_Brutal_Swing();
int F_Roar();
int F_RageOfZecram();

int F_Concentration();
int F_Avanging_Crash();
int F_Swift_Axe();
int F_Bone_Crash();


int F_Destoryer();
int F_Berserker();
int F_Cyclone_Strike();
int F_Boost_Health();


int F_Pike_Wind();
int F_Ice_Attribute();
int F_Critical_Hit();
int F_Jumping_Crash();

int F_Ground_Pike();
int F_Tornado_Pike();
int F_Weapone_Defence_Mastery();
int F_Expansion();

int F_Venom_Spear();
int F_Vanish();
int F_Critical_Mastery();
int F_Chain_Lance();

int F_Assassin_Eye();
int F_Charging_Strike();
int F_Vague();
int F_Shadow_Master();


int F_Scout_Hawk();
int F_Shooting_Mastery();
int F_Wind_Arrow();
int F_Perfect_Aim();

int F_Dions_Eye();
int F_Falcon();
int F_Arrow_of_Rage();
int F_Avalanche();

int F_E_Shot();
int F_G_Falcon();
int F_B_Shot();
int F_Perforation();


int F_Recall_Wolverin();
int F_Evasion_Mastery();
int F_Phoenix_Shot();
int F_Force_Of_Nature();






extern int E_Shield_BlockRate[10];
extern int E_Shield_UseTime[10];
extern int E_Shield_UseMana[10];


extern int Mechanic_Bomb_Damage[10][2];
extern int Mechanic_Bomb_Attack_Range[10];
extern int Mechanic_Bomb_UseMana[10];


extern int P_Absorb[10][2];
extern int P_Absorb_UseTime[10];
extern int P_Absor_bUseMana[10];


extern int PlusPoison[10];


extern int G_Smash_Attack_Rate[10];
extern int G_Smash_Attack_Rage[10];
extern int G_Smash_UseMana[10];


extern int Maximize_Damage[10];
extern int Maximize_Weapon_Speed[10];
extern int Maximize_Time[10];
extern int Maximize_UseMana[10];


extern int Automation_Damage[10];
extern int Automation_Speed[10];
extern int Automation_Time[10];
extern int Automation_UseMana[10];


extern int Spark_Damage[10][2];
extern int Spark_Area[10];
extern int Spark_UseMana[10];


extern int Metal_Armor_Defense[10];
extern int Metal_Armor_Time[10];
extern int Metal_Armor_UseMana[10];


extern int Grand_Smash_AttackRate[10];
extern int Grand_Smash_Damage[10];
extern int Grand_Smash_UseMana[10];


extern int M_Weapon_Mastey[10];


extern int Spark_Shield_Damage[10];
extern int Spark_Shield_Defense[10];
extern int Spark_Shield_Time[10];
extern int Spark_Shield_UseMana[10];



extern int Impulsion_LightingDamage[10][2];
extern int Impulsion_Range[10];
extern int Impulsion_LightingNum[10];
extern int Impulsion_UseMana[10];


extern int Compulsion_AddAbsorb[10];
extern int Compulsion_Area[10];
extern int Compulsion_Time[10];
extern int Compulsion_UseMana[10];


extern int Magnetic_Sphere_AddDamage[10][2];
extern int Magnetic_Sphere_Area[10];
extern int Magnetic_Sphere_AttackDelay[10];
extern int Magnetic_Sphere_Time[10];
extern int Magnetic_Sphere_UseMana[10];


extern int Metal_Golem_Damage[10][2];
extern int Metal_Golem_Hit[10];
extern int Metal_Golem_Defense[10];
extern int Metal_Golem_Life[10];
extern int Metal_Golem_UseMana[10];



extern int Melee_Mastery_DamagePercent[10];


extern int PlusFire[10];


extern int Raving_Damage[10];
extern int Ravind_Speed[10];
extern float Raving_UseLife[10];
extern int Raving_UseMana[10];


extern int Impact_Attack_Rating[10];
extern int Impact_Damage[10];
extern int Impact_UseMana[10];


extern int T_Impact_Damage[10];
extern int T_Impact_Hit[10];
extern int T_Impact_UseMana[10];


extern int B_Swing_Damage[10];
extern int B_Swing_Critical[10];
extern int B_Swing_UseMana[10];


extern int Roar_Range[10];
extern int Roar_Time[10];
extern int Roar_UseMana[10];


extern int R_Zecram_Damage[10];
extern int R_Zecram_UseMana[10];


extern int Concentration_AttackRate[10];
extern int Concentration_Time[10];
extern int Concentration_UseMana[10];


extern int A_Crash_Damage[10];
extern int A_Crash_AttackRate[10];
extern int A_Crash_UseMana[10];


extern int Swift_Axe_Speed[10];
extern int Swift_Axe_Time[10];
extern int Swift_Axe_UseMana[10];


extern int B_Crash_Damage[10];
extern int B_Crash_DemonDamage[10];
extern int B_Crash_UseMana[10];




extern int Destoryer_DamagePercent[10];
extern int Destoryer_AddCritical[10];
extern int Destoryer_UseMana[10];


extern int Berserker_AddAttack[10];
extern int Berserker_SubAbsorb[10];
extern int Berserker_Time[10];
extern int Berserker_UseMana[10];


extern int Cyclone_Strike_DamagePercent[10];
extern int Cyclone_Strike_AreaDamage[10][2];
extern int Cyclone_Strike_AttackNum[10];
extern int Cyclone_Strike_Area[10];
extern int Cyclone_Strike_UseMana[10];


extern int Boost_Health_Life[10];




extern int Pike_Wind_Damage[10][2];
extern int Pike_Wind_Push_Lenght[10];
extern int Pike_Wind_Throw_Height[10];
extern int Pike_Wind_UseMana[10];


extern int PlusIce[10];


extern int Critical_Hit_Critical[10];
extern int Critical_Hit_UseMana[10];


extern int Jumping_Crash_UseMana[10];
extern int Jumping_Crash_Attack_Rating[10];
extern int Jumping_Crash_Damage[10];


extern int G_Pike_Damage[10][2];
extern int G_Pike_Range[10];
extern int G_Pike_UseMana[10];
extern int G_Pike_Time[10];


extern int Tornado_Damage[10];
extern int Tornado_Stun[10];
extern int Tornado_Range[10];
extern int Tornado_UseMana[10];


extern int W_D_Mastery_Block[10];


extern int Expansion_Size[10];
extern int Expansion_UseMana[10];
extern int Expansion_Damage[10];


extern int VenomSpear_Damage[10][2];
extern int VenomSpear_Num[10];
extern int VenomSpear_Time[10];
extern int VenomSpear_Range[10];
extern int VenomSpear_UseMana[10];

extern float Vanish_Speed[10];
extern int Vanish_Damage[10];
extern int Vanish_Range[10];
extern int Vanish_Time[10];
extern int Vanish_UseMana[10];


extern int Critical_Mastery_Critical[10];


extern int Chain_Lance_Damage[10];

extern int Chain_Lance_UseMana[10];



extern int Assassin_Eye_AddCritical[10];
extern int Assassin_Eye_M_SubCritical[10];
extern int Assassin_Eye_Time[10];
extern int Assassin_Eye_UseMana[10];


extern int Charging_Strike_DamagePercent[10];
extern int Charging_Strike_CharingDamagePercent[10];
extern int Charging_Strike_Time[10];
extern int Charging_Strike_UseMana[10];


extern int Vague_EvasionPercent[10];
extern int Vague_Time[10];
extern int Vague_UseMana[10];


extern int Shadow_Master_DamagePercent[10];
extern int Shadow_Master_AddHit[10];
extern int Shadow_Master_ShadowNum[10];
extern int Shadow_Master_UseMana[10];




extern int Scout_Hawk_Attack_Rate[10];
extern int Scout_Hawk_UseTime[10];
extern int Scout_Hawk_UseMana[10];


extern int S_Mastery_DamagePercent[10];


extern int Wind_Arrow_Speed[10];
extern int Wind_Arrow_Damage[10];
extern int Wind_Arrow_UseMana[10];



extern int Perfect_Aim_Attack_Rate[10];
extern int Perfect_Aim_Damage[10];
extern int Perfect_Aim_Damage_LV[10];
extern int Perfect_Aim_UseMana[10];


extern int D_Eye_Attack_Rate[10];


extern int Falcon_Damage[10][2];
extern int Falcon_Time[10];
extern int Falcon_UseMana[10];


extern int A_Rage_ArrowNum[10];
extern int A_Rage_Damage[10];
extern int A_Rage_Area[10];
extern int A_Rage_UseMana[10];


extern int Avalanche_Speed[10];
extern int Avalanche_Damage[10];
extern int Avalanche_ArrowNum[10];
extern int Avalanche_UseMana[10];


extern int Elemental_Shot_Ice[10][2];
extern int Elemental_Shot_Fire[10][2];
extern int Elemental_Shot_Lightning[10][2];
extern int Elemental_Shot_UseMana[10];


extern int   Golden_Falcon_Damage[10];
extern float Golden_Falcon_LifeRegen[10];
extern int   Golden_Falcon_Time[10];
extern int   Golden_Falcon_UseMana[10];


extern int BombShot_Damage[10];
extern int BombShot_DemonDamage[10];
extern int BombShot_AddDamage[10][2];
extern int BombShot_Area[10];
extern int BombShot_UseMana[10];


extern int Perforation_Damage[10];
extern int Perforation_Critical[10];
extern int Perforation_UseMana[10];
extern int Perforation_Attack_Range[10];



extern int Recall_Wolverin_Damage[10][2];
extern int Recall_Wolverin_Hit[10];
extern int Recall_Wolverin_Defense[10];
extern int Recall_Wolverin_Life[10];
extern int Recall_Wolverin_UseMana[10];


extern int Evasion_Mastery_AddPercent[10];


extern int   Phoenix_Shot_DamagePercent[10];
extern int   Phoenix_Shot_Time[10];
extern int   Phoenix_Shot_UseMana[10];


extern int Force_Of_Nature_AddDamage[10];
extern int Force_Of_Nature_AddHit[10];
extern int Force_Of_Nature_FalconAddDamage[10];
extern int Force_Of_Nature_Time[10];
extern int Force_Of_Nature_UseMana[10];




extern int sinMasterSkill_Money[16];
extern int sinMasterSkill_PlusMoney[16];



extern int SkillTextColor[10];


extern int NotUseSkillElement[3];
extern int sinMasteryIncreaIndex[16];



extern int C_Skill_HpPoint[10];
extern int C_Skill_AttPercent[10];
extern int C_Skill_EvaPercent[10];

extern int Stinger_Damage[10];
extern int Stingger_UseMana[10];
extern int Double_Blow_Damage[10];
extern int DoubleBlow_UseMana[10];
extern int D_Mastery_DamagePercent[10];
extern int Wisp_UseTime[10];
extern int Wisp_Reduction[10];
extern int Wisp_UseMana[10];
extern int VenomThorn_Time[10];
extern int VenomThorn_Chance[10];
extern int VenomThorn_Damage[10];
extern int VenomThorn_UseMana[10];
extern int Alas_Time[10];
extern int Alas_UseMana[10];
extern int Alas_EvasionPercent[10];
extern int SoulChock_Range[10];
extern int SoulChock_Time[10];
extern int SoulChock_UseMana[10];
extern int A_Mastery_AddPercent[10];
extern int A_Mastery_AddPercent2[10];
extern int SoreSword_Damage[10];
extern int SoreSword_UseMana[10];
extern int BeatUp_Damage[10];
extern int BeatUp_Area[10];
extern int BeatUp_UseMana[10];
extern int Inpes_Time[10];
extern int Inpes_Speed[10];
extern int Inpes_UseMana[10];
extern int Blind_Time[10];
extern int Blind_Damage[10];
extern int Blind_Range[10];
extern int Blind_UseMana[10];
extern int FrostWind_Damage[10];
extern int FrostWind_UseMana[10];
extern int F_Mastery_Critical[10];
extern int ViolenceStab_Damage[10];
extern int ViolenceStab_UseMana[10];
extern int PastingShadow_Damage[10];
extern int PastingShadow_UseMana[10];
