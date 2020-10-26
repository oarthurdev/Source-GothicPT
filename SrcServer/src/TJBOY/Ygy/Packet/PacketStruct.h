
#ifndef __PACKETSTRUCT_H__
#define __PACKETSTRUCT_H__


#define STRING_MAX			(64+4)



#define CHANAME_MAX		64
#define CLANNAME_MAX    64





#define P_IDANDNAME				10001
#define P_OUT					10002
#define P_CLANINFO				10003



#define INSIDE_IPPORT						20010 
#define INSIDE_USERINFO						20001
#define INSIDE_USERINFOCHG					20030 
#define INSIDE_GAME_OUT						20003
#define INSIDE_CLANCHAT                     20011 
#define INSIDE_VD		                    20012
#define GOPRIS_VUSERIDs         200030		
#define GOPRIS_VCLIENTINFO      200031		

#define INSIDE_MICONOFF         200050		


#define INSIDE_GAMELOGIN					20000
#define INSIDE_GETWND                       20004
#define INSIDE_CLAWONLIST                   20005

#define INSIDE_DELCLANWON                20013 
#define INSIDE_DELCLAN                   20014 
#define INSIDE_MAKECLAN					 20015 



#define INSIDE_CLIENTINFO			250000   




#define SERVER_CLANWONLS			30000
#define SERVER_CLANCHAT				30001
#define SERVER_CLWIN				30002
#define SERVER_CLWOUT				30003
#define SERVER_SENDVOC				30004






typedef struct _tagIndex
{
	DWORD		dwIndex;
}INDEX, *LPINDEX;





typedef struct __tagIpPort
{
	INDEX           sIndex;
	char            ip[16];
	int				port;


}IPPORT, *LPIPPORT;



typedef struct _tagUserInfo
{
	INDEX   sIndex;

	DWORD	dwClanNum;
	char	szClanName[STRING_MAX];

	int     utype;
	char	szCharName[STRING_MAX];
	char	szID[STRING_MAX];
	char	szConnServerName[16];
}USERINFO;



typedef struct __tagPacketOut
{
	INDEX			sIndex;
}P_Out;



typedef struct __tagClanChat
{
	INDEX		sIndex;
	char		szMsg[256];
}CLANCHAT;



typedef struct
{
	INDEX	sIndex;
	int		vSize;
	char	vData[4];
}VOICEDATA;




#define STREAMDATACNT 8 
typedef struct
{
	INDEX	sIndex;
	DWORD	time;
	char	uID[STREAMDATACNT][32];
}VOICTALKUSERDATA;



typedef struct
{
	INDEX	sIndex;
	BOOL	bMicONOFF;
}VOICEONOFF;






enum
{
	VC_STATE_NOSERVER,
	VC_STATE_NOTCONNECT,
	VC_STATE_CONNECT,
	VC_STATE_DISCONNECT,
};
#define VC_STATE_NOSERVER_STR	"보이스서버가 없다."
#define VC_STATE_NOTCONNECT_STR	"보이스서버에 접속할수 없다."
#define VC_STATE_CONNECT_STR	"보이스서버와 connect"
#define VC_STATE_DISCONNECT_STR	"보이스서버와 disconnect"

typedef struct
{
	INDEX	sIndex;
	int		vcl_state;
}VCLIENTINFO;











typedef struct
{
	int     utype;
	char	szCharName[STRING_MAX];
	char	szID[STRING_MAX];
}SERVER_clanWon;

typedef struct __tagServer_ClanWonList
{
	INDEX               sIndex;
	int					clanwonSu;
	SERVER_clanWon		sclanwon[1];
}SERVER_CLANWONLIST;



typedef struct __tagServer_ClanChat
{
	INDEX               sIndex;
	SERVER_clanWon      clanwon;
	char				chat[256];
}SERVER_CLANCHATSTR;



typedef struct __tagServer_outClanWon
{
	INDEX               sIndex;
	SERVER_clanWon      clanwon;
}SERVER_inoutCLANWON;


typedef struct
{
	INDEX				sIndex;
	SERVER_clanWon		clanwon;
	int					vSize;
	char				vData[4];
}SERVER_VOICEDATA;



#endif 
