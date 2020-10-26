

#include "sinLinkHeader.h"

sMESSAGEBOX	sMessageBox[100] = {
	{" No hay suficiente espacio en el inventario "},
	{" Has excedido el l?ite de peso del inventario "},
	{" El objeto no puede ser utilizado todav? "},
	{" No hay suficiente oro "},
	{" El objeto no se puede mezclar "},
	{" Excede el n?ero  m?imo de objetos de transacci? "},
	{" Transacci? cancelada "},
	{" Las pociones no se pueden depositar "},
	{" La Mezcla de objetos ha fallado "},
	{" Gracias por su generosa donaci?"},
	{" Demasiados objetos en el dep?ito "},
	{" El objeto no puede ser Madurado "},
	{" El objeto ha cambiado. Por favor, controlar "},
	{" Excede el monto m?imo de posesi? de oro "},
	{" La Maduraci? del objeto ha fallado "},
	{" Las estad?ticas se han reseteado "},
	{" La imagen del objeto no est?preparada "},
	{" S?o se puede resetear una vez "},
	{" S?o los miembros del clan pueden utilizar este objeto "},
	{" Debes estar en un clan para utilizar este objeto "},
	{" Imposible transferir debido a restricci? de nivel "},
	{" El nivel de Maduraci? ha sido disminuido en -1 "},
	{" El nivel de Maduraci? ha sido disminuido en -2 "},
	{" El nivel de Maduraci? ha sido aumentado en +1 "},
	{" El nivel de Maduraci? ha sido aumentado en +2 "},
	{" Velocidad de ATK del objeto en misi? disminuida "},
	{"   Subir de nivel el objeto en misi?    "},
	{"   HP incrementado +15 "},
	{"   El rompecabezas est?completado    "},
	{"   El rompecabezas est?equivocado    "},
	{"   No hay m? objetos para vender  "},
	{" El objeto ya fue vendido "},
	{" La tienda privada del vendedor est?cerrada "},
	{"   No se encuentra al vendedor   "},
	{"    N?ero incorrecto de objetos     "},
	{"    El personaje masculino no puede usar    "},
	{"    El personaje femenino no puede usar    "},
	{" El personaje femenino no puede adquirir el objeto "},
	{" El personaje masculino no puede adquirir el objeto "},
	{"    El precio del objeto ha cambiado  "},
	{"    No hay dinero de premio del clan     "},
	{"  Tu nivel no puede usar el Orbe  "},
	{"     El Orbe est?en uso ahora   "},
	{"     La funci? ATK POW est?siendo probada    "},
	{"    La Maduraci? del Orbe de Fuerza ha sido completada    "},
	{"    Puntos stadisticas incrementados en 5    "},
	{"    Puntos de habilidad incrementados en 1    "},
	{"  Puntos de stat y habilidad incrementados en 5 y 1 "},
	{"  Puntos de stat y habilidad incrementados en 5 y 2 "},
	{"    Exp. de pena de muerte disminuido en 1  "},
	{"   Vitalidad incrementada en 40   " },
	{" Est? en una Misi? " },
	{" Sobre nivel 80, obtendr? 7 puntos stat en cada nivel. " },
	{" Sobre nivel 90, obtendr? 10 puntos stat en cada nivel. " },
	{" Reconfigura tus n?eros para entrenamiento. " },
	{" La misi? fall?por exceso en el tiempo. " },
	{" Demasiados soldados mercenarios. "},
	{" Est? usando un objeto-habilidad. "},
	{" No te puede transferir al Castillo Bless Castle, "},
	{" El objeto no se puede vender a la tienda personal. "},
	{" No hay suficiente monto de impuestos para ser retirado. "},
	{" Ya respondiste la preguntas. "},
	{" Gracias por responder las preguntas. "},
	{" El objeto-sello no corresponde a tu nivel. "},
	{" El objeto fue reconstruido. "},
	{" Gana en la confrontaci? con Furia. "},
	{" Pierde en la confrontaci? con Furia. "},
	{" Adquiri?objetos en compensaci?. "},
	{" Los objetos aliados no se pueden usar juntos. "},
	{" Se puede usar m? tarde "},
	{" Imposible cancelar mientras se mezcla "},
	{" No se puede llevar arma mientras se mezcla "},
	{" Se us?el mismo tipo de Poci? para Te?r el Cabello. "},
	{" Se us?el mismo tipo de Poci? la Te?r el Cabello. "},
        {"Ha fallado la Fundici?."}, 
	{"Ha fallado la Fabricaci? del objeto."}, 
	{"En la combinaci? no puedes mantener los Oros y Cristales."}, 
	{"En la combinaci? no puedes mantener las recetas."}, 
	{" Estas no son del mismo tipo o de cristales o Oro "}, 
	{" Esta no es la forma correcta de Fabricaci?."}, 
};



