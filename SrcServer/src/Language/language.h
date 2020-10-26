#define	_LANGUAGE_BRAZIL
#define	_LANGUAGE_BRAZIL_FIELDLEVEL
#define	_LANGUAGE_BRAZIL_FIELDLEVEL_CLOSE

#if defined (_LOG_)
#include "stdio.h"
#define MAKELOG(description)					\
{												\
	FILE *fpc_log = NULL;						\
	fpc_log = fopen(szLOG_FILENAME,"a+t");		\
	if( fpc_log != NULL )						\
	{											\
		fprintf(fpc_log,"\n %s",(description)); \
		fclose(fpc_log);						\
		fpc_log = NULL;							\
	}											\
}
#else
#define MAKELOG(desciption)
#endif


#ifdef _LANGUAGE_BRAZIL
#define	_LANGUAGE_WINDOW	
#define	LOG_THE_PK
#endif

#ifdef	_LANGUAGE_PHILIPIN
#define _DEATH_PANALTY			
#endif

#define	ATTACK_RATE		70	
#define	DEFENSE_RATE	80	



#ifdef	_LANGUAGE_CHINESE
#define	_IME_ACTIVE
#endif

#define	_NEW_PARTRADE



#define	_WINMODE_DEBUG	




#ifdef	_LANGUAGE_BRAZIL		
//#define	_PACKET_PASS_XOR	0x6E
#endif

#define	_MODE_EXP64



#define	_SECURITY_UPDATE



#ifdef	_LANGUAGE_BRAZIL
#define _LANGUAGE_ENGLISH_NEXTUP    

#define	_ON_MAP
#define _ON_PRIVATE_SHOP
#define	_ON_PET
#endif