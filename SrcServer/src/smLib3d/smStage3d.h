#ifndef _SMSTAGE3D_H_
#define _SMSTAGE3D_H_

#define ADD_TEMPFACE	2048
#define ADD_TEMPVERTEX	2048
#define MAP_SIZE		256


extern int Stage_StepHeight;
extern int smStage_WaterChk;

class smSTAGE3D
{
public:
	DWORD	Head;



	DWORD *StageArea[MAP_SIZE][MAP_SIZE];

	POINT *AreaList;
	int AreaListCnt;

	int	MemMode;

	DWORD SumCount;
	int CalcSumCount;

	smSTAGE_VERTEX		*Vertex;
	smSTAGE_FACE		*Face;
	smTEXLINK			*TexLink;
	smLIGHT3D			*smLight;

	smMATERIAL_GROUP	*smMaterialGroup;

	smSTAGE_OBJECT		*StageObject;
	smMATERIAL			*smMaterial;

	int nVertex;
	int nFace;
	int nTexLink;
	int	nLight;

	int	nVertColor;

	int	Contrast;
	int Bright;

	POINT3D VectLight;



	DWORD	*lpwAreaBuff;

	int		wAreaSize;
	RECT	StageMapRect;

	smSTAGE3D();
	~smSTAGE3D();
	smSTAGE3D(int nv, int nf);



	void Init(void);


	int Init(int nv, int nf);
	int Close();

	int AddVertex(int x, int y, int z);

	int AddFace(int a, int b, int c, int matrial = 0);

	int SetFaceMaterial(int FaceNum, int MatNum);


	int SetVertexColor(DWORD NumVertex, BYTE r, BYTE g, BYTE b, BYTE a = 255);

	int AddTexLink(int FaceNum, DWORD *hTex,
				   smFTPOINT *t1, smFTPOINT *t2, smFTPOINT *t3);




	int SetVertexShade(int isSetLight = TRUE);



	int AddVertexLightRound(POINT3D *LightPos, int r, int g, int b, int Range);


	int	InitDynLight(int nl);

	int AddDynLight(int type, POINT3D *LightPos, int r, int g, int b, int Range);



	int CheckFaceIceFoot(POINT3D *Pos, POINT3D *Angle, int CheckHeight);



	int MakeAreaFaceList(int x, int z, int width, int height, int top, int bottom);


	int GetPolyHeight(smSTAGE_FACE *face, int x, int z);

	int GetAreaHeight(int ax, int az, int x, int z);

	int GetAreaHeight2(int ax, int az, int x, int z);


	int GetHeight(int x, int z);

	int GetHeight2(int x, int z);


	int CheckSolid(int sx, int sy, int sz, int dx, int dy, int dz);

	int GetThroughPlane(smSTAGE_FACE *face, POINT3D *sp, POINT3D *ep);


	int GetPlaneProduct(smSTAGE_FACE *face, POINT3D *p);

	int GetTriangleImact(smSTAGE_FACE *face, smLINE3D *pLines, int LineCnt);

	int CheckNextMove(POINT3D *Posi, POINT3D *Angle, POINT3D *MovePosi, int dist, int ObjWidth, int ObjHeight, int CheckOverLap = 0);


	int CheckVecImpact(POINT3D *Posi, POINT3D *Angle, int dist);

	int CheckVecImpact2(int sx, int sy, int sz, int ex, int ey, int ez);


	int GetFloorHeight(int x, int y, int z, int ObjHeight);

	int GetFloorHeight2(int x, int y, int z, int ObjHeight);

	int GetEmptyHeight(int x, int y, int z, int ObjHeight);


	int CheckFloorFaceHeight(int x, int y, int z, int hSize);



	void clearStageArea();

	int getPolyAreas(POINT3D *ip1, POINT3D *ip2, POINT3D *ip3);

	int SetupPolyAreas();

	int RenderGeom();


	int DrawStage(int x, int y, int z, int angX, int angY, int angZ, smEMATRIX *eRotMatrix = 0);

	int DrawStage2(int x, int y, int z, int angX, int angY, int angZ, smEMATRIX *eRotMatrix = 0);



	int DrawOpeningStage(int x, int y, int z, int angX, int angY, int angZ, int FrameStep);



	int	SaveFile(char *szFile);

	int	LoadFile(char *szFile);
};

#endif