sMESSAGEBOX2 sMessageBox2[20] = {
	{" ¿Cu?tos objetos "," quieres comprar? "},
	{" ¿Cu?tos objetos "," quieres vender? "},
	{" ¿Cu?tos objetos "," quieres tirar? "},
	{" ¿Cu?to oro "," quieres tirar? "},
	{"  ","  "},
	{" ¿Cu?to oro "," quieres intercambiar? "},
	{" ¿Cu?to oro "," quieres mover? "},
	{" ¿Cu?to oro "," quieres recuperar? "},
	{" ¿Cu?tas estrellas "," quieres comprar? "},
	{" ¿Cu?to oro "," quieres donar? "},
	{" ¿Quieres registrar"," tu dinero en objetos?  "},
	{" ¿Cu?tos objetos "," quieres comprar? "},  
	{" ¿Cu?to oro "," quieres recuperar? "},
	{" ¿Quieres "," comprar el objeto? "},
	{" ¿Quieres "," comprar el objeto? "}, 
	{" ¿Cu?to oro "," quieres retirar? "},
	{" ¿Cu?tos mercenarios "," te gustar? comprar? "} 

};

sMESSAGEBOX3 sMessageBox3[MESSAGE3_MAX] = {
	{" ¿Quieres "," adquirir las habilidades? "},
	{" ¿Quieres ", " hacer rank up? "}, 
	{" ¿Quieres ", " llevar a cabo la misi?? "},
	{" ¿Quieres "," redistribuir? "},
	{" Cuesta oro "," para el evento "},
	{" ¿Quieres ","initializar las STATS? "},
	{" ¿Quieres ", " llevar a cabo la misi?? "}, 
	{" ¿Quieres ", " recibir el objeto? "}, 
	{" ¿Quieres ", " registrar el N?leo de Uni?? "}, 
	{" ¿Quieres ", " recibir el objeto? "}, 
	{" ¿Quieres ", " ir a ? "}, 
	{" "," Por favor tipea el n?ero "}, 
	{" ¿Quieres "," comprar un objeto estrella? "}, 
	{" ¿Quieres ", " vender el objeto? "}, 
	{" ¿Quieres ", " la misi?? "}, 
	{" ¿Quieres ", " pagar la donaci?? "}, 
	{" Tienda Privada ", " fffffffffff "}, 
	{" ¿Quieres ", "exchange to the item? "}, 
	{" ¿Quieres ", "buy the item?"}, 
	{" ¿Quieres ", " cancelar el Registro? "}, 
	{" ¿Quieres ", " intercambiar el objeto? "}, 
	{" ¿Quieres ", " intercambiar el objeto? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Ad?de ", " quieres ser teletransportado? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Quieres ", " buscar la misi?? "}, 
	{" ¿Quieres ", " hacer rank up? "}, 
	{" ¿Quieres ", " intercambiar el objeto? "},
	{" ¿Te teletransportar?s a ", " alg? lugar? "},    
	{" ¿te gustar? comprar "," una torre de  cristal? "},      
	{" ¿Quieres ", " obtener la Misi?? "}, 
	{" ¿Quieres ", " obtener la Misi?? "}, 
	{" ¿Quieres ", " obtener la Misi?? "}, 
	{" ¿Quieres ", " obtener la Misi?? "}, 
	{" ¿Quieres ", " obtener la Misi?? "}, 
	{" ¿Quieres ", " obtener la Misi?? "}, 
	{" ¿Quieres ", " obtener la Misi?? "}, 
	{" ¿Quieres ", " usar este objeto? "},       
	{" ¿Quieres ", " obtener la Misi?? "},
	{" ¿Quieres ", " recibir el objeto? "},   
	{" ¿Quieres "," ir a la Zona de Batalla? "},   
	{" ¿Quieres ", " Teletransportarte? "},
};


char *SkillMaster[4] = {
	" Aprender Habilidad ",
	" Cambiar Clase ",
	" Salir del Juego "

};
char *SkillMaster2[4] = {
	"",
	"",
	""

};

char *ReStartMsg[4] = {
	" ¿Recomenzar desde el campo? ",
	" ¿Recomenzar desde el pueblo? ",
	" ¿Salir del Juego? ",
	" No tienes suficiente XP "

};
char *ReStartMsg2[4] = {
	" Pena(Gold/XP) 1% ",
	"",
	"",
	" para permanecer en el campo ",

};

char *SkillUseInfoText[10]= { "    Entrenar Habilidad/Magia     ","    Seleccionar una Habilidad o Magia     ","      Para aprender o entrenar       ","  No tienes suficientes puntos de Habilidad  ","   para aprender o practicar " };
char *sinMsgSkillPoint = "    Puntos de Habilidad : %d";
char *sinMsgEliteSkillPoint = "Puntos de Habilidad de Elite : %d " ;
char *sinStateName[5]={"H P : %d/%d  ","M P : %d/%d  ","STM : %d/%d  ","X P : %d/%d  ","X P : %dM/%dM  "};


