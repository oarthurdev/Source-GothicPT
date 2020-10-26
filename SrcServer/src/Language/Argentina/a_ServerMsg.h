
char *srMsg_001 = " El Líder del grupo %s ha recomendado a %s para unirse al grupo ";
char *srMsg_002 = " envió un pedido de grupo a %s ";
char *srMsg_003 = " %s ya es miembro del grupo ";
char *srMsg_004 = " %s ya es miembro de otro grupo ";
char *srMsg_005 = " %s ya es miembro de otro grupo ";
char *srMsg_006 = " La diferencia de nivel es demasiado grande ";
char *srMsg_007 = " %s está en línea ";
char *srMsg_008 = " %s está desconectado, o no se lo puede encontrar ";
char *srMsg_009 = " %s objetos han sido creados ";
char *srMsg_010 = " %s objetos han sido enviados a %s ";
char *srMsg_011 = " Aviso> %s ";

char *srMsg_012 = " El máximo de usuarios ha sido establecido en %d ";
char *srMsg_013 = " El máximo establecido de usuarios actual es %d ";
char *srMsg_014 = " el código de autorización para el cliente %d ha sido agregado ( %d ) ";
char *srMsg_015 = " Imposible agregar código - LLENO ";
char *srMsg_016 = " La autorización del cliente ha sido inhabilitada ";
char *srMsg_017 = " Felicitaciones. Has sido expulsado %s ";
char *srMsg_018 = " %s cuenta ha sido establecida para el personaje %s ";
char *srMsg_019 = " Imposible conectar con la cuenta ";
char *srMsg_020 = " Mi estatus(%d) ";
char *srMsg_021 = " Líder del Grupo(%s) ";
char *srMsg_022 = " Has abandonado el grupo ";
char *srMsg_023 = " %s ha sido expulsado del grupo ";
char *srMsg_024 = " %s no es miembro del grupo o no puede ser expulsado ";
char *srMsg_025 = " El grupo ha sido desbandado ";
char *srMsg_026 = " %s ha sido delegado como el nuevo líder del grupo ";
char *srMsg_027 = " Cuenta( %s ) Nombre( %s ) IP( %s ) Connectado( %d mins ) ";
char *srMsg_028 = " Actualmente desconectado, o no se lo puede encontrar ";
char *srMsg_029 = " Cuenta( %s ) Nombre( %s ) IP( %s ) Connectado( %d mins ) ";
char *srMsg_030 = " Actualmente desconectado, o no se lo puede encontrar ";
char *srMsg_031 = " Posición de %s ( %s ) x=%d / z=%d ";
char *srMsg_032 = " Usuarios %d / Monstruos Activos  %d ";
char *srMsg_033 = " Abierto (%d) / Activo (%d) ";
char *srMsg_034 = " Imposible enviar mensajes privados ";
char *srMsg_035 = " Niega mensajes privados ";
char *srMsg_036 = " Acepta mensajes privados ";
char *srMsg_037 = " > %s Gana %s ";
char *srMsg_038 = " > %s  Mana(Místico) Obtiene [Quedan:%d] ";


char *srMsg_100 = " No puedes entrar porque se está llevando a cabo un evento. Por favor intenta otra vez mañana temprano. ";
char *srMsg_101 = " Todas las entradas están vendidas. Por favor, vuelve mañana al amanecer. ";
char *srMsg_102 = " Las entradas para el súper evento principal de monstruos están en venta. Te costará sólo 100.000 Oro ^^ ";
char *srMsg_103 = "         %d Ronda           ";
char *srMsg_104 = " Felicitaciones. El evento ha finalizado (adquirir $ %d ) ";
char *srMsg_105 = "       Score : %d           ";
char *srMsg_106 = " Todas las entradas para este evento están vendidas ";
char *srMsg_107 = " Tus habilidades no son lo suficientemente buenas para entrar. Por favor, entrena más y vuelve luego ";
char *srMsg_108 = " No puedes entrar en este momento. Por favor, vuelve en otra oportunidad. ";
char *srMsg_110 = " Tu equipo dejó(no.%d) Ganancia %doro ";
char *srMsg_111 = " %s vence un monstruo ( Ganancia %Punto ) ";

char *srMsg_200 = "  Has excedido el límite de invocaciones  ";
char *srMsg_201 = "   Sólo puedes invocar uno por vez   ";
char *srMsg_202 = "   No puedes usar este cristal   ";

char *srMsg_300 = "     contraseña(número telefónico) !es incorrecta!    ";
char *srMsg_301 = "   Si tipeas una contraseña incorrecta más de 5 veces, el sistema bloqueará tu contraseña. ";

char *srMsg_400 = "      Compró %d estrellas     ";
char *srMsg_401 = "      Donó %d        ";

char *srItem_BB = " Bolsa de la Suerte ";
char *srItem_PZ = " Rompecabezas ";

