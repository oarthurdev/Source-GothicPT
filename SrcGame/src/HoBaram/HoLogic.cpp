#include "..\\HoBaram\\HoLinkHeader.h"
#include "sinbaram\\sinLinkHeader.h"
#include "..\\PlayMain.h"



HoEffectPatDest::HoEffectPatDest()
{
	BlurCurrentFrame = FALSE;
	SumCount = 0;

	BlurStartFlag = FALSE;
	AniDataIndex = -1;
}

HoEffectPatDest::~HoEffectPatDest()
{

}

int HoEffectPatDest::Main()
{
	int x, y, z;

	if(!StartFlag)
		return FALSE;

	if(CurrentFrame > AnimationEnd * 160 - 1)
	{
		PrimitiveBillBoard.SetState(FALSE);
		Init();

		if(SkillType == MONSTER_WEB_SHOT1)
			StartEffectMonster(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), MONSTER_WEB_HIT1);
	}

	if(CurrentFrame > (AnimationEnd * 160 - 1) - 5 * FrameStep)
	{
		BlendStep -= 2;
		CurrentFrame += FrameStep / 10;
	}
	else
		CurrentFrame += FrameStep;

	if(WorkState == PAT_PROCESS)
	{
		if(CurrentFrame >= (AnimationEnd * 160 - 1) - 5 * FrameStep)
			CurrentFrame = 159;

	}

	if(CurrentFrame < (AnimationEnd * 160 - 1) - 5 * FrameStep)
	{
		GetMoveLocation(0, 0, Step, DestAngleX, DestAngleY, 0);
		if(SkillType == SKILL_PERFECT_AIM || SkillType == SKILL_WIND_ARROW || SkillType == MONSTER_WEB_SHOT1
		   || SkillType == SKILL_ARROW_OF_RAGE || SkillType == SKILL_AVALANCHE || SkillType == SKILL_GROUND_PIKE)
		{
			LocalX += GeoResult_X;
			LocalY += GeoResult_Y;
			LocalZ += GeoResult_Z;


			D3DXVECTOR3	attractLocation;
			attractLocation.x = DestX - (WorldX + LocalX);
			attractLocation.y = DestY - (WorldY + LocalY);
			attractLocation.z = DestZ - (WorldZ + LocalZ);

			D3DXVECTOR3 attractDir = attractLocation;

			float length;
			length = (float)sqrt(attractDir.x*attractDir.x + attractDir.y*attractDir.y + attractDir.z*attractDir.z);

			if(SkillType == SKILL_WIND_ARROW)
			{
				if(length < 10000 && WorkState == PAT_PROCESS)
				{
					CurrentFrame = ((AnimationEnd * 160 - 1) - FrameStep);
					PrimitiveBillBoard.SetState(FALSE);
					WorkState = PAT_END;
					EventEnd();
					return TRUE;
				}
				StartEffect(int(WorldX + LocalX + GeoResult_X), int(WorldY + LocalY + GeoResult_Y), int(WorldZ + LocalZ + GeoResult_Z), 100, 100, 100, 150, EFFECT_PARTICLE_BOW2);
			}
			else if(SkillType == SKILL_PERFECT_AIM)
			{
				if(length < 10000 && WorkState == PAT_PROCESS)
				{
					CurrentFrame = ((AnimationEnd * 160 - 1) - FrameStep);
					WorkState = PAT_END;
					PrimitiveBillBoard.SetState(FALSE);
					EventEnd();
					return TRUE;
				}
			}
			else if(SkillType == SKILL_ARROW_OF_RAGE)
			{

				if(length < 35000 && WorkState == PAT_PROCESS)
				{
					GetRadian3D(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), DestX, DestY - 40000, DestZ);

					Angle.x = GeoResult_X;
					Angle.y = GeoResult_Y;
					Angle.z = 0;

					Angle.y = (-Angle.y + ANGLE_180)&ANGCLIP;
				}

				if(length < 30000 && WorkState == PAT_PROCESS)
				{

					CurrentFrame = ((AnimationEnd * 160 - 1) - FrameStep);
					WorkState = PAT_END;
					PrimitiveBillBoard.SetState(FALSE);

					StartEffect(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), ARROW_OF_RAGE_POWER1);



					x = int(WorldX + LocalX);
					z = int(WorldZ + LocalZ);
					x = (DestX - x) >> FLOATNS;
					z = (DestZ - z) >> FLOATNS;
					z = (int)sqrt((double)(x*x + z*z));
					z /= 2;

					y = GetRadian2D(int(WorldX + LocalX), int(WorldZ + LocalZ), DestX, DestZ);

					GetMoveLocation(0, 0, z*fONE, 0, y, 0);

					x = int(WorldX + LocalX) + GeoResult_X;
					z = int(WorldZ + LocalZ) + GeoResult_Z;
					StartSkillDest(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), x, DestY - 40000, z, SKILL_ARROW_OF_RAGE_END, Level);
					return TRUE;
				}
			}
			else if(SkillType == SKILL_AVALANCHE)
			{






				StartSkill(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), DestAngleX, DestAngleY, DestAngleZ, SKILL_AVALANCHE_PARTICLE);


				if(length < 10000 && WorkState == PAT_PROCESS)
				{
					CurrentFrame = ((AnimationEnd * 160 - 1) - FrameStep);
					WorkState = PAT_END;
					PrimitiveBillBoard.SetState(FALSE);


					StartSkill(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), 0, 0, 0, SKILL_TRIPLE_IMPACT);
					return TRUE;
				}
			}
			else if(SkillType == MONSTER_WEB_SHOT1)
			{
				if(length < 10000 && WorkState == PAT_PROCESS)
				{

					CurrentFrame = ((AnimationEnd * 160 - 1) - 40);
					WorkState = PAT_END;
					PrimitiveBillBoard.SetState(FALSE);
					EventEnd();
					return TRUE;
				}
			}
			else if(SkillType == SKILL_GROUND_PIKE)
			{
				if(length < 10000 && WorkState == PAT_PROCESS)
				{





					CurrentFrame = ((AnimationEnd * 160 - 1) - 200);
					WorkState = PAT_END;
					PrimitiveBillBoard.SetState(FALSE);
					EventEnd();



					return TRUE;
				}
			}
		}
		else if(SkillType == SKILL_MECHANIC_BOMB)
		{

			D3DXVECTOR3	attractLocation;
			attractLocation.x = DestX - (WorldX + LocalX);
			attractLocation.y = DestY - (WorldY + LocalY);
			attractLocation.z = DestZ - (WorldZ + LocalZ);

			D3DXVECTOR3 attractDir = attractLocation;

			float length;
			length = (float)sqrt(attractDir.x*attractDir.x + attractDir.y*attractDir.y + attractDir.z*attractDir.z);

			if(length < 20000)
			{


				int mapY1 = int(WorldY + LocalY);
				int mapY2 = int(WorldY + LocalY);

				if(smGameStage[0])
				{
					mapY1 = smGameStage[0]->GetHeight(int(WorldX + LocalX), int(WorldZ + LocalZ));
				}
				if(smGameStage[1])
				{
					mapY2 = smGameStage[1]->GetHeight(int(WorldX + LocalX), int(WorldZ + LocalZ));
					if(mapY1 < mapY2) mapY1 = mapY2;
				}


				if(mapY1 > (WorldY + LocalY - 4000) || length < 3000)
				{
					CurrentFrame = ((AnimationEnd * 160 - 1) - 5 * FrameStep);
					PrimitiveBillBoard.SetState(FALSE);
					WorkState = PAT_END;
					Init();
					EventEnd();
					return TRUE;
				}
			}

			if(length > 10000)
				VelocityY += int(attractDir.y / length * 120.0f);
			else
				VelocityY += int(attractDir.y / length * 60.0f);

			if(VelocityY >= 5000)
			{
				VelocityY *= 0.75f;
			}

			LocalX += GeoResult_X;

			LocalY += VelocityY;
			LocalZ += GeoResult_Z;

			StartEffect(int(WorldX + LocalX) + rand() % 2000 - 1000 + GeoResult_X, int(WorldY + LocalY) + rand() % 1000 - 1000, int(WorldZ + LocalZ) + rand() % 2000 - 1000 + GeoResult_Z, EFFECT_MECHANICBOMB_DUST1);

			Angle.x += ANGLE_45 / 4;
			Angle.x = Angle.x&ANGCLIP;
		}
		else
		{
			LocalX += GeoResult_X;
			LocalY += GeoResult_Y;
			LocalZ += GeoResult_Z;

			int mapY1 = int(WorldY + LocalY);
			int mapY2 = int(WorldY + LocalY);

			if(smGameStage[0])
			{
				mapY1 = smGameStage[0]->GetHeight(int(WorldX + LocalX), int(WorldZ + LocalZ));
			}
			if(smGameStage[1])
			{
				mapY2 = smGameStage[1]->GetHeight(int(WorldX + LocalX), int(WorldZ + LocalZ));
				if(mapY1 < mapY2) mapY1 = mapY2;
			}


			if(WorkState == PAT_PROCESS && mapY1 > (WorldY + LocalY - 4000))
			{
				CurrentFrame = ((AnimationEnd * 160 - 1) - 5 * FrameStep);
				PrimitiveBillBoard.SetState(FALSE);
				WorkState = PAT_END;

				if(SkillType == SKILL_ARROW_OF_RAGE_END)
				{
					BlurBlendValue = 0;
					StartEffect(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), EFFECT_ARROW_OF_RAGE_HIT1);
				}
			}
		}

		POINT3D velocity;
		velocity.x = GeoResult_X;
		velocity.y = GeoResult_Y;
		velocity.z = GeoResult_Z;

		PrimitiveBillBoard.TranslateWorld(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ));
		PrimitiveBillBoard.SetDirectionVelocity(velocity);
		PrimitiveBillBoard.Main();

		MainBlur();
	}
	return TRUE;
}


