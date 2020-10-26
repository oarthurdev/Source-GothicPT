







#ifndef _HO_EFFECT_MODEL_H_
#define _HO_EFFECT_MODEL_H_
#include "math\\mathGlobal.h"
#include "math\\point3.h"
#include "math\\color4.h"
#include "math\\matrix4.h"
#include <vector>
#include <string>
#include <list>
enum EffectType
{
    CLASS_EFFECT_NONE,
    CLASS_EFFECT_PARENT,
    CLASS_EFFECT_MESH,
    CLASS_EFFECT_TEXTURE,
    CLASS_EFFECT_BILLBOARD,
    CLASS_EFFECT_CREATE_MESH,
    CLASS_EFFECT_BILLBOARD_AXIAL,
    CLASS_EFFECT_PARTICLE_SYSTEM,
};


class HoEffectTextureNameProperty
{
public:
    HoEffectTextureNameProperty() : m_iAniIndex(0),
                                    m_iAniIndexCount(0),
                                    m_fAniTimer(0.f),
                                    m_fAniDelayTime(0.5f) {};
    ~HoEffectTextureNameProperty() {Clear();};
private:
    int     m_iAniIndex;
    int     m_iAniIndexCount;
    float   m_fAniDelayTime;
    float   m_fAniTimer;

    std::vector<std::string> m_TextureName;
public:
    bool    Main(float elapsedTime);
    void    Init(const std::string &fileName);
    void    Init(const std::string &fileName, int textureCount, float aniDelayTime);
    int     GetMatNum();
    void    Clear();
};

class HoEffectEventInterface;
class HoEffectModelInterface
{
public:
    HoEffectModelInterface();
    virtual ~HoEffectModelInterface() {};

    color4  m_Color;
    color4  m_ColorStep;

    point3  m_Size;
    point3  m_SizeStep;

    point3  m_Translate;
    point3  m_TranslateStep;

	point3  m_Angle;
	point3  m_AngleStep;

    int     m_iBlendType;
    bool    m_bLiveFlag;

    float   m_fEndTime;
    float   m_fStartDelayTime;

    float   m_fEventTimer;
    float   m_fTimer;
    int     m_iClassID;
	//std::vector < HoEffectEventInterface *>::iterator m_CurrentEvent;

	int currentEvent; // Index of the current Event

	//std::_Array_iterator<HoEffectEventInterface *, 100U> m_CurrentEvent;

	//bool is_CurrentEvent;

public:
    void    Init();
    void    SetColor(const color4 &color)         { m_Color = color; };
    void    SetColorStep(const color4 &colorStep) { m_ColorStep = colorStep; }
    void    SetSize(const point3 &size)           { m_Size = size; }
    void    SetSizeStep(const point3 &sizeStep)   { m_SizeStep = sizeStep; }
    void    SetTranslate(const point3 &translate) { m_Translate = translate; }
    void    SetTranslateStep(const point3 &translateStep) { m_TranslateStep = translateStep; }
	void	SetAngle(const point3 &angle)         { m_Angle = angle; }
	void	SetAngleStep(const point3 &angleStep)  { m_AngleStep = angleStep; }

    void    SetBlendType(int type)                { m_iBlendType = type; }
    void    SetLive(bool flag)                    { m_bLiveFlag = flag; }

    void    SetEndTime(float endTime)             { m_fEndTime = endTime; }
    void    SetStartDelayTime(float delayTime)    { m_fStartDelayTime = delayTime; }

    void    SetEventTimer(float time)             { m_fEventTimer = time; }
    void    SetTimer(float time)                  { m_fTimer = time; }

   // void    SetCurrentTime(std::vector < HoEffectEventInterface *>::iterator currentEvent)
	//void    SetCurrentTime(std::_Array_iterator<HoEffectEventInterface *, 100U> currentEvent)
	void SetCurrentTime(int currentEvent)
	{ 
		this->currentEvent = currentEvent;
	}

    void    SetClassID(int classID)               { m_iClassID = classID; }
    const   color4 &GetColor()                      { return m_Color; }
    const   color4 &GetColorStep()                  { return m_ColorStep;}
    const   point3 &GetSize()                       { return m_Size;}
    const   point3 &GetSizeStep()                   { return m_SizeStep;}
    const   point3 &GetTranslate()                  { return m_Translate;}
    const   point3 &GetTranslateStep()              { return m_TranslateStep;}

    int     GetBlendType(int type)                  { return m_iBlendType;}
    bool    IsLive()                                { return m_bLiveFlag;}

    float   GetEndTime(float endTime)               { return m_fEndTime;}
    float   GetStartDelayTime(float delayTime)      { return m_fStartDelayTime;}

    float   GetEventTimer(float time)               { return m_fEventTimer;}
    float   GetTimer(float time)                    { return m_fTimer;}

   // std::vector < HoEffectEventInterface *>::iterator &GetCurrentTime() { return m_CurrentEvent;}
	//std::_Array_iterator<HoEffectEventInterface *, 100U>  &GetCurrentTime()

	int &GetCurrentTime()
	{
		return currentEvent;
	}

};


class HoEffectTextureModel : public HoEffectModelInterface
{
public:
    HoEffectTextureModel() : m_Direction(0.f, 1.f, 0.f)
                             { m_iClassID  = CLASS_EFFECT_BILLBOARD;
                               m_bLiveFlag = false;}
public:
    HoEffectTextureNameProperty m_TextureNameProperty;
    point3                      m_Direction;            
public:
    void    Init();
    void    Init(const std::string &fileName);
    void    Init(const std::string &fileName, int textureCount, float aniDelayTime);
    bool    UpdateView(int x, int y, int z, int ax, int ay, int az);
};


class HoEffectBillboardAxialModel : public HoEffectModelInterface
{
public:
    HoEffectBillboardAxialModel() : m_CurPos(0.f, 0.f, 0.f),
                                    m_DesPos(0.f, 100.f, 0.f)
                                    {m_Size.Assign(10.f, 100.f, 50.f);};
    ~HoEffectBillboardAxialModel() {};
    
    point3  m_CurPos;
    point3  m_DesPos;

    HoEffectTextureNameProperty m_TextureNameProperty;
public:
    void    Init(const std::string &fileName);
    void    Init(const std::string &fileName, int textureCount, float aniDelayTime);
    bool    UpdateView(int x, int y, int z, int ax, int ay, int az);
};

class HoEffectLineListModel : public HoEffectModelInterface
{
public:
	HoEffectLineListModel() : m_iMaxCount(20){ SetColor(color4(100.f, 100.f, 100.f, 100.f));};
	~HoEffectLineListModel() { m_TraceList.clear(); };
private:
	std::list<point3>	m_TraceList;
	unsigned int		m_iMaxCount;
public:
	HoEffectTextureNameProperty m_TextureNameProperty;
public:
	void	Init(const std::string &fileName);
	void	AddData(const point3 &pos);

	bool	UpdateView(int x, int y, int z, int ax, int ay, int az);
};

class HoEffectMeshModel : public HoEffectModelInterface
{
public:
    HoEffectMeshModel() : m_fCurrentFrame(0) {};
    ~HoEffectMeshModel() {};
    float   m_fCurrentFrame;            
    int     m_iMaxFrame;                

    std::string m_MeshName;
    std::string m_BoneName;
public:
    void    Init(const std::string &meshName);
    void    Init(const std::string &meshName, const std::string &boneName);
    bool    UpdateView(int x, int y, int z, int ax, int ay, int az);
};

#endif

