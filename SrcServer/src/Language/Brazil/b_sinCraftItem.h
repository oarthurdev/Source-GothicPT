

#define   SIN_ADD_FIRE			0x00000001	
#define   SIN_ADD_ICE			0x00000002	
#define   SIN_ADD_LIGHTNING			0x00000004	
#define   SIN_ADD_POISON			0x00000008	
#define   SIN_ADD_BIO			0x00000010	
#define   SIN_ADD_Critico			0x00000020	
#define   SIN_ADD_ATTACK_RATE		0x00000040	
#define   SIN_ADD_DAMAGE_MIN		0x00000080	
#define   SIN_ADD_DAMAGE_MAX		0x00000100	
#define   SIN_ADD_ATTACK_SPEED		0x00000200	
#define   SIN_ADD_ABSORB			0x00000400	
#define   SIN_ADD_DEFENCE			0x00000800	
#define   SIN_ADD_BLOCK_RATE		0x00001000	
#define   SIN_ADD_MOVE_SPEED		0x00002000	
#define   SIN_ADD_LIFE			0x00004000	
#define   SIN_ADD_MANA			0x00008000	
#define   SIN_ADD_STAMINA			0x00010000	
#define   SIN_ADD_LIFEREGEN			0x00020000 	
#define   SIN_ADD_MANAREGEN		0x00040000  	
#define   SIN_ADD_STAMINAREGEN		0x00080000  	

#define   SIN_ADD_NUM				1
#define   SIN_ADD_PERCENT			2

/*
sinWP1 = foice
sinWS1 = Espada
sinWS2 = Arco
sinWT1 = Lança
sinWH1 = Hammer
sinWC1 = Staff
sinWN1 = Shaman
sinWD1 = Assasina

*/



//MIX ARMAS DEVNINE MIX 1



#define   SIN_ADD_FIRE			0x00000001	
#define   SIN_ADD_ICE			0x00000002	
#define   SIN_ADD_LIGHTNING			0x00000004	
#define   SIN_ADD_POISON			0x00000008	
#define   SIN_ADD_BIO			0x00000010	
#define   SIN_ADD_Critico			0x00000020	
#define   SIN_ADD_ATTACK_RATE		0x00000040	
#define   SIN_ADD_DAMAGE_MIN		0x00000080	
#define   SIN_ADD_DAMAGE_MAX		0x00000100	
#define   SIN_ADD_ATTACK_SPEED		0x00000200	
#define   SIN_ADD_ABSORB			0x00000400	
#define   SIN_ADD_DEFENCE			0x00000800	
#define   SIN_ADD_BLOCK_RATE		0x00001000	
#define   SIN_ADD_MOVE_SPEED		0x00002000	
#define   SIN_ADD_LIFE			0x00004000	
#define   SIN_ADD_MANA			0x00008000	
#define   SIN_ADD_STAMINA			0x00010000	
#define   SIN_ADD_LIFEREGEN			0x00020000 	
#define   SIN_ADD_MANAREGEN		0x00040000  	
#define   SIN_ADD_STAMINAREGEN		0x00080000  	

#define   SIN_ADD_NUM				1
#define   SIN_ADD_PERCENT			2



//____________________________________ MIX ARMAS - DEVINE 1 ____________________________________