int HoEffectPatDest::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag)
	{
		HoEffectPat::Draw(x, y, z, ax, ay, az);
		PrimitiveBillBoard.Draw(x, y, z, ax, ay, az);
		DrawBlur(x, y, z, ax, ay, az);
	}
	return TRUE;
}


int HoEffectPatDest::StartDest(POINT3D currentPos, POINT3D destPos, smPAT3D *pat, int skillType, int level)
{
	if(pat == NULL || StartFlag)
		return FALSE;

	Angle.y = 0;
	Angle.x = 0;
	Level = level;
	HoEffectPat::Init();
	PatObj = pat;
	WorldX = (float)currentPos.x, WorldY = (float)currentPos.y, WorldZ = (float)currentPos.z;
	LocalX = 0, LocalY = 0, LocalZ = 0;

	StartFlag = TRUE;
	CurrentFrame = 159;
	PatObj->Frame = CurrentFrame;
	BlendStep = 0;

	DestX = destPos.x;
	DestY = destPos.y;
	DestZ = destPos.z;

	SkillType = skillType;
	WorkState = PAT_PROCESS;
	Step = 12 * fONE;
	FrameStep = 40;

	if(SkillType == SKILL_ARROW_OF_RAGE)
	{
		Step = fONE * 8;
		DestY += 60000;
	}
	else if(SkillType == SKILL_ARROW_OF_RAGE_END)
	{
		Step = fONE * 5;
	}

	GetRadian3D(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), DestX, DestY, DestZ);

	DestAngleX = GeoResult_X;
	DestAngleY = GeoResult_Y;
	DestAngleZ = 0;

	Angle.x = GeoResult_X;
	Angle.y = GeoResult_Y;
	Angle.z = 0;

	Angle.y = (-Angle.y + ANGLE_180)&ANGCLIP;


	if(SkillType == SKILL_MECHANIC_BOMB)
	{
		Step = 4 * fONE;



		D3DXVECTOR3	attractLocation;
		attractLocation.x = DestX - (WorldX + LocalX);
		attractLocation.y = DestY - (WorldY + LocalY);
		attractLocation.z = DestZ - (WorldZ + LocalZ);

		D3DXVECTOR3 attractDir = attractLocation;

		float length;
		length = (float)sqrt(attractDir.x*attractDir.x + attractDir.y*attractDir.y + attractDir.z*attractDir.z);

		if(length >= 30000)
			VelocityY = 800;
		else
			VelocityY = 400;
	}
	else if(SkillType == SKILL_PERFECT_AIM)
	{
		Step = 9 * fONE;
		POINT	size;
		size.x = 10;
		size.y = 400;

		GetMoveLocation(0, 0, Step, DestAngleX, DestAngleY, 0);
		PrimitiveBillBoard.StartBillRect(int(WorldX + LocalX) + GeoResult_X,
										 int(WorldY + LocalY) + GeoResult_Y + 200, int(WorldZ + LocalZ) + GeoResult_Z, "SkillPerfectAim1.ini", ANI_LOOP, PRIMITIVE_PATH_RECT_LINE);
		PrimitiveBillBoard.SetSize(size);
	}
	else if(SkillType == SKILL_WIND_ARROW)
	{
		Step = 9 * fONE;
	}
	else if(SkillType == MONSTER_WEB_SHOT1)
	{
		Step = 4 * fONE;
		GetMoveLocation(0, 0, Step * 7, DestAngleX, DestAngleY, 0);
		DestX += GeoResult_X;
		DestZ += GeoResult_Z;
		FrameStep = 20;
	}
	else if(SkillType == SKILL_ARROW_OF_RAGE)
	{
		POINT	size;
		size.x = 17;
		size.y = 600;



		StartBlur("Blur1.ini");
		Level = level;
	}
	else if(SkillType == SKILL_ARROW_OF_RAGE_END)
	{
		Step = 18 * fONE;
		StartBlur("Blur1.ini");
	}
	else if(SkillType == SKILL_AVALANCHE)
	{
		Step = 12 * fONE;
	}
	else if(SkillType == SKILL_GROUND_PIKE)
	{
		Step = 8 * fONE;
		SetBlendStep(-110);
	}
	return TRUE;
}

