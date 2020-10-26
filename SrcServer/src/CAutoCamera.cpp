





#include "smlib3d\\smd3d.h"
#include "CAutoCamera.h"


#define AUTO_CAMERA_EXT		("cam")








CAutoCamera::CAutoCamera(void)
{
	Init();
}








CAutoCamera::~CAutoCamera(void)
{
	Close();
}








void CAutoCamera::Init(void)
{
	m_Frame = 0;
	m_LastFrame = 0;

	m_fCameraPos_x = m_fCameraPos_y = m_fCameraPos_z = 0.f;
	m_iCameraRot_x = m_iCameraRot_y = m_iCameraRot_z = 0;

	m_TmPosCnt = 0;
	m_lpTmPos = NULL;

	m_RotCnt = 0;
	m_lpRotAng = NULL;
	m_lpRotQuat = NULL;
	m_lpRotMat = NULL;

	m_WarpFrameCnt = 0;
	::ZeroMemory(m_WarpFrameStBuff, sizeof(m_WarpFrameStBuff));
	::ZeroMemory(m_WarpFrameEndBuff, sizeof(m_WarpFrameEndBuff));
}








void CAutoCamera::Close(void)
{
	if(m_lpTmPos)
	{
		delete[] m_lpTmPos;
		m_lpTmPos = NULL;
	}

	if(m_lpRotAng)
	{
		delete[] m_lpRotAng;
		m_lpRotAng = NULL;
	}

	if(m_lpRotQuat)
	{
		delete[] m_lpRotQuat;
		m_lpRotQuat = NULL;
	}

	if(m_lpRotMat)
	{
		delete[] m_lpRotMat;
		m_lpRotMat = NULL;
	}
}








