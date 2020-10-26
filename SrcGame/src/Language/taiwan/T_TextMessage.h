#include "TextMessage.h"

char *szAppName="精靈";


char *mgRequestTrade = "向%s請求交易";
char *mgRequestTrade2 = "%s由於距離太遠，無法進行交易";

char *mgDiconnect = "與伺服器的連接中斷";
char *mgDiconnect1 = "與伺服器的連接中斷 (1)";
char *mgDiconnect2 = "與伺服器的連接中斷 (2)";
char *mgDiconnect3 = "與伺服器的連接中斷 (3)";
char *mgDiconnect4 = "與伺服器的連接中斷 (4)";

char *mgCloseGame = "離開遊戲";
char *mgCloseWindow = "請您先關閉開啟的視窗，再離開遊戲";
char *mgCloseBattle = "戰鬥中不能離開遊戲";

char *mgQuestName[][4] = {
	{	"轉職考驗"	,	"轉職考驗（已完成）" , "ChangeJob1a.Msg" , "ChangeJob1b.Msg" },
	{	"轉職考驗[皇家果凍膠]"	,	"轉驗考試 (完成)" , "ChangeJob2a.Msg" , "ChangeJob1b.Msg" },
	{	"轉職考驗[生髮劑]"	,	"轉職考驗 (完成)" , "ChangeJob3a.Msg" , "ChangeJob1b.Msg" }
};

char *mgRefuseWhisper = "悄悄話被拒絕了！";
char *mgWeightOver = "你超重了 !!!!!";