int HoEffectPatDest::CreatePathFace()
{


	memset(Vertex, 0, sizeof(Vertex));
	memset(Face, 0, sizeof(Face));
	memset(TexLink, 0, sizeof(TexLink));
	VertexCount = 0;
	FaceCount = 0;
	TexLinkCount = 0;

	POINT3D firstPos;
	POINT3D secondPos;

	for(int index = 0; index < PosListCount - 1; index++)
	{
		if((VertexCount - 4) >= MAX_BLUR_VERTEX)
			break;

		firstPos.x = int(PosList[index].x);
		firstPos.y = int(PosList[index].y);
		firstPos.z = int(PosList[index].z);

		secondPos.x = int(PosList[index + 1].x);
		secondPos.y = int(PosList[index + 1].y);
		secondPos.z = int(PosList[index + 1].z);

		int blendStep = BlurBlendValue / ((PosListCount - 1));
		hoPOINT3D inVector;
		hoPOINT3D outVector;

		inVector.x = float(PosList[index].x + PosList[index + 1].x);
		inVector.y = float(PosList[index].y + PosList[index + 1].y);
		inVector.z = float(PosList[index].z + PosList[index + 1].z);

		double length = sqrt(inVector.x*inVector.x + inVector.y*inVector.y + inVector.z*inVector.z);
		inVector.x = float(inVector.x / length);
		inVector.y = float(inVector.y / length);
		inVector.z = float(inVector.z / length);


		outVector.x = -inVector.x;
		outVector.y = -inVector.y;
		outVector.z = -inVector.z;

		if(index == 0)
		{

			Vertex[VertexCount].x = int(firstPos.x + outVector.x*SizeWidth * 20);
			Vertex[VertexCount].y = int(firstPos.y + outVector.y*SizeWidth * 20);
			Vertex[VertexCount].z = int(firstPos.z + outVector.z*SizeWidth * 20);
			Vertex[VertexCount].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[3] = (int)BlurBlendValue;

			Vertex[VertexCount + 1].x = int(firstPos.x + inVector.x*SizeWidth * 20);
			Vertex[VertexCount + 1].y = int(firstPos.y + inVector.y*SizeWidth * 20);
			Vertex[VertexCount + 1].z = int(firstPos.z + inVector.z*SizeWidth * 20);
			Vertex[VertexCount + 1].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount + 1].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount + 1].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount + 1].sDef_Color[3] = (int)BlurBlendValue;


			Vertex[VertexCount + 2].x = int(secondPos.x + outVector.x*SizeWidth * 20);
			Vertex[VertexCount + 2].y = int(secondPos.y + outVector.y*SizeWidth * 20);
			Vertex[VertexCount + 2].z = int(secondPos.z + outVector.z*SizeWidth * 20);
			Vertex[VertexCount + 2].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount + 2].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount + 2].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount + 2].sDef_Color[3] = (int)BlurBlendValue;

			Vertex[VertexCount + 3].x = int(secondPos.x + inVector.x*SizeWidth * 20);
			Vertex[VertexCount + 3].y = int(secondPos.y + inVector.y*SizeWidth * 20);
			Vertex[VertexCount + 3].z = int(secondPos.z + inVector.z*SizeWidth * 20);

			Vertex[VertexCount + 3].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount + 3].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount + 3].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount + 3].sDef_Color[3] = (int)BlurBlendValue;
		}
		else
		{

			Vertex[VertexCount].x = Vertex[VertexCount - 2].x;
			Vertex[VertexCount].y = Vertex[VertexCount - 2].y;
			Vertex[VertexCount].z = Vertex[VertexCount - 2].z;
			Vertex[VertexCount].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount].sDef_Color[3] = (int)BlurBlendValue;

			Vertex[VertexCount + 1].x = Vertex[VertexCount - 1].x;
			Vertex[VertexCount + 1].y = Vertex[VertexCount - 1].y;
			Vertex[VertexCount + 1].z = Vertex[VertexCount - 1].z;
			Vertex[VertexCount + 1].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount + 1].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount + 1].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount + 1].sDef_Color[3] = (int)BlurBlendValue;


			Vertex[VertexCount + 2].x = int(secondPos.x + outVector.x*SizeWidth * 20);
			Vertex[VertexCount + 2].y = int(secondPos.y + outVector.y*SizeWidth * 20);
			Vertex[VertexCount + 2].z = int(secondPos.z + outVector.z*SizeWidth * 20);
			Vertex[VertexCount + 2].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount + 2].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount + 2].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount + 2].sDef_Color[3] = (int)BlurBlendValue;

			Vertex[VertexCount + 3].x = int(secondPos.x + inVector.x*SizeWidth * 20);
			Vertex[VertexCount + 3].y = int(secondPos.y + inVector.y*SizeWidth * 20);
			Vertex[VertexCount + 3].z = int(secondPos.z + inVector.z*SizeWidth * 20);

			Vertex[VertexCount + 3].sDef_Color[0] = (int)BlurBlendValue;
			Vertex[VertexCount + 3].sDef_Color[1] = (int)BlurBlendValue;
			Vertex[VertexCount + 3].sDef_Color[2] = (int)BlurBlendValue;
			Vertex[VertexCount + 3].sDef_Color[3] = (int)BlurBlendValue;
		}





		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;

		TexLink[TexLinkCount].u[0] = (1.0f)*(float(index) / float(PosListCount));
		TexLink[TexLinkCount].v[0] = 0.0f;
		TexLink[TexLinkCount].u[1] = (1.0f)*(float(index) / float(PosListCount));
		TexLink[TexLinkCount].v[1] = 1.0f;
		TexLink[TexLinkCount].u[2] = (1.0f)*(float(index + 1) / float(PosListCount));
		TexLink[TexLinkCount].v[2] = 0.0f;

		TexLink[TexLinkCount + 1].hTexture = 0;
		TexLink[TexLinkCount + 1].NextTex = 0;
		TexLink[TexLinkCount + 1].u[0] = (1.0f)*(float(index + 1) / float(PosListCount));
		TexLink[TexLinkCount + 1].v[0] = 0.0f;
		TexLink[TexLinkCount + 1].u[1] = (1.0f)*(float(index) / float(PosListCount));
		TexLink[TexLinkCount + 1].v[1] = 1.0f;
		TexLink[TexLinkCount + 1].u[2] = (1.0f)*(float(index + 1) / float(PosListCount));
		TexLink[TexLinkCount + 1].v[2] = 1.0f;



		Face[FaceCount].Vertex[0] = VertexCount;
		Face[FaceCount].Vertex[1] = VertexCount + 1;
		Face[FaceCount].Vertex[2] = VertexCount + 2;
		Face[FaceCount].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount].lpTexLink = &TexLink[TexLinkCount];
		Face[FaceCount].sum = 0;

		Face[FaceCount + 1].Vertex[0] = VertexCount + 2;
		Face[FaceCount + 1].Vertex[1] = VertexCount + 1;
		Face[FaceCount + 1].Vertex[2] = VertexCount + 3;
		Face[FaceCount + 1].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount + 1].lpTexLink = &TexLink[TexLinkCount + 1];
		Face[FaceCount + 1].sum = 0;


		VertexCount += 4;
		FaceCount += 2;
		TexLinkCount += 2;
	}

	return TRUE;
}


int HoEffectPatDest::StartBlur(char *iniName)
{

	AniDataIndex = AnimDataMgr.GetSearchSequenceData(iniName);
	if(AniDataIndex == -1)
		return FALSE;

	memset(PosList, 0, sizeof(PosList));
	PosListCount = 0;

	BlurBlendValue = 120;
	BlurTimeCount = 0;
	BlurCurrentFrame = 0;
	SizeWidth = 4;

	if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 0)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_COLOR;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 1)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_ALPHA;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 2)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_LAMP;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 3)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_SHADOW;

	BlurStartFlag = TRUE;
	return TRUE;
}

int HoEffectPatDest::MainBlur()
{
	if(BlurStartFlag == FALSE || AniDataIndex == -1)
		return FALSE;






	GetMoveLocation(0, 0, Step, DestAngleX, DestAngleY, 0);
	if(PosListCount < MAX_BLUR_LIST)
	{
		POINT3D tempPosList[MAX_BLUR_LIST - 1];
		memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
		memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
		PosList[0].x = int(WorldX + LocalX + GeoResult_X);
		PosList[0].y = int(WorldY + LocalY + GeoResult_Y);
		PosList[0].z = int(WorldZ + LocalZ + GeoResult_Z);

		PosListCount++;
	}
	else
	{
		POINT3D tempPosList[MAX_BLUR_LIST - 1];
		memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
		memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
		PosList[0].x = int(WorldX + LocalX + GeoResult_X);
		PosList[0].y = int(WorldY + LocalY + GeoResult_Y);
		PosList[0].z = int(WorldZ + LocalZ + GeoResult_Z);
	}

	if(StartFlag == FALSE)
		return FALSE;


	if(BlurCurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(BlurTimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[BlurCurrentFrame].Delay)
		{
			BlurTimeCount = 0;
			BlurCurrentFrame++;
			if(BlurCurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount - 1)
				BlurCurrentFrame = 1;
		}

		BlurTimeCount++;
	}

	return TRUE;
}

int HoEffectPatDest::DrawBlur(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag == FALSE || BlurStartFlag == FALSE || AniDataIndex == -1)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);

	smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AniDataIndex].GetMaterialNum()].TwoSide = TRUE;

	smMaterialGroup->SetMaterialAnimFrame(&smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()],
										  AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[BlurCurrentFrame].ImageNum);


	smRender.SetCameraPosi(x, y, z, ax, ay, az);

	CreatePathFace();
	smRender.InitStageMesh(Vertex, SumCount);
	for(int index = 0; index < FaceCount; index++)
		smRender.AddStageFace(&Face[index]);

	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);

	smRender.RenderD3D();


	SumCount++;

	return TRUE;
}

int HoEffectPatDest::StartAni(int x, int y, int z, int angleX, int angleY, int angleZ,
							  int destX, int destY, int destZ,
							  smPAT3D *pat, char *addEffectName)
{
	if(pat == NULL || StartFlag)
		return FALSE;

	Angle.y = ((ANGLE_270 - angleY)&ANGCLIP);
	Angle.x = ANGLE_270;

	HoEffectPat::Init();
	PatObj = pat;
	WorldX = (float)x, WorldY = (float)y, WorldZ = (float)z;
	LocalX = 0, LocalY = 0, LocalZ = 0;

	StartFlag = TRUE;
	CurrentFrame = 159;
	PatObj->Frame = CurrentFrame;
	BlendStep = 0;

	DestX = destX;
	DestY = destY;
	DestZ = destZ;
	GetRadian3D(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), DestX, DestY, DestZ);

	DestAngleX = GeoResult_X;
	DestAngleY = GeoResult_Y;
	DestAngleZ = 0;

	Angle.x = GeoResult_X;
	Angle.y = GeoResult_Y;
	Angle.z = 0;

	Angle.y = (-Angle.y + ANGLE_180)&ANGCLIP;
	if(addEffectName != NULL)
	{
		POINT	size;
		size.x = 16;
		size.y = 100;
		PrimitiveBillBoard.StartBillRect(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), addEffectName, ANI_LOOP, PRIMITIVE_PATH_RECT_LINE);
		PrimitiveBillBoard.SetSize(size);
	}

	WorkState = PAT_PROCESS;
	FrameStep = 40;

	return TRUE;
}

