/*Tabela de Skills
Organizada e reestruturada por Zaraki.*/

/*__________________________________________________________________________________________________________________________

SKILLS MECÂNICO
_____________________________________________________________________________________________________________________________*/

// _______________________ TIER 1 _______________________

// Escudo Extremo
int E_Shield_BlockRate[10] = { 2,3,4,5,6,7,8,9,10,11 };
int E_Shield_UseTime[10] = { 30,50,70,90,110,130,150,170,190,210 };
int E_Shield_UseMana[10] = { 12,14,17,20,23,26,30,34,39,44 };

// Bomba Mecânica
int Mechanic_Bomb_Damage[10][2] = { { 5,29 },{ 6,33 },{ 7,37 },{ 8,42 },{ 9,47 },{ 10,53 },{ 11,60 },{ 12,68 },{ 13,77 },{ 14,87 } };
int Mechanic_Bomb_Attack_Range[10] = { 50,53,56,59,62,64,66,68,70,72 };
int Mechanic_Bomb_UseMana[10] = { 8,10,12,14,17,20,23,26,29,33 };

// Absorção Física
int P_Absorb[10][2] = { { 3,4 },{ 3,5 },{ 4,6 },{ 4,7 },{ 5,8 },{ 5,9 },{ 6,10 },{ 6,11 },{ 7,12 },{ 7,13 } };
int P_Absorb_UseTime[10] = { 30,50,70,90,110,130,150,170,190,210 };
int P_Absor_bUseMana[10] = { 20,24,28,32,36,40,44,48,52,56 };

// Resistência a Veneno
int PlusPoison[10] = { 9,17,24,30,35,39,42,44,45,46 };

// _______________________ TIER 2 _______________________

// Grande Golpe
int G_Smash_Attack_Rate[10] = { 60,70,80,90,100,120,140,160,180,200 };

int G_Smash_Attack_Rage[10] = { 8,16,24,32,40,48,56,64,72,80 };

int G_Smash_UseMana[10] = { 22,25,28,31,34,38,42,46,50,54 };

// Maximizar
int Maximize_Damage[10] = { 15,20,25,30,35,40,45,50,55,60 };
int Maximize_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
int Maximize_UseMana[10] = { 26,28,30,33,36,39,43,47,51,56 };

// Automação
int Automation_Damage[10] = { 30,35,40,44,48,52,55,58,63,66 };
int Automation_Speed[10] = { 1,1,1,1,1,2,2,2,2,2 };
int Automation_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
int Automation_UseMana[10] = { 24,27,30,33,36,39,42,45,48,51 };

// Spark
int Spark_Damage[10][2] = { { 30,82 },{ 33,89 },{ 36,96 },{ 38,103 },{ 40,110 },{ 42,117 },{ 44,123 },{ 46,129 },{ 48,135 },{ 50,141 } };
int Spark_Area[10] = { 50,54,58,62,66,70,74,78,82,86 };
int Spark_UseMana[10] = { 26,28,31,34,37,40,44,46,50,55 };

// _______________________ TIER 3 _______________________

// Armadura Metálica
int Metal_Armor_Defense[10] = { 6,11,16,20,24,28,31,34,36,38 };
int Metal_Armor_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Metal_Armor_UseMana[10] = { 32,35,38,41,44,48,52,56,60,64 };

// Golpe Grandioso
int Grand_Smash_AttackRate[10] = { 60,80,100,120,140,160,180,200,220,240 };
int Grand_Smash_Damage[10] = { 43,49,55,61,67,73,79,85,91,97 };
int Grand_Smash_UseMana[10] = { 26,29,32,35,38,41,44,47,50,53 };

// Mestre dos Mecânicos
int M_Weapon_Mastey[10] = { 5,9,13,17,21,25,29,33,37,41 };

// Escudo Espinhoso
int Spark_Shield_Damage[10] = { 30,42,54,66,78,90,102,114,126,138 };
int Spark_Shield_Defense[10] = { 8,16,24,32,40,48,56,64,72,80 };
int Spark_Shield_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Spark_Shield_UseMana[10] = { 34,36,38,41,44,47,51,55,59,64 };

// _______________________ TIER 4 _______________________

// Impulso
int Impulsion_LightingDamage[10][2] = { { 140,180 },{ 150,190 },{ 160,200 },{ 170,210 },{ 180,220 },
{ 190,230 },{ 200,240 },{ 210,250 },{ 220,260 },{ 230,270 } };
int Impulsion_Range[10] = { 130,135,140,145,150,155,160,165,170,175 };
int Impulsion_LightingNum[10] = { 3,3,4,4,5,5,6,6,7,7 };
int Impulsion_UseMana[10] = { 35,38,40,43,46,49,53,57,61,65 };

// Implosão 
int Compulsion_AddAbsorb[10] = { 5,7,9,11,13,15,17,19,21,23 };
int Compulsion_Area[10] = { 150,160,170,180,190,200,210,220,230,240 };
int Compulsion_Time[10] = { 16,24,32,40,48,57,66,75,84,93 };
int Compulsion_UseMana[10] = { 50,54,58,62,66,70,74,78,82,86 };

// Esfera Magnética
int Magnetic_Sphere_AddDamage[10][2] = { { 30,40 },{ 40,50 },{ 50,60 },{ 60,70 },{ 70,80 },
{ 80,90 },{ 90,100 },{ 100,110 },{ 110,120 },{ 120,130 } };
int Magnetic_Sphere_Area[10] = { 80,80,85,85,90,90,95,95,100,100 };
int Magnetic_Sphere_AttackDelay[10] = { 6,6,6,5,5,5,4,4,4,3 };
int Magnetic_Sphere_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
int Magnetic_Sphere_UseMana[10] = { 60,65,70,75,80,85,90,95,100,105 };

