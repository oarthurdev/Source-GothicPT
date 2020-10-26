

#include "sinLinkHeader.h"

sMESSAGEBOX	sMessageBox[100] = {
	{"Espaço insuficiente"},
	{"Excede o Peso limite"},
	{"Este item não pode ser usado"},
	{"Ouro insuficiente"},
	{"Este item não pode ser Mixado"},
	{"Excede o número Máx. de itens"},
	{"Troca cancelada"},
	{"Poções não podem ser armazenadas"},
	{"A Mixagem do Item falhou"},
	{"Obrigado pela sua contribuição"},
	{"Muitos Itens no Armazém"},
	{"Este item não pode ser usado no Aging"},
	{"A troca foi alterada, confira"},
	{"Excede o limite de Ouro"},
	{"O Aging falhou"},
	{"Status reiniciado"},
	{"A imagem do item não está pronta"},
	{"Você só pode reiniciar uma vez"},
	{"Somente para  membros de Clan"},
	{"Somente para  membros de Clan"},
	{"Nível insuficiente"},
	{"O Nível do Aging caiu -1"},
	{"O Nível do Aging caiu -2"},
	{"O Nível do Aging subiu +1"},
	{"O Nível do Aging subiu +2"},
	{"A Vel. de ATQ do Item foi reduzida"},
	{"   Mature o Item do Desafio    "},
	{"   HP +15"},
	{"   Quebra-cabeças completo    "},
	{"   Quebra-cabeças incorreto    "},
	{"   Nenhum item para vender  "},
	{"O item já foi vendido"},
	{"A loja pessoal do jogador já fechou"},
	{"   Vendedor não encontrado   "},
	{"    Número de itens incorreto     "},
	{"    Guerreiros não podem usar este item    "},
	{"    Guerreiras não podem usar este item    "},
	{" Guerreiras não podem apanhar este item "},
	{" Guerreiros não podem apanhar este item "},
	{"    O preço do item foi alterado  "},
	{"    Nenhuma recompensa para o Clan    "},
	{"  Você não está acima do Nível limite  "},
	{"     A Força Orb está sendo usada agora    "},
	{"     A função do Poder de Ataque está em teste    "},
	{"    A maturação da Força Orb está completa    "},
	{"    +5 Pontos de Status    "},
	{"    +1 Ponto de Habilidade    "},
	{" +1 Ponto de Habilidade, +5 Pontos de Status"},
	{" +2 Pontos de Habilidade, +5 Pontos de Status"},
	{"   Penalidade pela morte reduzida em 1%  "},
	{"   Vitalidade +40   " },
	{"    Você já está sob Desafio     " },
	{"Após o Nível 80, você ganhará 7 pontos por Nível." },
	{"Após o Nível 90, você ganhará 10 pontos por Nível." },
	{"Status reiniciado" },
	{"Missão incompleta pelo tempo" },
	{"Muitos soldados mercenários"},
	{"Está sendo usada nas Habilidades"},
	{"Transporte impossível. Por favor, chame um GM"},
	{"Este Item não pode ser vendido"},
	{"Não há taxas suficientes"},
	{"Você já respondeu a estas perguntas"},
	{"Obrigado por responder às perguntas"},
	{"O item é incompatível com seu Nível"},
	{"O item foi reconstruído"},
	{"Encontrado no confronto contra o Fúria"},
	{"Perdido no confronto contra o Fúria"},
	{"Itens de compensação"},
	{"Itens aliados não podem ser combinados"},
	{"Poderá ser usado futuramente"},
	{"Impossível cancelar enquanto sheltoms são usados"},
	{"Impossível carregar arma enquanto sheltoms são usados"},
	{"Tipo de poção repetido"},
};


sMESSAGEBOX2 sMessageBox2[20] = {
	{"Quantos itens","você deseja comprar?"},
	{"Quantos itens","você deseja vender?"},
	{"Quantos itens","você deseja abandonar?"},
	{"Quanto dinheiro","você deseja abandonar?"},
	{"",""},
	{"Quanto dinheiro"," você deseja trocar?"},
	{"Quanto dinheiro","você deseja transferir?"},
	{"Quanto dinheiro","você deseja retirar?"},
	{" Quantas estrelas ","você deseja comprar?"},
	{"  Quanto dinheiro  ","você deseja doar?"},
	{"Você deseja registrar","o preço de seu item? "},
	{"Quantos itens","você deseja comprar?"},  
	{"Quanto dinheiro","você deseja retirar?"},
	{"  Você deseja ","comprar o item?"},
	{"  Você deseja ","comprar o item?"}, 
	{"Quanto dinheiro","você deseja investir?"},
	{"Quantos mercenários ","você deseja contratar?"} 

};