int HoEffectPatDest::EventEnd()
{

	switch(SkillType)
	{
		case SKILL_MECHANIC_BOMB:
		{
			SkillPlaySound(SKILL_SOUND_MECHANIC_BOMB2, int(WorldX + LocalX), int(WorldY + LocalY + 1000), int(WorldZ + LocalZ));
			StartEffect(int(WorldX + LocalX), int(WorldY + LocalY + 1000), int(WorldZ + LocalZ), EFFECT_FIRE_HIT1, Level);
		}

		case SKILL_PERFECT_AIM:
		{

			SkillPlaySound(SKILL_SOUND_ARROW_HIT1, int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ));
			StartEffect(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), EFFECT_CRITICAL_HIT1);
		}

		case SKILL_WIND_ARROW:
		{
			SkillPlaySound(SKILL_SOUND_ARROW_HIT2, int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ));
			StartEffect(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), EFFECT_CRITICAL_HIT1);
		}

		case MONSTER_WEB_SHOT1:
		{



		}
	}
	return TRUE;
}





HoEffectShield::HoEffectShield()
{
	AniDataIndex = -1;
	StartFlag = FALSE;
	CurrentFrame = 0;

	SumCount = 0;

	memset(Vertex, 0, sizeof(Vertex));
	VertexCount = 0;
	memset(Face, 0, sizeof(Face));
	FaceCount = 0;
	memset(TexLink, 0, sizeof(TexLink));
	TexLinkCount = 0;

	Character = NULL;


}

HoEffectShield::~HoEffectShield()
{

}

int HoEffectShield::CreatePathFace()
{

	memset(Vertex, 0, sizeof(Vertex));
	memset(Face, 0, sizeof(Face));
	memset(TexLink, 0, sizeof(TexLink));
	VertexCount = 0;
	FaceCount = 0;
	TexLinkCount = 0;


	POINT3D firstPos;
	POINT3D secondPos;

	for(int index = 0; index < PosListCount - 1; index++)
	{
		firstPos.x = int(PosList[index].x + WorldX);
		firstPos.y = int(PosList[index].y + WorldY);
		firstPos.z = int(PosList[index].z + WorldZ);

		secondPos.x = int(PosList[index + 1].x + WorldX);
		secondPos.y = int(PosList[index + 1].y + WorldY);
		secondPos.z = int(PosList[index + 1].z + WorldZ);

		int blendStep = CurrentBlendValue / ((PosListCount - 1) + 10);



		hoPOINT3D inVector;
		hoPOINT3D outVector;

		inVector.x = float(PosList[index].x + PosList[index + 1].x);
		inVector.y = float(PosList[index].y + PosList[index + 1].y);
		inVector.z = float(PosList[index].z + PosList[index + 1].z);

		double length = sqrt(inVector.x*inVector.x + inVector.y*inVector.y + inVector.z*inVector.z);
		inVector.x = float(inVector.x / length);
		inVector.y = float(inVector.y / length);
		inVector.z = float(inVector.z / length);


		outVector.x = -inVector.x;
		outVector.y = -inVector.y;
		outVector.z = -inVector.z;

		if(index == 0)
		{

			Vertex[VertexCount].x = int(firstPos.x + outVector.x*SizeHeight * 20);
			Vertex[VertexCount].y = int(firstPos.y + outVector.y*SizeHeight * 20);
			Vertex[VertexCount].z = int(firstPos.z + outVector.z*SizeHeight * 20);
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 1].x = int(firstPos.x + inVector.x*SizeHeight * 20);
			Vertex[VertexCount + 1].y = int(firstPos.y + inVector.y*SizeHeight * 20);
			Vertex[VertexCount + 1].z = int(firstPos.z + inVector.z*SizeHeight * 20);
			Vertex[VertexCount + 1].sDef_Color[0] = 255;
			Vertex[VertexCount + 1].sDef_Color[1] = 255;
			Vertex[VertexCount + 1].sDef_Color[2] = 255;
			Vertex[VertexCount + 1].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;


			Vertex[VertexCount + 2].x = int(secondPos.x + outVector.x*SizeHeight * 20);
			Vertex[VertexCount + 2].y = int(secondPos.y + outVector.y*SizeHeight * 20);
			Vertex[VertexCount + 2].z = int(secondPos.z + outVector.z*SizeHeight * 20);
			Vertex[VertexCount + 2].sDef_Color[0] = 255;
			Vertex[VertexCount + 2].sDef_Color[1] = 255;
			Vertex[VertexCount + 2].sDef_Color[2] = 255;
			Vertex[VertexCount + 2].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 3].x = int(secondPos.x + inVector.x*SizeHeight * 20);
			Vertex[VertexCount + 3].y = int(secondPos.y + inVector.y*SizeHeight * 20);
			Vertex[VertexCount + 3].z = int(secondPos.z + inVector.z*SizeHeight * 20);

			Vertex[VertexCount + 3].sDef_Color[0] = 255;
			Vertex[VertexCount + 3].sDef_Color[1] = 255;
			Vertex[VertexCount + 3].sDef_Color[2] = 255;
			Vertex[VertexCount + 3].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;
		}
		else
		{

			Vertex[VertexCount].x = Vertex[VertexCount - 2].x;
			Vertex[VertexCount].y = Vertex[VertexCount - 2].y;
			Vertex[VertexCount].z = Vertex[VertexCount - 2].z;
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 1].x = Vertex[VertexCount - 1].x;
			Vertex[VertexCount + 1].y = Vertex[VertexCount - 1].y;
			Vertex[VertexCount + 1].z = Vertex[VertexCount - 1].z;
			Vertex[VertexCount + 1].sDef_Color[0] = 255;
			Vertex[VertexCount + 1].sDef_Color[1] = 255;
			Vertex[VertexCount + 1].sDef_Color[2] = 255;
			Vertex[VertexCount + 1].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;


			Vertex[VertexCount + 2].x = int(secondPos.x + outVector.x*SizeHeight * 20);
			Vertex[VertexCount + 2].y = int(secondPos.y + outVector.y*SizeHeight * 20);
			Vertex[VertexCount + 2].z = int(secondPos.z + outVector.z*SizeHeight * 20);
			Vertex[VertexCount + 2].sDef_Color[0] = 255;
			Vertex[VertexCount + 2].sDef_Color[1] = 255;
			Vertex[VertexCount + 2].sDef_Color[2] = 255;
			Vertex[VertexCount + 2].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 3].x = int(secondPos.x + inVector.x*SizeHeight * 20);
			Vertex[VertexCount + 3].y = int(secondPos.y + inVector.y*SizeHeight * 20);
			Vertex[VertexCount + 3].z = int(secondPos.z + inVector.z*SizeHeight * 20);

			Vertex[VertexCount + 3].sDef_Color[0] = 255;
			Vertex[VertexCount + 3].sDef_Color[1] = 255;
			Vertex[VertexCount + 3].sDef_Color[2] = 255;
			Vertex[VertexCount + 3].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;
		}




		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;
		TexLink[TexLinkCount].u[0] = (1.0f)*(float(index) / float(PosListCount - 1));
		TexLink[TexLinkCount].v[0] = 0.0f;
		TexLink[TexLinkCount].u[1] = (1.0f)*(float(index) / float(PosListCount - 1));
		TexLink[TexLinkCount].v[1] = 1.0f;
		TexLink[TexLinkCount].u[2] = (1.0f)*(float(index + 1) / float(PosListCount - 1));
		TexLink[TexLinkCount].v[2] = 0.0f;

		TexLink[TexLinkCount + 1].hTexture = 0;
		TexLink[TexLinkCount + 1].NextTex = 0;
		TexLink[TexLinkCount + 1].u[0] = (1.0f)*(float(index + 1) / float(PosListCount - 1));
		TexLink[TexLinkCount + 1].v[0] = 0.0f;
		TexLink[TexLinkCount + 1].u[1] = (1.0f)*(float(index) / float(PosListCount - 1));
		TexLink[TexLinkCount + 1].v[1] = 1.0f;
		TexLink[TexLinkCount + 1].u[2] = (1.0f)*(float(index + 1) / float(PosListCount - 1));
		TexLink[TexLinkCount + 1].v[2] = 1.0f;


		Face[FaceCount].Vertex[0] = VertexCount;
		Face[FaceCount].Vertex[1] = VertexCount + 1;
		Face[FaceCount].Vertex[2] = VertexCount + 2;
		Face[FaceCount].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount].lpTexLink = &TexLink[TexLinkCount];
		Face[FaceCount].sum = 0;

		Face[FaceCount + 1].Vertex[0] = VertexCount + 2;
		Face[FaceCount + 1].Vertex[1] = VertexCount + 1;
		Face[FaceCount + 1].Vertex[2] = VertexCount + 3;
		Face[FaceCount + 1].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount + 1].lpTexLink = &TexLink[TexLinkCount + 1];
		Face[FaceCount + 1].sum = 0;


		VertexCount += 4;
		FaceCount += 2;
		TexLinkCount += 2;








	}
	return TRUE;
}

void HoEffectShield::Init()
{
	StartFlag = FALSE;
}

