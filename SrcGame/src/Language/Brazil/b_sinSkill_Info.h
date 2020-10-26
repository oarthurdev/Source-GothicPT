#define SIN_SKILL_USE_RIGHT 0x01000000 
#define SIN_SKILL_USE_LEFT 0x02000000 
#define SIN_SKILL_USE_ALL 0x03000000 
#define SIN_SKILL_USE_NOT 0x04000000 





{ "Escudo Extremo", "Aumenta o Bloqueio de Escudos, temporariamente",
10, 34, 2, 110, 4,
{ 0,0,0 }, { sinDS1,0,0,0,0,0,0,0 },
F_Extreme_Shield, SKILL_EXTREME_SHIELD, SIN_SKILL_USE_ALL, E_Shield_UseMana },

{ "Bomba Mecânica", "Arremessa uma granada para ferir os inimigos em seu alcance",
12, 28,2, 73,3,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Mechanic_Bomb,SKILL_MECHANIC_BOMB,SIN_SKILL_USE_ALL,Mechanic_Bomb_UseMana },

{ "Resistência a Veneno", "Aumenta a Resistência a Veneno, permanentemente",
14, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Poison_Attribute,SKILL_POISON_ATTRIBUTE,SIN_SKILL_USE_NOT,0 },

{ "Absorção Física", "Aumenta, temporariamente, a capacidade de Absorção",
17, 30,2, 110,5,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Physical_Absorption,SKILL_PHYSICAL_ABSORB,SIN_SKILL_USE_ALL,P_Absor_bUseMana },

{ "Grande Golpe", "Carrega e desfere um golpe poderoso nos inimigos",
20, 38,2, 73,3,
{0,0,0}, {sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0},
F_Great_Smash,SKILL_GREAT_SMASH,SIN_SKILL_USE_ALL,G_Smash_UseMana },

{ "Maximizar", "Aumenta temporáriamente o Poder de ATQ Máximo da Arma equipada",
23, 41,2, 110,4,
{0,0,0}, {sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0},
F_Maximize,SKILL_MAXIMIZE,SIN_SKILL_USE_ALL,Maximize_UseMana },

{ "Automação", "Aperfeiçoa o uso de Armas de longo alcance, aumentando Vel. e Poder de ATQ",
26, 42,2, 110,4,
{0,0,0}, {sinWS1,sinWT1,0,0,0,0,0,0},
F_Automation,SKILL_AUTOMATION,SIN_SKILL_USE_ALL,Automation_UseMana },

{ "Spark", "Ataca os inimigos, utilizando esferas de energia concentrada",
30, 40,2, 82,2,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Spark,SKILL_SPARK,SIN_SKILL_USE_ALL,Spark_UseMana },

{ "Armadura Metálica", "Aumenta temporariamente a Def. de Armaduras especializadas para Mecânicos",
40, 48,2, 110,5,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Metal_Armor,SKILL_METAL_ARMOR,SIN_SKILL_USE_ALL,Metal_Armor_UseMana },

{ "Golpe Grandioso", "Desfere dois poderosos golpes com Poder e Taxa de ATQ adicionais",
43, 44,2, 82,2,
{0,0,0}, {sinWA1,sinWC1,sinWP1,sinWS2, sinWH1,0,0,0},
F_Grand_Smash,SKILL_GRAND_SMASH,SIN_SKILL_USE_ALL,Grand_Smash_UseMana },

{ "Mestre dos Mecânicos", "Aperfeiçoa o uso de Armas especializadas para Mecânicos",
46, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_M_W_Mastery,SKILL_MECHANIC_WEAPON,SIN_SKILL_USE_NOT,0 },

{ "Escudo Espinhoso",    "Escudo de energia que aumenta a Def. e fere inimigos ao atacarem. Dano baseado na habilidade Spark",
50, 52,2, 110,2,
{0,0,0}, {sinDS1,0,0,0,0,0,0,0},
F_Spark_Shield,SKILL_SPARK_SHIELD,SIN_SKILL_USE_ALL,Spark_Shield_UseMana },


{ "Impulso","Ataque duplo que libera uma forte descarga elétrica",
60,     55,2, 0,0,
{1,0,0},            {sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0},
F_Impulsion,SKILL_IMPULSION,SIN_SKILL_USE_ALL,Impulsion_UseMana },

{ "Implosão","Implosão que atrai inimigos e aumenta temporáriamente a Abs",
63,     65,2, 440,0,
{1,0,0},            {0,0,0,0,0,0,0,0},
F_Compulsion,SKILL_COMPULSION,SIN_SKILL_USE_ALL,Compulsion_UseMana },

{ "Esfera Magnética","Cria esferas magnéticas, que ferem os inimigos mais próximos",
66,     71,2, 600,0,
{1,0,0},            {0,0,0,0,0,0,0,0},
F_Magnetic_Sphere,SKILL_MAGNETIC_SPHERE,SIN_SKILL_USE_ALL,Magnetic_Sphere_UseMana },

{ "Golem de Metal","Invoca um Monstro de metal, para auxiliar nas batalhas",
70,     71,2, 1000,0,
{1,0,0},            {0,0,0,0,0,0,0,0},
F_Metal_Golem,SKILL_METAL_GOLEM,SIN_SKILL_USE_ALL,Metal_Golem_UseMana },



{ "Mestre das Armas", "Aumenta a eficiência de Machados, Garras, Martelos e Espadas, permanentemente",
10, 0,0, 0,0,
{0,0,0}, {sinWA1,sinWC1,sinWH1,sinWS2,0,0,0,0},
F_Melee_Mastery,SKILL_MELEE_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Resistência a Fogo", "Aumenta a Resistência a Fogo, permanentemente",
12, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Fire_Attribute,SKILL_FIRE_ATTRIBUTE,SIN_SKILL_USE_NOT,0 },

{ "Raiva", "Fica nervoso e mais letal, mas perde HP com o tempo",
14, 35,2, 93,3,
{0,0,0}, {sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0},
F_Raving,SKILL_RAVING,SIN_SKILL_USE_ALL,Raving_UseMana },

{ "Impacto", "Desfere golpes com Taxa e Poder de ATQ adicionais",
17, 37,2, 86,4,
{0,0,0}, {sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0},
F_Impact,SKILL_IMPACT,SIN_SKILL_USE_ALL,Impact_UseMana },

{ "Impacto Triplo", "Versão aprimorada de 'Impacto'",
20, 39,2, 80,4,
{0,0,0}, {sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0},
F_Triple_Impact,SKILL_TRIPLE_IMPACT,SIN_SKILL_USE_ALL,T_Impact_UseMana },