// Golem de Metal
int Metal_Golem_Damage[10][2] = { { 95,115 },{ 100,120 },{ 105,125 },{ 110,130 },{ 115,135 },
{ 120,140 },{ 125,145 },{ 130,150 },{ 135,155 },{ 140,160 } };
int Metal_Golem_Hit[10] = { 660,680,700,720,740,760,780,800,820,840 };
int Metal_Golem_Defense[10] = { 355,400,445,490,535,580,625,670,715,760 };
int Metal_Golem_Life[10] = { 4100,4300,4500,4700,4900,5100,5300,5500,5700,5900 };
int Metal_Golem_UseMana[10] = { 60,64,68,72,76,80,84,88,92,96 };

/*__________________________________________________________________________________________________________________________

SKILLS LUTADOR
_____________________________________________________________________________________________________________________________*/

// _______________________ TIER 1 _______________________

// Mestre das Armas
int Melee_Mastery_DamagePercent[10] = { 6,10,14,18,21,24,26,28,30,32 };

// Resistência a Fogo
int PlusFire[10] = { 9,17,24,30,35,39,42,44,45,46 };

// Raiva
int Raving_Damage[10] = { 13,16,19,22,25,28,31,34,37,40 };
int Ravind_Speed[10] = { 2,2,2,3,3,3,4,4,4,4 };
float Raving_UseLife[10] = { 1.f,1.3f,1.6f,1.9f,2.2f,2.5f,2.8f,3.1f,3.4f,3.7f };
int Raving_UseMana[10] = { 14,16,18,20,22,24,26,29,32,35 };

// Impacto
int Impact_Attack_Rating[10] = { 20,40,60,80,100,120,140,160,180,200 };
int Impact_Damage[10] = { 20,25,29,33,37,41,45,49,52,55 };
int Impact_UseMana[10] = { 18,20,22,24,26,29,33,37,41,45 };

// _______________________ TIER 2 _______________________

// Impacto Triplo 
int T_Impact_Damage[10] = { 35,40,25,30,35,25,30,35,40,45 };
int T_Impact_Hit[10] = { 1,1,2,2,2,3,3,3,3,3 };
int T_Impact_UseMana[10] = { 22,24,26,29,32,35,38,41,44,47 };

// Girada Brutal
int B_Swing_Damage[10] = { 10,16,22,28,34,40,45,50,55,60 };
int B_Swing_Critical[10] = { 3,7,10,13,16,19,21,24,27,30 };
int B_Swing_UseMana[10] = { 24,26,28,31,34,38,42,47,52,58 };

// Rugido
int Roar_Range[10] = { 50,60,70,80,90,100,108,116,124,130 };
int Roar_Time[10] = { 4,6,8,10,12,14,16,18,20,22 };
int Roar_UseMana[10] = { 26,28,30,33,36,39,42,45,49,53 };


// Fúria de Zecram
int R_Zecram_Damage[10] = { 14,28,42,56,70,84,98,112,126,140 };
int R_Zecram_UseMana[10] = { 29,31,33,36,39,42,45,49,53,58 };

// _______________________ TIER 3 _______________________

// Concentração
int Concentration_AttackRate[10] = { 16,32,48,64,80,96,112,128,144,160 };
int Concentration_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Concentration_UseMana[10] = { 35,38,41,44,47,50,53,56,59,62 };

// Golpe da Vingaça
int A_Crash_Damage[10] = { 50,55,60,65,70,75,80,85,90,95 };
int A_Crash_AttackRate[10] = { 5,10,15,20,25,30,35,40,45,52 };
int A_Crash_UseMana[10] = { 32,34,36,38,41,44,47,50,53,56 };

// Machado Veloz
int Swift_Axe_Speed[10] = { 2,4,6,8,10,11,12,13,14,15 };
int Swift_Axe_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Swift_Axe_UseMana[10] = { 40,44,48,52,56,60,64,68,72,76 };

// Quebra Ossos
int B_Crash_Damage[10] = { 50,55,60,65,70,75,80,85,90,95 };
int B_Crash_DemonDamage[10] = { 20,25,30,35,40,45,50,55,60,65 };
int B_Crash_UseMana[10] = { 34,36,38,41,44,47,50,53,56,59 };

// _______________________ TIER 4 _______________________

// Destroyer
int Destoryer_DamagePercent[10] = { 15,30,45,60,75,90,105,120,135,150 };
int Destoryer_AddCritical[10] = { 10,12,14,16,18,20,22,24,26,28 };
int Destoryer_UseMana[10] = { 46,48,50,52,54,56,58,60,62,64 };

// Fúria
int Berserker_AddAttack[10] = { 20,24,28,32,36,40,44,48,52,56 };
int Berserker_SubAbsorb[10] = { -2,-4,-6,-8,-10,-12,-14,-16,-18,-20 };
int Berserker_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
int Berserker_UseMana[10] = { 52,55,58,61,64,67,70,73,76,79 };

// Golpe Giratório
int Cyclone_Strike_DamagePercent[10] = { 15,22,29,36,43,50,57,64,71,78 };
int Cyclone_Strike_AreaDamage[10][2] = { { 120,150 },{ 135,165 },{ 150,180 },{ 165,195 },{ 180,210 },
{ 195,225 },{ 210,240 },{ 225,255 },{ 240,270 },{ 255,285 } };
int Cyclone_Strike_AttackNum[10] = { 5,5,6,6,7,7,8,8,9,9 };
int Cyclone_Strike_Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
int Cyclone_Strike_UseMana[10] = { 50,53,56,59,62,65,68,71,74,77 };

// Bônus de Vitalidade
int Boost_Health_Life[10] = { 10,20,30,40,50,70,90,110,130,150 };

/*__________________________________________________________________________________________________________________________

SKILLS PIKEMAN
_____________________________________________________________________________________________________________________________*/

// _______________________ TIER 1 _______________________

// Sopro Afiado
int Pike_Wind_Throw_Height[10] = { 10,10,10,10,10,10,10,10,10,10 };
int Pike_Wind_Damage[10][2] = { { 3,20 },{ 5,27 },{ 7,34 },{ 9,41 },{ 11,48 },{ 13,52 },{ 15,59 },{ 17,66 },{ 19,73 },{ 21,80 } };
int Pike_Wind_Push_Lenght[10] = { 70,75,80,85,90,95,100,105,110,120 };
int Pike_Wind_UseMana[10] = { 14,16,18,20,23,26,29,32,35,39 };