sMESSAGEBOX3 sMessageBox3[MESSAGE3_MAX] = {
	{"Você deseja","adquirir as Habilidades?"},
	{"Deseja", "acabar o Desafio de classe?"}, 
	{"Você aceita", "o Desafio?"},
	{"Você deseja","redistribuir?"},
	{"O evento"," custa"},
	{"Deseja","reiniciar seus STATUS?"},
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o item?"}, 
	{"Nomear o", "Core de União?"}, 
	{"Você aceita", "o item?"}, 
	{"Mover-se ao lugar", "indicado ?"}, 
	{"","Por favor, digite o número"}, 
	{"Deseja","comprar as Estrelas?"}, 
	{"Deseja", "vender o item?"}, 
	{"Você aceita", "o Desafio?"}, 
	{" Deseja", "mesmo doar?"}, 
	{" Loja pessoal ", "fffffffffff"}, 
	{"Deseja", "trocar os itens? "}, 
	{"Deseja", "comprar o item?"}, 
	{"Deseja ", "cancelar o registro?"}, 
	{"Deseja", "trocar o item? "}, 
	{"Deseja", "trocar o item? "}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Para onde", "você deseja ir?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio de Classe?"}, 
	{"Deseja", "trocar o item? "},
	{"Deseja ser transportado", "a algum lugar?"},    
	{"Gostaria de comprar","uma Torre de Cristais?"},      
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Você aceita", "o Desafio?"}, 
	{"Deseja", "usar este item"},       
	{"Você aceita", "o Desafio?"},
	{"Você aceita", "receber o item?"},   
	{"Deseja","ir para o Campo de Batalha?"},   
	{"Deseja", "Teletransportar-se?"},
};


char *SkillMaster[4] = {
	"Aprender Habilidade",
	"Mudar de Classe",
	"Sair do jogo"

};
char *SkillMaster2[4] = {
	"",
	"",
	""

};

char *ReStartMsg[4] = {
	" Recomeçar no Campo de Batalha",
	" Recomeçar na Cidade",
	" Sair do jogo",
	" EXP. insuficiente"

};
char *ReStartMsg2[4] = {
	" Penalidade(Ouro/EXP.) 1%",
	"",
	"",
	" para recomeçar no Campo de Batalha",

};

char *SkillUseInfoText[10]= { "    Treinar Habilidade/Magia     "," Selecione um Habilidade     ","      Para treiná-la ou aprendê-la       ",
				"Pontos de Habilidade  ","   insuficientes " };
char *sinMsgSkillPoint = "    Pontos de Habilidade : %d";
char *sinMsgEliteSkillPoint = "Pontos Especiais : %d " ;
char *sinStateName[5]={"H P : %d/%d  ","M P : %d/%d  ","R E S : %d/%d  ","E X P : %d/%d  ","E X P : %dM/%dM  "};


char *TownName[3] = {"Voltar para Ricarten\r","Voltar para Navisko\r","Voltar para Pillai\r"};

char *sinAbilityName[50] = {"Poder de Ataque:  \r","Vel. da Arma:\r","Alcance:  \r","Crítico:  \r","Taxa de Defesa:  \r","Taxa de Ataque:\r",
					"Absorção:  \r","Bloqueio:  \r","Velocidade:  \r","Integridade:\r","Regen de MP:  \r","Regen de HP :  \r",
					"Regen de RES:  \r","Res. Orgânica:  \r","Nature Type:  \r","Res. a Fogo:  \r","Res. a Gelo:  \r","Res. a Raio:  \r","Res. a Veneno: \r",
					"Water Type:  \r","Wind Type:  \r","HP Regen:  \r","MP Regen: \r","STM Regen: \r","Add. HP: \r",
					"MP Adicional:  \r","RES Adicional:  \r","Limite de Poções:  \r","Nível Necessário:  \r","Força Necessária:  \r","Inteligência Necessária:  \r",
					"Talento Necessário:  \r","Agilidade Necessária:  \r","Vitalidade Necessária:  \r"};