int HoEffectShield::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);

	smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AniDataIndex].GetMaterialNum()].TwoSide = TRUE;

	smMaterialGroup->SetMaterialAnimFrame(&smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()],
										  AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].ImageNum);


	smRender.SetCameraPosi(x, y, z, ax, ay, az);







	smRender.SetCameraPosi(x, y, z, ax, ay, az);
	CreatePathFace();
	smRender.InitStageMesh(Vertex, SumCount);

	for(int index = 0; index < FaceCount; index++)
		smRender.AddStageFace(&Face[index]);


	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	smRender.RenderD3D();
	SumCount++;
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	BackBillBoard.Draw(x, y, z, ax, ay, az);
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	if(ShieldType == SKILL_SHIELD2)
	{
		if(UnderPat.GetState())
			UnderPat.Draw(x, y, z, ax, ay, az);
	}

	return TRUE;
}


int HoEffectShield::Main()
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;


	if(CurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(TimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay)
		{
			TimeCount = 0;
			CurrentFrame++;
			if(CurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount - 1)
				CurrentFrame = 1;


			BlendStep = (AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].AlphaValue - CurrentBlendValue) /
				AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay;
		}
		CurrentBlendValue = 250;
		TimeCount++;
	}



	WorldX = float(Character->pX);
	WorldY = float(Character->pY + 3000);
	WorldZ = float(Character->pZ);

	if(ShieldType == SKILL_SHIELD1)
	{
		DirectionAngle.y += (ANGLE_360 / 60)&ANGCLIP;
		DirectionAngle.y = DirectionAngle.y&ANGCLIP;

		GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, 0, DirectionAngle.y, 0);
		POINT3D tempGeoResult;
		tempGeoResult.x = GeoResult_X;
		tempGeoResult.y = GeoResult_Y;
		tempGeoResult.z = GeoResult_Z;

		GetMoveLocation(tempGeoResult.x, tempGeoResult.y, tempGeoResult.z, DirectionAngle.x, 0, 0);


		GeoResult_Y += 4500;
		BackBillBoard.TranslateWorld(int(GeoResult_X + WorldX), int(GeoResult_Y + WorldY), int(GeoResult_Z + WorldZ));
		BackBillBoard.Main();

		if(PosListCount < POS_LIST_MAX)
		{
			POINT3D tempPosList[POS_LIST_MAX - 1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;


			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;

			PosListCount++;
		}
		else
		{
			POINT3D tempPosList[POS_LIST_MAX - 1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));

			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;

		}

		static int particleCount = 0;
		if(particleCount >= 25)
		{
			StartEffect(int(GeoResult_X + WorldX), int(GeoResult_Y + WorldY), int(GeoResult_Z + WorldZ), EFFECT_SHIELD1_PARTICLE);
			particleCount = 0;

		}
		particleCount++;

		EndCount++;








		if(EndCount >= 150 * 70 || ((Character != NULL) && !(Character->dwDispAppSkill & SKILL_APPMASK_PHYSICAL_ABSORB)))
		{
			if(Character != NULL)
				Character->HoSkillCode = 0;

			Init();
			for(int index = 0; index < CHR_IN_EFFECT_OBJECT_MAX; index++)
			{
				if(ChrInEffectObject[index].object == (HoEffectObject *)this)
				{
					ChrInEffectObject[index].object = NULL;
					break;
				}
			}
		}
	}

	if(ShieldType == SKILL_SHIELD2)
	{
		static int shieldTwoCount = 0;
		if(UnderPat.GetState())
		{

			UnderPat.TranslateWorld(int(WorldX), int(WorldY - 1000), int(WorldZ));
			UnderPat.Main();
		}

		if(shieldTwoCount >= 20)
		{
			StartChildEffect(int(WorldX), int(WorldY + 3000), int(WorldZ), EFFECT_SHIELD2_PARTICLE, this);
			StartChildEffect(int(WorldX), int(WorldY - 2000), int(WorldZ), EFFECT_SHIELD2_PARTICLE);
			shieldTwoCount = 0;
		}
		shieldTwoCount++;

		EndCount++;
		if(EndCount >= 150 * 70 || ((Character != NULL) && !(Character->dwDispAppSkill & SKILL_APPMASK_AUTOMATION)))
		{
			if(Character != NULL)
				Character->HoSkillCode = 0;

			Init();
		}
	}

	return TRUE;
}

void HoEffectShield::SetUnderPat(smPAT3D *pat, int aniEnd)
{
	UnderPat.StartAni((int)WorldX, (int)WorldY, (int)WorldZ, 0, 0, 0, pat, ANI_LOOP);
	UnderPat.AnimationEnd = aniEnd;
}

int HoEffectShield::Start(int x, int y, int z, int shieldType, int angle, int circleRadius, smCHAR *character)
{
	if(StartFlag || character == NULL)
		return FALSE;



	char iniName[256];

	ShieldType = shieldType;
	if(shieldType == SKILL_SHIELD1)
	{
		memset(iniName, 0, sizeof(iniName));
		strcpy(iniName, "Shield1.ini");


		BackBillBoard.StartBillRect(x, y, z, "ShieldParticle1.ini", ANI_LOOP);
	}
	else if(shieldType == SKILL_SHIELD2)
	{
		memset(iniName, 0, sizeof(iniName));
		strcpy(iniName, "Shield2.ini");
	}

	EndCount = 0;
	Character = character;
	Character->HoSkillCode = SKILL_SHIELD1;

	memset(PosList, 0, sizeof(PosList));
	PosListCount = 0;
	DirectionAngle.x = angle;
	DirectionAngle.y = 0;
	DirectionAngle.z = angle;

	AniDataIndex = AnimDataMgr.GetSearchSequenceData(iniName);
	if(AniDataIndex == FALSE)
		return FALSE;
	Face2d.MatNum = AnimDataMgr.GetMaterialNum(AniDataIndex);
	if(Face2d.MatNum == -1)
		return FALSE;

	WorldX = (float)x;
	WorldY = (float)(Character->pY + 3000);
	WorldZ = (float)z;

	LocalX = 0;
	LocalY = 0;
	LocalZ = (float)circleRadius;

	StartFlag = TRUE;
	SizeWidth = 20;
	SizeHeight = 20;

	Face2d.x = (int)(WorldX + LocalX);
	Face2d.y = (int)(WorldX + LocalY);
	Face2d.z = (int)(WorldX + LocalZ);
	Face2d.TexRect.left = 0;
	Face2d.TexRect.top = 0;
	Face2d.TexRect.right = 1;
	Face2d.TexRect.bottom = 1;
	Face2d.width = (int)SizeWidth << FLOATNS;
	Face2d.height = (int)SizeHeight << FLOATNS;

	Face2d.Transparency = 255;
	Face2d.r = 255;
	Face2d.g = 255;
	Face2d.b = 255;

	CurrentBlendValue = (int)AnimDataMgr.SequenceDataBuffer[AniDataIndex].StartBlendValue;

	if(AnimDataMgr.SequenceDataBufferCount > 1)
	{

		CurrentBlendValue = AnimDataMgr.SequenceDataBuffer[AniDataIndex].StartBlendValue;
		BlendStep = (AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].AlphaValue - CurrentBlendValue) /
			AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay;
	}
	else
	{
		BlendStep = 0;
	}

	if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 0)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_COLOR;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 1)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_ALPHA;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 2)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_LAMP;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 3)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_SHADOW;

	Face2d.width = (int)(SizeWidth) << FLOATNS;
	Face2d.height = (int)(SizeHeight) << FLOATNS;



	return TRUE;
}



HoEffectPower::HoEffectPower()
{
	StartFlag = FALSE;
}

HoEffectPower::~HoEffectPower()
{

}


int HoEffectPower::Start(int x, int y, int z, int sw, int aniType, smCHAR *character)
{





	char iniName[32] = { 0, };
	if(sw == 1)
	{
		strcpy(iniName, "Power1.ini");
	}
	else
	{
		strcpy(iniName, "Power2.ini");
	}
	Skill_n = sw;







	Character = character;




	BackBillBoard.StartBillRect(x, y, z, iniName, aniType);

	StartFlag = TRUE;
	WorldX = (float)x;
	WorldY = (float)y;
	WorldZ = (float)z;

	LocalX = 0.f;
	LocalY = 0.f;
	LocalZ = 0.f;

	return TRUE;
}