char *TownName[3] = {" Llamada a Ricarten\r"," Llamada a  Navisko\r"," Llamada a  Pillai\r"};

char *sinAbilityName[50] = {"  Poder de Ataque:  \r "," Velocidad del Arma:  \r ","Rango:  \r "," Cr?ico:  \r "," Capacidad de Defensa:  \r "," Capacidad de Ataque:  \r ",
					" Capacidad de Absorci?:  \r "," Capacidad de Bloqueo:  \r "," Velocidad:  \r "," Integridad:  \r "," Recuperaci? de MP:  \r "," Recuperaci? de HP:  \r ",
					" Recuperaci? de STM:  \r "," Tipo Org?ico:  \r "," Tipo Naturaleza:  \r "," Tipo Llama:  \r "," Tipo Escarcha:  \r "," Tipo Rayo:  \r "," Tipo Veneno: \r ",
					" Tipo Agua:  \r "," Tipo Viento:  \r "," Regen. HP :  \r "," Regen. MP: \r "," Regen. STM: \r "," HP Adicional: \r ",
					" MP Adicional:  \r "," STM Adicional:  \r "," Inventario de Pociones:  \r "," Nivel Req.:  \r "," Fuerza Req.:  \r "," Esp?itu Req.:  \r ",
					"Req. Talent:  \r","Req. Agility:  \r","Req. Health:  \r"};


char *sinSpecialName[50] = {" ATK SPD Esp.:  \r "," CRIT Esp.:  \r "," DEF RTG Esp.:  \r "," ABS RTG Esp.:  \r ",
						" BLK RTG Esp.:  \r"," APT M?ica:  \r "," SPD Esp.:  \r "," Org?ico Esp.:  \r "," Naturaleza Esp.:  \r ",
						" Flame Esp.:  \r"," Escarcha Esp.:  \r "," Rayo Esp.:  \r "," Veneno Esp.:  \r ","Agua Esp.:  \r "," Viento Esp.:  \r ",
						" ATK POW Esp.:  \r"," ATK RTG Esp.:  \r "," RNG Esp.:  \r "," ATK Org?ico Esp. :  \r "," ATK Naturaleza Esp.:  \r "," ATK Llama Esp.:  \r "," ATK Escarcha Esp.:  \r ",
						" ATK Rayo Esp.:  \r"," ATK Veneno Esp.:  \r "," ATK Agua Esp.:  \r ","ATK Viento Esp.:  \r "," M?. Incremento de HP:  \r "," M?. Incremento de MP:  \r ",
						" Recuperaci? de HP:  \r "," Recuperaci? de MP:  \r "," Recuperaci? de STM:  \r "," Precio de Venta:  \r "," Costo:  \r "};


char *SpecialName3 = "%s Especial. \r ";
char *MixResultTitle = " Resultado de la Mezcla de Objetos ";
char *NowLevelText = " Nivel Actual\r ";
char *NextLevelText = " Pr?imo Nivel\r ";

char *NormalAttckName =" Ataque Est?dar ";
char *RequirLevel = " %s (Nivel Req.:%d)\r ";
char *UseItemGroupName = " Grupo de Objetos Compatible \r ";

char *PoisonName = " Tipo de Veneno:\r ";
char *FireName = " Tipo de Llama:\r ";
char *AttackAreaName = " Rango de Ataque:\r ";
char *Attack_RateName = " Capacidad de Ataque:\r ";
char *Max_DamageIncre = " Aumento M?imo de Da?:\r ";
char *DamageAddName = " Aumento de Da?:\r ";
char *Attack_SpeedAdd = " Aumento de Velocidad de Ataque:\r ";
char *IncreBlock = " Mejora de la Capacidad de Bloqueo:\r ";
char *CountinueTime = " Duraci?:\r ";
char *UseManaName = " Uso de MP:\r ";
char *DamageName = " Poder de Ataque:\r ";
char *ShootingRangeName = " Rango:\r ";
char *IncreAsorb = " Mejora de la Capacidad de Absorci?:\r ";
char *SecName = " seg ";
char *PlusDamageName = " Da? Adicional:\r ";
char *HitNumName = " N?ero de Golpes:\r ";
char *DecreLifeName = " Vida Disminuye:\r ";
char *Attck_RateAdd = " Poder de Ataque Adicional:\r ";
char *Add_CriticalName = " Cr?ico Adicional:\r ";
char *Push_AreaName = " Largo de Distanciamiento:\r ";
char *FireAttackDamageAdd =" Ataque de Llama:\r ";
char *IceName = " Propiedad de Escarcha:\r ";
char *IceAttackDamageAdd = " Ataque de Escarcha:\r ";
char *StuneRate = " Probabilidad de Paralizar:\r ";
char *DefenseRateIncre = " Capacidad de Defensa Incrementa:\r ";
char *WeaponSizeName =" Tama? del Arma:\r ";
char *HwakRotationNum = " Rotaciones de Halc?:\r ";
char *WeaponSpeedAddName  = " Velocidad Adicional del Arma:\r ";
char *IncreAttack_RateName = "Incremento en la Capacidad de Ataque:\r ";
char *ShootingNumName = " N? de Tiros:\r ";
char *SeriesShootingCount = " Fuego Continuo:\r ";
char *UseStaminaName = " Uso de Vigor:\r ";
char *MasterSkillMoneyName = " Costo de la Habilidad:\r ";