// Resistência a Gelo
int PlusIce[10] = { 8,15,21,26,30,33,36,39,42,45 };

// Ataque Crítico
int Critical_Hit_Critical[10] = { 15,19,23,26,29,32,34,36,38,40 };
int Critical_Hit_UseMana[10] = { 14,16,18,20,23,26,29,33,37,41 };

// Pulo Fatal
int Jumping_Crash_UseMana[10] = { 16,18,20,23,26,29,32,35,39,43 };
int Jumping_Crash_Attack_Rating[10] = { 10,20,30,40,50,55,60,65,70,75 };
int Jumping_Crash_Damage[10] = { 40,50,60,70,80,90,100,110,120,130 };

// _______________________ TIER 2 _______________________

// Espinhos de Gelo
int G_Pike_Damage[10][2] = { { 10,40 },{ 13,45 },{ 16,50 },{ 19,55 },{ 22,60 },{ 25,65 },{ 28,70 },{ 31,75 },{ 34,80 },{ 37,85 } };
int G_Pike_Range[10] = { 80,82,84,86,88,90,92,94,96,98 };
int G_Pike_UseMana[10] = { 19,21,23,25,28,31,34,38,42,46 };
int G_Pike_Time[10] = { 6,7,8,9,10,11,12,13,14,15 };

// Tornado 
int Tornado_Damage[10] = { 20,29,37,44,50,55,59,62,64,65 };
int Tornado_Stun[10] = { 8,16,24,32,40,48,56,64,72,80 };
int Tornado_Range[10] = { 50,53,56,59,62,65,68,71,74,77 };
int Tornado_UseMana[10] = { 23,25,27,29,32,35,38,42,46,51 };

// Mestre da Def.
int W_D_Mastery_Block[10] = { 2,4,6,8,10,11,12,13,14,15 };

// Expansão
int Expansion_Size[10] = { 30,38,46,54,62,70,78,86,94,102 };
int Expansion_Damage[10] = { 30,35,40,45,50,55,60,65,70,75 };
int Expansion_UseMana[10] = { 26,28,30,33,36,39,43,47,50,53 };

// _______________________ TIER 3 _______________________

// Lanças Venenosas
int VenomSpear_Damage[10][2] = { { 17,20 },{ 19,22 },{ 21,24 },{ 23,26 },{ 25,28 },{ 27,30 },{ 29,32 },{ 31,34 },{ 33,36 },{ 35,38 } };
int VenomSpear_Num[10] = { 3,3,3,4,4,4,5,5,5,5 };
int VenomSpear_Time[10] = { 5,5,5,5,6,6,6,6,7,7 };
int VenomSpear_Range[10] = { 90,94,98,102,106,110,114,118,122,126 };
int VenomSpear_UseMana[10] = { 30,33,36,39,42,45,48,51,54,57 };

// Desaparecer
float Vanish_Speed[10] = { 0.2f,0.4f,0.6f,0.8f,1.0f,1.2f,1.4f,1.6f,1.8f,2.0f };
int Vanish_Damage[10] = { 10,20,30,40,50,60,70,80,90,100 };
int Vanish_Range[10] = { -40,-46,-52,-58,-64,-70,-75,-80,-85,-90 };
int Vanish_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Vanish_UseMana[10] = { 40,43,46,49,52,55,58,62,66,70 };

// Mestre do ATQ Crítico
int Critical_Mastery_Critical[10] = { 9,11,12,13,14,15,16,17,18,19 };

// Foice de Aço
int Chain_Lance_Damage[10] = { 10,15,20,25,30,35,40,45,50,55 };
int Chain_Lance_UseMana[10] = { 32,35,38,41,44,47,50,53,56,59 };

// _______________________ TIER 4 _______________________

// Olho Assassino
int Assassin_Eye_AddCritical[10] = { 10,14,18,22,26,30,34,38,42,46 };
int Assassin_Eye_M_SubCritical[10] = { -4,-5,-6,-7,-8,-9,-10,-11,-12,-13 };
int Assassin_Eye_Time[10] = { 12,13,14,15,16,17,18,19,20,21 };
int Assassin_Eye_UseMana[10] = { 47,49,51,53,55,57,59,61,63,65 };

// Golpe Carregado
int   Charging_Strike_DamagePercent[10] = { 10,15,20,25,30,35,40,45,50,55 };
int   Charging_Strike_CharingDamagePercent[10] = { 30,45,60,75,90,105,120,135,150,165 };
int   Charging_Strike_Time[10] = { 9,18,27,36,45,54,63,72,81,90 };
int   Charging_Strike_UseMana[10] = { 48,51,54,57,60,63,66,69,72,75 };

// Furtivo
int Vague_EvasionPercent[10] = { 6,8,10,12,14,17,20,23,26,29 };
int Vague_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
int Vague_UseMana[10] = { 55,58,61,64,67,70,73,76,79,82 };

// Mestre das Sombras
int Shadow_Master_DamagePercent[10] = { 10,15,20,25,25,30,35,40,40,45 };
int Shadow_Master_AddHit[10] = { 110,120,130,140,150,160,170,180,190,200 };
int Shadow_Master_ShadowNum[10] = { 3,3,4,4,5,5,6,6,7,7 };
int Shadow_Master_UseMana[10] = { 52,55,58,61,64,67,70,73,76,79 };

/*__________________________________________________________________________________________________________________________

SKILLS ARQUEIRA
_____________________________________________________________________________________________________________________________*/

// _______________________ TIER 1 _______________________

// Falcão Vigia
int Scout_Hawk_Attack_Rate[10] = { 10,20,30,40,50,60,70,80,90,100 };
int Scout_Hawk_UseTime[10] = { 5,6,7,8,9,10,11,12,13,14 };
int Scout_Hawk_UseMana[10] = { 14,16,18,20,23,26,30,34,39,44 };

// Mestra do Tiro
int S_Mastery_DamagePercent[10] = { 4,8,12,16,20,24,28,32,36,40 };