int CAutoCamera::ReadASE_AutoCamera(char *lpFileName)
{

	char *lpLoadName = smFindFile(lpFileName, AUTO_CAMERA_EXT, NULL);
	if(lpLoadName)
	{
		if(m_LastFrame)
		{
			Close();
			Init();
		}

		if(Load_AutoCamera(lpLoadName))
			return TRUE;
	}


	FILE *fp = fopen(lpFileName, "rt");
	if(fp == NULL)
		return FALSE;

	char *p, line[256], decode[256], strBuff[256];
	int   LastFrame = 0, IsReadCamera = 0;


	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			return FALSE;
		}

		p = GetWord(decode, line);


		if(lstrcmp(decode, "*SCENE_LASTFRAME") == 0)
		{
			p = GetWord(strBuff, p);
			LastFrame = atoi(strBuff) * 160;
		}


		if(lstrcmp(decode, "*CAMERAOBJECT") == 0)
		{
			IsReadCamera = 1;
			break;
		}
	}


	if(IsReadCamera == 0 || LastFrame <= 0)
		return FALSE;

	if(m_LastFrame)
	{
		Close();
		Init();
	}


	int			TmRotCnt = 0;
	smDTM_ROT	TmDRot[4096];

	int			TmPosCnt = 0;
	smTM_POS	TmPos[4096];

	smFMATRIX		   fTm;
	smFIdentityMatrix(fTm);

	smFMATRIX		   fTmInvert;
	smFIdentityMatrix(fTmInvert);

	int strLevel = 0;

	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			return FALSE;
		}

		p = GetWord(decode, line);


		if(lstrcmp(decode, "*TM_ROW0") == 0)
		{
			p = GetWord(strBuff, p);
			fTm._11 = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			fTm._12 = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			fTm._13 = (float)atof(strBuff);
		}

		if(lstrcmp(decode, "*TM_ROW1") == 0)
		{
			p = GetWord(strBuff, p);
			fTm._21 = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			fTm._22 = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			fTm._23 = (float)atof(strBuff);
		}

		if(lstrcmp(decode, "*TM_ROW2") == 0)
		{
			p = GetWord(strBuff, p);
			fTm._31 = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			fTm._32 = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			fTm._33 = (float)atof(strBuff);
		}


		if(lstrcmp(decode, "*CONTROL_ROT_SAMPLE") == 0)
		{
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].frame = atoi(strBuff);
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].x = atof(strBuff);
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].y = atof(strBuff);
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].z = atof(strBuff);
			p = GetWord(strBuff, p);
			TmDRot[TmRotCnt].w = atof(strBuff);

			TmRotCnt++;
		}


		if(lstrcmp(decode, "*CONTROL_POS_SAMPLE") == 0)
		{
			p = GetWord(strBuff, p);
			TmPos[TmPosCnt].frame = atoi(strBuff);
			p = GetWord(strBuff, p);
			TmPos[TmPosCnt].x = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			TmPos[TmPosCnt].z = (float)atof(strBuff);
			p = GetWord(strBuff, p);
			TmPos[TmPosCnt].y = (float)atof(strBuff);

			TmPosCnt++;
		}


		p = GetWord(strBuff, p);

		if(lstrcmp(decode, "{") == 0 || lstrcmp(strBuff, "{") == 0)
		{
			strLevel++;
		}

		if(lstrcmp(decode, "}") == 0 || lstrcmp(strBuff, "}") == 0)
		{
			strLevel--;
			if(strLevel < 0)
				break;
		}
	}

	m_LastFrame = LastFrame;
	fclose(fp);


	if(TmPosCnt > 0 && TmPos[TmPosCnt - 1].frame < LastFrame)
	{
		memcpy(&TmPos[TmPosCnt], &TmPos[TmPosCnt - 1], sizeof(smTM_POS));
		TmPos[TmPosCnt].frame = LastFrame;

		TmPosCnt++;
	}


	if(TmRotCnt > 0 && TmDRot[TmRotCnt - 1].frame < LastFrame)
	{
		memcpy(&TmDRot[TmRotCnt], &TmDRot[TmRotCnt - 1], sizeof(smDTM_ROT));
		TmDRot[TmRotCnt].frame = LastFrame;

		TmRotCnt++;
	}


	if(TmPosCnt > 0)
	{
		m_TmPosCnt = TmPosCnt;
		m_lpTmPos = new smTM_POS[m_TmPosCnt];

		memcpy(m_lpTmPos, TmPos, sizeof(smTM_POS) * m_TmPosCnt);
	}


	if(TmRotCnt > 0)
	{

		m_RotCnt = TmRotCnt;


		m_lpRotAng = new SRotAngle[m_RotCnt];
		::ZeroMemory(m_lpRotAng, sizeof(SRotAngle) * m_RotCnt);


		m_lpRotQuat = new smDTM_ROT[m_RotCnt];
		::CopyMemory(m_lpRotQuat, TmDRot, sizeof(smDTM_ROT) * m_RotCnt);


		m_lpRotMat = new smEMATRIX[m_RotCnt];
		::ZeroMemory(m_lpRotMat, sizeof(smEMATRIX) * m_RotCnt);


		smFMatrixInvert(fTmInvert, fTm);

		smDMATRIX dPrevMat;
		smDIdentityMatrix(dPrevMat);

		for(int cnt = 0; cnt < m_RotCnt; cnt++)
		{
			m_lpRotAng[cnt].frame = TmDRot[cnt].frame;


			smDMATRIX dtmat;
			smDQuaternionFromAxis(m_lpRotQuat[cnt].x, m_lpRotQuat[cnt].y, m_lpRotQuat[cnt].z, m_lpRotQuat[cnt].w);
			smDMatrixFromQuaternion(dtmat, m_lpRotQuat[cnt].x, m_lpRotQuat[cnt].y, m_lpRotQuat[cnt].z, m_lpRotQuat[cnt].w);

			smDMatrixMult(dPrevMat, dPrevMat, dtmat);


			smFMATRIX fPrevMat;
			smFMatrixFromDMatrix(fPrevMat, dPrevMat);
			smFMatrixMult(fPrevMat, fTmInvert, fPrevMat);

			DXtoEMatrixFromFMatrix(m_lpRotMat[cnt], fPrevMat);
		}


		for(int cnt = 0; cnt < m_RotCnt; cnt++)
		{
			int   stNum_x, stNum_y, stNum_z;
			int   end_x, end_y, end_z;

			stNum_x = stNum_y = stNum_z = 0;
			end_x = end_y = end_z = ANGLE_360;

			int UnitStep = 128, StepNum = 8;
			while(TRUE)
			{
				CameraMatrixCheckUnit(cnt, m_lpRotMat[cnt], stNum_x, stNum_y, stNum_z, UnitStep, end_x, end_y, end_z);

				UnitStep -= StepNum;
				if(UnitStep <= 10)
					StepNum = 1;

				if(UnitStep <= 0)
					break;

				if(end_x - UnitStep < 0)	stNum_x = 0;
				else						stNum_x = end_x - UnitStep;
				if(end_y - UnitStep < 0)	stNum_y = 0;
				else						stNum_y = end_y - UnitStep;
				if(end_z - UnitStep < 0)	stNum_z = 0;
				else						stNum_z = end_z - UnitStep;

				if(end_x + UnitStep > ANGLE_360)	end_x = ANGLE_360;
				else								end_x = end_x + UnitStep;
				if(end_y + UnitStep > ANGLE_360)	end_y = ANGLE_360;
				else								end_y = end_y + UnitStep;
				if(end_z + UnitStep > ANGLE_360)	end_z = ANGLE_360;
				else								end_z = end_z + UnitStep;
			}

			m_lpRotAng[cnt].Angle_x &= ANGLE_MASK;
			m_lpRotAng[cnt].Angle_y &= ANGLE_MASK;
			m_lpRotAng[cnt].Angle_z &= ANGLE_MASK;
		}
	}

	char *lpSaveName = ChangeFileExt(lpFileName, AUTO_CAMERA_EXT);
	Save_AutoCamera(lpSaveName);
	return TRUE;
}