char *ItemAgingResult;		

char *sinGold =" %dOro ";
char *sinGiveItem5 = " Objeto de Regalo\r ";
char *sinCopyItem5 = " Objeto Copiado\r ";
char *sinNum7 = " RND ";
char *sinSkillPointName = " Punto de Habilidad ";	
char *sinG_Pike_Time3 = " Tiempo Congelado:\r ";	
char *sinItemLimitTimeOverMsg = " El l?ite de tiempo ha expirado\r ";
char *sinDeadSongPyeunEat = " ¡Maldici?! ¡Es una podrida torta de arroz! ";
char *SmeltingResultTitle = "Resultado de la Fundici?";		
char *ManufactureResultTitle = "Creando";	
char *ManufacturingTitle = "al Azar";	
char *Expired	= "validaci? vencida";


char *sinMaxDamageAdd = " Incremento el Da? M?imo+\r ";
char *sinDamagePiercing = " (Ataque Punzante)\r ";
char *sinAddStamina = " Vigor Agregado:\r ";
char *sinAddLife = " Recuperaci? de Vida:\r ";

char *sinDamageUndead50 = "50% m? da? a unidades de muertos vivos:\r ";
char *sinNumCount2 = " n?ero:\r ";
char *sinNumCount3 = " cantidad\r ";
char *sinDecreDamage = " Disminuci? de da?:\r ";
char *sinConvert4 = " ?dice de conversi?:\r ";
char *sinIncreElement = " Incremento en caracter?tica de elemento:\r ";
char *sinPartyIncreElement = " Miembro del grupo re?e 50% del incremento del elemento\r ";
char *sinFireBallDamage2 = " (100% de da? al enemigo objetivo)\r ";
char *sinFireBallDamage3 = " ( ?ea objetivo 60 (1/3 da?))\r ";
char *sinAddDamage7 = " da? agregado:\r ";
char *PlusDamageWeapon = " arma ";
char *SparkDamage = " da? por unidad:\r ";
char *SparkNum7 = " # de chispa m?imo:\r ";
char *StunRage = " Rango de Paralizaci?:\r ";
char *RecvPotion7 = " Poci? ";


char *PartyArea7 =" Área del Grupo:\r ";
char *Area17 =" Área:\r ";
char *AddAttack_Rate9 =" Capacidad de Ataque:\r ";
char *PiercingRange =" Rango de Incisi?:\r ";
char *IncreDefense = "Increase Defense:\r";
char *AddShootingRange = " Rango Incrementado de SHT:\r ";
char *LifeAbsorb = " Absorci? de Vida:\r ";
char *FireDamage = " Da? por Fuego:\r ";
char *IceDamage = " Da? por Hielo:\r ";
char *LightningDamage = " Da? por Rayo:\r ";
char *AddManaRegen = " Man?Adicional Regen.:\r ";
char *LightNum = " # de Rayo:\r ";
char *ReturnDamage = " Retorno de Da?:\r ";
char *Area18 = " Rango disponible:\r ";
char *IncreMana5 = " Incremento de Man?\r ";
char *Area19 = " Área disponible:\r ";
char *HelpTitle8 = " A Y U D A ";
char *QuestTitle8 = " M I S I ?N  ";
char *ResearchTitle8 = " INVESTIGACI? ";
char *TeleportTitle8 = " TELETRANSPORTE ";