{ "Girada Brutal", "Desfere um poderoso golpe com Crítico adicional",
23, 41,2, 82,2,
{0,0,0}, {sinWA1,sinWS2,0,0,0,0,0,0},
F_Brutal_Swing,SKILL_BRUTAL_SWING,SIN_SKILL_USE_ALL,B_Swing_UseMana },

{ "Rugido", "Atordoa, temporáriamente, os inimigos.",
26, 39,2, 112,4,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Roar,SKILL_ROAR,SIN_SKILL_USE_ALL,Roar_UseMana },

{ "Fúria de Zecram", "Salta enquanto golpeia o chão com a Arma, causando dano por Fogo",
30, 45,2, 84,4,
{0,0,0}, {sinWA1,sinWH1,sinWS2,0,0,0,0,0},
F_RageOfZecram,SKILL_RAGE_OF_ZECRAM,SIN_SKILL_USE_ALL,R_Zecram_UseMana },

{ "Concentração", "Aumenta, temporáriamente, a Taxa de ATQ.",
40, 53,2, 110,3,
{0,0,0}, {sinWA1,sinWS2,0,0,0,0,0,0},
F_Concentration,SKILL_CONCENTRATION,SIN_SKILL_USE_ALL,Concentration_UseMana },

{ "Golpe da Vingança", "Ataque poderoso, com Poder e Taxa de ATQ adicionais.",
43, 48,2, 73,3,
{0,0,0}, {sinWA1,sinWP1,sinWS2,0,0,0,0,0},
F_Avanging_Crash,SKILL_AVANGING_CRASH,SIN_SKILL_USE_ALL,A_Crash_UseMana },

{ "Machado Veloz", "Aumenta, temporariamente, a Vel. de ATQ com Machados.",
46, 53,2, 200,3,
{0,0,0}, {sinWA1,0,0,0,0,0,0,0},
F_Swift_Axe,SKILL_SWIFT_AXE,SIN_SKILL_USE_ALL,Swift_Axe_UseMana },

{ "Quebra Ossos", "Ataque múltiplo, com dano adicional contra Demônios.",
50, 54,2, 73,3,
{0,0,0}, {sinWA1,sinWP1,sinWS2,0,0,0,0,0},
F_Bone_Crash,SKILL_BONE_CRASH,SIN_SKILL_USE_ALL,B_Crash_UseMana },


{ "Destroyer", "Ataque múltiplo fatal.",
60, 45,2, 150,0,
{1,0,0}, {sinWA1,sinWH1,0,0,0,0,0,0},
F_Destoryer,SKILL_DETORYER,SIN_SKILL_USE_ALL,Destoryer_UseMana },

{ "Fúria","Aumenta a força do Lutador, mas diminui, considerávelmente, a Abs.",
63, 60,2, 700,0,
{1,0,0}, {0,0,0,0,0,0,0,0},
F_Berserker,SKILL_BERSERKER,SIN_SKILL_USE_ALL,Berserker_UseMana },

{ "Golpe Giratório","Golpe múltiplo e giratório letal a grupos de inimigos.",
66, 55,2, 0,0,
{1,0,0}, {sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0},
F_Cyclone_Strike,SKILL_CYCLONE_STRIKE,SIN_SKILL_USE_ALL,Cyclone_Strike_UseMana },

{ "Bônus de Vitalidade","Aumenta, permanentemente, o HP total.",
70, 0,0, 0,0,
{1,0,0}, {0,0,0,0,0,0,0,0},
F_Boost_Health,SKILL_BOOST_HEALTH,SIN_SKILL_USE_NOT, },


{ "Sopro Afiado", "Lança a foice para o alto, fazendo os inimigos recuar",
10, 27,2, 80,4,
{0,0,0}, {sinWP1,0,0,0,0,0,0,0},
F_Pike_Wind,SKILL_PIKE_WIND,SIN_SKILL_USE_ALL,Pike_Wind_UseMana },

{ "Resistência a Gelo", "Aumenta a Resistência a Gelo, permanentemente",
12, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Ice_Attribute,SKILL_ICE_ATTRIBUTE,SIN_SKILL_USE_NOT,0 },

{ "Ataque Crítico", "Busca o ponto fraco do inimigo, atacando com Crítico aperfeiçoado",
14, 31,2, 84,3,
{0,0,0}, {sinWP1,sinWC1,sinWH1,sinWS2,0,0,0,0},
F_Critical_Hit,SKILL_CRITICAL_HIT,SIN_SKILL_USE_ALL,Critical_Hit_UseMana },

{ "Pulo Fatal", "Explode no ar, com um giro fatal, que fere o inimigo",
17, 34,2, 76,4,
{0,0,0}, {sinWA1,sinWP1,sinWS2,0,0,0,0,0},
F_Jumping_Crash,SKILL_JUMPING_CRASH,SIN_SKILL_USE_ALL,Jumping_Crash_UseMana },

{ "Espinhos de Gelo", "Espinhos de gelo surgem e paralisam os inimigos por um tempo",
20, 36,2, 84,4,
{0,0,0}, {sinWP1,0,0,0,0,0,0,0},
F_Ground_Pike,SKILL_GROUND_PIKE,SIN_SKILL_USE_ALL,G_Pike_UseMana },

{ "Tornado", "Ataque giratório letal para os inimigos",
23, 38,2, 00,0,
{0,0,0}, {sinWP1,0,0,0,0,0,0,0},
F_Tornado_Pike,SKILL_TORNADO,SIN_SKILL_USE_ALL,Tornado_UseMana },

{ "Mestre da Def.", "Aumenta permanentemente o Bloqueio com Foices de duas mãos",
26, 0,0, 0,0,
{0,0,0}, {sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0},
F_Weapone_Defence_Mastery,SKILL_WEAPONE_DEFENCE_MASTERY,SIN_SKILL_USE_NOT,0 },


{ "Expansão", "Desfere um golpe letal",
30, 42,2, 82,4,
{0,0,0}, {sinWA1,sinWH1,sinWP1,0,0,0,0,0},
F_Expansion,SKILL_EXPANSION,SIN_SKILL_USE_ALL,Expansion_UseMana },

{ "Lanças Venenosas", "Ataque rápido, que envenena os inimigos.",
40, 50,2, 110,2,
{0,0,0}, {sinWP1,0,0,0,0,0,0,0},
F_Venom_Spear,SKILL_VENOM_SPEAR,SIN_SKILL_USE_ALL,VenomSpear_UseMana },

{ "Desaparecer", "Torna-o invisível, temporariamente",
43, 53,2, 140,2,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Vanish,SKILL_VANISH,SIN_SKILL_USE_ALL,Vanish_UseMana },