#define CHAT_ANGERMONSTER_MAX		5
char *szAngerMonster[CHAT_ANGERMONSTER_MAX] = {
	" !Ya no lo soporto! ",
	" Esta es la venganza de nuestra tribu. ",
	" No nos lastimes más. ",
	" !Injusto! !no lo soporto más! ",
	" No nos molestes ."
};

#define MORIF_CHAT_MAX		18
char *szMorifChatMsg[MORIF_CHAT_MAX] = {
	" Muere por mí, y Madura con éxito. ",
	" Si me golpeas, serás maldito con la falla de la Maduración... ",
	" !Eres un cobarde! No puedo ser paciente ",
	" !Dame todos tus objetos..! ",

	" Tratar de Madurar demasiado y fallar frecuentemente te hace más duro~ ",
	" Es bueno preparar el objeto antes de Madurarlo~ ",
	" Qué dirías si fallas en la Maduración? ",
	" Esta es mi maldición de Maduración~ ",
	" !Dame todas tus sheltoms~! ",
	" Ni pienses en Madurar +10~ ",
	" No tengas miedo de Madurar. Huuuu ",
	" Tendrás éxito en el 100% de las Maduraciones~~~~~ !Broma! !Ja Ja ! ",
	" Le tengo miedo a Abuelita Molly~ ",
	" Tú también eres débil~ Puedo Madurarte para que seas más fuerte? ",
	" Sabes que la armadura que estoy usando es la que un Guerrero perdió cuando falló la Maduración~ !Pero no soy miserable~! ",
	" Ja Ja ja~ Nunca obtendrás tu Devine~ ",
	" No quiero que falles en la Maduración~ Yo también sufro~ ",
	" !Hey! ~ Ya no te lleves mis sheltoms ~ Es mi tesoro~ "
};

#define MORIF_CHAT_DROP_MAX		15
char *szMorifChatDropMsg[MORIF_CHAT_DROP_MAX] = {
	" Cómo obtuve estos... ",
	" !Por Dios! Es mío. ",
	" !La próxima vez, me vengaré de ti! ",

	" Cómo obtuve las Sheltoms~Oh~Mis Sheltoms ",
	" !NOOOOO! !No te lleves mis sheltoms~Oh~! ",
	" La falla en la Maduración no es mi culpa~ Ahhh~ muy injusto. ",
	" Piensas que te irá bien después de todo lo que me hiciste~? ",
	" Ahh~ Maldición de la MAduración...... ",
	" Todos tus objetos fallidos está en mi depósito~ yap~! ",
	" Uy~ Te ganaré la próxima~ Victoria~!! ",
	" Oohuhuhu~Has entrado a la lista negra de mi tienda de Maduración! ",
	" Kuuk~ Debería tener más HP.... ",
	" !Te recordaré~! !Pagarás por esto en Pillai~! ",
	" Nunca te perdonaré~  ",
	" Será mejor que sólo hagas Mezcla en el futuro~Ho Ho Ho~! "
};

#define MOLLYWOLF_CHAT_MAX		28
char *szMollyWolfChatMsg[MOLLYWOLF_CHAT_MAX] = {
	" Todavía piensas que soy Abuelita Molly? ",
	" Hueles a pavo. Dame un poco, !y no te mataré! ",
	" El pavo recuperará el HP de todos tus amigos. ",
	" !Ha! !Cómo te atreves a desafiarme, el lobo que se robó al pavo!. ",
	" !También tomaré tu Devine! Controla tu inventario. ",
	" Soy el que robó el pavo de Abuelita. Quieres? ",
	" Me siento más fuerte en las ropas de Abuelita Molly ",
	" Tiene Jalea Real? !Me los comeré a todos! ",
	" Algun dia entenderas el amor que siento por los pavos!.",
	" !Abuelita Molly te engañó! !Ella se comió todo el pavo! ",
	" !Yo soy Abuelita Molly~! Quieres que te muestre mis manos? ",
	" Estas ropas lucen mucho mejor en mí, eh? huhu ",
	" !Yo soy el lobo mascota de Abuelita Molly! ",
	" Toma mi pavo, luego berás casarte conmigo!! ",
	" JaJa Te gusta el pavo madurado +10? Tiene buen sabor...",
	" Qué? !Quieres pelear conmigo? OK ven~ ",
	" Eh? Adónde se fueron los 3 chanchitos? Y de repente apareces tú...? ",
	" Soy un cordero con piel de lobo. ",
	" Abuelita Molly te hizo hacer esto? O fue papá Fuerza? ",
	" Yo soy la Molly real. La del pueblo es falsa. ",
	" No quiero pavo. !Tráeme Jalea Real~!! ",
	" Me parezco a un pavo?!! ",
	" El pavo está en mi estómago~ ",
	" El pavo es parte de mí ahora. ",
	" Dame una presa de pavo, así no te mato~ Grrrr~ ",
	" Felicidades~ Soy Molly~ ",
	" Oo-hehe Fuiste engañado~ Crees que soy humana?~ ",
	" !Bebé! te regalaré un pavo !divirtámonos! !Bebé~~!! "
};


