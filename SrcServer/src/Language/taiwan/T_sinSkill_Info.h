

#define SIN_SKILL_USE_RIGHT		0x01000000		
#define SIN_SKILL_USE_LEFT		0x02000000		
#define SIN_SKILL_USE_ALL		0x03000000		
#define SIN_SKILL_USE_NOT		0x04000000		


{"極光護盾",		"在自己使用的盾上附以極光，提高護盾的防禦能力。",
10,		34,2,		110,4,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0},
F_Extreme_Shield,SKILL_EXTREME_SHIELD,SIN_SKILL_USE_RIGHT,E_Shield_UseMana},

{"機械榴彈",			"扔出機械手榴彈，在一定距離內打擊敵人。",
12,		28,2,		73,3,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Mechanic_Bomb,SKILL_MECHANIC_BOMB,SIN_SKILL_USE_RIGHT,Mechanic_Bomb_UseMana},

{"毒之抵抗",		"增加對毒系魔法攻擊的抵抗能力。",
14,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Poison_Attribute,SKILL_POISON_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

{"靈光護體",		"汲取自然界之靈氣，暫時強化身體，減輕受到物理攻擊的傷害。",
17,		30,2,		110,5,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Physical_Absorption,SKILL_PHYSICAL_ABSORB,SIN_SKILL_USE_RIGHT,P_Absor_bUseMana},

{"狂暴一擊",		"凝聚全身的力氣，給予敵人強烈的一擊。",
20,		38,2,		73,3,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0},
F_Great_Smash,SKILL_GREAT_SMASH,SIN_SKILL_USE_ALL,G_Smash_UseMana},

{"憤怒之刃",			"將怒意灌注於武器中，提升武器的攻擊殺傷力。",
23,		41,2,		110,4,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0},
F_Maximize,SKILL_MAXIMIZE,SIN_SKILL_USE_RIGHT,Maximize_UseMana},

{"暴怒之獅",			"喚醒遠距離攻擊武器的靈魂，提升它的攻擊速度與殺傷力。",
26,		42,2,		110,4,
{0,0,0},			{sinWS1,sinWT1,0,0,0,0,0,0},
F_Automation,SKILL_AUTOMATION,SIN_SKILL_USE_RIGHT,Automation_UseMana},

{"雷神之擊",			"凝聚強烈的雷電能量，毀滅周圍的敵人。",
30,		40,2,		82,2,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Spark,SKILL_SPARK,SIN_SKILL_USE_RIGHT,Spark_UseMana},



{"格鬥之術",		"提高戰士近距離的格鬥搏擊能力，暫時增強攻擊力。",
10,		0,0,		0,0,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWS2,0,0,0,0},
F_Melee_Mastery,SKILL_MELEE_MASTERY,SIN_SKILL_USE_NOT,0},

{"炎之抵抗",		"增加對火系魔法攻擊的抵抗能力。",
12,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Fire_Attribute,SKILL_FIRE_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

{"絕地狂嚎",			"增加攻擊殺傷力、攻擊速度和連擊次數，但施展時自己會損失生命值。",
14,		35,2,		93,3,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0},
F_Raving,SKILL_RAVING,SIN_SKILL_USE_ALL,Raving_UseMana},

{"流星衝擊",			"短時間提高攻擊的命中率，相當有效地傷害敵人。",
17,		37,2,		86,4,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0},
F_Impact,SKILL_IMPACT,SIN_SKILL_USE_ALL,Impact_UseMana},

{"彗星轟擊",		"將攻擊命中率提升到極限，給予敵人最快速的傷害。",
20,		39,2,		80,4,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0},
F_Triple_Impact,SKILL_TRIPLE_IMPACT,SIN_SKILL_USE_ALL,T_Impact_UseMana},

{"毀滅風暴",			"猛烈的揮擊武器，進行攻擊將敵人粉碎。",
23,		41,2,		82,2,
{0,0,0},			{sinWA1,sinWS2,0,0,0,0,0,0},
F_Brutal_Swing,SKILL_BRUTAL_SWING,SIN_SKILL_USE_ALL,B_Swing_UseMana},

{"猛虎戰吼",			"凝聚全身之氣，發出強烈的戰吼，讓敵人陷入恐慌混亂。",
26,		39,2,		112,4,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Roar,SKILL_ROAR,SIN_SKILL_USE_RIGHT,Roar_UseMana},

