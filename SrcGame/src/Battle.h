class Battle
{
public:
	static Battle * GetInstance() { static Battle instance; return &instance; };
	void Open() { fOpen = true; };
	void Close() { fOpen = false; };
	bool IsOpen() { return fOpen; };
	void Hide() { IsBoss = false; };
	void Init();
	bool MouseAction(int x, int y, int w, int h);
	void Draw();
	void DrawImage(int Mat, int x, int y, int w, int h);
	void Button();
	void BossInfo(const smCHAR_INFO & smCharInfo);
private:
	int fOpen;
	int cImages[30];
	bool IsBoss;
	int  Life;
	int  MaxLife;
	float LifePercent;
	float NowHP;
	float MaxHP;
};