void CAutoCamera::CameraMatrixCheckUnit(int RotCnt, smEMATRIX &eSrcMatrix, int stNum_x, int stNum_y, int stNum_z, int UnitStep, int &end_x, int &end_y, int &end_z)
{
	smEMATRIX eMat_x, eMat_y, eMat_z, eMatchMat;
	int		  Loop_x, Loop_y, Loop_z;

	Loop_x = end_x;
	Loop_y = end_y;
	Loop_z = end_z;


	int UnitNum = 0, LastUnitNum = 0;

	for(int rot_x = stNum_x; rot_x <= Loop_x; rot_x += UnitStep)
	{
		if(rot_x > ANGLE_90 && rot_x < ANGLE_270)
			continue;

		smEIdentityMatrix(eMat_x);
		smERotateXMatrix(eMat_x, rot_x);

		for(int rot_y = stNum_y; rot_y <= Loop_y; rot_y += UnitStep)
		{
			smEIdentityMatrix(eMat_y);
			smERotateYMatrix(eMat_y, rot_y);

			for(int rot_z = stNum_z; rot_z <= Loop_z; rot_z += UnitStep)
			{
				smEIdentityMatrix(eMat_z);
				smERotateZMatrix(eMat_z, rot_z);

				smEIdentityMatrix(eMatchMat);
				smEMatrixMult(eMatchMat, eMat_y, eMat_x);
				smEMatrixMult(eMatchMat, eMatchMat, eMat_z);


				UnitNum = CameraMatrixCheck(eSrcMatrix, eMatchMat);

				if(UnitNum < LastUnitNum || LastUnitNum == 0)
				{
					LastUnitNum = UnitNum;

					end_x = rot_x;
					end_y = rot_y;
					end_z = rot_z;

					m_lpRotAng[RotCnt].Angle_x = rot_x;
					m_lpRotAng[RotCnt].Angle_y = rot_y;
					m_lpRotAng[RotCnt].Angle_z = rot_z;
				}
			}
		}
	}
}