char *IncreWeaponAttack_RateName = " Capacidad de ATK incrementada:\r ";
char *AddMaxDamage = " Da? m?imo incrementado:\r ";
char *LinkCoreName = " Teletransportar a un miembro del clan\r ";
char *DesLinkCore = " Nombre: ";
char *Itemul = " objeto ";
char *ItemRecvOk = " ¿Quieres esto? ";
char *Money5 = " oro ";
char *Exp5 = " EXP ";
char *WingItemName[6] = {" Ala de Metal "," Ala de Plata "," Ala de Oro "," Ala Diamante ", " Ala de Caos ", " Ala de Extremo "};
char *WarpGateName[10] = {" Puerta Warp "," Ricarten "," Pillai "," Tierra del Crep?culo "," Bosque de Bamb?"," Villa de Ruinen "," Pueblo de Navisko "," Tierra Prohibida ", " Villa de Eura ", " Tierra del Caos "};
char *sinWarningName5 = " Atenci? ";
char *ClanCristalName = " S?o para miembros del clan\r ";
char *NowMyShopSell = " En venta\r ";
char *SecretNumName = " Ingresar n?eros de autenticaci? ";
char *MyShopExpDoc7 = " Informaci? de Tienda ";
char *NotAgingItem2 = " Imposible madurar el objeto ";
char *ExpPercent2 = " EXP : %d.%d%s ";
char *ExpPercent3 = " EXP : %d.0%d%s ";
char *Mutant7   =   " Mutante ";
char *Mechanic7 = " Mec?ico ";
char *Demon7    = " Demonio ";
char *Nomal7    = " Normal ";
char *Undead7    = "Muerto Vivo ";
char *MonsterAddDamage2 = " agregar da? extra)\r ";
char *MonsterAddDamageFire = " agregar da? de elemento fuego)\r ";
char *HaWarpGateName[] = {" Castillo Bless ",0};
char *FallGameName = " Bosque Torcido ";
char *EndlessGameName = " Torre Interminable ";
char *LookHelp	= " m??"; 



char *HoldStarNumDoc = " El n?ero de tus estrellas ";
char *StarItemBuy7   = " Comprar las estrellas ";
char *ChangeMoney7   = "(El precio de una estrella: 100000) ";




char *LightningDamage2 = " Da? por Rayo:\r ";
char *SheildDefense = " Incrementa Defensa:\r ";

char *DemonDamage4  = " Poder de ATK VS Demonio:\r ";
char *PoisonDamage3  = " Da? por Veneno:\r ";
char *PikeNum4       = " N?ero de lanza:\r ";
char *poisoningTime  = " Tiempo de envenenamiento:\r ";
char *PlusCriticalName = " Incrementa Cr?ico%:\r ";
char *SpiritFalconDamage2 = " Da? por Esp?itu Halc?:\r ";
char *LifeGegenPlus = " Incrementa HP:\r ";
char *PlusDamage4 = " M? da?:\r ";
char *PiercingPercent = " Porcentaje de Incisi?:\r ";
char *DamageToLife = " Da? a Vida:\r ";
char *MyMonster7 = " Mi monstruo:\r ";
char *LifeIncre4 = " Incremento de vida:\r ";
char *UndeadDamage3 = " Da? por muerto vivo:\r ";

char *AttackNum3     = " N?ero de ATK:\r ";
char *AttackRateMinus = " Disminuye capacidad de ATK:\r ";
char *MaxDamagePlus2 = " M?imo Da? M?:\r ";
char *LightningAddDamage3 = " Da? Adicional por Rayo:\r ";
char *ReLifePercent4    = " Re. Porcentaje de Vida:\r ";
char *GetExp3    = " Obtener Exp:\r ";
char *ResurrectionChar4    = " Resurrecci? Pers. Nivel ";
char *ExtinctionPercent2    = " Porcentaje de Extinci?:\r ";
char *ExtinctionAmount2    = " Monto de Extinci?:\r ";
char *IncreLifePercent2   = " Incrementa Porcentaje de Vida:\r ";

char *ReduceDamage3 = " Reduce Da?:\r ";
char *IncreMagicDamage = " Incrementa Da? M?ico:\r ";
char *AttackDelay3   = " Retraso de Ataque:\r ";

char *FireDamage2 = " Da? por Fuego:\r ";
char *IceDamage2 = " Da? por Hielo:\r ";
char *AddDefense8 = " Defensa adicional:\r ";
char *SkillDamage5 = " Da? de Habilidad:\r ";

char *FireDamage3 = " Da? por Fuego:\r ";
char *AddSpeed7 = " Velocidad Agregada:\r ";
char *AfterDamage7 = " Da? Residual:\r ";
char *MonsterSight7 = " Visi? de monstruo:\r ";



char *LinghtingAddDamage4=" Capacidad de ataque adicionas en rayo:\r ";
char *MaxBoltNum4=" M? voltaje:\r ";
char *AddAbsorb4=" ?dice Adicional de absorci?:\r ";
char *IncreArea4=" Incrementar rango:\r ";
char *IncreAttack4=" M? poder de ataque:\r ";
char *GolemLife4=" Vida+STR:\r ";


char *SubAbsorb4=" Disminuye absorci?:\r ";
char *AreaDamage4=" Capacidad de ataque para el rango:\r ";
char *MaxAttackNum4=" M?. golpes:\r ";
char *LifeUp4=" Vitalidad adicional:\r ";