{"爆裂虎噬",		"釋放全身之力，瘋狂地進行毀滅性的攻擊。",
30,		45,2,		84,4,
{0,0,0},			{sinWA1,sinWH1,sinWS2,0,0,0,0,0},
F_RageOfZecram,SKILL_RAGE_OF_ZECRAM,SIN_SKILL_USE_RIGHT,R_Zecram_UseMana},



{"旋風之槍",			"同時打擊周圍多個目標，並且將敵人震退一段距離。",
10,		27,2,		80,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Pike_Wind,SKILL_PIKE_WIND,SIN_SKILL_USE_RIGHT,Pike_Wind_UseMana},

{"寒之抵抗",		"增加對冰系魔法攻擊的抵抗能力。",
12,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Ice_Attribute,SKILL_ICE_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

{"致命一擊",			"直擊敵人的要害，提高致命攻擊的命中率與成功率。",
14,		31,2,		84,3,
{0,0,0},			{sinWS2,sinWP1,sinWH1,sinWC1,0,0,0,0},
F_Critical_Hit,SKILL_CRITICAL_HIT,SIN_SKILL_USE_ALL,Critical_Hit_UseMana},

{"霹靂破擊",			"掌握對方空隙，高高躍起，猛烈打擊敵人。",
17,		34,2,		76,4,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0},
F_Jumping_Crash,SKILL_JUMPING_CRASH,SIN_SKILL_USE_ALL,Jumping_Crash_UseMana},

{"大地之矛",		"將冰屬性與全身能量結合，瞬間釋放傷害周圍的敵人。",
20,		36,2,		84,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Ground_Pike,SKILL_GROUND_PIKE,SIN_SKILL_USE_RIGHT,G_Pike_UseMana},

{"裂地颶風",			"用手中武器激起的風牆，猛烈的撕裂四周的敵人。",
23,		38,2,		83,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Tornado_Pike,SKILL_TORNADO,SIN_SKILL_USE_RIGHT,Tornado_UseMana},

{"護衛之牆",	"高超的使槍技巧，在險惡的戰鬥中，用武器來防禦保護自己。",
26,		0,0,		0,0,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0},
F_Weapone_Defence_Mastery,SKILL_WEAPONE_DEFENCE_MASTERY,SIN_SKILL_USE_NOT,0},

{"惡龍之爪",			"將全身的力與氣灌注在武器上，瞬間給敵人最大的傷害。",
30,		42,2,		82,4,
{0,0,0},			{sinWA1,sinWH1,sinWP1,0,0,0,0,0},
F_Expansion,SKILL_EXPANSION,SIN_SKILL_USE_ALL,Expansion_UseMana},



{"偵察之鷹",			"召喚獵鷹，開闊射手的視野，提高攻擊命中率。",
10,		25,2,		115,5,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Scout_Hawk ,SKILL_SCOUT_HAWK,SIN_SKILL_USE_RIGHT,Scout_Hawk_UseMana },

{"強力之箭",		"將右手之力灌注於箭上，提高射手每一枝箭的攻擊殺傷力。",
12,		0,0,		0,0,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Shooting_Mastery,SKILL_SHOOTING_MASTERY,SIN_SKILL_USE_NOT,0},

{"疾風之箭",			"射出如疾風般飛快的箭，提高攻擊力和攻擊速度。",
14,		25,2,		82,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Wind_Arrow,SKILL_WIND_ARROW,SIN_SKILL_USE_ALL,Wind_Arrow_UseMana},

{"奪命之箭",			"增加弓箭攻擊的準確性，提高命中率和攻擊力，更致命地殺傷敵人。",
17,		29,2,		81,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Perfect_Aim,SKILL_PERFECT_AIM,SIN_SKILL_USE_ALL,Perfect_Aim_UseMana},


{"神鷹之眼",			"如同傳說中的神射手一般，擁有絕佳的視野與命中率。",
20,		0,0,		0,0,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Dions_Eye,SKILL_DIONS_EYE,SIN_SKILL_USE_NOT,0},

{"召喚戰隼",			"召喚比獵鷹更強的戰隼，有著強大的殺傷力，更增添射手的威力。",
23,		36,2,		115,4,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Falcon ,SKILL_FALCON,SIN_SKILL_USE_RIGHT,Falcon_UseMana },

