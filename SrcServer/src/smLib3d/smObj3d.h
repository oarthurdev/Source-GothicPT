#pragma once

#include "smDsx.h"


class smPAT3D;
class smMATERIAL_GROUP;

#define OBJ_FRAME_SEARCH_MAX		32



#define OBJ_HEAD_TYPE_NEW_NORMAL				0x80000000



class smPOINT3D
{
public:

	smVERTEX	*pVertex;

	int			rx, ry, rz;
	int			wx, wy, wz;
	int			sx, sy, sz;
	int			ox, oy, oz;

	int			X, Y, Z;
	int			x2d, y2d;
	BYTE		Clip2d[4];

	smPOINT3D();
	smPOINT3D(smVERTEX *pv);
	~smPOINT3D();

	void SetTo(smVERTEX *pv);
	void xform2d();
	void GlobalRotate(int *trig);

	void Move(int dx, int dy, int dz);

	void GlobalXform();

};



struct smFRAME_POS
{
	int StartFrame;
	int EndFrame;
	int PosNum;
	int PosCnt;
};

struct smDFILE_HEADER
{
	char szHeader[24];
	int ObjCounter;
	int MatCounter;
	int MatFilePoint;
	int First_ObjInfoPoint;
	int TmFrameCounter;
	smFRAME_POS TmFrame[OBJ_FRAME_SEARCH_MAX];
};

struct smDFILE_OBJINFO
{
	char szNodeName[32];
	int Length;
	int ObjFilePoint;
};



struct SMotionStEndInfo
{
	DWORD	StartFrame;
	DWORD	EndFrame;
};


class smOBJ3D
{
	DWORD		Head;
public:

	smVERTEX	*Vertex;
	smFACE		*Face;
	smTEXLINK	*TexLink;

	smOBJ3D		**Physique;

	smVERTEX	ZeroVertex;

	int maxZ, minZ;
	int maxY, minY;
	int maxX, minX;

	int dBound;
	int Bound;

	int MaxVertex;
	int MaxFace;

	int nVertex;
	int nFace;

	int nTexLink;

	int ColorEffect;
	DWORD ClipStates;

	POINT3D Posi;
	POINT3D CameraPosi;
	POINT3D Angle;
	int	Trig[8];


	char	NodeName[32];
	char	NodeParent[32];
	smOBJ3D	*pParent;

	smMATRIX	Tm;
	smMATRIX	TmInvert;

	smFMATRIX	TmResult;
	smMATRIX	TmRotate;

	smMATRIX	mWorld;
	smMATRIX	mLocal;

	int		lFrame;

	float	qx, qy, qz, qw;
	int		sx, sy, sz;
	int		px, py, pz;

	smTM_ROT	*TmRot;
	smTM_POS	*TmPos;
	smTM_SCALE	*TmScale;



	smFMATRIX	*TmPrevRot;


	int TmRotCnt;
	int TmPosCnt;
	int TmScaleCnt;


	smFRAME_POS TmRotFrame[OBJ_FRAME_SEARCH_MAX];
	smFRAME_POS TmPosFrame[OBJ_FRAME_SEARCH_MAX];
	smFRAME_POS TmScaleFrame[OBJ_FRAME_SEARCH_MAX];
	int TmFrameCnt;

	smOBJ3D();
	~smOBJ3D();
	smOBJ3D(int nv, int nf);

	void Init(int nv, int nf, int pFlag = 0);

	int AddVertex(int x, int y, int z);

	int AddFace(int a, int b, int c);


	int ReformTexture(int Type, int MatNum, int MatCnt, POINT3D *pos, POINT3D *size);


	int SetFaceMaterial(int FaceNum, int MatNum);

	int AddTexLink(int FaceNum, DWORD *hTex, smFTPOINT *t1, smFTPOINT *t2, smFTPOINT *t3);

	int AddTexLinkTP(int FaceNum, DWORD *hTex, smTPOINT *t1, smTPOINT *t2, smTPOINT *t3);


	int AddFace(int a, int b, int c, smTPOINT *t1, smTPOINT *t2, smTPOINT *t3);


	void ZeroNormals();

	void SetGNormals();

	void SortMatrial();

	void SortVertex();

	void ReformTM();

