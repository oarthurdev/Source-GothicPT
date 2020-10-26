
#define MAX_CONTINUE_SKILL		30


int sinCheckSkillUseOk(sSKILL *lpSkill);
int sinUseManaStamina(sSKILL *lpSkill);
int sinContinueSkillSet(sSKILL *lpSkill);
int sinCheckContinueSkill();
int sinSwitchSkill(sSKILL *pSkill);

int F_DarkBolt();
int F_DarkWave();
int F_CurseLazy();
int F_SpiritualFlare();
int F_SoulManacle();
int F_ChasingHunt();
int F_AdventMigal();
int F_LandGhost();
int F_RainMaker();
int F_Haunt();
int F_Scratch();
int F_RBloodyKnight();
int F_Judgement();
int F_AdventMidranda();
int F_MourningOfPray();

int F_Sword_Blast();
int F_HolyBody();
int F_Physical_Traning();
int F_Double_Crash();

int F_Holy_Valor();
int F_Brandish();
int F_Piercing();
int F_Drastic_Spirit();

int F_S_Mastery();
int F_D_Inhalation();
int F_Holy_Incantation();
int F_Grand_Cross();


int F_Divine_Piercing();
int F_Godly_Shield();
int F_God_Bless();
int F_Sword_Of_Justice();


int F_S_Strike();
int F_Farina();
int F_D_Mastery();
int F_V_Spear();

int F_Windy();
int F_Twist_Javelin();
int F_Soul_Sucker();
int F_Fire_Javelin();

int F_Split_Javelin();
int F_T_Of_Valhalla();
int F_Lightning_Javelin();
int F_Storm_Javelin();


int F_Hall_Of_Valhalla();
int F_X_Rage();
int F_Frost_Javelin();
int F_Vengeance();


int F_Healing();
int F_HolyBolt();
int F_M_Spark();
int F_HolyMind();

int F_Meditation();
int F_Divine_Lightning();
int F_Holy_Reflection();
int F_Grand_Healing();

int F_Vigor_Ball();
int F_Resurrection();
int F_Extinction();
int F_Virtual_Life();


int F_Glacial_Spike();
int F_Regeneration_Field();
int F_Chain_Lightning();
int F_Summon_Muspell();




int F_Agony();
int F_FireBolt();
int F_Zenith();
int F_ZenithFromServer(int Time);
int F_FireBall();

int F_Mental_Mastery();
int F_Watornado();
int F_Enchant_Weapon();
int F_Dead_Ray();

int F_Energy_Shield();
int F_Diastrophism();
int F_Spirit_Elemental();
int F_D_Sword();


int F_Fire_Elemental();
int F_Flame_Wave();
int F_Distortion();
int F_Meteo();

///tier 5

int F_Soul_Breaker();



extern int Sword_Blast_UseMana[10];
extern int Sword_Blast_Damage[10][2];
extern int Sword_Blast_ShootingRange[10];


extern int HolyBody_UseMana[10];
extern int HolyBody_Absorb[10];
extern int HolyBody_Time[10];


extern int P_Traning_Stamina[10];


extern int D_Crash_UseMana[10];
extern int D_Crash_Damage[10];
extern int D_Crash_Critical[10];


extern int Holy_Valor_Damage[10];
extern int Holy_Valor_Time[10];
extern int Holy_Valor_Mana[10];


extern int Brandish_Range[10];
extern int Brandish_Damage[10];
extern int Brandish_Mana[10];


extern int Piercing_Damage[10];
extern int Piercing_Attack_Rating[10];
extern int Piercing_Mana[10];


extern int Drastic_Spirit_Defense[10];
extern int Drastic_Spirit_Time[10];
extern int Drastic_Spirit_Mana[10];




extern int Sword_Mastery_DamagePercent[10];


extern int D_Inhalation_Life[10];
extern int D_Inhalation_Block[10];
extern int D_Inhalation_Time[10];
extern int D_Inhalation_UseMana[10];


extern int H_Incantation_Success[10];
extern int H_Incantation_AddLife[10];
extern int H_Incantation_Time[10];
extern int H_Incantation_UseMana[10];


extern int Grand_Cross_Damage[10];
extern int Grand_Cross_AttackRate[10];
extern int Grand_Cross_UndeadDamage[10];
extern int Grand_Cross_UseMana[10];



extern int  Divine_Piercing_DamagePercent[10];
extern int  Divine_Piercing_AddHit[10];
extern int	Divine_Piercing_AttackNum[10];
extern int  Divine_Piercing_UseMana[10];


extern int Godly_Shield_AbsorbPercent[10];
extern int Godly_Shield_Time[10];
extern int Godly_Shield_UseMana[10];


