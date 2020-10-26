#include "HoEffectResMgr.h"
HoEffectResTexture::HoEffectResTexture()
{
}

HoEffectResTexture::~HoEffectResTexture()
{
}

bool HoEffectResTexture::LoadingRes(const std::string &fileName)
{
    char tempBuffer[128];
    strcpy(tempBuffer, fileName.c_str());

    m_iMatNum = CreateTextureMaterial(tempBuffer, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
    smMaterialGroup->ReadTextures();

    return true;
}

int HoEffectResTexture::GetRes()
{
    return m_iMatNum;
}

HoEffectResMesh::HoEffectResMesh():m_Mesh(NULL),
                                   m_Bone(NULL)
{
}

HoEffectResMesh::~HoEffectResMesh()
{
    if(m_Mesh != NULL)
    {
        delete m_Mesh;
        m_Mesh = NULL;
    }

    if(m_Bone != NULL)
    {
        delete m_Bone;
        m_Bone = NULL;
    }
}

bool HoEffectResMesh::LoadingRes(const std::string &meshName)
{
    char tempBuffer[128];
    strcpy(tempBuffer, meshName.c_str());

    smASE_SetPhysique(NULL);
    m_Mesh = smASE_Read(tempBuffer);
    if(m_Mesh == NULL)
        return false;

    m_Mesh->ZeroNormals();
    m_Mesh->smMaterialGroup->ReadTextures();

    if(m_Mesh->smMaterialGroup)
    {
        int matCount = m_Mesh->smMaterialGroup->MaterialCount;
        for(int i = 0; i < matCount; i++)
        {
            m_Mesh->smMaterialGroup->smMaterial[i].BlendType = SMMAT_BLEND_LAMP;
        }
    }
    return true;
}

smPAT3D *HoEffectResMesh::GetRes()
{
    if(m_Mesh == NULL)
        return NULL;

    return m_Mesh;
}

smPAT3D *HoEffectResMesh::GetBoneRes()
{
	if(m_Bone == NULL)
		return NULL;

	return m_Bone;
}

bool HoEffectResMesh::LoadingRes(const std::string &meshName, const std::string &boneName)
{
    char tempBuffer1[128];
    char tempBuffer2[128];
    strcpy(tempBuffer1, meshName.c_str());
    strcpy(tempBuffer2, boneName.c_str());
    m_Bone = smASE_ReadBone(tempBuffer1);
	smASE_SetPhysique(m_Bone);

    m_Mesh = smASE_Read(tempBuffer1);
    m_Mesh->ZeroNormals();
    m_Mesh->smMaterialGroup->ReadTextures();

    if(m_Mesh->smMaterialGroup)
    {
        int matCount = m_Mesh->smMaterialGroup->MaterialCount;
        for(int i = 0; i < matCount; i++)
        {
            m_Mesh->smMaterialGroup->smMaterial[i].BlendType = SMMAT_BLEND_LAMP;
        }
    }

    return true;
}

HoEffectResManager::HoEffectResManager()
{
}

HoEffectResManager::~HoEffectResManager()
{
    ResTextureMapIT M_stIT	= m_ResTextureMap.begin();
	ResTextureMapIT	M_endIT	= m_ResTextureMap.end();

	for(;M_stIT != M_endIT;)
	{
		delete M_stIT->second;
		++M_stIT;
	}

    ResMeshMapIT B_stIT	 = m_ResMeshMap.begin();
	ResMeshMapIT B_endIT = m_ResMeshMap.end();

	for(;B_stIT != B_endIT;)
	{
		delete B_stIT->second;
		++B_stIT;
	}

	m_ResTextureMap.clear();
	m_ResMeshMap.clear();
}

HoEffectResManager* HoEffectResManager::m_Instance = 0;
HoEffectResManager* HoEffectResManager::GetInstance()
{
    if(m_Instance == 0)
        m_Instance = new HoEffectResManager;
    return m_Instance;
}

smPAT3D *HoEffectResManager::GetResMesh(const std::string &meshName, const std::string &boneName)
{
    if(m_ResMeshMap.find(meshName) == m_ResMeshMap.end())
    {
        HoEffectResMesh *resMesh = new HoEffectResMesh;
        if(boneName.size() == 0)
            resMesh->LoadingRes(meshName);
        else
            resMesh->LoadingRes(meshName, boneName);
        m_ResMeshMap[meshName]	= resMesh;
        return resMesh->GetRes();
    }
    else
        return m_ResMeshMap[meshName]->GetRes();

    return NULL;
}

smPAT3D *HoEffectResManager::GetResBone(const std::string &meshName)
{
	if(m_ResMeshMap.find(meshName) != m_ResMeshMap.end())
		return m_ResMeshMap[meshName]->GetBoneRes();

	return NULL;
}

int HoEffectResManager::GetResTexture(const std::string &fileName)
{
    if(m_ResTextureMap.find(fileName) == m_ResTextureMap.end())
    {
        HoEffectResTexture *resTexture = new HoEffectResTexture;
        resTexture->LoadingRes(fileName);
        m_ResTextureMap[fileName] = resTexture;
        return resTexture->GetRes();
    }
    else
        return m_ResTextureMap[fileName]->GetRes();
    return -1;
}

void HoEffectResManager::Clear()
{
    ResTextureMapIT M_stIT	= m_ResTextureMap.begin();
	ResTextureMapIT	M_endIT	= m_ResTextureMap.end();

	for(;M_stIT != M_endIT;)
	{
		delete M_stIT->second;
		++M_stIT;
	}

    ResMeshMapIT B_stIT	 = m_ResMeshMap.begin();
	ResMeshMapIT B_endIT = m_ResMeshMap.end();

	for(;B_stIT != B_endIT;)
	{
		delete B_stIT->second;
		++B_stIT;
	}

	m_ResTextureMap.clear();
	m_ResMeshMap.clear();
}





 