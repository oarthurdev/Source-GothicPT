



struct sSINWARPGATE
{
	POINT GatePosi[10];
	int ShowFlag;
	int GateSelect;
	int MoveFieldNum;
	int SameAreaFlag;

	int GateUseIndex;
	POINT MapPosi;
	DWORD EffectTime;
	int   EffectFlag;

	POINT CancelPosi;
	int   CancelFlag;

};


class cSINWARPGATE
{

public:

	int MatWarpMap;
	int MatIcon;
	int MatSelect;

	LPDIRECT3DTEXTURE9 lpCancelBox;
	LPDIRECT3DTEXTURE9 lpCancelButton;
	LPDIRECT3DTEXTURE9 lpCancelButton_G;



public:

	cSINWARPGATE();
	~cSINWARPGATE();

	void Init();
	void Load();
	void Release();
	void Draw();
	void DrawText();
	void Close();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();




	int SerchUseWarpGate();


	int SetWarGateSelectEffect(int x, int y);

};


extern cSINWARPGATE cSinWarpGate;
extern sSINWARPGATE sSinWarpGate;
extern int WarpGateUseCost[10];
extern int sinWarpGateCODE[10];
extern int FieldLimitLevel_Table[];

extern sSINWARPGATE sHaWarpGate;
extern int haWarpGateCODE[10];