	void ReformPhysique();


	int	 BeginRender();

	int  TestRotate(int x, int y, int z, POINT3D *LocalAngle, POINT3D *GlobalAngle);

	int  WorldForm();




	int GetRotFrame(smFMATRIX &gmat, smFMATRIX *PrevRot, smTM_ROT *tmRot, int frame, SMotionStEndInfo *lpFrameInfo = NULL);


	int GetPosFrame(float &x, float &y, float &z, smTM_POS *tmPos, int frame);



	int GetScaleFrame(int &x, int &y, int &z, smTM_SCALE *tmSclae, int frame);


	int GetTmFramePos(int frame);

	int GetTmFrameRot(int frame);

	int GetTmFrameScale(int frame);



	int TmTalkAnimation(int frame);
	int TmAnimation(int frame, int ax, int ay, int az, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo = NULL);


	int  TmAnimation(int frame, int ax, int ay, int az, SMotionStEndInfo *lpFrameInfo = NULL);






	void SetPosi(POINT3D *point, POINT3D *angle);

	int  RenderD3D(POINT3D *camera, POINT3D *angle);



	int	 RenderD3dOpening(POINT3D *camera, POINT3D *angle);



	int TestRender(POINT3D *camera, POINT3D *angle);

	int ActionRenderD3D();



	int  GetSaveSize();

	int  SaveFile(HANDLE hFile);

	int  LoadFile(HANDLE hFile, smPAT3D *PatPhysique = 0);
};

class smPAT3D
{
	DWORD		Head;
public:
	smOBJ3D		*obj3d[128];
	BYTE		TmSort[128];

	smPAT3D	*TmParent;

	smMATERIAL_GROUP *smMaterialGroup;

	int MaxFrame;
	int Frame;

	int SizeWidth, SizeHeight;

	int nObj3d;
	DRZTEXTURE2 *hD3DTexture;

	POINT3D Posi;
	POINT3D Angle;
	POINT3D CameraPosi;

	int dBound;
	int Bound;

	smFRAME_POS TmFrame[OBJ_FRAME_SEARCH_MAX];
	int TmFrameCnt;

	int		TmLastFrame;
	POINT3D TmLastAngle;

	smPAT3D();
	~smPAT3D();


	void	Init();

	void	Close();


	int		AddObject(smOBJ3D *obj);

	int		LinkObject();

	int		LinkParentObject(smPAT3D *patParent, smOBJ3D *objParent = 0);

	int		ReformPhysique();

	int		ReformTM();


	smOBJ3D *GetObjectFromName(char *name);



	int		SetFrame(int frame, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo = NULL);
	int		TmTalkAnimation(int frame);
	int		TmAnimation(int frame, int ax, int ay, int az, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo = NULL);


	int		SetFrame(int frame, SMotionStEndInfo *lpFrameInfo = NULL);

	int		TmAnimation(int frame, int ax, int ay, int az, SMotionStEndInfo *lpFrameInfo = NULL);



	void	ZeroNormals();

	void	SetPosi(POINT3D *point, POINT3D *angle);

	void	SetFixPosi();



	int		RenderD3D(POINT3D *camera, POINT3D *angle, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo = NULL);
	int		ChoiseRenderD3D(POINT3D *camera, POINT3D *angle, char **szNodeList, int ListCnt, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo = NULL);


	int		RenderD3D(POINT3D *camera, POINT3D *angle, SMotionStEndInfo *lpFrameInfo = NULL);

	int		ChoiseRenderD3D(POINT3D *camera, POINT3D *angle, char **szNodeList, int ListCnt, SMotionStEndInfo *lpFrameInfo = NULL);




	int		RenderD3dOpening(POINT3D *camera, POINT3D *angle);



	int		SaveFile(char *szFile);

	int		LoadFile(char *szFile, char *szNodeName = 0);

};

extern	DWORD		smObjFixPos;

int smGetMapHeight(int x, int z);
int smAddVertexLight(smRGB *LightRGB, smLIGHT3D *light, POINT3D *posi, POINT3D *normal);
int smAddVertexLightSpot(smRGB *LightRGB, smLIGHT3D *light, POINT3D *posi, POINT3D *normal);


int smFindPatFile(char *szfile, char *FileExt);