extern int God_Bless_AddDamage[10];
extern int God_Bless_Time[10];
extern int God_Bless_UseMana[10];


extern int Sword_Of_Justice_DamagePercent[10];
extern int Sword_Of_Justice_Area[10];
extern int Sword_Of_Justice_UseMana[10];




extern int S_Strike_UseMana[10];
extern int S_Strike_Damage[10][2];



extern int Farina_UseMana[10];
extern int Farina_Speed[10];
extern int Farina_AttackRate[10];


extern int T_Mastery_Damage[10];


extern int V_Spear_UseMana[10];
extern int V_Spear_Damage[10][2];


extern int Windy_Attack_Rating[10];
extern int Windy_Time[10];
extern int Windy_Mana[10];


extern int Twist_Javelin_Damage[10];
extern int Twist_Javelin_Attack_Rating[10];
extern int Twist_Javelin_Mana[10];


extern int Soul_Sucker_Absorb[10];
extern int Soul_Sucker_Mana[10];


extern int Fire_Javelin_Damage[10][2];
extern int Fire_Javelin_Mana[10];


extern int Split_Javelin_AttackNum[10];
extern int Split_Javelin_Damage[10];
extern int Split_Javelin_AttackRate[10];
extern int Split_Javelin_UseMana[10];


extern int T_Of_Valhalla_Damage[10];
extern int T_Of_Valhalla_Time[10];
extern int T_Of_Valhalla_UseMana[10];


extern int Lightning_Javelin_Damage[10][2];
extern int Lightning_Javelin_UseMana[10];


extern int Storm_Javelin_Damage[10];
extern int Storm_Javelin_UseMana[10];



extern int Hall_Of_Valhalla_AddEvation[10];
extern int Hall_Of_Valhalla_Time[10];
extern int Hall_Of_Valhalla_UseMana[10];


extern int X_Rage_DamagePercent[10];
extern int X_Rage_Area[10];
extern int X_Rage_UseMana[10];


extern int Frost_Javelin_IceAddDamage[10][2];
extern int Frost_Javelin_SpeedSubPercent[10];
extern int Frost_Javelin_IceTime[10];
extern int Frost_Javelin_Time[10];
extern int Frost_Javelin_UseMana[10];



extern int Vengeance_DamagePercent[10];
extern int Vengeance_AddCritical[10];
extern int Vengeance_Range[10];
extern int Vengeance_UseMana[10];




extern int Healing_UseMana[10];
extern int Healing_Heal[10][2];


extern int HolyBolt_UseMana[10];
extern int HolyBolt_Damage[10];


extern int M_Spark_UseMana[10];
extern int M_Spark_Damage[10];
extern int M_Spark_Num[10];



extern int HolyMind_UseMana[10];
extern int HolyMind_DecDamage[10];
extern int HolyMind_Time[10];


extern float Meditation_Regen[10];


extern int Divine_Lightning_Damage[10];
extern int Divine_Lightning_Num[10];
extern int Divine_Lightning_Mana[10];


extern int Holy_Reflection_Return_Damage[10];
extern int Holy_Reflection_Time[10];
extern int Holy_Reflection_Mana[10];


extern int Grand_Healing[10][2];
extern int Grand_Healing_Range[10];
extern int Grand_Healing_Mana[10];


extern int Vigor_Ball_Damage[10];
extern int Vigor_Ball_UseMana[10];


extern int Resurrection_Percent[10];
extern int Resurrection_Exp[10];
extern int Resurrection_UseMana[10];


extern int Extinction_Percent[10];
extern int Extinction_Amount[10];
extern int Extinction_UseMana[10];


extern int Virtual_Life_Percent[10];
extern int Virtual_Life_Time[10];
extern int Virtual_Life_UseMana[10];



extern int Glacial_Spike_Damage[10];
extern int Glacial_Spike_Area[10];
extern int Glacial_Spike_UseMana[10];


extern float Regeneration_Field_LifeRegen[10];
extern float Regeneration_Field_ManaRegen[10];
extern int   Regeneration_Field_Time[10];
extern int   Regeneration_Field_Area[10];
extern int   Regeneration_Field_UseMana[10];


extern int Chain_Lightning_Damage[10];
extern int Chain_Lightning_Num[10];
extern int Chain_Lightning_Range[10];
extern int Chain_Lightning_UseMana[10];


extern int Summon_Muspell_Damage[10][2];
extern int Summon_Muspell_Attack_Delay[10];
extern int Summon_Muspell_UndeadAbsorbPercent[10];
extern int Summon_Muspell_BlockPercent[10];
extern int Summon_Muspell_Time[10];
extern int Summon_Muspell_UseMana[10];



extern int Agony_UseMana[10];
extern int Agony_ConvLife[10];