// Flecha de Vento
int Wind_Arrow_Speed[10] = { 2,2,2,3,3,3,4,4,4,5 };
int Wind_Arrow_Damage[10] = { 15,24,32,39,45,50,54,57,59,60 };
int Wind_Arrow_UseMana[10] = { 12,14,16,18,20,23,26,29,32,35 };

// Mira Perfeita
int Perfect_Aim_Attack_Rate[10] = { 26,27,29,32,36,41,47,54,62,71 };
int Perfect_Aim_Damage[10] = { 4,6,8,10,12,14,16,18,19,20 };
int Perfect_Aim_Damage_LV[10] = { 8,8,8,8,7,7,7,6,6,6 };
int Perfect_Aim_UseMana[10] = { 14,16,18,20,22,25,28,31,35,39 };

// _______________________ TIER 2 _______________________

// Olho de Dion
int D_Eye_Attack_Rate[10] = { 10,20,30,40,50,60,70,80,90,100 };

// Falcão
int Falcon_Damage[10][2] = { { 10,36 },{ 12,40 },{ 14,44 },{ 16,48 },{ 18,52 },{ 20,56 },{ 22,60 },{ 24,64 },{ 26,68 },{ 28,72 } };
int Falcon_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
int Falcon_UseMana[10] = { 24,26,28,30,33,36,39,43,47,52 };

// Flecha da Fúria
int A_Rage_ArrowNum[10] = { 2,3,4,5,6,7,8,9,10,11 };
int A_Rage_Damage[10] = { 6,6,6,6,5,5,5,5,4,4 };
int A_Rage_Area[10] = { 55,59,63,67,70,73,76,79,82,85 };
int A_Rage_UseMana[10] = { 24,26,28,31,34,37,40,44,48,53 };

// Avalanche
int Avalanche_Speed[10] = { 1,1,1,2,2,2,3,3,3,4 };
int Avalanche_Damage[10] = { 15,19,23,27,31,35,39,43,47,51 };
int Avalanche_ArrowNum[10] = { 3,3,3,4,4,4,5,5,5,6 };
int Avalanche_UseMana[10] = { 25,28,31,34,38,42,46,51,56,61 };

// _______________________ TIER 3 _______________________

// Tiro Elemental
int Elemental_Shot_Ice[10][2] = { { 10,20 },{ 13,24 },{ 16,28 },{ 19,32 },{ 22,36 },{ 25,40 },{ 28,44 },{ 31,48 },{ 34,52 },{ 37,56 } };
int Elemental_Shot_Fire[10][2] = { { 12,22 },{ 17,27 },{ 22,32 },{ 27,37 },{ 32,42 },{ 37,47 },{ 42,52 },{ 47,57 },{ 52,62 },{ 57,67 } };
int Elemental_Shot_Lightning[10][2] = { { 5,17 },{ 9,22 },{ 13,27 },{ 17,32 },{ 21,37 },{ 25,42 },{ 29,47 },{ 33,52 },{ 37,57 },{ 41,62 } };
int Elemental_Shot_UseMana[10] = { 27,29,31,33,36,39,42,45,48,51 };

// Falcão Dourado
int Golden_Falcon_Damage[10] = { 120,125,130,135,140,145,150,155,160,165 };
float Golden_Falcon_LifeRegen[10] = { 1.0f,1.3f,1.6f,1.9f,2.2f,2.5f,2.8f,3.1f,3.4f,3.7f };
int Golden_Falcon_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Golden_Falcon_UseMana[10] = { 33,36,39,42,46,50,54,59,64,70 };

// Tiro Explosivo
int BombShot_Damage[10] = { 5,10,15,20,25,30,35,40,45,50 };
int BombShot_DemonDamage[10] = { 5,10,15,20,25,30,35,40,45,50 };
int BombShot_AddDamage[10][2] = { { 15,27 },{ 18,31 },{ 21,35 },{ 24,39 },{ 27,43 },{ 30,47 },{ 33,51 },{ 36,55 },{ 39,59 },{ 42,63 } };
int BombShot_Area[10] = { 82,84,86,88,90,92,94,96,98,100 };
int BombShot_UseMana[10] = { 28,31,34,37,40,43,46,49,52,53 };

// Perfuração
int Perforation_Damage[10] = { 10,16,22,28,34,40,46,52,58,64 };
int Perforation_Critical[10] = { 3,6,9,12,15,18,21,24,27,30 };
int Perforation_UseMana[10] = { 28,31,34,37,40,43,46,49,52,53 };
int Perforation_Attack_Range[10] = { 30,34,38,42,46,50,54,58,62,66 };

// _______________________ TIER 4 _______________________

// Invocar Wolverine 
int Recall_Wolverin_Damage[10][2] = { { 50,75 },{ 55,80 },{ 60,85 },{ 65,90 },{ 70,95 },
{ 75,100 },{ 80,105 },{ 85,110 },{ 90,115 },{ 95,120 } };
int Recall_Wolverin_Hit[10] = { 900,1000,1100,1200,1300,1400,1500,1600,1700,1800 };
int Recall_Wolverin_Defense[10] = { 1000,1050,1100,1150,1200,1250,1300,1350,1400,1450 };
int Recall_Wolverin_Life[10] = { 2000,2200,2400,2600,2800,3000,3200,3400,3600,3800 };
int Recall_Wolverin_UseMana[10] = { 52,56,60,64,68,72,76,80,84,88 };

// Mestra da Esquiva
int Evasion_Mastery_AddPercent[10] = { 11,13,15,17,19,21,23,24,25,26 };

// Tiro Fênix
int   Phoenix_Shot_DamagePercent[10] = { 50,62,74,86,98,110,122,134,146,158 };
int   Phoenix_Shot_Time[10] = { 9,18,27,36,45,54,63,72,81,90 };
int   Phoenix_Shot_UseMana[10] = { 33,35,37,40,43,46,50,54,58,62 };

// Força da Natureza
int Force_Of_Nature_AddDamage[10] = { 12,15,18,21,24,27,30,33,36,39 };
int Force_Of_Nature_AddHit[10] = { 20,30,40,50,60,70,80,90,100,110 };
int Force_Of_Nature_FalconAddDamage[10] = { 22,26,30,34,38,42,46,50,54,58 };
int Force_Of_Nature_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
int Force_Of_Nature_UseMana[10] = { 51,54,57,60,63,66,69,72,75,78 };

