







#ifndef _HO_EFFECT_VIEW_H_
#define _HO_EFFECT_VIEW_H_
#include "math\\mathGlobal.h"
#include "math\\point3.h"
#include "math\\color4.h"

#include "HoNewEffectHeader.h"
#ifndef _HO_NEW_WIN32_
#include ".\\smlib3d\\smd3d.h"
#endif

#ifdef  _HO_NEW_WIN32_
#include "..\\..\\smlib3d\\smd3d.h"
#endif

#include <list>
enum
{
    BILLBOARD_DEFAULT,
    BILLBOARD_AXIAL,
    CREATE_MESH,
};

class SBillboardRenderInfo
{
public:
    int     m_Type;
    point3  m_Pos;    
    point3  m_DesPos;
    point3  m_Size;   
    point3  m_Angle;  
    color4  m_Color;  

    int     m_MatID;
    int     m_iBlendType;
    SBillboardRenderInfo() : m_Type(BILLBOARD_DEFAULT),
                             m_Pos(0.f, 0.f, 0.f),
                             m_DesPos(0.f, 0.f, 0.f),
                             m_Size(0.f, 0.f, 0.f),
                             m_Angle(0.f, 0.f, 0.f),
                             m_Color(1.f, 1.f, 1.f, 1.f),
                             m_iBlendType(SMMAT_BLEND_LAMP){};
};

class SMeshRenderInfo
{
public:
    point3	m_Pos;     
    point3	m_Scale;   
    point3	m_Angle;   
    color4	m_Color;
    int		m_iCurrentFrame;
    smPAT3D *m_Pat;
    int     m_iBlendType;
    SMeshRenderInfo() : m_Pos(0.f, 0.f, 0.f),
                        m_Scale(0.f, 0.f, 0.f),
                        m_Angle(0.f, 0.f, 0.f),
                        m_Color(1.f, 1.f, 1.f, 1.f),
                        m_iCurrentFrame(0),
                        m_iBlendType(SMMAT_BLEND_LAMP){};
};

class SLineListRenderInfo
{
public:
	int					m_iBlendType;
	color4				m_Color;
	point3				m_Size;
	std::list<point3>   *m_pList;
	
	int					m_MatID;
	SLineListRenderInfo() : m_Color(1.f, 1.f, 1.f, 1.f),
		                    m_Size(2.f, 2.f, 0.f),
							m_MatID(-1),
							m_pList(NULL),
		                    m_iBlendType(SMMAT_BLEND_LAMP){};
};

class HoEffectView
{
public:
    HoEffectView();
    ~HoEffectView();
public:
    static bool UpdateBillboard(const SBillboardRenderInfo *renderInfo, int ix, int iy, int iz, int ax, int ay, int az);
    static bool UpdateMesh(const SMeshRenderInfo *renderInfo, int iX, int iY, int iZ, int ax, int ay, int az);
	static bool UpdateLineList(const SLineListRenderInfo *renderInfo, int ix, int iy, int iz, int ax, int ay, int az);
};

#endif