{"狂暴箭雨",		"貫注全身之氣，使射出的箭在敵人的上空迸裂，如同暴雨般的殺傷敵人。",
26,		38,2,		82,4,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Arrow_of_Rage,SKILL_ARROW_OF_RAGE,SIN_SKILL_USE_RIGHT,A_Rage_UseMana},

{"雪崩箭嵐",			"在一瞬間勁射如雪崩般的大量箭矢，淹沒敵人。",
30,		41,2,		103,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Avalanche,SKILL_AVALANCHE,SIN_SKILL_USE_RIGHT,Avalanche_UseMana},


	

{"御劍氣擊",		"以強烈的劍氣，破空揮擊對敵人造成傷害。",
10,		22,2,		82,2,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0},
F_Sword_Blast,SKILL_SWORD_BLAST,SIN_SKILL_USE_ALL,Sword_Blast_UseMana},

{"神聖軀體",			"藉由神聖的力量，在一定的時間內，增加對不死系怪物的額外防禦力。",
12,		28,2,		110,3,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_HolyBody ,SKILL_HOLY_BODY,SIN_SKILL_USE_RIGHT,HolyBody_UseMana },

{"精力提昇",		"藉由不斷的訓練，使精力值永久提高，增強人物的屬性。",
14,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Physical_Traning,SKILL_PHYSICAL_TRANING,SIN_SKILL_USE_NOT,0},

{"雙重衝擊",			"以更強大的力量，更快速的攻擊敵人。",
17,		35,2,		82,2,
{0,0,0},			{sinWA1,sinWC1,sinWS2,0,0,0,0,0},
F_Double_Crash,SKILL_DOUBLE_CRASH,SIN_SKILL_USE_RIGHT,D_Crash_UseMana},

{"神聖靈氣",			"使身體充滿聖靈氣，對不死系怪獸的攻擊力增加。",
20,		36,2,		100,3,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Holy_Valor,SKILL_HOLY_VALOR,SIN_SKILL_USE_RIGHT,Holy_Valor_Mana},

{"聖武劍擊",			"攻擊有效半徑內的所有敵人。",
23,		38,2,		82,2,
{0,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0},
F_Brandish,SKILL_BRANDISH,SIN_SKILL_USE_ALL,Brandish_Mana},

{"狂亂猛擊",			"以強烈的肉體力量與精神力量擊殺敵人。",
26,		41,2,		82,2,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0},
F_Piercing,SKILL_PIERCING,SIN_SKILL_USE_ALL,Piercing_Mana},

{"鋼鐵精神",	"一定時間內提高防禦力。",
30,		44,2,		100,2,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Drastic_Spirit,SKILL_DRASTIC_SPIRIT,SIN_SKILL_USE_RIGHT,Drastic_Spirit_Mana},



{"漂浮盾技",		"將盾牌飛射投擲，攻擊敵人，可以貫穿並使敵人動作停頓。",
10,		23,2,		82,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0},
F_S_Strike ,SKILL_SHIELD_STRIKE,SIN_SKILL_USE_RIGHT,S_Strike_UseMana },

{"飄花槍術",			"快速閃動的長槍，飛散如花瓣飄飄般的殘影，以急速攻擊來消滅敵人。",
12,		26,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Farina,SKILL_FARINA,SIN_SKILL_USE_ALL,Farina_UseMana},

{"投槍之術",		"裝備投槍類的武器，其攻擊力會永久上升，發揮強力遠距離攻擊。",
14,		0,0,		0,0,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_D_Mastery,SKILL_THROWING_MASTERY,SIN_SKILL_USE_NOT,0},

{"魄力槍擊",			"聚氣於投槍之上攻擊敵人，產生加成的傷害。",
17,		32,2,		82,2,
{0,0,0},			{sinWP1,sinWT1,0,0,0,0,0,0},
F_V_Spear,SKILL_VIGOR_SPEAR,SIN_SKILL_USE_ALL,V_Spear_UseMana},

{"御風槍術",			"使槍能投射更遠，更能命中遠方敵人。",
20,		34,2,		100,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Windy,SKILL_WINDY,SIN_SKILL_USE_RIGHT,Windy_Mana},

{"迴旋雙擊",	"在攻擊的同時旋轉槍，使攻擊力與命中率提高。",
23,		36,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Twist_Javelin,SKILL_TWIST_JAVELIN,SIN_SKILL_USE_RIGHT,Twist_Javelin_Mana},