/*__________________________________________________________________________________________________________________________

SKILLS CAVALEIRO
_____________________________________________________________________________________________________________________________*/

// _______________________ TIER 1 _______________________

// Rajada Sagrada
int Sword_Blast_UseMana[10] = { 8,10,12,15,18,21,25,29,33,38 };
int Sword_Blast_Damage[10][2] = { { 12,16 },{ 15,20 },{ 18,24 },{ 21,28 },{ 24,32 },{ 27,36 },{ 30,40 },{ 33,44 },{ 36,48 },{ 39,52 } };
int Sword_Blast_ShootingRange[10] = { 80,84,88,92,96,100,104,108,112,116 };

// Corpo Sagrado
int HolyBody_UseMana[10] = { 18,21,24,27,30,34,38,42,46,50 };
int HolyBody_Absorb[10] = { 8,12,16,19,22,25,27,29,31,33 };
int HolyBody_Time[10] = { 30,50,70,90,110,130,150,170,190,210 };

// Treinamento Físico
int P_Traning_Stamina[10] = { 5,8,11,14,17,20,23,26,28,30 };

// Golpe Duplo
int D_Crash_UseMana[10] = { 18,20,22,24,27,30,33,36,39,42 };
int D_Crash_Damage[10] = { 10,14,18,22,25,28,31,34,37,40 };
int D_Crash_Critical[10] = { 3,3,4,4,5,5,6,6,7,7 };

// _______________________ TIER 2 _______________________

// Valor Sagrado
int Holy_Valor_Damage[10] = { 18,22,26,30,34,38,42,46,50,54 };
int Holy_Valor_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
int Holy_Valor_Mana[10] = { 23,26,29,32,35,38,41,44,47,50 };

// Brandish
int Brandish_Range[10] = { 70,72,74,76,78,80,82,84,86,88 };
int Brandish_Damage[10] = { 10,16,22,28,34,40,46,52,58,64 };
int Brandish_Mana[10] = { 22,24,26,28,30,33,36,39,42,45 };

// Piercing
int Piercing_Damage[10] = { 10,17,24,31,38,45,52,59,66,73 };
int Piercing_Attack_Rating[10] = { 40,50,60,70,80,90,100,110,120,130 };
int Piercing_Mana[10] = { 24,26,28,30,32,34,36,38,40,42 };

// Espírito Drástico
int Drastic_Spirit_Defense[10] = { 6,9,12,15,18,20,22,23,24,25 };
int Drastic_Spirit_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
int Drastic_Spirit_Mana[10] = { 25,27,29,32,35,38,41,45,49,54 };

// _______________________ TIER 3 _______________________

// Mestre da Espada
int Sword_Mastery_DamagePercent[10] = { 11,14,17,20,23,26,29,32,35,38 };


// Escudo Divino
int D_Inhalation_Life[10] = { 9,18,27,36,45,54,63,72,81,90 };
int D_Inhalation_Block[10] = { 2,2,3,3,4,4,5,5,6,6 };
int D_Inhalation_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int D_Inhalation_UseMana[10] = { 30,33,36,39,43,47,51,55,60,65 };

// Encantamento Sagrado
int H_Incantation_Success[10] = { 45,54,62,69,75,80,84,88,92,96 };
int H_Incantation_AddLife[10] = { 100,120,140,160,180,200,220,240,260,280 };
int H_Incantation_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int H_Incantation_UseMana[10] = { 36,39,42,45,48,52,56,60,65,70 };

// Grande Cruzada
int Grand_Cross_Damage[10] = { 35,40,45,50,55,60,65,70,75,95 };
int Grand_Cross_AttackRate[10] = { 35,40,45,50,55,60,65,70,75,100 };
int Grand_Cross_UndeadDamage[10] = { 5,10,15,20,25,30,35,40,45,50 };
int Grand_Cross_UseMana[10] = { 28,31,34,37,40,43,46,49,52,55 };

// _______________________ TIER 4 _______________________

// Espada da Justiça
int Sword_Of_Justice_DamagePercent[10] = { 100,110,120,130,140,150,160,170,180,190 };
int Sword_Of_Justice_Area[10] = { 130,135,140,145,150,155,160,165,170,175 };
int Sword_Of_Justice_UseMana[10] = { 50,53,56,59,62,65,68,71,74,77 };

// Escudo dos Deuses
int Godly_Shield_AbsorbPercent[10] = { 2,4,6,8,10,12,14,16,18,20 };
int Godly_Shield_Time[10] = { 100,110,120,130,140,150,160,170,180,190 };
int Godly_Shield_UseMana[10] = { 47,50,53,56,59,62,65,68,71,74 };

// Benção Divina
int God_Bless_AddDamage[10] = { 6,9,12,15,18,21,24,27,30,33 };
int God_Bless_Time[10] = { 120,130,140,150,160,170,180,190,200,210 };
int God_Bless_UseMana[10] = { 57,60,63,66,69,72,75,78,81,84 };

// Piercing Divino
int Divine_Piercing_DamagePercent[10] = { 10,14,18,22,20,25,30,35,30,35 };
int Divine_Piercing_AddHit[10] = { 20,30,40,50,50,60,70,80,80,90 };
int Divine_Piercing_AttackNum[10] = { 3,3,3,3,5,5,5,5,7,7 };
int Divine_Piercing_UseMana[10] = { 45,47,49,51,53,55,57,59,61,63 };

/*__________________________________________________________________________________________________________________________

SKILLS ATALANTA
_____________________________________________________________________________________________________________________________*/

// _______________________ TIER 1 _______________________

// Golpe de Escudo
int S_Strike_UseMana[10] = { 16,18,20,22,24,27,30,33,36,40 };
int S_Strike_Damage[10][2] = { { 4,20 },{ 5,25 },{ 6,30 },{ 8,35 },{ 10,40 },{ 12,45 },{ 14,50 },{ 16,55 },{ 18,60 },{ 20,65 } };
int S_Strike_Stun[10] = { 6,9,12,15,18,21,24,27,30,34 };