char *sinSpecialName[50] = {"Spec. ATK SPD:  \r","Crítico Adicional: \r","Def. Adicional:  \r","Abs Adicional:  \r",
						"Bloqueio Adicional  \r","Bônus Mágico:  \r","Vel. Adicional:  \r","R.Org. Adicional:  \r","Spec. Nature:  \r",
						"R. Fogo Adicional:  \r","R. Gelo Adicional:  \r","R. Raio Adicional:\r","R. Veneno Adicional:  \r","R. Água Adicional:  \r","R. Vento Adicional:  \r",
						"P. de ATQ Adicional:  \r","Taxa de ATQ ad.:  \r","Spec. RNG:\r","ATQ Org. Adicional:  \r","Spec. Nature ATK:  \r","ATQ Fogo Adicional\r","ATQ Gelo Adicional:  \r",
						"ATQ Raio Adicional:  \r","ATQ Veneno Adicional:  \r","ATQ Água Adicional:  \r","ATQ Vento Adicional:  \r","Bônus HP Max.:  \r","Bônus MP Max.:  \r",
						"Regen de HP:  \r","Regen de MP:  \r","Regen de RES:  \r","Preço de venda:  \r","Preço:  \r"};


char *SpecialName3 = "%s +. \r";
char *MixResultTitle = "Resultado da Mixagem";
char *NowLevelText = "Nível atual\r";
char *NextLevelText = "Próximo Nível\r";

char *NormalAttckName ="Ataque Padrão";
char *RequirLevel = "%s (Nv. Necess.:%d)\r";
char *UseItemGroupName = "Item compatível\r";

char *PoisonName = "Res. a Veneno:\r";
char *FireName = "Elemento Fogo:\r";
char *AttackAreaName = "Alcance:\r";
char *Attack_RateName = "Taxa de Ataque:\r";
char *Max_DamageIncre = "Bônus no dano Max.:\r";
char *DamageAddName = "Bônus no dano:\r";
char *Attack_SpeedAdd = "Bônus na Vel. de ATQ:\r";
char *IncreBlock = "Bônus no Bloqueio:\r";
char *CountinueTime = "Duração:\r";
char *UseManaName = "Custo de MP:\r";
char *DamageName = "Poder de Ataque:\r";
char *ShootingRangeName = "Alcance:\r";
char *IncreAsorb = "Bônus na Absorção:\r";
char *SecName = "seg.";
char *PlusDamageName = "Dano Adicional:\r";
char *HitNumName = "No. de Acertos:\r";
char *DecreLifeName = "HP diminui:\r";
char *Attck_RateAdd = "Poder de ATQ Ad.:\r";
char *Add_CriticalName = "Crítico Adicional:\r";
char *Push_AreaName = "Duração do recuo:\r";
char *FireAttackDamageAdd ="ATQ por Fogo:\r";
char *IceName = "Elemento Gelo:\r";
char *IceAttackDamageAdd = "ATQ por Gelo:\r";
char *StuneRate = "Probabilidade de Recuo:\r";
char *DefenseRateIncre = "Defesa aumenta:\r";
char *WeaponSizeName ="Tamanho da Arma:\r";
char *HwakRotationNum = "Número de voltas:\r";
char *WeaponSpeedAddName  = "Vel. de ATQ Ad:\r";
char *IncreAttack_RateName = "Poder de ATQ aumenta:\r";
char *ShootingNumName = "No. de disparos:\r";
char *SeriesShootingCount = "Fogo contínuo:\r";
char *UseStaminaName = "RES utilizada:\r";
char *MasterSkillMoneyName = "Preço da Habilidade:\r";

char *ItemAgingResult;		

char *sinGold ="%dOuro";
char *sinGiveItem5 = "Recompensa\r";
char *sinCopyItem5 = "Item duplicado\r";
char *sinNum7 = "RND";
char *sinSkillPointName = "Ponto de Habilidade";	
char *sinG_Pike_Time3 = "Tempo de Efeito:\r";	
char *sinItemLimitTimeOverMsg = "O tempo limite acabou\r";
char *sinDeadSongPyeunEat = "Mas, que meleca! Isso não presta!";
char *SmeltingResultTitle = "Resultado da Fundição";		
char *ManufactureResultTitle = "Resultado da Fabricação";	
char *ManufacturingTitle = "Aleatório";	


char *sinMaxDamageAdd = "Dano Máx. adicional\r";
char *sinDamagePiercing = "(ATQ Piercing)\r";
char *sinAddStamina = "RES adicional:\r";
char *sinAddLife = "Regen de HP:\r";