{"吸魂大法",	"吸收敵人的生命值。",
26,		42,2,		110,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0},
F_Soul_Sucker,SKILL_SOUL_SUCKER,SIN_SKILL_USE_RIGHT,Soul_Sucker_Mana},

{"火炎槍法",	"把火之力灌注到槍上，給予敵人傷害。",
30,		40,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Fire_Javelin,SKILL_FIRE_JAVELIN,SIN_SKILL_USE_ALL,Fire_Javelin_Mana},


{"治癒之術",			 "藉由聖潔的力量，使對象之生命力恢復。",
10,		15,2,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Healing,SKILL_HEALING,SIN_SKILL_USE_RIGHT,Healing_UseMana},

{"神聖衝擊",			"以神聖的氣攻擊敵人，對不死系怪物更是有效。",
12,		11,2,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_HolyBolt,SKILL_HOLY_BOLT,SIN_SKILL_USE_RIGHT,HolyBolt_UseMana},

{"閃光之術",			 "用聖潔之光迸射出碎片，來攻擊大範圍的敵人。",
14,		14,2,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_M_Spark,SKILL_MULTISPARK,SIN_SKILL_USE_RIGHT,M_Spark_UseMana},

{"神聖精神",			"以神聖的禱告，弱化敵人的邪惡之力。",
17,		19,2,		100,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_HolyMind,SKILL_HOLY_MIND,SIN_SKILL_USE_RIGHT,HolyMind_UseMana},

{"聖潔心境",		"永久提升魔法值恢復能力。",
20,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Meditation,SKILL_MEDITATION,SIN_SKILL_USE_NOT,0},

{"神之審判",	"藉由神的力量招喚閃電，懲罰敵人。",
23,		21,2,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Divine_Lightning,SKILL_DIVINE_LIGHTNING,SIN_SKILL_USE_RIGHT,Divine_Lightning_Mana},

{"神聖盾牌",	"產生出神聖的魔法盾牌，反射不死系怪獸的攻擊。.",
26,		23,2,		100,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Holy_Reflection,SKILL_HOLY_REFLECTION,SIN_SKILL_USE_RIGHT,Holy_Reflection_Mana},

{"強力治療",	"恢復隊員的生命值。",
30,		27,2,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Grand_Healing,SKILL_GRAND_HEALING,SIN_SKILL_USE_RIGHT,Grand_Healing_Mana},



{"神聖轉換",			"將自身的生命力轉換成魔法力，迅速補充魔法值。",
10,		12,2,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Agony,SKILL_AGONY,SIN_SKILL_USE_RIGHT,Agony_UseMana},

{"火炎之術",			"發射魔法火炎攻擊敵人。",
12,		11,2,		84,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_FireBolt,SKILL_FIRE_BOLT,SIN_SKILL_USE_ALL,FireBolt_UseMana},

{"元素操弄",			"以強大的精神力，在一定的時間提升元素屬性，使防禦加成。",
14,		15,2,		100,3,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Zenith,SKILL_ZENITH,SIN_SKILL_USE_RIGHT,Zenith_UseMana},

{"火球之術",			"以可怕的強烈魔法火團，攻擊大範圍的敵人。",
17,		19,2,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_FireBall,SKILL_FIRE_BALL,SIN_SKILL_USE_RIGHT,FireBall_UseMana},

{"精神統一",	"增加魔法值最大值。",
20,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Mental_Mastery,SKILL_MENTAL_MASTERY,SIN_SKILL_USE_NOT,0},

{"水龍捲擊",	"使用像龍捲風一樣的「水龍捲」攻擊敵人。",
23,		21,2,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Watornado,SKILL_WATORNADO,SIN_SKILL_USE_RIGHT,Watornado_Mana},

{"元素增力",	"把元素屬性賦予到隊員的武器上。",
26,		28,2,		110,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Enchant_Weapon,SKILL_ENCHANT_WEAPON,SIN_SKILL_USE_RIGHT,Enchant_Weapon_Mana},

{"光擊之術",	"在手掌聚集光之法力，發射強烈的光線來攻擊敵人。",
30,		26,2,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Dead_Ray,SKILL_DEAD_RAY,SIN_SKILL_USE_ALL,Dead_Ray_Mana},