{ "Mestre do ATQ Crítico", "Treina o uso de Foices, aumentando a Taxa de Crítico permanentemente",
46, 0,0, 0,0,
{0,0,0}, {sinWP1,0,0,0,0,0,0,0},
F_Critical_Mastery,SKILL_CRITICAL_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Foice de Aço",     "Ataque giratório triplo",
50, 51,2, 00,0,
{0,0,0}, {sinWC1,sinWP1,sinWS2,0,0,0,0,0},
F_Chain_Lance,SKILL_CHAIN_LANCE,SIN_SKILL_USE_ALL,Chain_Lance_UseMana },


{ "Olho Assassino", "Encontra o ponto fraco dos monstros, aumentando a Taxa de Crítico",
60, 61,2, 520,0,
{1,0,0}, {sinWP1,0,0,0,0,0,0,0},
F_Assassin_Eye,SKILL_ASSASSIN_EYE,SIN_SKILL_USE_ALL,Assassin_Eye_UseMana },

{ "Golpe Carregado", "Desfere golpes letais, após se concentrar",
63, 75,2, 150,0,
{1,0,0}, {sinWP1,sinWS2,0,0,0,0,0,0},
F_Charging_Strike,SKILL_CHARGING_STRIKE,SIN_SKILL_USE_ALL,Charging_Strike_UseMana },

{ "Furtivo", "Aumenta a furtividade do personagem",
66, 71,2, 650,0,
{1,0,0}, {sinWP1,0,0,0,0,0,0,0},
F_Vague,SKILL_VAGUE,SIN_SKILL_USE_ALL,Vague_UseMana },

{ "Mestre das Sombras", "Ataque múltiplo de sombras misteriosas, para destruir o inimigo.",
70, 51,2, 160,0,
{1,0,0}, {sinWP1,sinWS2,0,0,0,0,0,0},
F_Shadow_Master,SKILL_SHADOW_MASTER,SIN_SKILL_USE_ALL,Shadow_Master_UseMana },



{ "Falcão Vigia", "Invoca um falcão para vigiar a área, aumentando a Taxa de ATQ",
10, 25,2, 115,5,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Scout_Hawk ,SKILL_SCOUT_HAWK,SIN_SKILL_USE_ALL,Scout_Hawk_UseMana },