char *sinDamageUndead50 = "50% a mais de dano contra mortos-vivos:\r";
char *sinNumCount2 = "número:\r";
char *sinNumCount3 = "qtde.\r";
char *sinDecreDamage = "Prejuízo ao dano:\r";
char *sinConvert4 = "Taxa de conversão:\r";
char *sinIncreElement = "Adição a res. elemental:\r";
char *sinPartyIncreElement = "Membros do grupo ganham 50% de res. elemental\r";
char *sinFireBallDamage2 = "(100% de dano ao inimigo atacado)\r";
char *sinFireBallDamage3 = "(área de alcance 60 (1/3 dano))\r";
char *sinAddDamage7 = "dano adicional:\r";
char *PlusDamageWeapon = "arma";
char *SparkDamage = "dano por unidade:\r";
char *SparkNum7 = "# máx. de fagulhas:\r";
char *StunRage = "Alcance do recuo:\r";
char *RecvPotion7 = "Poção";


char *PartyArea7 ="Alcance no grupo:\r";
char *Area17 ="Área:\r";
char *AddAttack_Rate9 ="Taxa de ATQ:\r";
char *PiercingRange ="Alcance do Piercing:\r";
char *IncreDefense = "Aumento na Def.:\r";
char *AddShootingRange = "Aumento no alcance:\r";
char *LifeAbsorb = "Absorção do HP.:\r";
char *FireDamage = "Dano por Fogo:\r";
char *IceDamage = "Dano por Gelo:\r";
char *LightningDamage = "Dano por Raio:\r";
char *AddManaRegen = "Regen de Mana ad.:\r";
char *LightNum = "# de Raios:\r";
char *ReturnDamage = "Dano refletido:\r";
char *Area18 = "Alcance:\r";
char *IncreMana5 = "Aumento na Mana:\r";
char *Area19 = "Alcance:\r";
char *HelpTitle8 = " A J U D A ";
char *QuestTitle8 = " D E S A F I O ";
char *ResearchTitle8 = "B U S C A";
char *TeleportTitle8 = "TELEPORT";

char *IncreWeaponAttack_RateName = "Aumento na Taxa de ATQ:\r";
char *AddMaxDamage = "Aumento no dano Máx.:\r";
char *LinkCoreName = "Transportar-se ao membro do Clan\r";
char *DesLinkCore = "Nome:";
char *Itemul = "item";
char *ItemRecvOk = "Você aceita isto?";
char *Money5 = "ouro";
char *Exp5 = "EXP.";
char *WingItemName[] = {"Asa de Metal","Asa de Prata","Asa de Ouro","Asa de Diamante", "Asa do Caos"};
char *WarpGateName[] = {"Portal","Ricarten","Pillai","Terra do Crepúsculo","Floresta Bamboo","Vila Ruinen","Cidade de Navisko","Terra Proibida", "Vila Eura"};
char *sinWarningName5 = "A  V  I  S  O";
char *ClanCristalName = "Somente para membros de Clan\r";
char *NowMyShopSell = "A venda\r";
char *SecretNumName = "Número de autenticação";
char *MyShopExpDoc7 = "Detalhes da Loja";
char *NotAgingItem2 = "'Impossível aplicar o Aging";
char *ExpPercent2 = "EXP : %d.%d%s";
char *ExpPercent3 = "EXP : %d.0%d%s";
char *Mutant7   =   "Mutante";
char *Mechanic7 = "Mecânico";
char *Demon7    = "Demônio";
char *Nomal7    = "Normal";
char *Undead7    = "Morto Vivo";
char *MonsterAddDamage2 = "dano adicional)\r";
char *MonsterAddDamageFire = "dano por fogo adicional)\r";
char *HaWarpGateName[] = {"Castelo Bless",};
char *FallGameName = "Twisted forest";
char *EndlessGameName = "Torre sem Fim";
char *LookHelp = ">>more...";


char *HoldStarNumDoc = "O número das suas estrelas";
char *StarItemBuy7   = "Comprar as estrelas";
char *ChangeMoney7   = "(Preço de uma estrela : 100000)";




char *LightningDamage2 = "Dano por Raio:\r";
char *SheildDefense = "Aumento na Def.:\r";

