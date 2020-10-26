#include "HoEffectModel.h"
#include "HoEffectView.h"
#include "HoEffectResMgr.h"

void HoEffectTextureNameProperty::Init(const std::string &fileName)
{
	Clear();
    m_TextureName.push_back(fileName);
	unsigned int testCount = m_TextureName.size();
}

void HoEffectTextureNameProperty::Init(const std::string &fileName, int textureCount, float aniDelayTime)
{
	Clear();
    m_iAniIndexCount = textureCount;
    m_fAniDelayTime = aniDelayTime;
    m_iAniIndex = 0;
	unsigned int testCount = m_TextureName.size();
    for(int i = 0; i < m_iAniIndexCount; i++)
    {
        char buffer[256];
        char extName[64];
        strcpy(buffer, fileName.c_str());
        int index;
        for(index = strlen(buffer); index >= 0; index--)
        {
            if(buffer[index] == '.')
            {
                buffer[index] = 0;
                break;
            }
        }
        strcpy(extName, &buffer[index+1]);
        char tempBuffer[256];
        if(stricmp(extName, "bmp") == 0)
            wsprintf(tempBuffer, "%s%d%s",buffer,i+1, ".bmp");
        else
            wsprintf(tempBuffer, "%s%d%s",buffer,i+1, ".tga");

        std::string textureNewName = tempBuffer;
        m_TextureName.push_back(textureNewName);
    }
}

bool HoEffectTextureNameProperty::Main(float elapsedTime)
{
    if(m_iAniIndexCount > 0)
    {
          if(m_fAniTimer > m_fAniDelayTime)
        {
            m_iAniIndex++; 
            m_fAniTimer = 0.f;
             if(m_iAniIndex >= m_iAniIndexCount)
                m_iAniIndex = 0;
        }
		else
			m_fAniTimer += elapsedTime;
	}
    else
        return false;

    return true;
}

int HoEffectTextureNameProperty::GetMatNum()
{
     int matNum = -1;
	 char testBuffer[256];
	 strcpy(testBuffer, m_TextureName[m_iAniIndex].c_str() );
 	 matNum = HoEffectResManager::GetInstance()->GetResTexture(m_TextureName[m_iAniIndex]);
    return matNum;
}

void HoEffectTextureNameProperty::Clear()
{
    m_TextureName.clear();
}

HoEffectModelInterface::HoEffectModelInterface() : m_Color(255.f, 255.f, 255.f, 255.f),
                                                   m_ColorStep(0.f, 0.f, 0.f, 0.f),
                                                   m_Size(20.f, 20.f, 20.f),
                                                   m_SizeStep(0.f, 0.f, 0.f),
                                                   m_Translate(0.f, 0.f, 0.f),
                                                   m_TranslateStep(0.f, 0.f, 0.f),
												   m_Angle(0.f, 0.f, 0.f),
												   m_AngleStep(0.f, 0.f, 0.f),
                                                   m_fTimer(0.f),
                                                   m_iBlendType(SMMAT_BLEND_LAMP),
                                                   m_fEventTimer(0.f),
                                                   m_CurrentEvent(),
                                                   m_bLiveFlag(true),
                                                   m_fEndTime(0.f),
                                                   m_fStartDelayTime(0.f)
{
}

void HoEffectModelInterface::Init()
{
    m_Color.Assign(255.f, 255.f, 255.f, 255.f);
    m_ColorStep.Assign(0.f, 0.f, 0.f, 0.f);
    m_Size.Assign(20.f, 20.f, 20.f);
    m_SizeStep.Assign(0.f, 0.f, 0.f);
    m_Translate.Assign(0.f, 0.f, 0.f);
    m_TranslateStep.Assign(0.f, 0.f, 0.f);
    m_fTimer = 0.f;
    m_iBlendType = SMMAT_BLEND_LAMP;
    m_fEventTimer = 0.f;
	*( int* )&m_CurrentEvent = NULL;
    m_bLiveFlag = true;
    m_fEndTime = 0.f;
    m_fStartDelayTime = 0.f;
}

void HoEffectTextureModel::Init()
{
    HoEffectModelInterface::Init();
    m_Direction.Assign(0.f, 1.f, 0.f);
    m_bLiveFlag = false;
}

void HoEffectTextureModel::Init(const std::string &fileName)
{
    m_TextureNameProperty.Init(fileName);
}

void HoEffectTextureModel::Init(const std::string &fileName, int textureCount, float aniDelayTime)
{
    m_TextureNameProperty.Init(fileName, textureCount, aniDelayTime);
}