extern int FireBolt_UseMana[10];
extern int FireBolt_Damage[10];


extern int Zenith_UseMana[10];
extern int Zenith_Element[10];
extern int Zenith_Time[10];



extern int FireBall_UseMana[10];
extern int FireBall_Damage[10];
extern int FireBall_Range[10];
extern int FireBall_Area[10];


extern int Mental_Mastery_Mana[10];





extern int Watornado_Damage[10];
extern int Watornado_Range[10];
extern int Watornado_Mana[10];
extern int Watornado_Area[10];


extern int Enchant_Weapon_Damage_Ice[10][2];
extern int Enchant_Weapon_Damage_Fire[10][2];
extern int Enchant_Weapon_Damage_Lightning[10][2];
extern int Enchant_Weapon_Time[10];
extern int Enchant_Weapon_Mana[10];



extern int Dead_Ray_Damage[10];
extern int Dead_Ray_Range[10];
extern int Dead_Ray_Mana[10];


extern int Energy_Shield_DecDamage[10];
extern int Energy_Shield_Time[10];
extern int Energy_Shield_UseMana[10];


extern int Diastrophism_Damage[10];
extern int Diastrophism_Area[10];
extern int Diastrophism_UseMana[10];


extern float Spirit_Elemental_RegenMana[10];
extern int Spirit_Elemental_Damage[10];
extern int Spirit_Elemental_Time[10];
extern int Spirit_Elemental_UseMana[10];


extern int Dancing_Sword_IceDamage[10][2];
extern int Dancing_Sword_FireDamage[10][2];
extern int Dancing_Sword_AttackDelay[10];
extern int Dancing_Sword_Time[10];
extern int Dancing_Sword_UseMana[10];




extern int Fire_Elemental_Damage[10][2];
extern int Fire_Elemental_Hit[10];
extern int Fire_Elemental_Life[10];
extern int Fire_Elemental_UseMana[10];


extern int Flame_Wave_FireDamage[10];
extern int Flame_Wave_Area[10];
extern int Flame_Wave_UseMana[10];


extern int Distortion_SpeedSubPercent[10];
extern int Distortion_DamageSubPercent[10];
extern int Distortion_Area[10];
extern int Distortion_Time[10];
extern int Distortion_UseMana[10];


extern int Meteo_Damage[10];
extern int Meteo_Area[10];
extern int Meteo_UseMana[10];

extern int DarkBolt_Damage[10];
extern int DarkBolt_UseMana[10];
extern int InnerPeace_Add[10];
extern int SoulManacle_Time[10];
extern int SoulManacle_UseMana[10];
extern int Haunt_Damage[10];
extern int Haunt_UseMana[10];
extern int Scratch_Damage[10];
extern int Scratch_UseMana[10];
extern int Judgement_Damage[10];
extern int Judgement_Range[10];
extern int Judgement_UseMana[10];
extern int DarkWave_Damage[10];
extern int DarkWave_Area[10];
extern int DarkWave_Range[10];
extern int DarkWave_UseMana[10];
extern int CurseLazy_SpeedSubPercent[10];
extern int CurseLazy_DamageSubPercent[10];
extern int CurseLazy_Area[10];
extern int CurseLazy_Time[10];
extern int CurseLazy_UseMana[10];
extern int SpiritualFlare_Damage[10];
extern int SpiritualFlare_Area[10];
extern int SpiritualFlare_Range[10];
extern int SpiritualFlare_UseMana[10];
extern int ChasingHunt_Time[10];
extern int ChasingHunt_Area[10];
extern int ChasingHunt_UseMana[10];
extern int LandGhost_Damage[10];
extern int LandGhost_Range[10];
extern int LandGhost_UseMana[10];
extern int MourningOfPray_Damage[10];
extern int MourningOfPray_Range[10];
extern int MourningOfPray_UseMana[10];
extern int BloodyKnight_Damage[10][2];
extern int BloodyKnight_Hit[10];
extern int BloodyKnight_Defense[10];
extern int BloodyKnight_Life[10];
extern int BloodyKnight_UseMana[10];
extern int BloodyKnight_Time[10];
extern int AdventMigal_AttackRate[10];
extern int AdventMigal_UseMana[10];
extern int AdventMigal_Time[10];
extern int RainMaker_Absorb[10];
extern int RainMaker_UseMana[10];
extern int RainMaker_Time[10];
extern int AdventMidranda_UseMana[10];
extern int AdventMidranda_Speed[10];
extern int AdventMidranda_Time[10];


///TIER 5 

extern int Soul_Breaker_DamagePercent[10];
extern int Soul_Breaker_AttackRate[10];
extern int Soul_Breaker_UseMana[10];