char *DemonDamage4  = "ATQ Ad. em Demônios:\r"; 
char *PoisonDamage3  = "Dano por Veneno ad.:\r";
char *PikeNum4       = "Número de Foices:\r";
char *poisoningTime  = "Duração do veneno:\r";
char *PlusCriticalName = "Crítico adicional:\r";
char *SpiritFalconDamage2 = "Dano adicional:\r";
char *LifeGegenPlus = "Aumento no HP:\r";
char *PlusDamage4 = "Aumento no Dano:\r";
char *PiercingPercent = "Taxa de perfuração:\r";
char *DamageToLife = "Dano convertido:\r";
char *MyMonster7 = "Dominação:\r";
char *LifeIncre4 = "Aumento no HP:\r";
char *UndeadDamage3 = "Dano ad. em Mortos vivos:\r";

char *AttackNum3     = "No. de ATQs:\r";
char *AttackRateMinus = "Deficit de Taxa de ATQ:\r";
char *MaxDamagePlus2 = "MaxDamagePlus:\r";
char *LightningAddDamage3 = "Dano ad. por Raio:\r";
char *ReLifePercent4    = "Taxa de Rec. de HP:\r";
char *GetExp3    = "Exp. adquirida:\r";
char *ResurrectionChar4    = "Taxa de restauração";
char *ExtinctionPercent2    = "% de extinção:\r";
char *ExtinctionAmount2    = "Taxa de extinção:\r";
char *IncreLifePercent2   = "% ad. de HP:\r";

char *ReduceDamage3 = "Redução no dano:\r";
char *IncreMagicDamage = "Aumento no dano Mágico:\r";
char *AttackDelay3   = "Atraso no ATQ:\r";

char *FireDamage2 = "Dano por Fogo:\r";
char *IceDamage2 = "Dano por Gelo:\r";
char *AddDefense8 = "Def. Adicional:\r";
char *SkillDamage5 = "Dano da Habilidade:\r";

char *FireDamage3 = "Dano por Fogo:\r";
char *AddSpeed7 = "Vel. adicional:\r";
char *AfterDamage7 = "pós dano: \r";
char *MonsterSight7 = "percepção inimiga: \r";



char *LinghtingAddDamage4="Dano ad. por Raio:\r";
char *MaxBoltNum4="Voltagem Max.:\r";
char *AddAbsorb4="Abs. adicional:\r";
char *IncreArea4="Alcance adicional:\r";
char *IncreAttack4="Poder de ATQ Ad.:\r";
char *GolemLife4="HP+Força:\r";


char *SubAbsorb4="Redução da Abs.:\r";
char *AreaDamage4="Alcance do ATQ:\r";
char *MaxAttackNum4="Acertos max.:\r";
char *LifeUp4="Vitalidade adicional:\r";

char *CriticalAddDamage4="Crítico adicional:\r";
char *MonstervsSubCritical4="Redução do ATQ:\r";
char *ChargingAddPercentDamage4="Taxa de ATQ ad. por Carga:\r";

char *IncreEvasionPercent4="Esquiva adicional:\r";
char *AddShadowNum4="Furtividade ad.:\r";

char *WolverinLife4="Vitalidade:\r";
char *WolverinRate4="Precisão:\r";
char *WolverinDefense4="Defesa:\r";
char *AddEvasion4="Esquiva adicional:\r";
char *AddDamage4="Taxa de ATQ ad.:\r";
char *FalconAddDamage4="Taxa de ATQ ad. do Falcão:\r";


char *IncreAttackAbsorb4="Abs adicional:\r";

char *RectAngleArea4="Desfere ataques precisos e fatais:\r";

char *MonsterSubSpeed4="Redução da vel. do ATQ:\r";


char *AddLifeRegen4="Regen de HP ad.:\r";
char *AddManaRegen4="Regen de MP ad.:\r";
char *MagicArea4="Alcance mágico:\r";
char *ChainNum4="No. de inimigos afetados:\r";
char *ChainRange4="Efeito nos inimigos feridos:\r";
char *UndeadDamageAbsorb4="Abs ad. contra mortos vivos:\r";
char *UserBlockPercent4="Bloqueio adicional:\r";

char *SecondIncreMana4="Regen de Mana por seg.:\r";
char *FireDamage4="Taxa de ATQ por Fogo:\r";
char *DecreSpeed4="Redução na Vel.:\r";
char *DecreAttack4="Redução na Taxa de ATQ:\r";
char *AddPercentDamage4="Taxa de ATQ ad.:\r";
char *Move_SpeedAdd = "Move_SpeedAdd:\r";
char *AddLifeRegen5 = "Add Life Regen:\r";
char *AddStmRegen5 = "Add Stm Regen:\r";