int CAutoCamera::CameraMatrixCheck(smEMATRIX &eSrcMatrix, smEMATRIX &eMatchMatrix)
{
	int TotalNum;

	TotalNum = abs(eSrcMatrix._11 - eMatchMatrix._11);
	TotalNum += (abs(eSrcMatrix._21 - eMatchMatrix._21) * 100);
	TotalNum += (abs(eSrcMatrix._31 - eMatchMatrix._31) * 200);

	TotalNum += (abs(eSrcMatrix._12 - eMatchMatrix._12) * 300);
	TotalNum += (abs(eSrcMatrix._22 - eMatchMatrix._22) * 400);
	TotalNum += (abs(eSrcMatrix._32 - eMatchMatrix._32) * 500);

	TotalNum += (abs(eSrcMatrix._13 - eMatchMatrix._13) * 600);
	TotalNum += (abs(eSrcMatrix._23 - eMatchMatrix._23) * 700);
	TotalNum += (abs(eSrcMatrix._33 - eMatchMatrix._33) * 800);

	return TotalNum;
}








int CAutoCamera::Load_AutoCamera(char *lpLoadName)
{
	FILE *fp = fopen(lpLoadName, "rb");
	if(fp == NULL)
		return 0;

	fread(&m_Frame, sizeof(int), 1, fp);
	fread(&m_LastFrame, sizeof(int), 1, fp);
	fread(&m_TmPosCnt, sizeof(int), 1, fp);
	fread(&m_RotCnt, sizeof(int), 1, fp);

	if(m_TmPosCnt > 0)
	{
		m_lpTmPos = new smTM_POS[m_TmPosCnt];
		fread(m_lpTmPos, sizeof(smTM_POS) * m_TmPosCnt, 1, fp);

	}

	if(m_RotCnt > 0)
	{
		m_lpRotAng = new SRotAngle[m_RotCnt];
		fread(m_lpRotAng, sizeof(SRotAngle) * m_RotCnt, 1, fp);

		m_lpRotQuat = new smDTM_ROT[m_RotCnt];
		fread(m_lpRotQuat, sizeof(smDTM_ROT) * m_RotCnt, 1, fp);

		m_lpRotMat = new smEMATRIX[m_RotCnt];
		fread(m_lpRotMat, sizeof(smEMATRIX) * m_RotCnt, 1, fp);
	}

	fclose(fp);
	return 1;
}








int CAutoCamera::Save_AutoCamera(char *lpSaveName)
{
	FILE *fp = fopen(lpSaveName, "wb");
	if(fp == NULL)
		return 0;

	fwrite(&m_Frame, sizeof(int), 1, fp);
	fwrite(&m_LastFrame, sizeof(int), 1, fp);
	fwrite(&m_TmPosCnt, sizeof(int), 1, fp);
	fwrite(&m_RotCnt, sizeof(int), 1, fp);

	if(m_TmPosCnt > 0)
		fwrite(m_lpTmPos, sizeof(smTM_POS) * m_TmPosCnt, 1, fp);

	if(m_RotCnt > 0)
	{
		fwrite(m_lpRotAng, sizeof(SRotAngle) * m_RotCnt, 1, fp);
		fwrite(m_lpRotQuat, sizeof(smDTM_ROT) * m_RotCnt, 1, fp);
		fwrite(m_lpRotMat, sizeof(smEMATRIX) * m_RotCnt, 1, fp);
	}

	fclose(fp);
	return 1;
}








void CAutoCamera::DXtoEMatrixFromFMatrix(smEMATRIX &smEmat, smFMATRIX &smFmat)
{
	smEmat._11 = int(smFmat._11 * wfONE);
	smEmat._12 = int(smFmat._13 * wfONE);
	smEmat._13 = int(smFmat._12 * wfONE);
	smEmat._14 = 0;

	smEmat._21 = int(smFmat._31 * wfONE);
	smEmat._22 = int(smFmat._33 * wfONE);
	smEmat._23 = int(smFmat._32 * wfONE);
	smEmat._24 = 0;

	smEmat._31 = int(smFmat._21 * wfONE);
	smEmat._32 = int(smFmat._23 * wfONE);
	smEmat._33 = int(smFmat._22 * wfONE);
	smEmat._34 = 0;

	smEmat._41 = 0;
	smEmat._42 = 0;
	smEmat._43 = 0;
	smEmat._44 = wfONE;
}








