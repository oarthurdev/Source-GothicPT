
#define FILED_GATE_MAX			12
#define FIELD_MAX				256
#define FIELD_AMBENT_MAX		80
class sFIELD;



struct sFGATE
{
	int	x, z, y;
	sFIELD* lpsField;
};


struct sWARPGATE
{
	int	x, z, y;
	int	height, size;
	sFGATE	OutGate[FILED_GATE_MAX];
	int		OutGateCount;
	int		LimitLevel;
	int		SpecialEffect;
};

struct	sAMBIENT_POS
{
	int	x, y, z;
	int	round;
	int	AmbentNum;
};

#define FIELD_STATE_VILLAGE		0x100
#define FIELD_STATE_FOREST		0x200
#define FIELD_STATE_DESERT		0x300
#define FIELD_STATE_RUIN		0x400
#define FIELD_STATE_DUNGEON		0x500
#define FIELD_STATE_IRON		0x600
#define FIELD_STATE_ROOM		0x800
#define FIELD_STATE_QUEST_ARENA	FIELD_STATE_DUNGEON



#define FIELD_STATE_ICE			0x900


#define FIELD_STATE_CASTLE		0xA00
#define FIELD_STATE_ACTION		0xB00


#define FIELD_STATE_ALL			0x1000

#define FIELD_BACKIMAGE_RAIN		0x00
#define FIELD_BACKIMAGE_NIGHT		0x01
#define FIELD_BACKIMAGE_DAY			0x02
#define FIELD_BACKIMAGE_GLOWDAY		0x03
#define FIELD_BACKIMAGE_DESERT		0x04
#define FIELD_BACKIMAGE_GLOWDESERT	0x05
#define FIELD_BACKIMAGE_NIGHTDESERT	0x06
#define FIELD_BACKIMAGE_RUIN1		0x07
#define FIELD_BACKIMAGE_RUIN2		0x08
#define FIELD_BACKIMAGE_NIGHTRUIN1	0x09
#define FIELD_BACKIMAGE_NIGHTRUIN2	0x0A

#define FIELD_BACKIMAGE_GLOWRUIN1	0x0B
#define FIELD_BACKIMAGE_GLOWRUIN2	0x0C


#define FIELD_BACKIMAGE_NIGHTFALL	0x11
#define FIELD_BACKIMAGE_DAYFALL		0x12
#define FIELD_BACKIMAGE_GLOWFALL	0x13

#define FIELD_BACKIMAGE_NIGHTIRON1	0x14
#define FIELD_BACKIMAGE_NIGHTIRON2	0x15
#define FIELD_BACKIMAGE_DAYIRON		0x16
#define FIELD_BACKIMAGE_GLOWIRON	0x17

#define FIELD_BACKIMAGE_SODSKY      0x18    
#define FIELD_BACKIMAGE_SODMOON     0x19    
#define FIELD_BACKIMAGE_SODSUN      0x20    
#define FIELD_BACKIMAGE_SODNONE     0x21    
#define FIELD_BACKIMAGE_IRONBOSS    0x22    

#define FIELD_BACKIMAGE_DAYSNOW		0x23    
#define FIELD_BACKIMAGE_GLOWSNOW    0x24    
#define FIELD_BACKIMAGE_NIGHTSNOW   0x25    

#define FIELD_BACKIMAGE_DAYGREDDY	 0x26    
#define FIELD_BACKIMAGE_GLOWGREDDY   0x27    
#define FIELD_BACKIMAGE_NIGHTGREDDY  0x28    


#define FIELD_BACKIMAGE_DAYLOST		 0x29    
#define FIELD_BACKIMAGE_GLOWLOST	 0x2A    
#define FIELD_BACKIMAGE_NIGHTLOST    0x2B    

#define FIELD_BACKIMAGE_DAYTEMPLE	 0x2C	
#define FIELD_BACKIMAGE_GLOWTEMPLE	 0x2D	
#define FIELD_BACKIMAGE_NIGHTTEMPLE	 0x2E	


#define	FIELD_EVENT_NIGHTMARE		0x01

#define	FIELD_START_POINT_MAX		8

#define	FIELD_STAGE_OBJ_MAX			52



#define START_FIELD_NUM			3
#define START_FIELD_NEBISCO		9
#define START_FIELD_MORYON		21//21
#define START_FIELD_CASTLE		33

struct	ACTION_FIELD_CAMERA
{
	POINT3D	FixPos;
	int		LeftX, RightX;
};


class sFIELD
{
	DWORD	head;
public:
	char	szName[64];
	char	szNameMap[64];
	char	szNameTitle[64];
	int		State;
	int		BackImageCode[3];
	int		BackMusicCode;
	int		FieldEvent;

	int		GateCount;
	sFGATE	FieldGate[FILED_GATE_MAX];

	int		WarpGateCount;
	int		WarpGateActiveNum;
	sWARPGATE	WarpGate[FILED_GATE_MAX];
	POINT3D	PosWarpOut;

	sAMBIENT_POS	AmbientPos[FIELD_AMBENT_MAX];
	int		AmbentCount;


	int		LimitLevel;
	int		FieldSight;

	char* lpStageObjectName[FIELD_STAGE_OBJ_MAX];
	DWORD	StgObjBip[FIELD_STAGE_OBJ_MAX];
	int		StgObjCount;

	int		cX, cZ;
	int		FieldCode;
	int		ServerCode;

	POINT	StartPoint[FIELD_START_POINT_MAX];
	int		StartPointCnt;

	ACTION_FIELD_CAMERA	ActionCamera;
	int	AddStageObject(char* szStgObjName, int BipAnimation = 0);
	int	GetStageObjectName(int num, char* szNameBuff, size_t size);

	int	SetCenterPos(int x, int z);
	int AddGate(sFIELD* lpsField, int x, int z, int y);
	int SetName(char* lpName, char* lpNameMap = 0);
	int AddGate2(sFIELD* lpsField, int x, int z, int y);

	int	AddWarpGate(int x, int y, int z, int size, int height);
	int	AddWarpOutGate(sFIELD* lpsField, int x, int z, int y);
	int	CheckWarpGate(int x, int y, int z);

	int AddStartPoint(int x, int z);
	int GetStartPoint(int x, int z, int* mx, int* mz);
	int CheckStartPoint(int x, int z);

	int AddAmbientPos(int x, int y, int z, int round, int AmbCode);
	int	PlayAmbient();

};




int FieldMain(int x, int y, int z);

int InitField();

int StartField();

int WarpNextField(int* mx, int* mz);

int WarpField(int FieldNum, int* mx, int* mz);

int WarpFieldNearPos(int FieldNum, int x, int z, int* mx, int* mz);

int WarpStartField(int* mx, int* mz);

int WarpCustomField(int* mx, int* mz);


int WarpStartField(int FieldNum, int* mx, int* mz);


int WarpPrisonField(int* mx, int* mz);


int	WingWarpGate_Field(int dwFieldCode);


int WarpField2(int Num);


int WarpCastleField(int MasterClan, int* dx, int* dz);



extern sFIELD	sField[FIELD_MAX];
extern int	PrisonX;
extern int	PrisonZ;
extern RECT	PrisonRect;
extern DWORD	dwNextWarpDelay;



smSTAGE3D* LoadStageFromField(sFIELD* lpField, sFIELD* lpSecondField);

smSTAGE3D* LoadStageFromField2(sFIELD* lpField, sFIELD* lpSecondField);

extern	sFIELD* StageField[2];

extern  int FieldLimitLevel_Table[];



extern int FieldCount;