int HoEffectPower::Main()
{
	if(StartFlag)
	{
		BackBillBoard.Main();



		BackBillBoard.TranslateWorld(int(WorldX), int(WorldY), int(WorldZ));
		static int count;
		if(count > 5)
		{
			count = 0;








			if(Skill_n == 1)
			{
				StartEffectMonster(int(WorldX), int(WorldY), int(WorldZ), MONSTER_PIGON_PARTICLE1);
			}
			else
			{
				StartEffectMonster(int(WorldX), int(WorldY), int(WorldZ), MONSTER_PIGON_PARTICLE2);
			}


		}
		count++;

		if(BackBillBoard.GetState() == FALSE)
			StartFlag = FALSE;
	}

	return TRUE;
}


int HoEffectPower::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag)
	{
		BackBillBoard.Draw(x, y, z, ax, ay, az);
	}
	return TRUE;
}

HoEffectHitLine::HoEffectHitLine()
{
	AniDataIndex = -1;
	StartFlag = FALSE;
	CurrentFrame = 0;


	delayCount = 0;
}

HoEffectHitLine::~HoEffectHitLine()
{

}




#ifndef KTJ_D2


int HoEffectHitLine::Main()
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;


	if(CurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(TimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay)
		{
			TimeCount = 0;
			CurrentFrame++;
			if(CurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount - 1)
				CurrentFrame = 1;
		}
		CurrentBlendValue = 250;
		TimeCount++;
	}



	if(DirectionAngle.y >= ANGLE_360)
	{
		delayCount++;

		CurrentBlendValue -= 30;
		if(delayCount > 5)
		{




			if(Skill_n == SKILL_TORNADO)
			{
				StartSkill(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), 0, 0, 0, SKILL_GREAT_SMASH);
			}
			else
			{
				StartSkill(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), 0, 0, 0, SKILL_GREAT_SMASH2);
			}

			StartFlag = FALSE;
			delayCount = 0;
		}
	}
	else
	{
		DirectionAngle.y += (ANGLE_360 / 30);
		GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, 0, DirectionAngle.y, 0);
		if(PosListCount < POS_LIST_MAX)
		{
			POINT3D tempPosList[POS_LIST_MAX - 1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;

			PosListCount++;
		}
		else
		{
			POINT3D tempPosList[POS_LIST_MAX - 1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;
		}
	}
	return TRUE;
}

#else

int HoEffectHitLine::Main()
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;



	cntM++;



	if(CurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(TimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay)
		{
			TimeCount = 0;
			CurrentFrame++;
			if(CurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount - 1)
				CurrentFrame = 1;
		}
		CurrentBlendValue = 250;
		TimeCount++;
	}



	if(cntM > 5)
	{
		cntM = 0;

		delayCount++;

		CurrentBlendValue -= 30;
		if(delayCount > 5)
		{





			if(Skill_n == SKILL_TORNADO)
			{
				StartSkill(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), 0, 0, 0, SKILL_GREAT_SMASH);
			}
			else
			{
				StartSkill(int(WorldX + LocalX), int(WorldY + LocalY), int(WorldZ + LocalZ), 0, 0, 0, SKILL_GREAT_SMASH2);
			}



			StartFlag = FALSE;
			delayCount = 0;
		}
	}
	else
	{







		if(cnt0 == 0)DirectionAngle.y += (ANGLE_360 / 30);





		GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, 0, DirectionAngle.y, 0);


		if(PosListCount < POS_LIST_MAX)
		{
			POINT3D tempPosList[POS_LIST_MAX - 1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));

			PosList[0].x = WorldX;
			PosList[0].y = WorldY;
			PosList[0].z = WorldZ;

			PosListCount++;
		}
		else
		{
			POINT3D tempPosList[POS_LIST_MAX - 1];
			memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
			memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;


			PosList[0].x = WorldX;
			PosList[0].y = WorldY;
			PosList[0].z = WorldZ;
		}


		if(cnt0 == 0)
		{
			PosList[0].x = GeoResult_X;
			PosList[0].y = GeoResult_Y;
			PosList[0].z = GeoResult_Z;
		}
		else
		{

			PosList[0].x = WorldX;
			PosList[0].y = WorldY;
			PosList[0].z = WorldZ;
		}



		cnt0++;
	}

	WorldX += (int)Vx;
	WorldY += (int)Vy;
	WorldZ += (int)Vz;

	return TRUE;
}
#endif







int HoEffectHitLine::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);

	smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AniDataIndex].GetMaterialNum()].TwoSide = TRUE;

	smMaterialGroup->SetMaterialAnimFrame(&smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()],
										  AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].ImageNum);


	smRender.SetCameraPosi(x, y, z, ax, ay, az);

	CreatePathFace();
	smRender.InitStageMesh(Vertex, SumCount);
	for(int index = 0; index < FaceCount; index++)
		smRender.AddStageFace(&Face[index]);

	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	smRender.RenderD3D();
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	SumCount++;
	return TRUE;
}

int HoEffectHitLine::CreatePathFace()
{


	memset(Vertex, 0, sizeof(Vertex));
	memset(Face, 0, sizeof(Face));
	memset(TexLink, 0, sizeof(TexLink));
	VertexCount = 0;
	FaceCount = 0;
	TexLinkCount = 0;

	POINT3D firstPos;
	POINT3D secondPos;

	for(int index = 0; index < PosListCount - 1; index++)
	{
		firstPos.x = int(PosList[index].x + WorldX);
		firstPos.y = int(PosList[index].y + WorldY);
		firstPos.z = int(PosList[index].z + WorldZ);

		secondPos.x = int(PosList[index + 1].x + WorldX);
		secondPos.y = int(PosList[index + 1].y + WorldY);
		secondPos.z = int(PosList[index + 1].z + WorldZ);

		int blendStep = CurrentBlendValue / ((PosListCount - 1) + 10);
		hoPOINT3D inVector;
		hoPOINT3D outVector;

		inVector.x = float(PosList[index].x + PosList[index + 1].x);
		inVector.y = float(PosList[index].y + PosList[index + 1].y);
		inVector.z = float(PosList[index].z + PosList[index + 1].z);

		double length = sqrt(inVector.x*inVector.x + inVector.y*inVector.y + inVector.z*inVector.z);
		inVector.x = float(inVector.x / length);
		inVector.y = float(inVector.y / length);
		inVector.z = float(inVector.z / length);


		outVector.x = -inVector.x;
		outVector.y = -inVector.y;
		outVector.z = -inVector.z;

		if(index == 0)
		{

			Vertex[VertexCount].x = int(firstPos.x + outVector.x*SizeHeight * 20);
			Vertex[VertexCount].y = int(firstPos.y + outVector.y*SizeHeight * 20 + 5000);
			Vertex[VertexCount].z = int(firstPos.z + outVector.z*SizeHeight * 20);
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 1].x = int(firstPos.x + inVector.x*SizeHeight * 20);
			Vertex[VertexCount + 1].y = int(firstPos.y + inVector.y*SizeHeight * 20);
			Vertex[VertexCount + 1].z = int(firstPos.z + inVector.z*SizeHeight * 20);
			Vertex[VertexCount + 1].sDef_Color[0] = 255;
			Vertex[VertexCount + 1].sDef_Color[1] = 255;
			Vertex[VertexCount + 1].sDef_Color[2] = 255;
			Vertex[VertexCount + 1].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;


			Vertex[VertexCount + 2].x = int(secondPos.x + outVector.x*SizeHeight * 20);
			Vertex[VertexCount + 2].y = int(secondPos.y + outVector.y*SizeHeight * 20 + 5000);
			Vertex[VertexCount + 2].z = int(secondPos.z + outVector.z*SizeHeight * 20);
			Vertex[VertexCount + 2].sDef_Color[0] = 255;
			Vertex[VertexCount + 2].sDef_Color[1] = 255;
			Vertex[VertexCount + 2].sDef_Color[2] = 255;
			Vertex[VertexCount + 2].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 3].x = int(secondPos.x + inVector.x*SizeHeight * 20);
			Vertex[VertexCount + 3].y = int(secondPos.y + inVector.y*SizeHeight * 20);
			Vertex[VertexCount + 3].z = int(secondPos.z + inVector.z*SizeHeight * 20);

			Vertex[VertexCount + 3].sDef_Color[0] = 255;
			Vertex[VertexCount + 3].sDef_Color[1] = 255;
			Vertex[VertexCount + 3].sDef_Color[2] = 255;
			Vertex[VertexCount + 3].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;
		}
		else
		{

			Vertex[VertexCount].x = Vertex[VertexCount - 2].x;
			Vertex[VertexCount].y = Vertex[VertexCount - 2].y;
			Vertex[VertexCount].z = Vertex[VertexCount - 2].z;
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 1].x = Vertex[VertexCount - 1].x;
			Vertex[VertexCount + 1].y = Vertex[VertexCount - 1].y;
			Vertex[VertexCount + 1].z = Vertex[VertexCount - 1].z;
			Vertex[VertexCount + 1].sDef_Color[0] = 255;
			Vertex[VertexCount + 1].sDef_Color[1] = 255;
			Vertex[VertexCount + 1].sDef_Color[2] = 255;
			Vertex[VertexCount + 1].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;


			Vertex[VertexCount + 2].x = int(secondPos.x + outVector.x*SizeHeight * 20);
			Vertex[VertexCount + 2].y = int(secondPos.y + outVector.y*SizeHeight * 20 + 5000);
			Vertex[VertexCount + 2].z = int(secondPos.z + outVector.z*SizeHeight * 20);
			Vertex[VertexCount + 2].sDef_Color[0] = 255;
			Vertex[VertexCount + 2].sDef_Color[1] = 255;
			Vertex[VertexCount + 2].sDef_Color[2] = 255;
			Vertex[VertexCount + 2].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 3].x = int(secondPos.x + inVector.x*SizeHeight * 20);
			Vertex[VertexCount + 3].y = int(secondPos.y + inVector.y*SizeHeight * 20);
			Vertex[VertexCount + 3].z = int(secondPos.z + inVector.z*SizeHeight * 20);

			Vertex[VertexCount + 3].sDef_Color[0] = 255;
			Vertex[VertexCount + 3].sDef_Color[1] = 255;
			Vertex[VertexCount + 3].sDef_Color[2] = 255;
			Vertex[VertexCount + 3].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;
		}




		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;

		TexLink[TexLinkCount].u[0] = (1.0f)*(float(index) / float(PosListCount));
		TexLink[TexLinkCount].v[0] = 0.0f;
		TexLink[TexLinkCount].u[1] = (1.0f)*(float(index) / float(PosListCount));
		TexLink[TexLinkCount].v[1] = 1.0f;
		TexLink[TexLinkCount].u[2] = (1.0f)*(float(index + 1) / float(PosListCount));
		TexLink[TexLinkCount].v[2] = 0.0f;

		TexLink[TexLinkCount + 1].hTexture = 0;
		TexLink[TexLinkCount + 1].NextTex = 0;
		TexLink[TexLinkCount + 1].u[0] = (1.0f)*(float(index + 1) / float(PosListCount));
		TexLink[TexLinkCount + 1].v[0] = 0.0f;
		TexLink[TexLinkCount + 1].u[1] = (1.0f)*(float(index) / float(PosListCount));
		TexLink[TexLinkCount + 1].v[1] = 1.0f;
		TexLink[TexLinkCount + 1].u[2] = (1.0f)*(float(index + 1) / float(PosListCount));
		TexLink[TexLinkCount + 1].v[2] = 1.0f;




		Face[FaceCount].Vertex[0] = VertexCount;
		Face[FaceCount].Vertex[1] = VertexCount + 1;
		Face[FaceCount].Vertex[2] = VertexCount + 2;
		Face[FaceCount].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount].lpTexLink = &TexLink[TexLinkCount];
		Face[FaceCount].sum = 0;

		Face[FaceCount + 1].Vertex[0] = VertexCount + 2;
		Face[FaceCount + 1].Vertex[1] = VertexCount + 1;
		Face[FaceCount + 1].Vertex[2] = VertexCount + 3;
		Face[FaceCount + 1].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount + 1].lpTexLink = &TexLink[TexLinkCount + 1];
		Face[FaceCount + 1].sum = 0;


		VertexCount += 4;
		FaceCount += 2;
		TexLinkCount += 2;
	}

	return TRUE;
}