#define MOLLYWOLF_CHAT_DROP_MAX		25
char *szMollyWolfChatDropMsg[MOLLYWOLF_CHAT_DROP_MAX] = {
	" Ya está en mal estado. Te dolerá el estómago si comes esto. ",
	" Piensas que lapuedes pasar bien luego de haberme lastimado? ",
	" Khuhuhuhuhuk! ",
	" !Oh Mi Dios! Sólo comí unos pocos. ",
	" !NUNCA te daré el pavo con Jalea Real! ",
	" No me importa si muero. Ya robé todo lo que quería... ",
	" Nunca olvidaré esto...  ",
	" Te ganaré la próxima vez. No será tan fácil. ",
	" !No soy Moriff! !No tengo Sheltoms o nada como eso~! ",
	" !Estarás bajo la maldición del mal pavo! ",
	" Ohhh..Molly siempre me busca en T.T ",
	" Estoy buscando un lindo pavo para el dia de Accion de Gracias T.T ",
	" Es un bocadillo que me robé. ",
	" Tú deseabas tener estas ropas también? T.T ",
	" Te odio, Molly~ T.T ",
	" Cómete el pavo solo y serás un cerdo..-_- compártelo con tu grupo~ ",
	" No tiene buen sabor, porque Molly lo cocinó. ",
	" Oops~Me estás matando~~~Felicidades, de todas maneras~ ",
	" Ooh....Pagarás por esto la próxima vez. ",
	" OK Eres taaaaaan genial. Sírvete pavo y que te dé dolor de estómago. ",
	" Ooh~ La próxima vez robaré tus ropas. ",
	" Huhu~ Que se te arruine el pavo. ",
	" !Jesús! !Tomaste mi pavo!! !Mis amigos te enseñarán una lección! ",
	" Este tipo me va a matar aunque le dé un pavo~ ",
	" Oh... pagué por la Fuerza~ "
};

#define SANTAGOBLIN_CHAT_MAX		18
char *szSantaGoblinChatMsg[SANTAGOBLIN_CHAT_MAX] = {
	" !No me moelestes! !Puedo ser más grande!! ",
	" !Feliz Navidad a toda la gente que luce peor que yo! Y tú no eres la excepción. ",
	" No recibirás un regalo de Navidad si me golpeas. ",
	" Hey, donde estuviste la navidad del ultimo año?",
	" Asegúrate de pasar tiempo con tu ¨Priston-novia en Mundo Priston. ",
	" Santa fue a hacerse la 8va Maduración. Sin duda fallará ",
	" Es demasiado. Sólo aparezco una vez al año. ",
	" Que tengas un buen año... ",
	" !Quiero un regalo de Navidad!!! ",
	" !Cazé a Rodolfo y me lo comí~!. ",
	" Ayudemos a los deafortunados. ",
	" !Feliz Navidad!! Por favor, recibe un golpe como celebración, !y te daré un regalo! ",
	" Soy un Goblin pero también Santa, Soy Santa? ",
	" !Maldición sobre la pareja cursi de Navidad!! ",
	" Mi cuerpo me dice que lloverá en Navidad. ",
	" Si me golpeas, tendrás una hija que lucirá como yo. ",
	" Que por qué hablo demasiado? Bueno, !es mi trabajo!!! ",
	" Ayuda a los desafortunados a obtener un objeto. "
};

#define SKILLMASTER_CHAT_MAX		16
char *szSkillMasterChatMsg[SKILLMASTER_CHAT_MAX] = {
	" No te daré un descanso. Haz tu mejor esfuerzo. ",
      	" Dije, atácame mucho más fuerte. ",
        " Este ataque no es suficiente la combatir con un monstruo. !Mucho más fuerte!!! ",
     	" !Junta toda tu habilidd para atacarme! ",
     	" El ataque es la mejor defensa! !Hazlo certero y poderoso! ",
       	" !No olvides el espíritu de los Tempscrons! !Usa tu robusto cuerpo para hacer un ataque poderoso! ",
    	" !No podrías ni acercarte a la Furia! ",
   	" Piensa que soy Igolano, !y lucha conmigo a muerte! ",
      	" Ya estás tratando de usar el núcleo para escaparte? ",
      	" Los Cristales de Monstruo nunca se invocan aquí. !Ni siquiera lo pienses! ",
       	" Si pasas por Pillai en el Norte, saluda a Raymon de mi parte. ",
  	" No confíes en tus equipos, en cambio, disciplina tu cuerpo. ",
     	" !Ese fue muy bueno! !Sigue intentando, vamos! ",
     	" !Has crecido tanto desde que viniste la primera vez con la cola del Wolverine! ",
        " Es una vergüenza que hagas un ataque tan malo con un equipo tan magnífico. ",
      	" Me has hecho cosquillas. "
};