// Farina
int Farina_UseMana[10] = { 17,19,21,23,26,29,32,35,38,41 };
int Farina_Speed[10] = { 1,1,1,1,2,2,2,2,2,2 };
int Farina_AttackRate[10] = { 30,40,50,60,70,80,90,100,110,120 };

// Mestra do Arremesso
int T_Mastery_Damage[10] = { 18,22,26,30,34,38,41,44,47,50 };

// Lança Gigante
int V_Spear_UseMana[10] = { 19,21,23,25,28,31,34,37,40,43 };
int V_Spear_Damage[10][2] = { { 4,10 },{ 6,15 },{ 8,20 },{ 10,25 },{ 11,30 },{ 12,35 },{ 13,40 },{ 14,45 },{ 15,50 },{ 16,55 } };

// _______________________ TIER 2 _______________________

// Windy
int Windy_Attack_Rating[10] = { 10,20,30,40,50,60,70,80,90,100 };
int Windy_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
int Windy_Mana[10] = { 24,26,28,30,32,34,37,40,44,48 };

// Lança Giratória
int Twist_Javelin_Damage[10] = { 10,22,34,46,58,70,82,94,106,118 };
int Twist_Javelin_Attack_Rating[10] = { 10,22,34,46,58,70,82,94,106,118 };
int Twist_Javelin_Mana[10] = { 20,22,24,27,30,33,36,40,44,48 };

// Ladrão de Almas
int Soul_Sucker_Absorb[10] = { 10,13,16,19,22,25,28,31,34,37 };
int Soul_Sucker_Mana[10] = { 25,28,31,34,38,42,46,50,55,60 };

// Lança de Fogo
int Fire_Javelin_Damage[10][2] = { { 20,30 },{ 25,35 },{ 30,40 },{ 35,45 },{ 40,50 },{ 45,55 },{ 50,60 },{ 55,65 },{ 60,70 },{ 65,75 } };
int Fire_Javelin_Mana[10] = { 25,27,29,32,35,38,41,44,47,50 };

// _______________________ TIER 3 _______________________

// Lança Partida
int Split_Javelin_AttackNum[10] = { 3,3,3,3,3,3,3,3,3,3 };
int Split_Javelin_Damage[10] = { 8,14,20,26,32,38,44,50,56,62 };
int Split_Javelin_AttackRate[10] = { -10,-7,-4,-1,2,5,8,12,16,20 };
int Split_Javelin_UseMana[10] = { 30,33,36,39,42,45,48,51,54,57 };

// Triunfo de Valhalla
int T_Of_Valhalla_Damage[10] = { 5,10,15,20,25,30,35,40,45,50 };
int T_Of_Valhalla_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int T_Of_Valhalla_UseMana[10] = { 32,34,36,39,42,45,49,54,59,65 };

// Lança de Raio
int Lightning_Javelin_Damage[10][2] = { { 20,40 },{ 23,46 },{ 26,52 },{ 29,58 },{ 32,64 },{ 35,70 },{ 38,76 },{ 41,82 },{ 44,88 },{ 47,96 } };
int Lightning_Javelin_UseMana[10] = { 30,32,34,37,40,43,47,50,53,56 };

// Chuva de Lanças
int Storm_Javelin_Damage[10] = { 22,28,34,40,46,52,58,64,70,76 };
int Storm_Javelin_UseMana[10] = { 34,36,38,41,44,47,50,53,56,59 };

// _______________________ TIER 4 _______________________

// Inferno de Valhalla
int Hall_Of_Valhalla_AddEvation[10] = { 5,8,11,14,17,20,23,26,29,32 };
int Hall_Of_Valhalla_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
int Hall_Of_Valhalla_UseMana[10] = { 36,39,42,45,48,52,56,60,65,70 };

// Fúria-X
int X_Rage_DamagePercent[10] = { 70,80,90,100,110,120,130,140,150,160 };
int X_Rage_Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
int X_Rage_UseMana[10] = { 34,36,38,41,44,47,50,54,58,62 };

// Lança de Gelo
int Frost_Javelin_IceAddDamage[10][2] = { { 40,50 },{ 42,54 },{ 44,58 },{ 46,62 },{ 48,66 },
{ 50,70 },{ 52,74 },{ 54,78 },{ 56,82 },{ 58,86 } };
int Frost_Javelin_SpeedSubPercent[10] = { 7,8,9,10,11,12,13,14,15,16 };
int Frost_Javelin_IceTime[10] = { 5,5,6,6,7,7,8,8,9,9 };
int Frost_Javelin_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
int Frost_Javelin_UseMana[10] = { 33,36,39,42,44,48,52,56,60,65 };

// Vingança
int Vengeance_DamagePercent[10] = { 10,20,30,40,50,60,70,80,90,100 };
int Vengeance_Range[10] = { 10,15,20,25,30,35,40,45,50,55 };
int Vengeance_UseMana[10] = { 33,35,37,39,41,43,45,47,49,51 };
int Vengeance_AddCritical[10] = { 2,4,6,8,10,13,16,19,22,25 };

/*__________________________________________________________________________________________________________________________

SKILLS MAGO
_____________________________________________________________________________________________________________________________*/

// _______________________ TIER 1 _______________________


// Agonia
int Agony_UseMana[10] = { 5,6,7,8,9,10,11,12,13,14 };
int Agony_ConvLife[10] = { 4,8,12,16,20,24,28,32,36,40 };

// Fagulha
int FireBolt_UseMana[10] = { 16,18,20,22,25,28,31,34,38,42 };
int FireBolt_Damage[10] = { 16,18,20,22,25,28,31,34,38,42 };

// Zenith
int Zenith_UseMana[10] = { 18,20,22,25,28,31,35,39,43,48 };
int Zenith_Element[10] = { 2,3,4,5,6,7,8,9,10,11 };
int Zenith_Time[10] = { 30,50,70,90,110,130,150,170,190,210 };