int HoEffectHitLine::Start(int x, int y, int z, int destX, int destY, int destZ, int sw)
{




	cntM = 0;
	cnt0 = 0;


	char iniName[32] = { 0, };
	if(sw == 0)
	{
		strcpy(iniName, "SkillTornado.ini");
	}
	if(sw == 1)
	{
		strcpy(iniName, "SkillTornado2.ini");
	}


	if(sw == 2)
	{
		strcpy(iniName, "SkillTornado3.ini");
	}




	AniDataIndex = AnimDataMgr.GetSearchSequenceData(iniName);
	if(AniDataIndex == -1)
		return FALSE;

	WorldX = float(x);
	WorldY = float(y);
	WorldZ = float(z);

	LocalX = float(destX - x);
	LocalY = float(destY - y);
	LocalZ = float(destZ - z);






	if(sw == 2)
	{
		DestPos.x = destX;
		DestPos.y = destY;
		DestPos.z = destZ;
		LocalX = 0.f;
		LocalY = 0.f;
		LocalZ = 0.f;

		Vx = 0.f;
		Vy = 0.f;
		Vz = 0.f;

		POINT3D currentPos;
		currentPos.x = int(WorldX + LocalX);
		currentPos.y = int(WorldY + LocalY);
		currentPos.z = int(WorldZ + LocalZ);


		float vx = float(DestPos.x - currentPos.x);
		float vy = float(DestPos.y - currentPos.y);
		float vz = float(DestPos.z - currentPos.z);

		float length = (float)sqrt(vx*vx + vz*vz + vy*vy);

		Vx += vx / length * 1500;
		Vy += vy / length * 1500;
		Vz += vz / length * 1500;
	}












	memset(PosList, 0, sizeof(PosList));
	PosListCount = 0;

	DirectionAngle.x = 0;
	DirectionAngle.y = 0;
	DirectionAngle.z = 0;

	CurrentBlendValue = 200;
	TimeCount = 0;
	CurrentFrame = 0;
	SizeHeight = 170;
	StartFlag = TRUE;



	if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 0)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_COLOR;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 1)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_ALPHA;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 2)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_LAMP;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 3)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_SHADOW;
	return TRUE;
}


HoEffectStun::HoEffectStun()
{


	StartFlag = FALSE;
	Character = NULL;

}

HoEffectStun::~HoEffectStun()
{

}


int HoEffectStun::Start(int worldX, int worldY, int worldZ, smCHAR *character)
{



	char *iniName = "ContinueStun.ini";
	AniDataIndex = AnimDataMgr.GetSearchSequenceData(iniName);
	if(AniDataIndex == -1)
		return FALSE;

	WorldX = float(worldX);
	WorldY = float(worldY);
	WorldZ = float(worldZ);

	LocalX = 3000;
	LocalY = 0;
	LocalZ = 0;

	memset(PosList, 0, sizeof(PosList));
	PosListCount = 0;

	DirectionAngle.x = 0;
	DirectionAngle.y = 0;
	DirectionAngle.z = 0;

	CurrentBlendValue = 200;
	TimeCount = 0;
	CurrentFrame = 0;
	SizeHeight = 10;
	StartFlag = TRUE;



	if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 0)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_COLOR;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 1)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_ALPHA;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 2)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_LAMP;
	else if(AnimDataMgr.SequenceDataBuffer[AniDataIndex].BlendType == 3)
		smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()].BlendType = SMMAT_BLEND_SHADOW;

	Character = character;
	return TRUE;
}

int HoEffectStun::Main()
{


	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;


	if(CurrentFrame < AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount)
	{
		if(TimeCount >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].Delay)
		{
			TimeCount = 0;
			CurrentFrame++;
			if(CurrentFrame >= AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrameCount - 1)
				CurrentFrame = 1;
		}
		CurrentBlendValue = 250;
		TimeCount++;
	}



	WorldX = float(Character->pX);
	WorldY = float(Character->pY + 10000);
	WorldZ = float(Character->pZ);

	DirectionAngle.y += (ANGLE_360 / 50);
	GetMoveLocation((int)LocalX, (int)(LocalY), (int)LocalZ, 0, DirectionAngle.y, 0);
	if(PosListCount < STUN_POS_LIST_MAX)
	{
		POINT3D tempPosList[STUN_POS_LIST_MAX - 1];
		memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
		memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
		PosList[0].x = GeoResult_X;
		PosList[0].y = GeoResult_Y;
		PosList[0].z = GeoResult_Z;

		PosListCount++;
	}
	else
	{
		POINT3D tempPosList[STUN_POS_LIST_MAX - 1];
		memcpy(tempPosList, &PosList[0], sizeof(tempPosList));
		memcpy(&PosList[1], tempPosList, sizeof(tempPosList));
		PosList[0].x = GeoResult_X;
		PosList[0].y = GeoResult_Y;
		PosList[0].z = GeoResult_Z;
	}
	return TRUE;
}