#define MAGICMASTER_CHAT_MAX		16
char *szMagicMasterChatMsg[MAGICMASTER_CHAT_MAX] = {
	" Concentra toda tu energía, !y haz tu mejor ataque! ",
  	" Piensas que mereces el Punto Elite con esto? ",
        " !No estás usando tus habilidades a la perfección! !Concéntrate! ",
     	" Es esto todo lo que aprendiste de mí? ",
      	" !Eso fue muy bueno! !Lo hiciste bien! ",
        " !El espíritu de los Morions se basa en una mente religiosa y moderada! !Focaliza tu ataque con la mente clara! ",
       	" !No podrías ni raspar a Hellion con esto! ",
      	" Ya estás tratando de usar el núcleo para escaparte? ",
     	" Los Cristales de Monstruo nunca se invocan aquí. !Ni siquiera lo pienses! ",
        " Si pasas por Ricarten en el Sur, saluda a Verkan de mi parte. ",
    	" Hasta el monstruo más poderoso tiene un punto débil. !No debes temer a nada si entrenas bien tu espíritu! ",
    	" Me estoy cansando de entrenar a mis discípulos de a uno. ",
     	" No tendrás que madurar la habilidad que obtendrás luego de vencerme. ",
      	" Has crecido tanto desde que viniste la primera vez con sólo un punto de habilidad. ",
   	" Tengo sueño. ",
	" !Si me respetas como a un maestro!!! Quédate quieto... huhuhu "
};

char *szMonsterFlagMsg= " !Peligro! área de propagación de monstruos ";

#define		SERVER_DOWN_MSG_COUNT	5
#ifdef		_LANGUAGE_PHILIPIN
char *szServerDownMsg[SERVER_DOWN_MSG_COUNT] = {
	" Aviso> Su atención, por favor ",
	" Aviso> Los servidores se cerrarán por mantenimiento ",
	" Aviso> Por favor, intenta ingresar mas tarde ",
	" Aviso> Los servidores se cerrarán pronto ",
	" Aviso> Para más información sobre el mantenimiento visita www.axeso5.com. !Gracias! "
};
#else
char *szServerDownMsg[SERVER_DOWN_MSG_COUNT] = {
	" Aviso> Su atención, por favor ",
	" Aviso> Los servidores se cerrarán por mantenimiento ",
	" Aviso> Por favor, intenta ingresar mas tarde ",
	" Aviso> Los servidores se cerrarán pronto ",
	" Aviso> Por favor, desbes salir del juego, intenta ingresar mas tarde. Gracias "
};
#endif
char *szSeverDownCountMsg = " Cierre> Quedan %d mins %d segs para salir. Por favor, debes salir del juego ";

char *srBlessCastle_LeagueMsg_01 = " Castillo Bless está por comenzar. Por favor, prepárate para participar. ";
char *srBlessCastle_LeagueMsg_02 = " Castillo Bless está en progreso. Deseamos buena suerte a todos los jugadores. ";
char *srBlessCastle_LeagueMsg_03 = " Castillo Bless ha terminado. Gracias por venir a Castillo Bless. ";
char *srBlessCastle_LeagueMsg_04 = " Castillo Bless comenzará en 30 mins. Por favor, prepárense. ";
char *srBlessCastle_LeagueMsg_05 = " Castillo Bless comenzará en 1 hora. Por favor, prepárense. ";

char *srMsg_StartUser_PresentItem = "    Te daremos  %s de objeto como regalo   ";
char *srMsg_ThanksPolling = "   Gracias por participar de la encuesta ";


char *szNotLinkCore = " No puede usar núcleo de unión ";
char *szNotLinkCore2 = "  Clan equivocado  ";
char *szNotLinkCore3 = " El nivel no es lo suficientemente alto como para entrar ";


char	*srMsg_Bl_01	= " Quedan %d minutos. ";
char	*srMsg_Bl_02	= " [Internet Cafe] ";
char	*srMsg_BI_03	= " Has reservado  [%dY %dM %dD] ";
char	*srMsg_BI_04	= " Has reservado otras [%d horas] ";

char	*srMsg_Bl_100	= " %sPuedes jugar hasta %d:%d - %d/%d/%d (GMT).%s ";
char	*srMsg_Bl_1001	= " %sPuedes jugar hasta %d:0%d - %d/%d/%d (GMT).%s ";
char	*srMsg_Bl_101	= " %sPuedes jugar por %d hora %d minutos.%s ";
char	*srMsg_Bl_102	= " %sQuedan %d minutos.%s ";