// Bola de Fogo
int FireBall_UseMana[10] = { 22,24,26,28,31,34,38,42,46,50 };
int FireBall_Damage[10] = { 22,24,26,28,31,34,38,42,46,50 };
int FireBall_Range[10] = { 163,166,169,172,175,178,181,184,187,190 };

// _______________________ TIER 2 _______________________

// Mestre da Mente
int Mental_Mastery_Mana[10] = { 5,8,11,14,17,20,23,26,29,32 };

// Watornado
int Watornado_Damage[10] = { 70,72,74,76,78,80,82,84,86,88 };
int Watornado_Area[10] = { 70,72,74,76,78,80,82,84,86,88 };
int Watornado_Range[10] = { 170,174,178,182,186,190,194,198,202,206 };
int Watornado_Mana[10] = { 25,27,29,32,35,38,42,46,50,55 };

// Encanto
int Enchant_Weapon_Damage_Ice[10][2] = { { 3,8 },{ 6,12 },{ 9,16 },{ 12,20 },{ 15,24 },{ 18,28 },{ 21,32 },{ 24,36 },{ 27,40 },{ 30,44 } };
int Enchant_Weapon_Damage_Fire[10][2] = { { 4,10 },{ 8,16 },{ 12,22 },{ 16,28 },{ 20,34 },{ 24,40 },{ 28,46 },{ 32,52 },{ 36,58 },{ 40,64 } };
int Enchant_Weapon_Damage_Lightning[10][2] = { { 4,8 },{ 6,13 },{ 8,18 },{ 10,23 },{ 12,28 },{ 14,33 },{ 16,38 },{ 18,43 },{ 20,48 },{ 22,53 } };
int Enchant_Weapon_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
int Enchant_Weapon_Mana[10] = { 30,32,34,37,40,44,48,53,58,64 };

// Raio da Morte
int Dead_Ray_Damage[10] = { 185,190,195,200,205,210,215,220,225,230 };
int Dead_Ray_Range[10] = { 185,190,195,200,205,210,215,220,225,230 };
int Dead_Ray_Mana[10] = { 26,29,32,35,39,43,47,51,55,59 };

// _______________________ TIER 3 _______________________

// Escudo Energético
int Energy_Shield_DecDamage[10] = { 10,13,16,19,21,24,26,28,29,30 };
int Energy_Shield_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Energy_Shield_UseMana[10] = { 34,37,40,43,47,51,55,60,66,72 };

// Terremoto
int Diastrophism_Damage[10] = { 100,105,110,115,120,125,130,135,140,145 };
int Diastrophism_Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
int Diastrophism_UseMana[10] = { 30,33,36,39,43,47,51,56,61,67 };

// Espírito Elemental
float Spirit_Elemental_RegenMana[10] = { 0.2f,0.4f,0.6f,0.8f,1.0f,1.2f,1.4f,1.6f,1.8f,2.0f };
int Spirit_Elemental_Damage[10] = { 12,14,16,18,20,23,36,39,32,35 };
int Spirit_Elemental_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Spirit_Elemental_UseMana[10] = { 36,39,42,45,48,51,54,57,60,63 };

// Espada Dançante	
int Dancing_Sword_IceDamage[10][2] = { { 20,26 },{ 22,29 },{ 24,32 },{ 26,35 },{ 28,38 },{ 30,41 },{ 32,44 },{ 34,47 },{ 36,50 },{ 38,53 } };
int Dancing_Sword_FireDamage[10][2] = { { 20,26 },{ 23,30 },{ 26,34 },{ 29,38 },{ 32,42 },{ 35,46 },{ 38,50 },{ 41,54 },{ 44,58 },{ 47,62 } };
int Dancing_Sword_AttackDelay[10] = { 5,5,5,5,4,4,4,4,3,3 };
int Dancing_Sword_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Dancing_Sword_UseMana[10] = { 35,37,39,42,45,48,52,56,61,66 };

// _______________________ TIER 4 _______________________

// Chama Elemental
int Fire_Elemental_Damage[10][2] = { { 80,95 },{ 85,100 },{ 90,105 },{ 95,110 },{ 100,115 },
{ 105,120 },{ 110,125 },{ 115,130 },{ 120,135 },{ 125,140 } };
int Fire_Elemental_Hit[10] = { 500,550,600,650,700,750,800,850,900,950 };
int Fire_Elemental_Life[10] = { 2000,2200,2400,2600,2800,3000,3200,3400,3600,3800 };
int Fire_Elemental_UseMana[10] = { 52,56,60,64,68,72,76,80,84,88 };

// Ondas de Fogo
int Flame_Wave_FireDamage[10] = { 110,120,130,140,150,160,170,180,190,200 };
int Flame_Wave_Area[10] = { 110,120,130,140,150,160,170,180,190,200 };
int Flame_Wave_UseMana[10] = { 75,79,83,87,91,95,99,103,107,111 };

// Distorção
int Distortion_SpeedSubPercent[10] = { 4,6,8,10,12,14,16,18,20,22 };
int Distortion_DamageSubPercent[10] = { 5,6,7,8,9,10,11,12,13,14 };
int Distortion_Area[10] = { 120,125,130,135,140,145,150,155,160,165 };
int Distortion_Time[10] = { 4,6,8,10,12,14,16,18,20,22 };
int Distortion_UseMana[10] = { 105,110,115,120,125,130,135,140,145,150 };

// Meteóro
int Meteo_Damage[10] = { 100,105,110,115,120,125,130,135,140,145 };
int Meteo_Area[10] = { 100,105,110,115,120,125,130,135,140,145 };
int Meteo_UseMana[10] = { 100,104,108,112,116,120,124,128,132,136 };

/*__________________________________________________________________________________________________________________________

SKILLS SACER
_____________________________________________________________________________________________________________________________*/

// _______________________ TIER 1 _______________________

// Cura
int Healing_UseMana[10] = { 11,14,17,20,24,28,32,37,42,47 };
int Healing_Heal[10][2] = { { 64,86 },{ 72,98 },{ 80,110 },{ 88,122 },{ 96,134 },{ 104,146 },{ 112,158 },{ 120,170 },{ 128,182 },{ 136,194 } };