char *ChainDamage3    = "Dano por faíscas)\r";
char *BrandishDamage3 = "Dano pelo Brandish";
char *PhysicalAbsorb3 = "Absorção física";
char *SparkDamage3    = "Dano pelas fagulhas";
char *GrandSmash3 = "GrandSmash";
char *BrutalSwingCritical3   = "Crítico brutal";
char *Attck_RateAdd5 = "Attck_RateAdd:\r";
char *Triumph4="Triunfo";
char *Use4="Você ";
char *DivineShield4="Bloqueio do escudo divino";


char *QuestMonsterName[] = {"Bargon","Guerreiro do Mal","Decapitador","Besouro Blindado ","Esqueleto Patrulheiro","Titan",
                         "Monstros da Terra Esquecida","Monstros de Oásis","Monstros do 1° Andar do Calabouço Antigo"};



char *VampOption[10] ={"Increaseagaing%: \r","Vampiro: \r","Danorelativo:\r","ReduçãodeHP: \r","Sorte: \r"};


char *Quest3ItemName[]={"Caça demônios","Vingador antigo","Mito","Lado demoníaco","Anaconda","Espada de Platina","Fantasma"};

char *Quset3ItemDoc15 = "Os itens do Desafio";
char *Quset3ItemDoc16 = " se foram ";

char *SparkDamage10 = "Dano das faíscas:\r";

char *RequirLevel3 = "(Nv.Necessário:%d)\r";

char *RecvItemTT = "Recebo o Item";
char *PuzzleEvent5 = "Cartão completo";
char *BabelHorn = "Chifre de Babel";
char *NineTailFoxItem = "Amuleto das Nove Caudas";
char *ChristMas = "Chiny Powder";		
char *MyShopItemSell5 = "O Preço: \r";
char *CristalItem     ="os 7 Cristais";


char *sinDeadCandyEat = "Que meleca! O gosto é horrível!";

char *PotionCntDoc2 = "Poções";
char *ItemPrice7 = "Preço do Item";

char *BuyMyShopItem7 = "%s comprou %d do vendedor %s por %d";
char *BuyMyShopItem8 = "%s comprou %d do vendedor %s por %d";
char *ItemName87 = "item";

char *sinEvent87 = "Desafio do Colecionador";
char *sinAddDamageItem = "P. de ATQ ad.: \r";
char *sinContinueTimeItem = "Duração: \r";
char *BuyPotionMoney = "Ouro:";
char *BuyPotionKind = "Número:";
char *SheltomName2[] = {"Lucidy","Sereno","Fadeo","Sparky","Raident","Transparo","Murky","Devine","Celesto", "Mirage", "Inferna", "Enigma"};

char *AddPercentDamage3= "P. de ATQ ad.%: \r";

char *sinLuckyBox = "Saco da Sorte";
char *SodMessage_Etc[]= {
			"A tarifa do torneio de Bellatra irá para",
			"Somente os Líderes de Clan recebem",
			"Agora, a taxa é %d%s.",
			};

char *SodMessage_Clan[] = {
			"O lucro total é de ",
			"Bellatra distribuiu a tarifa ontem.",
			};

char *SodMessage_Master[] = {
			"O total do prêmio é de",
			"Bellatra distribuiu a tarifa ontem.",
			"Deseja retirar?",
			};

char *OtherClanMaster[] = {
			"O Clan ainda possui a Tarifa",
			"ajuste o desconto.",
			};

char *SiegeMessage_Taxrates[] = {
	"A tarifa foi mudada para %d%s.",
	"O total das tarifas acumulou",
	"Ouro.",
	"Gostaria de arrecadar a tarifa?",
	"A tarifa agora é de %d%s.",
};
char *SiegeMessage_MercenrayA[] = {
	"Milícia de Ricarten",
	"Esta é a Milícia",
	"São fracos, porém, eficientes.",
	"Qtde. máx. de Mercenários: 20 / %d",
};
char *SiegeMessage_MercenrayB[] = {
	"Guarda de Ricarten",
	"O preço e as habilidades são equilibrados",
	"São soldados melhor treinados para combate.",
	"Qtde. máx. de Mercenários: 20 / %d",
};
char *SiegeMessage_MercenrayC[] = {
	"Membro da Guarda Imperial",
	"Mercenários especializados em grandes Guerras.",
	"São os melhores soldados que você encontrará.",
	"Qtde. máx. de Mercenários:20 / %d",
};
char *SiegeMessage_TowerIce[] = {
	"Torre de Cristais de Gelo",
	"O Gelo reduz a movimentação",
	"mas aumenta a velocidade de ATQ.",
	"Posicionamento dos Cristais de Gelo completo",
};
char *SiegeMessage_TowerFire[] = {
	"Torre de Cristais de Fogo",
	"O Fogo causa danos terríveis",
	"mas não possui nenhum efeito extra.",
	"Posicionamento dos Cristais de Fogo completo",
};
char *SiegeMessage_TowerLighting[] = {
	"Torre de Cristais de Raio",
	"O Raio diminui a velocidade de ATQ e",
	"e de movimentação dos adversários.",
	"Posicionamento dos Cristais de Raio completo",
};
char *SiegeMessage_MerMoney   = "Custo por Mercenário: ";
char *SiegeMessage_TowerMoney = "Custo por Torre: ";