{ "Mestra do Tiro", "Aumenta, permanentemente, o Poder de ATQ com Arcos",
12, 0,0, 0,0,
{0,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_Shooting_Mastery,SKILL_SHOOTING_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Flecha de Vento", "Dispara uma flecha de Vento, com Vel. adicional",
14, 25,2, 82,3,
{0,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_Wind_Arrow,SKILL_WIND_ARROW,SIN_SKILL_USE_ALL,Wind_Arrow_UseMana },

{ "Mira Perfeita", "Desfere um tiro certeiro, com Taxa e Poder de ATQ adicionais",
17, 29,2, 81,3,
{0,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_Perfect_Aim,SKILL_PERFECT_AIM,SIN_SKILL_USE_ALL,Perfect_Aim_UseMana },

{ "Olho de Dion", "Treina a pontaria, aumentando a Taxa de ATQ, permanentemente",
20, 0,0, 0,0,
{0,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_Dions_Eye,SKILL_DIONS_EYE,SIN_SKILL_USE_NOT,0 },

{ "Falcão", "Invoca um falcão, para abater os inimigos",
23, 36,2, 115,4,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Falcon ,SKILL_FALCON,SIN_SKILL_USE_ALL,Falcon_UseMana },

{ "Flecha da Fúria", "Rajada fatal, que explode e fere um grupo de inimigos",
26, 38,2, 82,4,
{0,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_Arrow_of_Rage,SKILL_ARROW_OF_RAGE,SIN_SKILL_USE_ALL,A_Rage_UseMana },

{ "Avalanche", "Lança uma seqüência de flechas perfuradoras, para destruir os inimigos",
30, 41,2, 00,0,
{0,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_Avalanche,SKILL_AVALANCHE,SIN_SKILL_USE_ALL,Avalanche_UseMana },

{ "Tiro Elemental", "Disparos de fogo ou gelo, para abater os inimigos",
40, 43,2, 82,2,
{0,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_E_Shot,SKILL_ELEMENTAL_SHOT,SIN_SKILL_USE_ALL,Elemental_Shot_UseMana },

{ "Falcão Dourado", "Invoca um falcão, com dano adicional e que aumenta a regeneração de HP",
43, 52,2, 120,4,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_G_Falcon,SKILL_GOLDEN_FALCON,SIN_SKILL_USE_ALL,Golden_Falcon_UseMana },

{ "Tiro Explosivo",     "Dispara duas flechas explosivas, causando dano por área.",
46, 46,2, 87,3,
{0,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_B_Shot,SKILL_BOMB_SHOT,SIN_SKILL_USE_ALL,BombShot_UseMana },

{ "Perfuração", "Ataque preciso e contínuo, que atravessa os inimigos.",
50, 48,2, 00,0,
{0,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_Perforation,SKILL_PERFORATION,SIN_SKILL_USE_ALL,Perforation_UseMana },


{ "Invocar Wolverine", "Invoca um Wolverine.",
60, 58,2, 900,0,
{1,0,0}, {0,0,0,0,0,0,0,0},
F_Recall_Wolverin,SKILL_RECALL_WOLVERIN,SIN_SKILL_USE_ALL,Recall_Wolverin_UseMana },

{ "Mestra da Esquiva", "Aumenta a Esquiva, para desviar melhor dos ataques inimigos.",
63, 0,0, 0,0,
{1,0,0}, {0,0,0,0,0,0,0,0},
F_Evasion_Mastery,SKILL_EVASION_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Tiro Fênix", "Tiro explosivo, com a força da Fênix.",
66, 55,2, 100,0,
{1,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_Phoenix_Shot,SKILL_PHOENIX_SHOT,SIN_SKILL_USE_ALL,Phoenix_Shot_UseMana },

{ "Força da Natureza","Aumenta seus poderes, pela força da natureza.",
70, 56,2, 900,0,
{1,0,0}, {sinWS1,0,0,0,0,0,0,0},
F_Force_Of_Nature,SKILL_FORCE_OF_NATURE,SIN_SKILL_USE_ALL,Force_Of_Nature_UseMana },






{ "Rajada Sagrada", "Rajada divina que fere os inimigos",
10, 22,2, 82,2,
{0,0,0}, {sinWS2,0,0,0,0,0,0,0},
F_Sword_Blast,SKILL_SWORD_BLAST,SIN_SKILL_USE_ALL,Sword_Blast_UseMana },

{ "Corpo Sagrado", "Recebe a bênção divina, para aumentar a Abs. contra Mortos Vivos",
12, 28,2, 110,3,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_HolyBody ,SKILL_HOLY_BODY,SIN_SKILL_USE_ALL,HolyBody_UseMana },

{ "Treinamento Físico", "Aumenta a RES, permanentemente",
14, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Physical_Traning,SKILL_PHYSICAL_TRANING,SIN_SKILL_USE_NOT,0 },

{ "Golpe Duplo", "Ataque duplo, veloz e letal.",
17, 35,2, 82,2,
{0,0,0}, {sinWA1,sinWC1,sinWS2,0,0,0,0,0},
F_Double_Crash,SKILL_DOUBLE_CRASH,SIN_SKILL_USE_ALL,D_Crash_UseMana },

{ "Valor Sagrado", "Aumenta, temporariamente, o Poder de ATQ contra mortos vivos",
20, 36,2, 100,3,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Holy_Valor,SKILL_HOLY_VALOR,SIN_SKILL_USE_ALL,Holy_Valor_Mana },

{ "Brandish", "Ataca os inimigos, causando dano por área",
23, 38,2, 82,2,
{0,0,0}, {sinWP1,sinWS2,0,0,0,0,0,0},
F_Brandish,SKILL_BRANDISH,SIN_SKILL_USE_ALL,Brandish_Mana },

{ "Piercing", "Carrega a espada com um ataque que atravessa seus alvos",
26, 41,2, 82,2,
{0,0,0}, {sinWS2,0,0,0,0,0,0,0},
F_Piercing,SKILL_PIERCING,SIN_SKILL_USE_ALL,Piercing_Mana },

{ "Espírito Drástico", "Aumenta a Def., por um período determinado.",
30, 44,2, 100,2,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Drastic_Spirit,SKILL_DRASTIC_SPIRIT,SIN_SKILL_USE_ALL,Drastic_Spirit_Mana },

{ "Mestre da Espada", "Treina o uso de espadas, aumentando o Poder de ATQ, permanentemente.",
40, 0,0, 0,0,
{0,0,0}, {sinWS2,0,0,0,0,0,0,0},
F_S_Mastery,SKILL_SWORD_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Escudo Divino", "Absorve o ATQ de Mortos Vivos, convertendo-o para HP.",
43, 46,2, 130,1,
{0,0,0}, {sinDS1,0,0,0,0,0,0,0},
F_D_Inhalation,SKILL_DIVINE_INHALATION,SIN_SKILL_USE_ALL,D_Inhalation_UseMana },

{ "Encantamento Sagrado", "Encanto sagrado que converte mortos-vivos em aliados",
46, 50,2, 120,1,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Holy_Incantation,SKILL_HOLY_INCANTATION,SIN_SKILL_USE_ALL,H_Incantation_UseMana },

{ "Grande Cruzada", "Golpe duplo e veloz, para derrubar os inimigos.",
50, 45,2, 82,2,
{0,0,0}, {sinWH1,sinWS2,0,0,0,0,0,0},
F_Grand_Cross,SKILL_GRAND_CROSS,SIN_SKILL_USE_ALL,Grand_Cross_UseMana },


{ "Piercing Divino", "Desfere uma seqüência letal de golpes, com a bênção sagrada ao final",
70, 51,2, 160,0,
{1,0,0}, {sinWS2,0,0,0,0,0,0,0},
F_Divine_Piercing,SKILL_DIVINE_PIERCING,SIN_SKILL_USE_ALL,Divine_Piercing_UseMana },

{ "Escudo dos deuses", "Cria um escudo divino, dando proteção extrema ao Cavaleiro",
63, 50,2, 400,0,
{1,0,0}, {sinDS1,0,0,0,0,0,0,0},
F_Godly_Shield,SKILL_GODLY_SHIELD,SIN_SKILL_USE_ALL,Godly_Shield_UseMana },

{ "Bênção Divina", "Invoca a força divina, para aumentar o poder de ATQ, temporariamente",
66, 51,2, 330,0,
{1,0,0}, {sinWS2,0,0,0,0,0,0,0},
F_God_Bless,SKILL_GOD_BLESS,SIN_SKILL_USE_ALL,God_Bless_UseMana },

{ "Espada da Justiça","Poderoso ataque em área com dano adicional",
60, 53,2, 250,0,
{1,0,0}, {sinWS2,0,0,0,0,0,0,0},
F_Sword_Of_Justice,SKILL_SWORD_OF_JUSTICE,SIN_SKILL_USE_ALL,Sword_Of_Justice_UseMana },

/// TIER 5
{ "Soul Breaker",	"Tâìn công maònh meÞ vaÌo  linh hôÌn cuÒa ðôìi phýõng",
80,	69,2, 73,0,
{ 2,0,0 },{ sinWS2,0,0,0,0,0,0,0 },
F_Soul_Breaker,SKILL_SOUL_BREAKER,SIN_SKILL_USE_RIGHT,Soul_Breaker_UseMana },



{ "Golpe do Escudo", "Atira o escudo ferindo inimigos e paralizando-os temporariamente",
10, 23,2, 82,2,
{0,0,0}, {sinDS1,0,0,0,0,0,0,0},
F_S_Strike ,SKILL_SHIELD_STRIKE,SIN_SKILL_USE_ALL,S_Strike_UseMana },

{ "Farina", "Arremessa uma lança Fantasma no alvo com grande precisão",
12, 26,2, 82,2,
{0,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_Farina,SKILL_FARINA,SIN_SKILL_USE_ALL,Farina_UseMana },

{ "Mestra do Arremesso", "Treina a perfeição dos arremessos e aumenta o Poder de ATQ, permanentemente",
14, 0,0, 0,0,
{0,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_D_Mastery,SKILL_THROWING_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Lança Gigante", "Ataca os inimigos, com a força divina",
17, 32,2, 82,2,
{0,0,0}, {sinWP1,sinWT1,0,0,0,0,0,0},
F_V_Spear,SKILL_VIGOR_SPEAR,SIN_SKILL_USE_ALL,V_Spear_UseMana },

{ "Windy", "Aumenta o Alcance e a Taxa de ATQ de suas Lanças",
20, 34,2, 100,2,
{0,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_Windy,SKILL_WINDY,SIN_SKILL_USE_ALL,Windy_Mana },

{ "Lança Giratória", "Aumenta a Taxa e o Poder de ATQ, a cada ataque",
23, 36,2, 82,2,
{0,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_Twist_Javelin,SKILL_TWIST_JAVELIN,SIN_SKILL_USE_ALL,Twist_Javelin_Mana },

{ "Ladrão de Almas", "Absorve o HP dos inimigos",
26, 42,2, 110,2,
{0,0,0}, {sinDS1,0,0,0,0,0,0,0},
F_Soul_Sucker,SKILL_SOUL_SUCKER,SIN_SKILL_USE_ALL,Soul_Sucker_Mana },

{ "Lança de Fogo", "Ataca os inimigos, com o poder do Fogo",
30, 40,2, 82,2,
{0,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_Fire_Javelin,SKILL_FIRE_JAVELIN,SIN_SKILL_USE_ALL,Fire_Javelin_Mana },

{ "Lança Partida", "Ataque múltiplo, veloz e letal aos inimigos",
40, 43,2, 115,1,
{0,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_Split_Javelin,SKILL_SPLIT_JAVELIN,SIN_SKILL_USE_ALL,Split_Javelin_UseMana },

{ "Triunfo de Valhalla", "Concede ao alvo o poder de Valhalla, aumentando o dano máximo",
43, 50,2, 120,1,
{0,0,0}, {sinWT1,sinWS2,sinWS1,sinWP1,sinWH1,sinWA1,sinWC1,sinWM1},
F_T_Of_Valhalla,SKILL_TRIUMPH_OF_VALHALLA,SIN_SKILL_USE_ALL,T_Of_Valhalla_UseMana },

{ "Lança de Raio", "Adiciona dano elemental às Lanças.",
46, 46,2, 82,2,
{0,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_Lightning_Javelin,SKILL_LIGHTNING_JAVELIN,SIN_SKILL_USE_ALL,Lightning_Javelin_UseMana },

{ "Chuva de Lanças",    "Arremessa Lanças como devastadores espirais que destroem tudo em seu caminho",
50, 48,2, 00,0,
{0,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_Storm_Javelin,SKILL_STORM_JAVELIN,SIN_SKILL_USE_ALL,Storm_Javelin_UseMana },


{ "Inferno de Valhalla", "Aumenta temporariamente a Evasão, usando o poder máximo de Valhalla",
60, 52,2, 750,0,
{1,0,0}, {sinWA1,sinWC1,sinWH1,sinWP1,sinWS1,sinWT1,0,0},
F_Hall_Of_Valhalla,SKILL_HALL_OF_VALHALLA,SIN_SKILL_USE_ALL,Hall_Of_Valhalla_UseMana },

{ "Fúria-X", "Pula ao ar e atira 3 lanças explosivas ferindo todo inimigos na área",
63, 48,2, 0,0,
{1,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_X_Rage,SKILL_X_RAGE,SIN_SKILL_USE_ALL,X_Rage_UseMana },

{ "Lança de Gelo", "Temporariamente encanta a Lança com elemento gelo, reduzindo a velocidade dos inimigos quando atingidos",
66, 50,2, 720,0,
{1,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_Frost_Javelin,SKILL_FROST_JAVELIN,SIN_SKILL_USE_ALL,Frost_Javelin_UseMana },

{ "Vingança", "Ataque rápido, múltiplo e letal",
70, 55,2, 100,0,
{1,0,0}, {sinWT1,0,0,0,0,0,0,0},
F_Vengeance,SKILL_VENGEANCE,SIN_SKILL_USE_ALL,Vengeance_UseMana },


{ "Cura",  "Cura os personagens escolhidos com a bênção divina",
10, 15,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Healing,SKILL_HEALING,SIN_SKILL_USE_ALL,Healing_UseMana },

{ "Fagulha Sagrada", "Faísca mágica para ferir os inimigos",
12, 11,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_HolyBolt,SKILL_HOLY_BOLT,SIN_SKILL_USE_ALL,HolyBolt_UseMana },

{ "Espinhos Múltiplos", "Dispara fagulhas mágicas, para abater os inimigos",
14, 14,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_M_Spark,SKILL_MULTISPARK,SIN_SKILL_USE_ALL,M_Spark_UseMana },

{ "Feitiço Divino", "Encanta e reduz o Poder de ATQ dos inimigos",
17, 19,1, 100,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_HolyMind,SKILL_HOLY_MIND,SIN_SKILL_USE_ALL,HolyMind_UseMana },

{ "Meditação", "Aumenta o Regen de Mana, permanentemente",
20, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Meditation,SKILL_MEDITATION,SIN_SKILL_USE_NOT,0 },

{ "Raios Divinos", "Relâmpagos divinos caem das nuvens atingindo os inimigos",
23, 21,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Divine_Lightning,SKILL_DIVINE_LIGHTNING,SIN_SKILL_USE_ALL,Divine_Lightning_Mana },

{ "Reflexão Divina", "Reflete o ataque de Mortos Vivos, ao criar um escudo mágico.",
26, 23,1, 120,1,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Holy_Reflection,SKILL_HOLY_REFLECTION,SIN_SKILL_USE_ALL,Holy_Reflection_Mana },

{ "Cura Máxima", "Cura os membros do Grupo.",
30, 27,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Grand_Healing,SKILL_GRAND_HEALING,SIN_SKILL_USE_ALL,Grand_Healing_Mana },

{ "Esferas de Vigor", "Dispara duas esferas luminosas letais contra os inimigos.",
40, 24,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Vigor_Ball,SKILL_VIGOR_BALL,SIN_SKILL_USE_ALL,Vigor_Ball_UseMana },

{ "Ressurreição", "Permite trazer um membro do grupo de volta a vida",
43, 31,1, 130,1,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Resurrection,SKILL_RESURRECTION,SIN_SKILL_USE_ALL,Resurrection_UseMana },

{ "Extinção", "Lança um feitiço que destrói parte do HP dos Mortos Vivos",
46, 28,1, 150,1,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Extinction,SKILL_EXTINCTION,SIN_SKILL_USE_ALL,Extinction_UseMana },

{ "HP Virtual", "Aumenta o HP do alvo temporariamente",
50, 31,1, 00,0,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Virtual_Life,SKILL_VIRTUAL_LIFE,SIN_SKILL_USE_ALL,Virtual_Life_UseMana },


{ "Espinhos Glaciais", "Lâminas afiadas de gelo projetam do chão contra os inimigos",
60, 35,1, 120,0,
{1,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Glacial_Spike,SKILL_GLACIAL_SPIKE,SIN_SKILL_USE_ALL,Glacial_Spike_UseMana },

{ "Campo de Regen", "Gera um campo que acelera o regen de HP e MP do grupo, em troca da sua imobilidade",
63, 41,1, 950,0,
{1,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Regeneration_Field,SKILL_REGENERATION_FIELD,SIN_SKILL_USE_RIGHT,Regeneration_Field_UseMana },

{ "Raios Contínuos", "Gera uma corrente de ataques elétricos que atinge alvos em proximidade",
66, 41,1, 0,0,
{1,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Chain_Lightning,SKILL_CHAIN_LIGHTNING,SIN_SKILL_USE_ALL,Chain_Lightning_UseMana },

{ "Invocar Muspell", "Anjo que batalha e protege a Celestial, aumentando seu Bloqueio e sua Abs. contra MortosVivos",
70, 47,1, 800,0,
{1,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Summon_Muspell,SKILL_SUMMON_MUSPELL,SIN_SKILL_USE_ALL,Summon_Muspell_UseMana },


{ "Agonia", "Sacrifica o HP, para restaurar o MP",
10, 12,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Agony,SKILL_AGONY,SIN_SKILL_USE_ALL,Agony_UseMana },

{ "Fagulha", "Dispara pequenas fagulhas, para ferir os inimigos",
12, 11,1, 84,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_FireBolt,SKILL_FIRE_BOLT,SIN_SKILL_USE_ALL,FireBolt_UseMana },

{ "Zenith", "Aumenta a resistência elemental, durante determinado período",
14, 15,1, 100,3,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Zenith,SKILL_ZENITH,SIN_SKILL_USE_ALL,Zenith_UseMana },

{ "Bola de Fogo", "Dispara grandes bolas de fogo, para abater os inimigos",
17, 19,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_FireBall,SKILL_FIRE_BALL,SIN_SKILL_USE_ALL,FireBall_UseMana },

{ "Mestre da Mente", "Aumenta a Mana total",
20, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
F_Mental_Mastery,SKILL_MENTAL_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Watornado", "Um poderoso tornado d'agua é arremessado, explodindo contra os inimigos",
23, 21,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Watornado,SKILL_WATORNADO,SIN_SKILL_USE_ALL,Watornado_Mana },

{ "Encanto", "Encanta as Armas do grupo com elementais, aumentando o Poder de ATQ",
26, 28,1, 104,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Enchant_Weapon,SKILL_ENCHANT_WEAPON,SIN_SKILL_USE_ALL,Enchant_Weapon_Mana },

{ "Raio da Morte", "Um raio poderoso sai das mãos do Feiticeiro, pronto pra desintegrar um alvo",
30, 26,1, 82,2,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Dead_Ray,SKILL_DEAD_RAY,SIN_SKILL_USE_ALL,Dead_Ray_Mana },

{ "Escudo Energético", "Forma um escudo mágico, absorvendo parte dos ataques sofridos ao custo de mana",
40, 40,1, 150,1,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Energy_Shield,SKILL_ENERGY_SHIELD,SIN_SKILL_USE_ALL,Energy_Shield_UseMana },

{ "Terremoto", "Cria uma explosão devastadora, baseada no elemento 'terra'",
43, 33,1, 0,1,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Diastrophism,SKILL_DIASTROPHISM,SIN_SKILL_USE_ALL,Diastrophism_UseMana },

{ "Espírito Elemental", "Invoca um pequeno fantasma, para aumentar o dano mágico",
46, 35,1, 150,1,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Spirit_Elemental,SKILL_SPIRIT_ELEMENTAL,SIN_SKILL_USE_ALL,Spirit_Elemental_UseMana },

{ "Espada Dançante", "Uma espada fantasma aparece e ajuda a combater os inimigos com danos elementais",
50, 30,1, 150,1,
{0,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_D_Sword,SKILL_DANCING_SWORD,SIN_SKILL_USE_ALL,Dancing_Sword_UseMana },


{ "Chama Elemental", "Invoca uma criatura de Fogo, para derrotar os inimigos",
60, 120,2, 900,0,
{1,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Fire_Elemental,SKILL_FIRE_ELEMENTAL,SIN_SKILL_USE_ALL,Fire_Elemental_UseMana },

{ "Ondas de Fogo", "Ataca os monstros, com poderosas ondas incandescentes",
63, 32,1, 124,0,
{1,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Flame_Wave,SKILL_FLAME_WAVE,SIN_SKILL_USE_ALL,Flame_Wave_UseMana },

{ "Distorção", "Gera um pulso de energia, temporariamente reduzindo os atributos dos inimigos na área",
66, 43,1, 460,0,
{1,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Distortion,SKILL_DISTORTION,SIN_SKILL_USE_ALL,Distortion_UseMana },

{ "Meteóro", "Invoca uma chuva letal de Meteoros.",
70, 39,1, 82,0,
{1,0,0}, {sinWM1,0,0,0,0,0,0,0},
F_Meteo,SKILL_M_METEO,SIN_SKILL_USE_ALL,Meteo_UseMana },

{ "Ferrão",		"Se aproxima do inimigo, causando um dano permanente.",
10,	22, 2, 82, 1,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },
F_Stingger,SKILL_STINGGER,SIN_SKILL_USE_ALL,Stingger_UseMana },

{ "Ataque Duplo",		"Desfere dois ataques em sequência no inimigo.",
12,	27, 2,  82, 1,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },
F_R_Hit,SKILL_R_HIT,SIN_SKILL_USE_ALL,DoubleBlow_UseMana },

{ "Maestria em Adagas",			"Aumenta permanentemente o dano ao equipar Adagas.",
14,		0,0,		0,0,
{ 0,0,0 },{ 0,0,0,0,0,0,0,0 },
F_Meditation, SKILL_D_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Wisp",		"Reduz o poder de ataque do inimigo durante um tempo limitado.",
17,	19, 2, 100, 0,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },

F_Wisp,SKILL_WISP,SIN_SKILL_USE_ALL,Wisp_UseMana },

{ "Trono de Veneno",		"Acerta o inimigo dois ataques em sequência, utilizando um poder de veneno.",
20,	56, 2, 00, 0,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },

F_V_Throne,SKILL_V_THRONE,SIN_SKILL_USE_ALL,VenomThorn_UseMana },

{ "Alas",		"Utilizando da destreza da Assassina, garante esquiva adicional ao grupo.",
23,	41, 2,	100, 2,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },
F_Alas,SKILL_ALAS,SIN_SKILL_USE_ALL,Alas_UseMana },

{ "Choque na Alma",		"Com o poder de suas adagas, finca-as no chão, atordoando os inimigos em volta.",
26,		39,2,		82,2,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },

F_S_Shock,SKILL_S_SHOCK,SIN_SKILL_USE_ALL, SoulChock_UseMana },

{ "Maestria no Ataque",	"Aumenta permanentemente a evasão e a taxa de ataque.",
30,		0,0,		0,0,
{ 0,0,0 },{ 0,0,0,0,0,0,0,0 },
F_Meditation, SKILL_A_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Adaga Dolorida",		"Utilizando da sua agilidade, desfere um golpe contínuo, afiado e rápido no inimigo.",
40,		45,2,		52,4,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },

F_S_Sword,SKILL_S_SWORD,SIN_SKILL_USE_ALL,SoreSword_UseMana },

{ "Espancamento",		"Pula e desfere um golpe mortal rotatório no inimigo.",
43,		48,2,		00,0,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },

F_BeatUp,SKILL_B_UP,SIN_SKILL_USE_ALL,BeatUp_UseMana },

{ "Inpes",		"Utilizando-se de um alto grau de concentração, aumenta temporariamente a velocidade de ataque.",
46,		48,2,		110,5,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },
F_Inpes,SKILL_INPES,SIN_SKILL_USE_ALL,Inpes_UseMana },

{ "Sombria",	"Se esconde em sua própria sombra, dificultando a visão inimiga e aumentando seu poder de ataque.",
50,		53,2,		800,2,
{ 0,0,0 },{ sinWD1,0,0,0,0,0,0,0 },
F_Blind,SKILL_BLIND,SIN_SKILL_USE_ALL,Blind_UseMana },

{ "Vento Gelado",	"Movendo rapidamente o seu corpo, causa um dano fatal no inimigo.",
60,		53,2,		150,1,
{ 1,0,0 },{ sinWD1,0,0,0,0,0,0,0 },
F_FrostWind,SKILL_F_WIND,SIN_SKILL_USE_ALL,FrostWind_UseMana },

{ "Maestria Fatal",	"Aumenta permanentemente a chance de crítico ao equipar uma Adaga.",
63,		0,0,		0,0,
{ 1,0,0 },{ 0,0,0,0,0,0,0,0 },
F_Meditation, SKILL_F_MASTERY,SIN_SKILL_USE_NOT,0 },

{ "Violence Stab",	"Deals damage by repeatedly kicking the enemy.",
66,		55,2,		100,0,
{ 1,0,0 },{ sinWD1,0,0,0,0,0,0,0 },
F_ViolenceStab,SKILL_V_STAB,SIN_SKILL_USE_ALL,ViolenceStab_UseMana },

{ "Sombra Ninja",	"Entre em sua forma de sombra, atacando violentamente o inimigo.",
70,		51,2,		800,1,
{ 1,0,0 },{ sinWD1,0,0,0,0,0,0,0 },
F_PastingShadow,SKILL_P_SHADOW,SIN_SKILL_USE_ALL,PastingShadow_UseMana },

{ "Raio Negro",			"Com pedaços da escuridão, desfere um poder mágico contra o inimigo.",
10,		8,1,		84,2,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_DarkBolt,SKILL_DARKBOLT,SIN_SKILL_USE_ALL,DarkBolt_UseMana },
{ "Onda Negra",			"Realiza um ataque consecutivo de pedaços da escuridão no inimigo.",
12,		19,1,		82,2,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_DarkWave,SKILL_DARKWAVE,SIN_SKILL_USE_ALL,DarkWave_UseMana },
{ "Maldição Preguiçosa", "Utilizando-se dos poderes de maldição, diminui a velocidade e a taxa de ataque do inimigo.",
14,		20,1,		100,2,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_CurseLazy,SKILL_CURSELAZY,SIN_SKILL_USE_ALL,CurseLazy_UseMana },
{ "Paz Interior", "Através do treinamento mental, eleva uma energia permanente que aumenta permanentemente sua mana.",
17,		0,0,		0,0,
{ 0,0,0 },{ 0,0,0,0,0,0,0,0 },
F_Meditation, SKILL_L_PEACE,SIN_SKILL_USE_NOT,0 },

{ "Labareda Espiritual", "Invoca um poder mágico que desfere dano no inimigo.",
20,		11,1,		82,2,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_SpiritualFlare,SKILL_S_FLARE,SIN_SKILL_USE_ALL,SpiritualFlare_UseMana },

{ "Algemador", "Com o poder dos fantasmas, algema a alma do oponente temporariamente.",
23,		23,1,		100,2,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_SoulManacle,SKILL_S_MANACLE,SIN_SKILL_USE_ALL,SoulManacle_UseMana },

{ "Caçada", "Aumenta temporariamente o alcance do Xamã.",
26,		27,1,		100,2,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_ChasingHunt,SKILL_C_HUNT,SIN_SKILL_USE_ALL,ChasingHunt_UseMana },

{ "Advento Migal", "Invoca Migal, para temporariamente aumentar o poder de ataque.",
30,		28,1,		800,0,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_AdventMigal,SKILL_A_MIGAL,SIN_SKILL_USE_ALL,AdventMigal_UseMana },

{ "Chuva", "Invocando os Deuses da chuva, para aumentar temporariamente sua absorção.",
40,		31,1,		134,1,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_RainMaker,SKILL_R_MAKER,SIN_SKILL_USE_ALL,RainMaker_UseMana },

{ "Fantasmaria", "Controlando fantasmas amaldiçoados, invoca-os para atacar a área próxima.",
43,		33,1,		60,1,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_LandGhost,SKILL_L_GHOST,SIN_SKILL_USE_ALL,LandGhost_UseMana },

{ "Assombrar", "Com ajuda do fantasma, desfere um golpe e transforma parte do dano em vida.",
46,		35,1,		110,2,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_Haunt,SKILL_HAUNT,SIN_SKILL_USE_ALL,Haunt_UseMana },

{ "Arranhar", "Utilizando o fantasma como arma, arranha o oponente ferozmente.",
50,		32,1,		82,2,
{ 0,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_Scratch,SKILL_SCRATCH,SIN_SKILL_USE_ALL,Scratch_UseMana },

{ "Chamar Cavaleiro Sanguinário", "Através de magia negra, invoca um Cavaleiro Sanguinário amaldiçoado.",
60,		41,1,		900,1,
{ 1,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_RBloodyKnight,SKILL_R_KNIGHT,SIN_SKILL_USE_ALL,BloodyKnight_UseMana },

{ "Julgamento",			"Ataca o oponente com faixas de luz da escuridão.",
63,		41,1,		800,1,
{ 1,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_Judgement,SKILL_JUDGE,SIN_SKILL_USE_ALL,Judgement_UseMana },

{ "Advento Midranda",	"Invoca Midranda, para temporariamente aumentar a velocidade de ataque.",
66,		39,1,		800,1,
{ 1,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_AdventMidranda,SKILL_A_MIDRANDA,SIN_SKILL_USE_ALL,AdventMidranda_UseMana },

{ "Manhã de Oração",	"Utilizando os poderes de Midranda ou Migal, ataca o oponente próximo.",
70,		47, 1,		60, 1,
{ 1,0,0 },{ sinWN1,0,0,0,0,0,0,0 },
F_MourningOfPray,SKILL_M_PRAY,SIN_SKILL_USE_ALL,MourningOfPray_UseMana },


{ "Força Orb", "Aumenta o ATQ, de acordo com a Orb",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,SKILL_FORCE_ORB,0,0 },


{ "Desafio", "Caçar os monstros!",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,CHANGE_JOB3_QUEST,0,0 },


{ "Desafio", "Caçar os monstros!",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,CHANGE_ELEMENTARY_QUEST,0,0 },


{ "Absorção Extrema","+10 de Absorção, por uma semana",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,CLANSKILL_ABSORB,0,0 },

{ "Força Oculta","+10% de Poder de ATQ, por uma semana",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,CLANSKILL_ATTACK,0,0 },

{ "Instinto","+10% de Esquiva, por uma semana.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,CLANSKILL_EVASION,0,0 },


{ "Sacrifício de Pritos","Invencibilidade temporária. Poder de ATQ reduzido pela metade",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,SCROLL_INVULNERABILITY,0,0 },

{ "Precisão de Skronipe","Aumento de 5% no Ataque Crítico",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,SCROLL_CRITICAL,0,0 },

{ "Reflexo Selvagem","Aumento de 5% em Esquiva",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,SCROLL_EVASION,0,0 },

{ "Pedra da Revolta","Reduz o dano contra os Cristais de Fogo, em 50%",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_R_FIRECRYTAL,0,0 },

{ "Pedra da Revolta","Reduz o dano contra os Cristais de Gelo, em 50%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_R_ICECRYTAL,0,0 },

{ "Pedra da Revolta","Reduz o dano contra os Cristais de Raio, em 50%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_R_LINGHTINGCRYTAL,0,0 },

{ "Sentença de Morte ","Turbina o Poder de ATQ contra Lutadores, em 20%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_A_FIGHTER,0,0 },

{ "Sentença de Morte ","Turbina o Poder de ATQ contra Mecânicos, em 20%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_A_MECHANICIAN,0,0 },

{ "Sentença de Morte ","Turbina o Poder de ATQ contra Pikes, em 20%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_A_PIKEMAN,0,0 },

{ "Sentença de Morte ","Turbina o Poder de ATQ contra Arqueiras, em 20%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_A_ARCHER,0,0 },

{ "Sentença de Morte ","Turbina o Poder de ATQ contra Cavaleiros, em 20%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_A_KNIGHT,0,0 },

{ "Sentença de Morte ","Turbina o Poder de ATQ contra Atalantas, em 20%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_A_ATALANTA,0,0 },

{ "Sentença de Morte ","Turbina o Poder de ATQ contra Magos, em 20%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_A_MAGICIAN,0,0 },

{ "Sentença de Morte ","Turbina o Poder de ATQ contra Sacerdotisas, em 20%.",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,STONE_A_PRIESTESS,0,0 },

{ "Vida Eterna","Invencibilidade temporária. O ataque é reduzido pela 1/2",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,SCROLL_P_INVULNERABILITY,0,0 },

{ "Crítico Adicional","5% a mais de ataque crítico",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,SCROLL_P_CRITICAL,0,0 },

{ "Esquiva Adicional","15% a mais de esquiva",
0, 0,0, 0,0,
{0,0,0}, {0,0,0,0,0,0,0,0},
NULL,SCROLL_P_EVASION,0,0 },

{ "Chefe de Classe", "Adiciona 3% de ATK Pow e 50 de HP/MP/STM.",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, REIPVP, 0, 0 },

{ "Game Master", "Adiciona 1% de ATK Pow e 100 de HP/MP/STM.",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, PLAYERGM, 0, 0 },


{ "Jogador Beta", "Descricao aqui.",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, PLAYERBETA, 0, 0 }, 

{ "Top Level Classe", "Adiciona 50 de HP/MP/STM e 1 ATK Speed.",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, PLAYERGM, 0, 0 },

{ "Delay Chat Global", "",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, DELAY_GLOBAL, 0, 0 },

{ "Gladiador", "",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, PLAYER_ARENA, 0, 0 },

{ "Desafio Diário", "Lute Contra Jogadores!",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, QUEST_DIARY, 0, 0 },

{ "Nível de Batalha", "",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, BATTLE_LEVEL, 0, 0 },

{ "Booster HP", "Regeneração HP 15%.",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, BOOSTER_ITEM_LIFE, 0, 0 },

{ "Booster MP", "Regeneração MP 15%.",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, BOOSTER_ITEM_MANA, 0, 0 },

{ "Booster STM", "Regeneração STM 15%.",
0, 0, 0, 0, 0,
{ 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, BOOSTER_ITEM_STAMINA, 0, 0 },


{ "Bellatra", "",
0,		0,0,		0,0,
{ 0,0,0 },{ 0,0,0,0,0,0,0,0 },
NULL,SOD_SKILL_GOLD,0,0 },
{ "Bellatra", "",
0,		0,0,		0,0,
{ 0,0,0 },{ 0,0,0,0,0,0,0,0 },
NULL,SOD_SKILL_SILVER,0,0 },

{ "Bellatra", "",
0,		0,0,		0,0,
{ 0,0,0 },{ 0,0,0,0,0,0,0,0 },
NULL,SOD_SKILL_BRONZE,0,0 },

{ "BlessCastle", "+5% de Poder de ATQ, por uma semana",
0,		0,0,		0,0,
{ 0,0,0 },{ 0,0,0,0,0,0,0,0 },
NULL,BC_SKILL_SILVER,0,0 },

{ "BlessCastle", "+3% de Poder de ATQ, por uma semana",
0,		0,0,		0,0,
{ 0,0,0 },{ 0,0,0,0,0,0,0,0 },
NULL,BC_SKILL_BRONZE,0,0 },

// Descrição dos cristais
{ "Cristal de Hopi", "Cristal de Hopi Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 1, 0, 0 }, 

{ "Cristal de Duende Macabro", "Cristal de Duende Macabro Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 2, 0, 0 },

{ "Cristal de Decoy", "Cristal de Decoy Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 3, 0, 0 },

{ "Cristal de Bargon", "Cristal de Bargon Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 4, 0, 0 },

{ "Cristal de Decapitador", "Cristal de Decapitador Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 5, 0, 0 },

{ "Cristal de Figon", "Cristal de Figon Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 6, 0, 0 },

{ "Cristal de Rei Hopi", "Cristal de Rei Hopi Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 7, 0, 0 },

{ "Cristal de Hulk", "Cristal de Hulk Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 8, 0, 0 },

{ "Cristal Místico", "Cristal Mistico Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 9, 0, 0 },

{ "Cristal de Guardião Santo", "Cristal de Guardião Santo Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 10, 0, 0 },

{ "Cristal de Aranha", "Cristal de Aranha Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 11, 0, 0 },

{ "Cristal Negro", "Cristal Negro Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 12, 0, 0 },

{ "Cristal de Ferro", "Cristal de Ferro Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 13, 0, 0 },

{ "Cristal Mirotic", "Cristal Mirotic Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 17, 0, 0 },

{ "Cristal Gêmeo", "Cristal Gemeo Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 18, 0, 0 },

{ "Cristal Imperial", "Cristal Imperial Sumonado",
0, 0, 0, 0, 0,
{ 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
NULL, 19, 0, 0 },