// Fagulha Sagrada
int HolyBolt_UseMana[10] = { 14,17,20,23,27,31,35,40,45,50 };
int HolyBolt_Damage[10] = { 14,17,20,23,27,31,35,40,45,50 };

// Espinhos Múltiplos
int M_Spark_UseMana[10] = { 16,19,22,25,29,33,37,42,47,52 };
int M_Spark_Damage[10] = { 16,19,22,25,29,33,37,42,47,52 };
int M_Spark_Num[10] = { 4,4,4,5,5,5,6,6,7,7 };

// Feitiço Divino
int HolyMind_UseMana[10] = { 22,25,28,32,36,40,45,50,55,60 };
int HolyMind_DecDamage[10] = { 10,13,16,19,22,25,28,30,32,34 };
int HolyMind_Time[10] = { 15,15,15,15,15,15,15,15,15,15 };

// _______________________ TIER 2 _______________________

// Meditação
float Meditation_Regen[10] = { 0.6f,1.0f,1.4f,1.8f,2.2f,2.6f,3.0f,3.4f,3.8f,4.2f };

// Raios Divinos
int Divine_Lightning_Damage[10] = { 24,26,28,31,34,37,40,44,48,53 };
int Divine_Lightning_Num[10] = { 3,3,3,4,4,4,5,5,5,6 };
int Divine_Lightning_Mana[10] = { 24,26,28,31,34,37,40,44,48,53 };

// Reflexão Divina
int Holy_Reflection_Return_Damage[10] = { 20,30,40,50,60,70,80,90,100,110 };
int Holy_Reflection_Time[10] = { 60,80,100,120,140,160,180,200,220,240 };
int Holy_Reflection_Mana[10] = { 24,27,30,33,36,40,44,48,52,57 };

// Cura Máxima
int Grand_Healing[10][2] = { { 40,50 },{ 50,60 },{ 60,70 },{ 70,80 },{ 80,90 },{ 90,100 },{ 100,110 },{ 110,120 },{ 120,130 },{ 130,140 } };
int Grand_Healing_Range[10] = { 300,310,320,330,340,350,360,370,380,390 };
int Grand_Healing_Mana[10] = { 24,26,29,32,36,40,44,49,54,59 };

// _______________________ TIER 3 _______________________

// Esferas de Vigor
int Vigor_Ball_Damage[10] = { 26,28,30,33,36,39,42,45,48,51 };
int Vigor_Ball_UseMana[10] = { 26,28,30,33,36,39,42,45,48,51 };

// Ressureição
int Resurrection_Percent[10] = { 40,47,54,61,67,73,79,84,89,94 };
int Resurrection_Exp[10] = { 100,150,200,250,300,350,400,450,500,550 };
int Resurrection_UseMana[10] = { 70,66,62,58,54,50,46,42,38,34 };

// Extinção
int Extinction_Percent[10] = { 60,64,68,72,76,80,84,88,92,96 };
int Extinction_Amount[10] = { 20,25,30,34,38,41,44,47,50,52 };
int Extinction_UseMana[10] = { 30,32,34,37,40,43,47,51,55,60 };

// HP Virtual
int Virtual_Life_Percent[10] = { 12,14,16,18,20,22,24,26,28,30 };
int Virtual_Life_Time[10] = { 90,110,130,150,170,190,210,230,250,270 };
int Virtual_Life_UseMana[10] = { 60,63,66,69,73,77,81,86,91,97 };

// _______________________ TIER 4 _______________________

// Espinhos Glaciais
int Glacial_Spike_Damage[10] = { 150,155,160,165,170,175,180,185,190,195 };
int Glacial_Spike_Area[10] = { 150,155,160,165,170,175,180,185,190,195 };
int Glacial_Spike_UseMana[10] = { 65,68,71,74,77,80,83,86,89,92 };

// Campo de Regen
float Regeneration_Field_LifeRegen[10] = { 1.2f,2.4f,3.6f,4.8f,6.0f,7.2f,8.4f,9.6f,10.8f,12.0f };
float Regeneration_Field_ManaRegen[10] = { 1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f };
int   Regeneration_Field_Time[10] = { 35,40,45,50,55,60,65,70,75,80 };
int   Regeneration_Field_Area[10] = { 250,260,270,280,290,300,310,320,330,340 };
int   Regeneration_Field_UseMana[10] = { 100,104,108,112,116,120,124,128,132,136 };

// Raios Contínuos
int Chain_Lightning_Damage[10] = { 140,145,150,155,160,165,170,175,180,185 };
int Chain_Lightning_Num[10] = { 5,5,6,6,7,7,8,8,9,9 };
int Chain_Lightning_Range[10] = { 140,145,150,155,160,165,170,175,180,185 };
int Chain_Lightning_UseMana[10] = { 76,79,82,85,88,91,94,97,100,103 };

// Invocar Muspell
int Summon_Muspell_Damage[10][2] = { { 70,95 },{ 76,100 },{ 82,105 },{ 88,110 },{ 94,115 },
{ 100,120 },{ 106,125 },{ 112,130 },{ 118,135 },{ 124,140 } };
int Summon_Muspell_Attack_Delay[10] = { 7,7,7,6,6,6,5,5,5,4 };
int Summon_Muspell_UndeadAbsorbPercent[10] = { 10,14,18,22,26,30,34,38,42,46 };
int Summon_Muspell_BlockPercent[10] = { 5,6,7,8,9,10,11,12,13,14 };
int Summon_Muspell_Time[10] = { 120,140,160,180,200,220,240,260,280,300 };
int Summon_Muspell_UseMana[10] = { 110,114,118,122,126,130,134,138,140,146 };

// Desconhecido.
int C_Skill_HpPoint[10] = { 100,110,120,130,140,150,160,170,180,190 };
int C_Skill_AttPercent[10] = { 10,11,12,13,14,15,16,17,18,19 };
int C_Skill_EvaPercent[10] = { 10,11,12,13,14,15,16,17,18,19 };


/*__________________________________________________________________________________________________________________________

Tabela de Skills
Organizada e reestruturada por Zaraki.

__________________________________________________________________________________________________________________________*/