char *sinClanMaster7 = "Líder do Clan";
char *sinPrize7 = "Recompensa:  ";

char *sinLevelQuestMonster[]={"Bargon","Muffin","Abelha Selvagem","Typhoon","Ratoo","Grotesco","Punhos de Aço"};
char *sinLevelQusetDoc="Quest> %s %d monstros adicionados";

char *sinTeleportDoc[] = {"Entrada da Caverna dos Cogumelos","Entrada da Caverna das Abelhas","Terra Maldita","Terra Proibida"};
char *sinLevelQuest90_2Mon[] = {"Omega","Máquina-D","Montanha"};
char *sinLevelQusetDoc2="<Quest> Cacem %d dos %s";
char *sinLevelQusetDoc3="<Quest> Apanhem os itens dos %s";
char *sinLimitTiem2 = "Tempo: \r";
char *sinMinute2 = "minutos";
char *sinDay4    = "dia";
char *sinHour4   = "hora";
char *sinLevelQusetDoc4="<Quest> Conclua a caça de %d dos %s";

sinSTRING sinTestMsg7("Ha ha ha, seus otários... vocês não valem nada!");

char *sinMonCodeName[]={
	0,
	"Bargon",
	"Esqueleto Guerreiro",
	"Decapitador",
	"Besouro Blindado",
	"Esqueleto Patrulheiro",     
	"Titan",
	"Muffin",
	"Abelha Selvagem",
	"Typhoon",
	"Ratoo",                
	"Grotesco",
	"Punhos de Aço",
	"Omega",
	"Maquina-D",
	"Montanha",              
	"Cavaleiro do Mal",
	"Caramujo Rijo",
	"Caramujo Espinhoso",
	"Múmia",
	"Guardião Maldito",             
	"Figon",
	"Gigante de Pedra",
	"Golem de Pedra",
	"Guardião de Aço",
	"Centauro Arqueira",       
	"Centauro-L", 
	"Abelha do Mal",
	"Cavaleiro Fantasma",
	"Pesadelo",
	"Bruxa",                
	"Duende Guerreiro",
	"Dawlin",
	"Stygian",
	"Incubus",
	"Golem de Aço",           
	"Espectro Negro",
	"Metron",
	"Lorde Minotauro",
	"Dusk",
	"Ogro Mecânico",            
	0,
};

char *ChargingTime4="Vel. ad. por carga:\r";
char *AddIceDamage4="Dano ad. por Gelo:\r";
char *IceTime4="Tempo de recuo:\r";
char *sinAttackType = "Tipo de ATQ:\r";
char *sinAttackType2[2] ={"Manual\r","Automático\r"};

char *Won="Ouro";


char *CastlItemInfo[] ={
	{"Invencibilidade temporária\r"},
	{"Porcentagem crítica\r"},
	{"Esquiva adicional\r"},
	{"Restaura RES,HP,MP\r"},
	{"Ressurge imediatamente.\r"},
	{"ATQ da Torre de Cristais\r"},     
	{"Bônus de 20% no ATQ\r"},
	0,
};
char *CastlItemInfo2[] ={
	{"reduz o ATQ pela metade\r"},
	{"aumento de 5%.\r"},
	{"aumento de 5%.\r"},
	{"dos membros do grupo.\r"},
	{"\r"},
	{"reduzido em 50%.\r"},
	{"contra o alvo.\r"},
	0,
};


char *CharClassTarget[8]={
	"Alvo(Lutador)\r",
	"Alvo(Mecânico)\r",
	"Alvo(Pike)\r",
	"Alvo(Arqueira)\r",
	"Alvo(Cavaleiro)\r",
	"Alvo(Atalanta)\r",
	"Alvo(Mago)\r",
	"Alvo(Sacerdotisa)\r",
};
char *AttributeTower[4]={
	"Attribute(Fogo)\r",
	"Attribute(Gelo)\r",
	"Attribute(Raio)\r",
	"Duração:%dSeg\r",
};