char *CriticalAddDamage4=" Incremento de cr?ico:\r ";
char *MonstervsSubCritical4=" Debilitar cr?ico de monstruo:\r ";
char *ChargingAddPercentDamage4=" Capacidad de ataque adicional en carga:\r ";

char *IncreEvasionPercent4=" Porcentaje adicional de evasi?:\r ";
char *AddShadowNum4=" Incrementa combinaci? ocular:\r ";

char *WolverinLife4=" Vitalidad:\r ";
char *WolverinRate4=" Exactitud:\r ";
char *WolverinDefense4=" ?dice de Defensa:\r ";
char *AddEvasion4=" Incrementa habilidad de evasi?:\r ";
char *AddDamage4=" Incrementa ?dice de ataque(f?ico):\r ";
char *FalconAddDamage4=" Incrementa ?dica de ataque de halc?:\r ";


char *IncreAttackAbsorb4=" Incrementa ?dice de absorci?:\r ";

char *RectAngleArea4=" Atacar en ?gulo recto:\r ";

char *MonsterSubSpeed4=" Velocidad decreciente del monstruo atacado:\r ";


char *AddLifeRegen4=" Regeneraci? de vida adicional:\r ";
char *AddManaRegen4=" Regeneraci? de man?adicional:\r ";
char *MagicArea4=" Rango afectado por magia:\r ";
char *ChainNum4=" N?ero de monstruos afectados:\r ";
char *ChainRange4=" Furia del monstruo afectado:\r ";
char *UndeadDamageAbsorb4=" Absorci? del ataque de muertos vivientes:\r ";
char *UserBlockPercent4=" Capacidad de Bloqueo para el personaje:\r ";

char *SecondIncreMana4="Incremento de ?dice de mana por segundo:\r ";
char *FireDamage4=" ?dice de ataque de Fuego:\r ";
char *DecreSpeed4=" Velocidad en Disminuci?:\r ";
char *DecreAttack4=" ?dice de ataque disminuido:\r ";
char *AddPercentDamage4=" ?dice de ataque agregado:\r ";



char *ChainDamage3    = " Da? por Cadena)\r ";
char *BrandishDamage3 = " Da? por Embiste ";
char *PhysicalAbsorb3 = " Absorci? F?ica ";
char *SparkDamage3    = " Da? por Chispa ";
char *BrutalSwingCritical3   = " Swing Brutal Cr?ico ";
char *Attck_RateAdd5 = " Attck_RateAdd:\r ";
char *Triumph4=" Triunfo ";
char *Use4=" t?";
char *DivineShield4=" Bloqueando ?dice de escudo divino ";


char *QuestMonsterName[] = {" Bargon "," Guerrero Skeleton "," Cortacabezas "," Escarabajo Armado "," Soldado Skeleton "," Tit? " ,
                         " Monstruo de la Tierra Prohibida "," Monstruo del Oasis "," Monstruo del 1er piso de la Prisi? Antigua "};



char *VampOption[10] ={"Incremento de maduraci?%: \r "," Vampiro: \r "," RefDa?: \r "," DisminuirHP: \r "," Afortunado: \r "};


char *Quest3ItemName[]={" Cazador de Demonios "," Venganza Antigua "," Niebla "," Lado Demon?co "," Anaconda "," Espada Laminada "," Fantasma "};

char *Quset3ItemDoc15 = " El objeto de misi? ";
char *Quset3ItemDoc16 = " no est?";

char *SparkDamage10 = " Da? por Chispa:\r ";

char *RequirLevel3 = " (Nivel Requerido:%d)\r ";

char *RecvItemTT = " Recibo el objeto ";
char *PuzzleEvent5 = " Rompecabezas Completado ";
char *BabelHorn = " El Cuerno de Babel ";
char *NineTailFoxItem = " Amuleto Nine Tail ";
char *MyShopItemSell5 = " El Precio: \r ";
char *CristalItem     =" los 7 Cristales ";
char *StarDust		= " Polvo Destelleante ";
char *ChristMas	= " Polvo Brillante ";


char *sinDeadCandyEat = " ¡Tiene un gusto horrible! ";

char *PotionCntDoc2 = " Precio por unidad ";
char *ItemPrice7 = " Precio del Objeto ";

char *BuyMyShopItem7 = " %s jugador ha tra?o %d n?ero de %s por %dOro ";
char *BuyMyShopItem8 = " %s jugador ha tra?o %d n?ero de %s por %dOro ";
char *ItemName87 = " objeto ";

char *sinEvent87 = " Pedido del coleccionista de peligros ";
char *sinAddDamageItem = " ATKPOWER agregado: \r ";
char *sinContinueTimeItem = " Duraci?: \r ";
char *BuyPotionMoney = " Dinero: ";
char *BuyPotionKind = " N?ero: ";
char *SheltomName2[] = {" Lucidy "," Sereneo "," Fadeo "," Sparky "," Raident "," Transparo "," Murky "," Devine "," Celesto "};