{ {sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1, sinWD1, sinWN1 }, // Itens compatíveis para o mix
	{ 0,0,0,0,2,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
	{ SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_Critico,SIN_ADD_MANA,0,0,0 }, // Define dos Atributos do Mix
	{ 2,5,3,2,6,0,0,0 }, // Números dos Atributos do Mix
	{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Tipo de atribuição (Numero ou %)
	"Ataque Min+2\rAtaque Max+5\rTaxa de Ataque+3\rCritico+2%\rMP +6"},// Texto dos mix finalizado

{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1, sinWD1, sinWN1 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,3,7,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_Critico,SIN_ADD_MANA,0,0,0 }, // Define dos Atributos do Mix
{ 3,4,15,1,6,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Atack Min+3\rAtack Max +4\rAtk Rate +15\rCritico 1%\rMP +6" }, // Texto dos mix finalizado

//____________________________________ MIX ARMAS - CELESTO  ____________________________________

{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1, sinWD1, sinWN1 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_Critico,SIN_ADD_MANA,0,0,0 }, // Define dos Atributos do Mix
{ 4,7,2,1,12,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Atack Min +4\rAtack Max. +7\rAtk Rate +2\rCritical 1%\rAdd MP +12" }, // Texto dos mix finalizado

{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1, sinWD1, sinWN1 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,1,4,7,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_Critico,SIN_ADD_MANA,0,0,0 }, // Define dos Atributos do Mix
{ 5,6,20,1,12,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Atack Min +5\rAtack Power +6\rAtk Rate +20\rCritico 1%\rMP +12" },  // Texto dos mix finalizado

//____________________________________ MIX ARMAS - MIRAGE ____________________________________

{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1, sinWD1, sinWN1 }, // Itens compatíveis para o mix
{ 0,0,0,0,1,1,1,2,2,5,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_Critico,SIN_ADD_MANA,0,0,0 }, // Define dos Atributos do Mix
{ 5,9,7,2,15,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Atack Min. +5\rAtack Max. +9\rAtk Rate +7\rCritico 2%\rMP +15\r" }, // Texto dos mix finalizado

{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1, sinWD1, sinWN1 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,2,3,7,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_Critico,SIN_ADD_MANA,0,0,0 }, // Define dos Atributos do Mix
{ 6,8,25,1,15,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Attack Min +6\rAtack Max +8\rAtk Rate +25\rCritical 1%\rAdd MP +15\r" }, // Texto dos mix finalizado

//____________________________________ MIX ARMAS - INFERNA ____________________________________

{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1, sinWD1, sinWN1 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_Critico,SIN_ADD_MANA,0,0,0 }, // Define dos Atributos do Mix
{ 7,14,9,3,25,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Atack Min. +7\rAtack Max. +14\rAtk Rate +9\rCritico 3%\rMP +25\r" }, // Texto dos mix finalizado

{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1, sinWD1, sinWN1 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_Critico,SIN_ADD_MANA,0,0,0 }, // Define dos Atributos do Mix
{ 13,15,50,4,35,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Attack Min +13\rAtack Max +15\rAtk Rate +50\rCritical 4%\rAdd MP +35\r" }, // Texto dos mix finalizado

//______________________________________________________________________________________






//____________________________________ ARMADURAS E ROBES - DEVINE ______________________________

{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,2,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,0,0 }, // Define dos Atributos do Mix
{ 30,1.2,5,2,2,2,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0 }, // Quantidade de atributos
"Defesa +30\rAbs +1,2\rHP +5\rOrganica +2\rVeneno +2\rGelo +2\r" }, // Texto dos mix finalizado


{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,3,7,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,0,0 }, // Define dos Atributos do Mix
{ 50,1,5,1,1,1,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0 }, // Quantidade de atributos
"Defesa +50\rAbs +1\rHP +5\rOrganica +1\rVeneno +1\rGelo +1\r" }, // Texto dos mix finalizado	

//____________________________________ ARMADURAS E ROBES - CELESTO ______________________________

{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,0,0 }, // Define dos Atributos do Mix
{ 40,2.4,8,3,3,3,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0 }, // Quantidade de atributos
"Defesa +40\rAbs + 2,4\rHP +8\rOrganica +3\rVeneno +3\rGelo +3\r" }, // Texto dos mix finalizado


{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,1,4,7,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,0,0 }, // Define dos Atributos do Mix
{ 70,2,8,2,2,2,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0 }, // Quantidade de atributos
"Defesa +70\rAbs +2\rHP +8\rOrganica +2\rVeneno +2\rGelo +2\r" }, // Texto dos mix finalizado


//____________________________________ ARMADURAS E ROBES - MIRAGE ______________________________


{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,1,1,1,2,2,5,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,0,0 }, // Define dos Atributos do Mix
{ 60,3.6,10,4,4,4,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0 }, // Quantidade de atributos
"Defesa +60\rAbs +3,6\rHP+10\rOrganica +4\rVeneno +4\rGelo +4\r" }, // Texto dos mix finalizado

{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,2,3,7,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,0,0 }, // Define dos Atributos do Mix
{ 100,3,10,3,3,3,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0 }, // Quantidade de atributos
"Defesa +100\rAbs +3\rHP +10\rOrganic +3\rVeneno +3\rGelo +3\r" }, // Texto dos mix finalizado


//____________________________________ ARMADURAS E ROBES - INFERNA ______________________________


{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,0,0 }, // Define dos Atributos do Mix
{ 90,4.8,13,6,6,6,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0 }, // Quantidade de atributos
"Defesa +90\rAbs +4,8\rHP+13\rOrganica +6\rVeneno +6\rGelo +6\r" }, // Texto dos mix finalizado

{ { sinDA1,sinDA2,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,0,0 }, // Define dos Atributos do Mix
{ 200,5,25,5,5,5,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0 }, // Quantidade de atributos
"Defesa +200\rAbs +5\rHP +25\rOrganic +5\rVeneno +5\rGelo +5\r" }, // Texto dos mix finalizado

	

												  //______________________________________________________________________________________





												  //____________________________________ MIX ESCUDOS - DEVINE ____________________________________


{ { sinDS1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,2,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ABSORB,SIN_ADD_LIFE,0,0,0,0,0,0 }, // Define dos Atributos do Mix
{ 1,20,0,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0, 0, 0 }, // Quantidade de atributos
"Abs + 1\rHP +20\r" }, // Texto dos mix finalizado


{ { sinDS1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,3,7,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ABSORB,SIN_ADD_LIFE,0,0,0,0,0,0 }, // Define dos Atributos do Mix
{ 1,10,0,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0, 0, 0 }, // Quantidade de atributos
"Abs +1\rHP +10\r" }, // Texto dos mix finalizado


//____________________________________ MIX ESCUDOS - CELESTO ____________________________________


{ { sinDS1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,SIN_ADD_DEFENCE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,SIN_ADD_LIFE, 0 }, // Define dos Atributos do Mix
{ 1,1,10,2,2,2,30,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_PERCENT, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Abs +1\rBlock +1%\rDefesa +10\rOrganic +2\rVeneno +2\rGelo +2\rHP +30\r" }, // Texto dos mix finalizado

{ { sinDS1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,1,4,7,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,SIN_ADD_DEFENCE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,SIN_ADD_LIFE, 0 }, // Define dos Atributos do Mix
{ 1,1,5,1,1,1,20,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_PERCENT, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Abs +1\rBlock +1%\rDefesa + 5\rOrganic +1\rVeneno +1\rGelo +1\rHP +20\r" }, // Texto dos mix finalizado


//____________________________________ MIX ESCUDOS - MIRAGE ____________________________________

{ { sinDS1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,1,1,1,2,2,5,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,SIN_ADD_DEFENCE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,SIN_ADD_LIFE, 0 }, // Define dos Atributos do Mix
{ 1.5,1,15,3,3,3,40,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_PERCENT, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Abs + 1.5\rBlock 1%\rDefesa +15\rOrganic +3\rVeneno +3\rGelo +3\rAdd HP +40\r" }, // Texto dos mix finalizado

{ { sinDS1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,2,3,7,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,SIN_ADD_DEFENCE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,SIN_ADD_LIFE, 0 }, // Define dos Atributos do Mix
{ 1.5,2,10,2,2,2,30,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_PERCENT, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Abs + 1.5\rBlock 2%\rDefesa +10\rOrganic +2\rVeneno +2\rGelo +2\rAdd HP +30\r" }, // Texto dos mix finalizado

//____________________________________ MIX ESCUDOS - INFERNA ____________________________________

{ { sinDS1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,SIN_ADD_DEFENCE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,SIN_ADD_LIFE, 0 }, // Define dos Atributos do Mix
{ 2,2,25,4,4,4,60,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_PERCENT, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Abs + 2\rBlock 2%\rDefesa +25\rOrganic +4\rVeneno +4\rGelo +4\rAdd HP +60\r" }, // Texto dos mix finalizado

{ { sinDS1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,SIN_ADD_DEFENCE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,SIN_ADD_LIFE, 0 }, // Define dos Atributos do Mix
{ 3,5,15,3,3,3,50,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_PERCENT, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Abs + 3\rBlock 5%\rDefesa +15\rOrganic +3\rVeneno +3\rGelo +3\rAdd HP +50\r" }, // Texto dos mix finalizado


												 //______________________________________________________________________________________



	//____________________________________ MIX ORB - DEVINE ____________________________________

{ { sinOM1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,2,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANA,SIN_ADD_LIFE, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 40,1,10,30,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 }, // Quantidade de atributos
"Defesa +40\rAbs +1\rMP +10\rHP +30\r" }, // Texto dos mix finalizado

{ { sinOM1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,3,7,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANA,SIN_ADD_LIFE,0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 20,1,20,10,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 }, // Quantidade de atributos
"Defesa +20\rAbs +1\rMP + 20\rHP +10\r" }, // Texto dos mix finalizado

	//____________________________________ MIX ORB - CELESTO ____________________________________

{ { sinOM1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANA,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE, 0 }, // Define dos Atributos do Mix
{ 80,1.5,15,40,2,2,2,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Defesa +80\rAbs 1.5\rMP +15\rdHP +40\rOrganica +2\rVeneno +2\rGelo +2\r" }, // Texto dos mix finalizado

{ { sinOM1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,1,4,7,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANA,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE, 0 }, // Define dos Atributos do Mix
{ 40,2,40,15,1,1,1,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Defesa +40\rAbs +2\rMP +40\rHP +15\rOrganico +1\rVeneno +1\rGelo +1" }, // Texto dos mix finalizado


	//____________________________________ MIX ORB - MIRAGE ____________________________________

{ { sinOM1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,1,1,1,2,2,5,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANA,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE, 0 }, // Define dos Atributos do Mix
{ 120,2,20,50,3,3,3,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Defesa +120\rAbs +2\rAdd MP +20\rAdd HP +50\rOrganico +3\rVeneno + 3\rGelo +3" }, // Texto dos mix finalizado

{ { sinOM1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,2,3,7,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANA,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE, 0 }, // Define dos Atributos do Mix
{ 60,3,60,20,2,2,2,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Defesa +60\rAbs +3\rAdd MP +60\rAdd HP +20\rOrganico +2\rVeneno +2\rGelo +2" }, // Texto dos mix finalizado

	//____________________________________ MIX ORB - INFERNA ____________________________________

{ { sinOM1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANA,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE, 0 }, // Define dos Atributos do Mix
{ 160,2.5,25,55,4,4,4,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Defesa +160\rAbs +2.5\rAdd MP +25\rAdd HP +55\rOrganico +4\rVeneno + 4\rGelo +4" }, // Texto dos mix finalizado

{ { sinOM1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANA,SIN_ADD_LIFE,SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE, 0 }, // Define dos Atributos do Mix
{ 125,4.3,80,30,3,3,3,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0 }, // Quantidade de atributos
"Defesa +80\rAbs +4.3\rAdd MP +80\rAdd HP +30\rOrganico +3\rVeneno +3\rGelo +3" }, // Texto dos mix finalizado




												 //____________________________________ MIX BRACELETE - DEVINE ____________________________________

{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,2,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 10,30,8,30,5,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +10\rAtk Rate +30\rHP +8\rMP +30\rRess +5\r" },  // Texto dos mix finalizado


{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,3,7,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 30,10,10,10,20,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +30\rAtk Rate +10\rHP +10\rMP +10\rRess +20\r" },  // Texto dos mix finalizado

	 //____________________________________ MIX BRACELETE - CELESTO ____________________________________

{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 15,40,10,35,10,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +15\rAtk Rate +40\rHP +10\rMP +35\rRess +10\r" },  // Texto dos mix finalizado

{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,1,4,7,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 40,15,15,15,30,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +40\rAtk Rate +15\rHP +15\rMP +15\rRess +30\r" },  // Texto dos mix finalizado


	 //____________________________________ MIX BRACELETE - MIRAGE ____________________________________

{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,1,1,1,2,2,5,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 20,50,12,40,15,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +20\rAtk Rate +50\rHP +12\rMP +40\rRess +15\r" },  // Texto dos mix finalizado

{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,2,3,7,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 50,20,20,20,40,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +50\rAtk Rate +20\rHP +20\rMP +20\rRess +40\r" },  // Texto dos mix finalizado

	 //____________________________________ MIX BRACELETE - INFERNA ____________________________________

{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 25,60,14,45,20,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +25\rAtk Rate +60\rHP +14\rMP +45\rRess +20\r" },  // Texto dos mix finalizado

{ { sinOA2,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 45,60,20,25,30,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +45\rAtk Rate +60\rHP +20\rMP +25\rRess +30\r" },  // Texto dos mix finalizado





											 //______________________________________________________________________________________




											 //____________________________________ MIX LUVAS - DEVINE ____________________________________

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,2,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 10,0.5,8,30,5,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +10\rAbsorção +0.5\rHP +8\rMP +30\rRess +8\r" }, // Texto dos mix finalizado

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,3,7,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 5,1,10,10,20,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +5\rAbsorção +1\rHP +10\rMP +10\rRess +20\r" }, // Texto dos mix finalizado

	 //____________________________________ MIX LUVAS - CELESTO ____________________________________

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 30,1,10,35,10,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +30\rAbsorção +1\rHP +10\rMP +35\rRess +10\r" }, // Texto dos mix finalizado

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,1,4,7,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 15,2,15,15,30,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +15\rAbsorção +2\rHP +15\rMP +15\rRess +30\r" }, // Texto dos mix finalizado


	 //____________________________________ MIX LUVAS - MIRAGE ____________________________________

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,1,1,1,2,2,5,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 50,1.5,12,40,15,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +50\rAbsorção +1,2\rHP +12\rMP +40\rRess +15\r" }, // Texto dos mix finalizado

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,2,3,7,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 25,3,20,20,40,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +25\rAbsorção +3\rHP +20\rMP +20\rRess +40\r" }, // Texto dos mix finalizado

	 //____________________________________ MIX LUVAS - INFERNA ____________________________________

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 70,2,14,45,20,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +70\rAbsorção +2\rHP +14\rMP +45\rRess +20\r" }, // Texto dos mix finalizado

{ { sinDG1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0 }, // Define dos Atributos do Mix
{ 70,4,20,25,30,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0 }, // Quantidade de atributos
"Defesa +70\rAbsorção +4\rHP +20\rMP +25\rRess +30\r" }, // Texto dos mix finalizado


									   //______________________________________________________________________________________





									   //____________________________________ MIX BOTAS - DEVINE ____________________________________

{ { sinDB1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,2,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0 }, // Define dos Atributos do Mix
{ 10,0.6,1.8,8,30,5,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"Defesa+10\rAbsorção+0.6\rVelocidade+1.8\rHp +8\rMp +30\rRess +5\r" }, // Texto dos mix finalizado

{ { sinDB1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,3,7,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0 }, // Define dos Atributos do Mix
{ 5,1.2,0.9,10,10,20,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"Defesa+5\rAbsorção+1.2\rVelocidade+0.9\rHp +10\rMp +10\rRess +20\r" }, // Texto dos mix finalizado


//____________________________________ MIX BOTAS - CELESTO ____________________________________

{ { sinDB1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0 }, // Define dos Atributos do Mix
{ 15,1,2.7,10,35,10,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"Defesa+15\rAbsorção+1\rVelocidade+2.7\rHp +10\rMp +35\rRess +10\r" }, // Texto dos mix finalizado

{ { sinDB1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,1,4,7,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0 }, // Define dos Atributos do Mix
{ 7,1.8f,1.5,15,15,30,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"Defesa+7\rAbsorção+1.8\rVelocidade+1.5\rHp +15\rMp +15\rRess +30\r" }, // Texto dos mix finalizado


//____________________________________ MIX BOTAS - MIRAGE ____________________________________

{ { sinDB1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,1,1,1,2,2,5,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0 }, // Define dos Atributos do Mix
{ 20,1.4,3.6,12,40,15,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"Defesa+20\rAbsorção+1.4\rVelocidade+3.6\rHp +12\rMp +40\rRess +15\r" }, // Texto dos mix finalizado

{ { sinDB1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,2,3,7,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0 }, // Define dos Atributos do Mix
{ 10,2.4,2,20,20,40,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"Defesa+10\rAbsorção+2.4\rVelocidade+2\rHp +20\rMp +20\rRess +40\r" }, // Texto dos mix finalizado

//____________________________________ MIX BOTAS - INFERNA ____________________________________

{ { sinDB1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0 }, // Define dos Atributos do Mix
{ 25,1.8,4.6,14,45,20,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"Defesa+25\rAbsorção+1.8\rVelocidade+4.6\rHp +14\rMp +45\rRess +20\r" }, // Texto dos mix finalizado

{ { sinDB1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MOVE_SPEED, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0 }, // Define dos Atributos do Mix
{ 25,3,3.6,20,25,30,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"Defesa+25\rAbsorção+3\rVelocidade+3.6\rHp +20\rMp +25\rRess +30\r" }, // Texto dos mix finalizado



													   //______________________________________________________________________________________




													   //____________________________________ MIXES AMULETOS - DEVINE ___________________________________



{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,2,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 2,8,10,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0 }, // Quantidade de atributos
"HP+2\rMP+8\rST+10\r" }, // Texto dos mix finalizado

{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,3,7,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 4,4,5,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0 }, // Quantidade de atributos
"HP+4\rMP+4\rST+5\r" }, // Texto dos mix finalizado

//____________________________________ MIXES AMULETOS - CELESTO ___________________________________

{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 3,10,15,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0 }, // Quantidade de atributos
"HP+3\rMP+10\rST+15\r" }, // Texto dos mix finalizado

{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,1,4,7,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 6,5,7,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0 }, // Quantidade de atributos
"HP+6\rMP+5\rST+7\r" }, // Texto dos mix finalizado

//____________________________________ MIXES AMULETOS - MIRAGE ___________________________________


{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,1,1,1,2,2,5,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 6,16,20,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0 }, // Quantidade de atributos
"HP+6\rMP+16\rST+20\r" }, // Texto dos mix finalizado

{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,2,3,7,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 12,8,10,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0 }, // Quantidade de atributos
"HP+12\rMP+8\rST+10\r" }, // Texto dos mix finalizado


//____________________________________ MIXES AMULETOS - INFERNA ___________________________________


{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 9,20,25,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0 }, // Quantidade de atributos
"HP+9\rMP+20\rST+25\r" }, // Texto dos mix finalizado

{ { sinOA1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_STAMINA, SIN_ADD_LIFEREGEN, SIN_ADD_MANAREGEN, 0, 0, 0 }, // Define dos Atributos do Mix
{ 18,20,25,1.5,2,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0 }, // Quantidade de atributos
"HP+18\rMP+20\rST+25\rHP Regen+1.5\rMP Regen+2\r" }, // Texto dos mix finalizado


													//_____________________________________________________________________________________







													//____________________________________ MIXES RINGS - DEVINE ____________________________________



{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,2,2,3,5,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_MANA, 0, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 0.4,2,0,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0 }, // Quantidade de atributos
"HP Regen +0,4\rMP +2\r" }, // Texto dos mix finalizado

{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,3,7,0,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_LIFE, SIN_ADD_MANA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 0.1,2,1,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"HP Regen +0.1\rHP +2\rMP +1\r" }, // Texto dos mix finalizado

//____________________________________ MIXES RINGS - CELESTO ____________________________________

{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,2,2,3,5,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_LIFE, SIN_ADD_MANA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 0.5,3,4,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"HP Regen +0.5\rHP +3\rMP +4\r" }, // Texto dos mix finalizado

{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,1,4,7,0,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_LIFE, SIN_ADD_MANA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 0.2,4,2,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"HP Regen +0.2\rHP +4\rMP +2\r" }, // Texto dos mix finalizado


//____________________________________ MIXES RINGS - MIRAGE ____________________________________


{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,1,1,1,2,2,5,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_LIFE, SIN_ADD_MANA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 0.6,5,6,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"HP Regen +0.6\rHP +5\rMP +6\r" }, // Texto dos mix finalizado

{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,2,3,7,0,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_LIFE, SIN_ADD_MANA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 0.3,8,3,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"HP Regen +0.3\rHP +8\rMP +3\r" }, // Texto dos mix finalizado

//____________________________________ MIXES RINGS - INFERNA ____________________________________


{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_LIFE, SIN_ADD_MANA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 0.7,7,8,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"HP Regen +0.7\rHP +7\rMP +8\r" }, // Texto dos mix finalizado

{ { sinOR1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_ATTACK_RATE, 0, 0 }, // Define dos Atributos do Mix
{ 1.6,16,20,20,0.8,15,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"HP Regen +1.6\rHP +16\rMP +20\rDef +20\rAbs 0.8\rAtack Rate +15\r" }, // Texto dos mix finalizado

														   //_____________________________________________________________________________________

	//____________________________________ MIXES BRINCOS - INFERNA ____________________________________


{ { sinOE1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,3,3,6,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_LIFE, SIN_ADD_MANA, 0, 0, 0, 0, 0 }, // Define dos Atributos do Mix
{ 0.7,7,8,0,0,0,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"HP Regen +0.7\rHP +7\rMP +8\r" }, // Texto dos mix finalizado

{ { sinOE1,0,0,0,0,0,0,0 }, // Itens compatíveis para o mix
{ 0,0,0,0,0,0,0,0,0,3,9,0,0,0 }, // Sheltons utilizados
{ SIN_ADD_LIFEREGEN, SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_ATTACK_RATE, 0, 0 }, // Define dos Atributos do Mix
{ 1.6,16,20,20,0.8,15,0,0 }, // Números dos Atributos do Mix
{ SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0 }, // Quantidade de atributos
"HP Regen +1.6\rHP +16\rMP +20\rDef +20\rAbs 0.8\rAtack Rate +15\r" }, // Texto dos mix finalizado

														   //_____________________________________________________________________________________