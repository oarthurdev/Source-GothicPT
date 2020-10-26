





#pragma once


#define MAX_WARP_FRAME			10


struct SRotAngle
{
	int				frame;
	int				Angle_x;
	int				Angle_y;
	int				Angle_z;
};


class CAutoCamera
{
public:
	int				m_Frame;
	int				m_LastFrame;

	float			m_fCameraPos_x;
	float			m_fCameraPos_y;
	float			m_fCameraPos_z;

	int  			m_iCameraRot_x;
	int  			m_iCameraRot_y;
	int  			m_iCameraRot_z;

	smEMATRIX	    m_eCameraRotMat;

	int			    m_TmPosCnt;
	smTM_POS	   *m_lpTmPos;

	int			    m_RotCnt;
	SRotAngle	   *m_lpRotAng;
	smDTM_ROT	   *m_lpRotQuat;
	smEMATRIX	   *m_lpRotMat;

	int				m_WarpFrameCnt;
	int				m_WarpFrameStBuff[MAX_WARP_FRAME];
	int				m_WarpFrameEndBuff[MAX_WARP_FRAME];

public:
	CAutoCamera(void);
	~CAutoCamera(void);

	void Init(void);
	void Close(void);

	int  ReadASE_AutoCamera(char *lpFileName);
	int  SetWarpFrame(int StFrame, int EndFrame);
	int  FrameMain(int FrameStep);

private:
	int  Load_AutoCamera(char *lpLoadName);
	int  Save_AutoCamera(char *lpSaveName);

	void DXtoEMatrixFromFMatrix(smEMATRIX &smEmat, smFMATRIX &smFmat);

	void CameraMatrixCheckUnit(int RotCnt, smEMATRIX &eSrcMatrix, int stNum_x, int stNum_y, int stNum_z, int UnitStep, int &end_x, int &end_y, int &end_z);
	int  CameraMatrixCheck(smEMATRIX &eSrcMatrix, smEMATRIX &eMatchMatrix);
};

