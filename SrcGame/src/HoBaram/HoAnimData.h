

#ifndef _HO_ANIM_DATA_
#define _HO_ANIM_DATA_


#define INFO_NONE				0x00000000
#define	INFO_IMAGE				0x00000001
#define	INFO_DELAY				0x00000002
#define INFO_ALPHA				0x00000004


#define	INFO_SIZEWIDTH			0x00000008


#define INFO_ANGLE				0x00000010
#define	INFO_SIZEHEIGHT			0x00000020
#define INFO_RGB				0x00000040

#define INFO_DEFAULT			(INFO_IMAGE | INFO_DELAY | INFO_ALPHA)
#define INFO_ONESIZE			(INFO_IMAGE | INFO_DELAY | INFO_ALPHA | INFO_SIZEWIDTH)
#define INFO_ONESIZEANGLE		(INFO_IMAGE | INFO_DELAY | INFO_ALPHA | INFO_SIZEWIDTH | INFO_ANGLE)

struct hoAnimFrame
{

	unsigned short ImageNum;
	unsigned short Delay;
	BYTE AlphaValue;


	unsigned short SizeWidth;


	unsigned short SizeHeight;
	float Angle;
	BYTE ColorRValue;
	BYTE ColorGValue;
	BYTE ColorBValue;
};

class HoAnimDataMgr;

class HoAnimSequenceData
{
public:
	HoAnimSequenceData();
	~HoAnimSequenceData();

	hoAnimFrame *AnimFrame;
	int			AnimFrameCount;
	int			StartBlendValue;
	int			BlendType;

public:
	int  DataFileIndex;
	char IniName[64];

private:
	BYTE		InfoFlag;


public:
	int Load(char *iniName, HoAnimDataMgr *animationData = NULL);
	int Init();

	BYTE GetAnimInfo()
	{
		if(InfoFlag == INFO_DEFAULT)
		{
			return INFO_DEFAULT;
		}
		else if(InfoFlag == INFO_ONESIZE)
		{
			return INFO_ONESIZE;
		}
		else if(InfoFlag == INFO_ONESIZEANGLE)
		{
			return INFO_ONESIZEANGLE;
		}

		return INFO_NONE;
	}
};


class HoAnimImageData
{
private:
	int  MaterialNum;
	int	 AnimationCount;

public:
	char IniName[64];

	HoAnimImageData();
	~HoAnimImageData();

	char *GetIniName()
	{
		return IniName;
	}
	int Load(char *iniName);
	int GetAnimationCount()
	{
		return AnimationCount;
	}
	int GetMaterialNum()
	{
		return MaterialNum;
	}
	int Init();

private:
	int Load(char *textureName, int count);

};


#define MAX_IMAGEDATA_BUFFER	100
#define MAX_SEQUENCEDATA_BUFFER	100
class HoAnimDataMgr
{
public:
	HoAnimDataMgr();
	~HoAnimDataMgr();

	int SequenceLoad(char *iniName);
	int	ImageLoad(char *iniName);

public:
	HoAnimSequenceData SequenceDataBuffer[MAX_SEQUENCEDATA_BUFFER];
	int				   SequenceDataBufferCount;

	HoAnimImageData    ImageDataBuffer[MAX_IMAGEDATA_BUFFER];
	int				   ImageDataBufferCount;


	int	GetSearchSequenceData(char *iniName);
	int	GetSearchAnimImageData(char *iniName);

	int	Init();


	int GetMaterialNum(int aniDataIndex)
	{
		if(aniDataIndex >= 0 && aniDataIndex < SequenceDataBufferCount)
			return ImageDataBuffer[SequenceDataBuffer[aniDataIndex].DataFileIndex].GetMaterialNum();

		return -1;
	}
};
extern HoAnimDataMgr AnimDataMgr;

#endif