char *AddPercentDamage3= "AddATKPOWER%: \r";

char *sinLuckyBox = " Bolsa de la Suerte ";
char *SodMessage_Etc[]= {
			" El ingreso del clan que maneja Bellatra es ",
			" S?o el jefe del clan lo toma. ",
			" Ahora, el impuesto es %d%s. ",
			};

char *SodMessage_Clan[] = {
			" El ingreso total es como sigue ",
			" Bellatra provey?el premio ayer. ",
			};

char *SodMessage_Master[] = {
			" El ingreso total es como sigue ",
			" Bellatra provey?el premio ayer. ",
			" Lo quieres recibir? ",
			};

char *OtherClanMaster[] = {
			" El clan todav? obtiene el premio ",
			" escriba el oro a recibir. ",
			};

char *SiegeMessage_Taxrates[] = {
	" El ?dice de impuesto ha cambiado a %d%s. ",
	" El Total de impuesto se ha estado acumulando ",
	" Oro. ",
	" ¿Te gustar? retirar el impuesto?. ",
	" El ?dice de impuesto es ahora %d%s. ",
};
char *SiegeMessage_MercenrayA[] = {
	" Milicia de Ricarten ",
	" Consists en la milicia ",
	" Tiene habilidad de lucha d?il, a cambio de su bajo precio. ",
	" Monto m?imo de Mercenario::20 / %d ",
};
char *SiegeMessage_MercenrayB[] = {
	" Guardia de Ricarten ",
	" El precio y la habilidad est? en equilibrio paa convertirse en Mercenario ",
	" Tiene habilidad de lucha intermedia. ",
	" Monto m?imo de Mercenario::20 / %d ",
};
char *SiegeMessage_MercenrayC[] = {
	" Guardia Real de Bless ",
	" El nivel m? alto de Mercenario ",
	" habilidad de luchala mayor habilidad de lucha. ",
	" Monto m?imo de Mercenario:20 / %d ",
};
char *SiegeMessage_TowerIce[] = {
	" Torre de Cristal de Hielo ",
	" El Atributo de Hielo disminuye la velocidad de los movimientos y ",
	" tiene la habilidad de disminuir la velocidad de ATK. ",
	" La configuraci? del Cristal de Hielo est?completa ",
};
char *SiegeMessage_TowerFire[] = {
	" Torre de Cristal de Fuego ",
	" El Atributo de Fuego otorga un granpoder de ATK ",
	" No tiene habilidades especiales. ",
	" La configuraci? del Cristal de Fuego est?completa ",
};
char *SiegeMessage_TowerLighting[] = {
	"  Torre de Cristal Rayo ",
	" El Rayo disminuye la velocidad de los movimientos y ",
	" tiene la habilidad de disminuir la velocidad de ATK. ",
	" La configuraci? del Cristal de Rayo est?completa ",
};
char *SiegeMessage_MerMoney   = " Dinero de Mercenario: ";
char *SiegeMessage_TowerMoney = " Dinero de la Torre: ";

char *sinClanMaster7 = " Jefe del Clan ";
char *sinPrize7 = " Premio ";

char *sinLevelQuestMonster[]={" Bargon "," Muffin "," Abeja Terrible "," Tif? "," Rat?"," Grotesco "," Pu? de Hierro "};
char *sinLevelQusetDoc="Misi?> %s %d n?ero de monstruos necesario ";

char *sinTeleportDoc[] = {" Cueva Hongo "," Cueva Enjambre "," Tierra Maldita "," Tierra Prohibida "};
char *sinLevelQuest90_2Mon[] = {" Omega "," D-M?uina "," Monta? "};
char *sinLevelQusetDoc2=" <Misi?> Caza %d de %s ";
char *sinLevelQusetDoc3=" <Misi?> Obt? el objeto de %s ";
char *sinLimitTiem2 = " Tiempo L?ite: \r ";
char *sinMinute2 = " minuto ";
char *sinDay4    = " d? ";
char *sinHour4   = " hora ";
char *sinLevelQusetDoc4="<Misi?>  Finaliz?la caza %d de %s ";

sinSTRING sinTestMsg7(" Hurra, Neh Neh Neh Boo Boo, son perdedores! ");