bool HoEffectTextureModel::UpdateView(int x, int y, int z, int ax, int ay, int az)
{
    int matNum = -1;
    matNum = m_TextureNameProperty.GetMatNum();

    if(matNum == -1)
        return false;

    if(m_iClassID == CLASS_EFFECT_BILLBOARD)
    {
        SBillboardRenderInfo renderInfo;
        renderInfo.m_Pos   = m_Translate;
        renderInfo.m_Size  = m_Size;
        renderInfo.m_Color = m_Color;
        renderInfo.m_MatID = matNum;
        HoEffectView::UpdateBillboard(&renderInfo, x, y, z, ax, ay, az);
    }
    else if(m_iClassID == CLASS_EFFECT_CREATE_MESH)
    {
        SBillboardRenderInfo renderInfo;
        renderInfo.m_Type   = CREATE_MESH;
        renderInfo.m_Pos    = m_Translate;
        renderInfo.m_Size   = m_Size;
        renderInfo.m_Color  = m_Color;
		
        renderInfo.m_MatID  = matNum;
        HoEffectView::UpdateBillboard(&renderInfo, x, y, z, ax, ay, az);
    }
    else if(m_iClassID == CLASS_EFFECT_BILLBOARD_AXIAL)
    {
        SBillboardRenderInfo renderInfo;
        renderInfo.m_Type   = BILLBOARD_AXIAL;
        renderInfo.m_Pos    = m_Translate + m_Direction;
        renderInfo.m_DesPos = m_Translate + m_Direction * m_Size.y;
        renderInfo.m_Size   = m_Size;
        renderInfo.m_Color  = m_Color;
        renderInfo.m_MatID  = matNum;
        HoEffectView::UpdateBillboard(&renderInfo, x, y, z, ax, ay, az);
    }
    return true;
}

void HoEffectBillboardAxialModel::Init(const std::string &fileName)
{
    m_TextureNameProperty.Init(fileName);
}

void HoEffectBillboardAxialModel::Init(const std::string &fileName, int textureCount, float aniDelayTime)
{
    m_TextureNameProperty.Init(fileName, textureCount, aniDelayTime);
}

bool HoEffectBillboardAxialModel::UpdateView(int x, int y, int z, int ax, int ay, int az)
{
    int matNum = -1;
    matNum = m_TextureNameProperty.GetMatNum();

    if(matNum == -1)
        return false;
    SBillboardRenderInfo renderInfo;
    renderInfo.m_Type   = BILLBOARD_AXIAL;
    renderInfo.m_Pos    = m_CurPos+m_Translate;
    renderInfo.m_DesPos = m_DesPos+m_Translate;
    renderInfo.m_Size   = m_Size;
    renderInfo.m_Color  = m_Color;
    renderInfo.m_MatID  = matNum;
    HoEffectView::UpdateBillboard(&renderInfo, x, y, z, ax, ay, az);
    return true;
}

void HoEffectLineListModel::Init(const std::string &fileName)
{
	m_TextureNameProperty.Init(fileName);
}

void HoEffectLineListModel::AddData(const point3 &pos)
{
	int t = m_TraceList.size();
	if(m_TraceList.size() < m_iMaxCount)
		m_TraceList.push_front(pos);
	else
    {
		if(!m_TraceList.empty())
        {
			std::list<point3>::iterator i;
			i = m_TraceList.end();
            --i;
            m_TraceList.erase(i);
			m_TraceList.push_front(pos);
		}
	}
}

bool HoEffectLineListModel::UpdateView(int x, int y, int z, int ax, int ay, int az)
{
	int matNum = -1;
    matNum = m_TextureNameProperty.GetMatNum();

    if(matNum == -1)
        return false;

	SLineListRenderInfo renderInfo;
	renderInfo.m_Size       = m_Size;
	renderInfo.m_Color      = m_Color;
	renderInfo.m_MatID      = matNum;
    renderInfo.m_iBlendType = m_iBlendType;
	renderInfo.m_pList      = &m_TraceList;
	HoEffectView::UpdateLineList(&renderInfo, x, y, z, ax, ay, az);
	return true;	
}


void HoEffectMeshModel::Init(const std::string &meshName)
{
    m_MeshName = meshName;
    m_bLiveFlag = true;
}

void HoEffectMeshModel::Init(const std::string &meshName, const std::string &boneName)
{
    m_MeshName = meshName;
    m_BoneName = boneName;
    m_bLiveFlag = true;
}

bool HoEffectMeshModel::UpdateView(int x, int y, int z, int ax, int ay, int az)
{
    if(m_bLiveFlag == false)
        return false;
    smPAT3D *pat3D = HoEffectResManager::GetInstance()->GetResMesh(m_MeshName, m_BoneName);
    if(pat3D == NULL)
        return false;
	
	SMeshRenderInfo renderInfo;
    renderInfo.m_Pos           = m_Translate;
	renderInfo.m_Angle         = m_Angle;
    renderInfo.m_Pat           = pat3D;
    renderInfo.m_Color         = m_Color;
    renderInfo.m_iBlendType    = m_iBlendType;
    renderInfo.m_iCurrentFrame = (int)m_fCurrentFrame;
    HoEffectView::UpdateMesh(&renderInfo, x, y, z, ax, ay, az);
    return true;
}