int CAutoCamera::SetWarpFrame(int StFrame, int EndFrame)
{
	if(m_WarpFrameCnt >= MAX_WARP_FRAME)
		return FALSE;

	m_WarpFrameStBuff[m_WarpFrameCnt] = StFrame * 160;
	m_WarpFrameEndBuff[m_WarpFrameCnt] = EndFrame * 160;

	m_WarpFrameCnt++;
	return TRUE;
}








int CAutoCamera::FrameMain(int FrameStep)
{

	m_Frame += FrameStep;
	if(m_Frame >= m_LastFrame)
	{
		m_Frame = m_LastFrame - 1;
		return 0;
	}


	int retNum = 1;
	if(m_Frame >= 166000)
		retNum = 2;


	int   cnt, st, end, i;
	int   Section, SectionPos;
	float fUnit;


	if(m_TmPosCnt > 0)
	{
		cnt = 0;
		while(TRUE)
		{
			st = m_lpTmPos[cnt].frame;
			end = m_lpTmPos[cnt + 1].frame;
			if(st <= m_Frame && end > m_Frame)
				break;
			cnt++;
		}


		for(i = 0; i < m_WarpFrameCnt; i++)
		{
			if(st >= m_WarpFrameStBuff[i] && end <= m_WarpFrameEndBuff[i])
			{
				m_fCameraPos_x = m_lpTmPos[cnt + 1].x * 256.f;
				m_fCameraPos_y = m_lpTmPos[cnt + 1].y * 256.f;
				m_fCameraPos_z = m_lpTmPos[cnt + 1].z * 256.f;


				i = -1;
				break;
			}
		}


		if(i != -1)
		{
			Section = end - st;
			SectionPos = m_Frame - st;

			fUnit = float(SectionPos) / float(Section);

			m_fCameraPos_x = m_lpTmPos[cnt].x + ((m_lpTmPos[cnt + 1].x - m_lpTmPos[cnt].x) * fUnit);
			m_fCameraPos_y = m_lpTmPos[cnt].y + ((m_lpTmPos[cnt + 1].y - m_lpTmPos[cnt].y) * fUnit);
			m_fCameraPos_z = m_lpTmPos[cnt].z + ((m_lpTmPos[cnt + 1].z - m_lpTmPos[cnt].z) * fUnit);

			m_fCameraPos_x *= 256.f;
			m_fCameraPos_y *= 256.f;
			m_fCameraPos_z *= 256.f;
		}
	}
	else
	{
		m_fCameraPos_x = 0;
		m_fCameraPos_y = 0;
		m_fCameraPos_z = 0;
	}


	if(m_RotCnt > 0)
	{
		cnt = 0;
		while(TRUE)
		{
			st = m_lpRotAng[cnt].frame;
			end = m_lpRotAng[cnt + 1].frame;
			if(st <= m_Frame && end > m_Frame)
				break;
			cnt++;
		}


		for(i = 0; i < m_WarpFrameCnt; i++)
		{
			if(st >= m_WarpFrameStBuff[i] && end <= m_WarpFrameEndBuff[i])
			{

				m_iCameraRot_z = m_lpRotAng[cnt + 1].Angle_z & ANGLE_MASK;
				m_iCameraRot_y = m_lpRotAng[cnt + 1].Angle_y & ANGLE_MASK;
				m_iCameraRot_x = m_lpRotAng[cnt + 1].Angle_x & ANGLE_MASK;


				smEMatrixInvert(m_eCameraRotMat, m_lpRotMat[cnt + 1]);


				i = -1;
				break;
			}
		}


		if(i != -1)
		{
			Section = end - st;
			SectionPos = m_Frame - st;

			fUnit = float(SectionPos) / float(Section);


			float f_x;
			if(m_lpRotAng[cnt].Angle_x == 0 && m_lpRotAng[cnt + 1].Angle_x == 0)
				f_x = 0;
			else if((m_lpRotAng[cnt].Angle_x == 0 || m_lpRotAng[cnt + 1].Angle_x == 0) &&
					abs(m_lpRotAng[cnt].Angle_x - m_lpRotAng[cnt + 1].Angle_x) > ANGLE_90)
			{
				if(m_lpRotAng[cnt].Angle_x == 0)
					f_x = float(m_lpRotAng[cnt + 1].Angle_x - ANGLE_360) * fUnit;
				else
					f_x = float(ANGLE_360 - m_lpRotAng[cnt].Angle_x) * fUnit;
			}
			else
				f_x = float(m_lpRotAng[cnt + 1].Angle_x - m_lpRotAng[cnt].Angle_x) * fUnit;


			float f_y;
			if(m_lpRotAng[cnt].Angle_y == 0 && m_lpRotAng[cnt + 1].Angle_y == 0)
				f_y = 0;
			else if((m_lpRotAng[cnt].Angle_y == 0 || m_lpRotAng[cnt + 1].Angle_y == 0) &&
					abs(m_lpRotAng[cnt].Angle_y - m_lpRotAng[cnt + 1].Angle_y) > ANGLE_90)
			{
				if(m_lpRotAng[cnt].Angle_y == 0)
					f_y = float(m_lpRotAng[cnt + 1].Angle_y - ANGLE_360) * fUnit;
				else
					f_y = float(ANGLE_360 - m_lpRotAng[cnt].Angle_y) * fUnit;
			}
			else
				f_y = float(m_lpRotAng[cnt + 1].Angle_y - m_lpRotAng[cnt].Angle_y) * fUnit;


			float f_z;
			if(m_lpRotAng[cnt].Angle_z == 0 && m_lpRotAng[cnt + 1].Angle_z == 0)
				f_z = 0;
			else if((m_lpRotAng[cnt].Angle_z == 0 || m_lpRotAng[cnt + 1].Angle_z == 0) &&
					abs(m_lpRotAng[cnt].Angle_z - m_lpRotAng[cnt + 1].Angle_z) > ANGLE_90)
			{
				if(m_lpRotAng[cnt].Angle_z == 0)
					f_z = float(m_lpRotAng[cnt + 1].Angle_z - ANGLE_360) * fUnit;
				else
					f_z = float(ANGLE_360 - m_lpRotAng[cnt].Angle_z) * fUnit;
			}
			else
				f_z = float(m_lpRotAng[cnt + 1].Angle_z - m_lpRotAng[cnt].Angle_z) * fUnit;


			m_iCameraRot_z = (m_lpRotAng[cnt].Angle_z + int(f_z)) & ANGLE_MASK;
			m_iCameraRot_y = (m_lpRotAng[cnt].Angle_y + int(f_y)) & ANGLE_MASK;
			m_iCameraRot_x = (m_lpRotAng[cnt].Angle_x + int(f_x)) & ANGLE_MASK;


			float ax = float(m_lpRotQuat[cnt + 1].x);
			float ay = float(m_lpRotQuat[cnt + 1].y);
			float az = float(m_lpRotQuat[cnt + 1].z);
			float aw = float(m_lpRotQuat[cnt + 1].w);

			float qx, qy, qz, qw;
			D3DMath_QuaternionSlerp(qx, qy, qz, qw, 0, 0, 0, 0, ax, ay, az, aw, fUnit);

			smFMATRIX fMat;
			smFMatrixFromQuaternion(fMat, qx, qy, qz, qw);

			smEMATRIX eMat;
			DXtoEMatrixFromFMatrix(eMat, fMat);
			smEMatrixMult(eMat, m_lpRotMat[cnt], eMat);
			smEMatrixInvert(m_eCameraRotMat, eMat);
		}
	}
	else
	{
		smEIdentityMatrix(m_eCameraRotMat);
	}

	return retNum;
}