char *sinMonCodeName[]={
	0,
	" Bargon ",
	" Guerrero Skeleton ",
	" cortacabezas ",
	" Escarabajo Armado ",
	" Soldado Skeleton ",     
	" Tit? ",
	" Muffin ",
	" Abeja Terrible ",
	" Tif? ",
	" Rat?",                
	" Grotesco ",
	" Pu? de Hierro ",
	" Omega ",
	" D-M?uina ",
	" Monta? ",              
	" Caballero Skeleton ",
	" Caracol S?ido ",
	" Arrastraespina ",
	" Momia ",
	" Guardia de la Perdici? ",             
	" Figon ",
	" Gigante de Piedra",
	" Golem de Piedra ",
	" Guardia de Hierro ",
	" Avelin ",       
	" Avelisk-L ",
	" BeEvil ",
	" Caballero de la Ilusi? ",
	" Pesadilla ",
	" Bruja ",                
	" Goblin Pesado ",
	" Dawlin ",
	" Estigio ",
	" ?cubo ",
	" Golem Cadena ",           
	" Espectro Oscuro ",
	" Metron ",
	" Lord Avelisk ",
	" Crep?culo ",
	" Sadnesst ",            
	0,
};

char *ChargingTime4=" Elevar velocidad para cargar:\r ";
char *AddIceDamage4=" Da? Agregado de Elemental de Escarcha:\r ";
char *IceTime4=" Tiempo Congelado:\r ";
char *sinAttackType = " Tipo de Ataque:\r ";
char *sinAttackType2[2] ={" Manual\r "," Autm?ico\r "};

char *Won=" Oro ";


char *CastlItemInfo[] ={
	{" Con Modo Dios instant?eo pero\r "},
	{" Porcentaje Cr?ico\r "},
	{" Agregando porcentaje de evasi?\r "},
	{" ST,HP,MA de los jugadores del grupo\r "},
	{" resurreci? inmediatamente.\r "},
	{" ATK de torre de Cristal\r "},     
	{" poder de ATK est?20% en el objetivo\r "},
	0,
};
char *CastlItemInfo2[] ={
	{" poder de ATK disminuye en 1/2.\r "},
	{" 5% incremento.\r "},
	{" incrementar.\r "},
	{" recuperar todo.\r "},
	{" \r "},
	{" 50%compensaci?.\r "},
	{" Agregar.\r "},
	0,
};


char *CharClassTarget[8]={
	" Objetivo(Luchador)\r ",
	" Objetivo(Mec?ico)\r ",
	" Objetivo(Piquero)\r ",
	" Objetivo(Arquero)\r ",
	" Objetivo(Caballero)\r ",
	" Objetivo(Atalanta)\r ",
	" Objetivo(Mago)\r ",
	" Objetivo(Sacerdotisa)\r ",
};
char *AttributeTower[4]={
	" Atributo(Fuego)\r ",
	" Atributo(Hielo)\r ",
	" Atributo(Rayo)\r ",
	" Duraci?:%dSec\r ",
};

char *SiegeMessage_MerComplete =" Configuraci? de Mercenario completa ";


char *haQuestMonsterName[]={
	" Hoppie ",
	" Rabioso ",
	" Gnomo ",
	" Goblin del Norte ",
	" Skeleton ",
	" Corrupto ",
	" C?lope ",
	" Bargon ",
	0,
};
char *ha100LVQuestItemName[]={
	" Hacha Minotauro ",
	" Garra Extrema ",
	" Martillo de Hueso de Drag? ",
	" Guada? de Fuego Infernal ",
	" Arco de la Venganza ",
	" Espada Inmortal ",
	" Jabalina Salamandra ",
	" Cayado G?ico ",
	0,
};

char *ha100LVQuestMonterName[]={
	" Monsters en el Coraz? de Perum ",
	" Monstruos del Valle de Gallubia ",
	0,
};
char *ha100LVQuestName = " Fantasma de Furia ";


char *PremiumItemDoc[][2]={
	{" Hace que los puntos de stat\r "     ," sean restribuidos.\r "},     
	{" Hace que los puntos de habilidad\r "     ," sean restribuidos.\r "},    
	{" Hace que los puntos stat/hab \r "," sean restribuidos.\r "},     
	{" Hace que el personaje muerto \r "    ," reviva.\r "},        
	{" Se vuelve invencible por el tiempo establecido.\r "," El poder de ataque disminuye en 1/2\r "},    
	{" 15% de incremento \r "    ," en el ataque cr?ico.\r "},		
	{" 15% de incremento de \r "         ," chances de evadir.\r "},		
};
char *UpKeepItemDoc[] = {
	" Tiempo Restante : %dMinutos ",
	" %d%s Chance de Ca?a Adicional ",
	" %d%s incremento en EXP ",
	" Incremento %d%s Ataque ",
	" Recarga de HP por golpe ",
	" Recarga de MP por golpe ",
	" Incrementa la capacidad en d% ",
	" Reduce el uso de MP en %d%s ",
	0,
};
char *UpKeepItemName[] = {
	" Tercer Ojo ",
	" Poci? para incrementar EXP ",
	" Colmillo Vamp?ico ",
	" Poci? de Recarga de Man?",
	" Might of awell ",
	" Mana Reduce Potion ",
	" Phoenix ",
	0,
};