char *SiegeMessage_MerComplete ="Posicionamento dos Mercenários Completo";


char *haQuestMonsterName[]={
	"Hopi",
	"Coelho",
	"Duende Macabro",
	"Duende Selvagem",
	"Esqueleto",
	"Esqueleto do Mal",
	"Ciclope",
	"Bargon",
	0,
};
char *ha100LVQuestItemName[]={
	"Machado Minotauro",
	"Garra Extrema",
	"Martelo Dragão",
	"Foice Infernal",
	"Arco da Vingança",
	"Espada Imortal",
	"Lança Salamandra",
	"Cajado Gótico",
	"Enigma Dagger",
	"Kahsehtha Phantom",
	0,
};

char *ha100LVQuestMonterName[]={
	"Monstros de Perum",
	"Monstros de Gallubia", 
	0,
};
char *ha100LVQuestName = "Fantasma do Fúria";


char *PremiumItemDoc[][2]={
	{"Redistribui\r"     ,"pontos de Status.\r"},     
	{"Redistribui\r"     ,"pontos de Habilidade.\r"},    
	{"Redistribui\r"," pontos de St e Hab.\r"},     
	{"Ressuscita \r"    ,"personagens mortos.\r"},        
	{"Invencibilidade temporária\r","reduz o ATQ em 50%\r"},

	{"Aumento de 5% \r"    ,"no crítico.\r"},		
	{"Aumento de 5% \r"         ,"na esquiva.\r"},		
};

char *UpKeepItemDoc[] = {
	"Tempo restante : %dMin.",
	"Tx. de Drop %d%s adicional",
	"Exp. %d%s adicional",
	"Ataque %d%s adicional",
	"Converte % do dano em HP",
	"Converte % do dano em MP",
	"Aumenta a capacidade em d%",
	"Reduz o uso de MP em %d%s",
	"Exp. %d%s adicional",
	0,
};
char *UpKeepItemName[] = {
	"Olho Mágico",
	"Poção da Experiência",
	"Presa de Vampiro",
	"Drena Almas.",
	"Poder de Awell",
	"Poção de redução de Mana",
	"Fênix",
	0,
};


char *BoosterItemInfo[] = {
	{ "ÀÏÁ¤½Ã°£µ¿¾È »ý¸í·ÂÀ»\r" },
	{ "ÀÏÁ¤½Ã°£µ¿¾È ±â·ÂÀ»\r" },
	{ "ÀÏÁ¤½Ã°£µ¿¾È ±Ù·ÂÀ»\r" },
	0,
};
char *BoosterItemInfo2[] = {
	{ "15% »ó½Â½ÃÅ²´Ù.\r" },
	{ "15% »ó½Â½ÃÅ²´Ù.\r" },
	{ "15% »ó½Â½ÃÅ²´Ù.\r" },
	0,
};

char *BillingMagicForceName = "¸ÅÁ÷ Æ÷½º";

char *CandydaysItem = "7°³ÀÇ Äµµð¸¦"; 

char *ExpireItem = "Item Expirado";

char *FindinvestigatorItem = "³ªÀÎ¾Æ¹Ä·¿À»";
char *FindinvestigatorNineItem = "³ªÀÎ¾Æ¹Ä·¿À»";
char *FindinvestigatorTaleItem = "Å×ÀÏ¾Æ¹Ä·¿À»";



char *InventoryFull = "ÀÎº¥Åä¸® °ø°£ºÎÁ·";
char *InvenSpaceSecure = "°ø°£À» È®º¸ÇØ ÁÖ¼¼¿ä";

char *MagicalGreenEmeraldItem = "7°³ÀÇ ¿¡¸Þ¶öµå¸¦";

char *MagicalGreenJadeItem = "7°³ÀÇ ºñÃë¸¦";

char *TearOfKaraItem = "7°³ÀÇ Ä«¶óÀÇ ´«¹°À»";

char *MagicForceName = "";

char *StarItem = "7°³ÀÇ º°Á¶°¢À»"; 
								   
char *ValentineItem = "7°³ÀÇ ÃÊÄÝ¸´À»"; 
										
char *PristonAlphabetItem = "7°³ÀÇ ¾ËÆÄºªÀ¸·Î";