int HoEffectStun::Draw(int x, int y, int z, int ax, int ay, int az)
{



	if(StartFlag == FALSE || AniDataIndex == -1)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);

	smMaterialGroup->smMaterial[AnimDataMgr.ImageDataBuffer[AniDataIndex].GetMaterialNum()].TwoSide = TRUE;

	smMaterialGroup->SetMaterialAnimFrame(&smMaterial[AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum()],
										  AnimDataMgr.SequenceDataBuffer[AniDataIndex].AnimFrame[CurrentFrame].ImageNum);


	smRender.SetCameraPosi(x, y, z, ax, ay, az);

	CreatePathFace();
	smRender.InitStageMesh(Vertex, SumCount);
	for(int index = 0; index < FaceCount; index++)
		smRender.AddStageFace(&Face[index]);

	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	smRender.RenderD3D();
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	SumCount++;

	return TRUE;
}

int HoEffectStun::CreatePathFace()
{


	memset(Vertex, 0, sizeof(Vertex));
	memset(Face, 0, sizeof(Face));
	memset(TexLink, 0, sizeof(TexLink));
	VertexCount = 0;
	FaceCount = 0;
	TexLinkCount = 0;

	POINT3D firstPos;
	POINT3D secondPos;

	for(int index = 0; index < PosListCount - 1; index++)
	{
		firstPos.x = int(PosList[index].x + WorldX);
		firstPos.y = int(PosList[index].y + WorldY);
		firstPos.z = int(PosList[index].z + WorldZ);

		secondPos.x = int(PosList[index + 1].x + WorldX);
		secondPos.y = int(PosList[index + 1].y + WorldY);
		secondPos.z = int(PosList[index + 1].z + WorldZ);

		int blendStep = CurrentBlendValue / ((PosListCount - 1) + 10);
		hoPOINT3D inVector;
		hoPOINT3D outVector;

		inVector.x = float(PosList[index].x + PosList[index + 1].x);
		inVector.y = float(PosList[index].y + PosList[index + 1].y);
		inVector.z = float(PosList[index].z + PosList[index + 1].z);

		double length = sqrt(inVector.x*inVector.x + inVector.y*inVector.y + inVector.z*inVector.z);
		inVector.x = float(inVector.x / length);
		inVector.y = float(inVector.y / length);
		inVector.z = float(inVector.z / length);


		outVector.x = -inVector.x;
		outVector.y = -inVector.y;
		outVector.z = -inVector.z;

		if(index == 0)
		{

			Vertex[VertexCount].x = int(firstPos.x + outVector.x*SizeHeight * 20);
			Vertex[VertexCount].y = int(firstPos.y + outVector.y*SizeHeight * 20 + 1400);
			Vertex[VertexCount].z = int(firstPos.z + outVector.z*SizeHeight * 20);
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 1].x = int(firstPos.x + inVector.x*SizeHeight * 20);
			Vertex[VertexCount + 1].y = int(firstPos.y + inVector.y*SizeHeight * 20);
			Vertex[VertexCount + 1].z = int(firstPos.z + inVector.z*SizeHeight * 20);
			Vertex[VertexCount + 1].sDef_Color[0] = 255;
			Vertex[VertexCount + 1].sDef_Color[1] = 255;
			Vertex[VertexCount + 1].sDef_Color[2] = 255;
			Vertex[VertexCount + 1].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;


			Vertex[VertexCount + 2].x = int(secondPos.x + outVector.x*SizeHeight * 20);
			Vertex[VertexCount + 2].y = int(secondPos.y + outVector.y*SizeHeight * 20 + 1400);
			Vertex[VertexCount + 2].z = int(secondPos.z + outVector.z*SizeHeight * 20);
			Vertex[VertexCount + 2].sDef_Color[0] = 255;
			Vertex[VertexCount + 2].sDef_Color[1] = 255;
			Vertex[VertexCount + 2].sDef_Color[2] = 255;
			Vertex[VertexCount + 2].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 3].x = int(secondPos.x + inVector.x*SizeHeight * 20);
			Vertex[VertexCount + 3].y = int(secondPos.y + inVector.y*SizeHeight * 20);
			Vertex[VertexCount + 3].z = int(secondPos.z + inVector.z*SizeHeight * 20);

			Vertex[VertexCount + 3].sDef_Color[0] = 255;
			Vertex[VertexCount + 3].sDef_Color[1] = 255;
			Vertex[VertexCount + 3].sDef_Color[2] = 255;
			Vertex[VertexCount + 3].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;
		}
		else
		{

			Vertex[VertexCount].x = Vertex[VertexCount - 2].x;
			Vertex[VertexCount].y = Vertex[VertexCount - 2].y;
			Vertex[VertexCount].z = Vertex[VertexCount - 2].z;
			Vertex[VertexCount].sDef_Color[0] = 255;
			Vertex[VertexCount].sDef_Color[1] = 255;
			Vertex[VertexCount].sDef_Color[2] = 255;
			Vertex[VertexCount].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 1].x = Vertex[VertexCount - 1].x;
			Vertex[VertexCount + 1].y = Vertex[VertexCount - 1].y;
			Vertex[VertexCount + 1].z = Vertex[VertexCount - 1].z;
			Vertex[VertexCount + 1].sDef_Color[0] = 255;
			Vertex[VertexCount + 1].sDef_Color[1] = 255;
			Vertex[VertexCount + 1].sDef_Color[2] = 255;
			Vertex[VertexCount + 1].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;


			Vertex[VertexCount + 2].x = int(secondPos.x + outVector.x*SizeHeight * 20);
			Vertex[VertexCount + 2].y = int(secondPos.y + outVector.y*SizeHeight * 20 + 1400);
			Vertex[VertexCount + 2].z = int(secondPos.z + outVector.z*SizeHeight * 20);
			Vertex[VertexCount + 2].sDef_Color[0] = 255;
			Vertex[VertexCount + 2].sDef_Color[1] = 255;
			Vertex[VertexCount + 2].sDef_Color[2] = 255;
			Vertex[VertexCount + 2].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;

			Vertex[VertexCount + 3].x = int(secondPos.x + inVector.x*SizeHeight * 20);
			Vertex[VertexCount + 3].y = int(secondPos.y + inVector.y*SizeHeight * 20);
			Vertex[VertexCount + 3].z = int(secondPos.z + inVector.z*SizeHeight * 20);

			Vertex[VertexCount + 3].sDef_Color[0] = 255;
			Vertex[VertexCount + 3].sDef_Color[1] = 255;
			Vertex[VertexCount + 3].sDef_Color[2] = 255;
			Vertex[VertexCount + 3].sDef_Color[3] = (int)CurrentBlendValue - index*blendStep;
		}




		TexLink[TexLinkCount].hTexture = 0;
		TexLink[TexLinkCount].NextTex = 0;

		TexLink[TexLinkCount].u[0] = (1.0f)*(float(index) / float(PosListCount));
		TexLink[TexLinkCount].v[0] = 0.0f;
		TexLink[TexLinkCount].u[1] = (1.0f)*(float(index) / float(PosListCount));
		TexLink[TexLinkCount].v[1] = 1.0f;
		TexLink[TexLinkCount].u[2] = (1.0f)*(float(index + 1) / float(PosListCount));
		TexLink[TexLinkCount].v[2] = 0.0f;

		TexLink[TexLinkCount + 1].hTexture = 0;
		TexLink[TexLinkCount + 1].NextTex = 0;
		TexLink[TexLinkCount + 1].u[0] = (1.0f)*(float(index + 1) / float(PosListCount));
		TexLink[TexLinkCount + 1].v[0] = 0.0f;
		TexLink[TexLinkCount + 1].u[1] = (1.0f)*(float(index) / float(PosListCount));
		TexLink[TexLinkCount + 1].v[1] = 1.0f;
		TexLink[TexLinkCount + 1].u[2] = (1.0f)*(float(index + 1) / float(PosListCount));
		TexLink[TexLinkCount + 1].v[2] = 1.0f;




		Face[FaceCount].Vertex[0] = VertexCount;
		Face[FaceCount].Vertex[1] = VertexCount + 1;
		Face[FaceCount].Vertex[2] = VertexCount + 2;
		Face[FaceCount].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount].lpTexLink = &TexLink[TexLinkCount];
		Face[FaceCount].sum = 0;

		Face[FaceCount + 1].Vertex[0] = VertexCount + 2;
		Face[FaceCount + 1].Vertex[1] = VertexCount + 1;
		Face[FaceCount + 1].Vertex[2] = VertexCount + 3;
		Face[FaceCount + 1].Vertex[3] = AnimDataMgr.ImageDataBuffer[AnimDataMgr.SequenceDataBuffer[AniDataIndex].DataFileIndex].GetMaterialNum();
		Face[FaceCount + 1].lpTexLink = &TexLink[TexLinkCount + 1];
		Face[FaceCount + 1].sum = 0;


		VertexCount += 4;
		FaceCount += 2;
		TexLinkCount += 2;
	}

	return TRUE;
}

