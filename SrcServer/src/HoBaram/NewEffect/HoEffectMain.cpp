#include "HoEffectMain.h"

HoEffectMain	MainWindow;
HoEffectMain::HoEffectMain()
{
	m_EffectGroup = NULL;
	m_ModelController = NULL;
	m_WorkTypeName = CLASS_EFFECT_NONE;
	m_SpecificWorkTypeName = CLASS_EFFECT_NONE;
}

HoEffectMain::~HoEffectMain()
{

}

void HoEffectMain::Update(int x, int y, int z, int ax, int ay, int az)
{
	if(m_EffectGroup)
        m_EffectGroup->UpdateView( x, y, z, ax, ay, az);
}

void HoEffectMain::Main(float elapsedTime)
{
	if(m_EffectGroup)
		m_EffectGroup->Main(elapsedTime);
}

HoEffectGroup *HoEffectMain::LoadScript(const char *str)
{
	if(m_EffectGroup)
		m_EffectGroup = NULL;
	
	if(m_PiScript.RunScriptFile(str))
	{
		m_EffectGroup->CreateFadeList();
		m_EffectGroup->Main(0.f);
		return m_EffectGroup;
	}
	return NULL;
}

HoEffectBillboardAxialController *HoEffectMain::LoadScriptAxial(const char *str)
{
	m_SpecificWorkTypeName = CLASS_EFFECT_BILLBOARD_AXIAL;
	if(m_PiScript.RunScriptFile(str))
	{
		m_ModelController->CreateFadeList();
		m_ModelController->Main(0.f);
		return (HoEffectBillboardAxialController *)m_ModelController;
	}

	return NULL;
}


void HoEffectMain::LuaBegin(const char *typeName, const char *parentMeshName)
{
    if(stricmp(typeName, "Parent") == 0)
    {
        m_WorkTypeName = CLASS_EFFECT_PARENT;
        m_EffectGroup = new HoEffectGroup();
    }
    else if(stricmp(typeName, "Mesh") == 0)
    {
        m_WorkTypeName = CLASS_EFFECT_MESH;
        m_ModelController = NULL;
        m_ModelController = m_EffectGroup->CreateFactory(CLASS_EFFECT_MESH);
    }
    else if(stricmp(typeName, "CreateMesh") == 0)
    {
        m_WorkTypeName    = CLASS_EFFECT_TEXTURE;
        m_ModelController = NULL;
        m_ModelController = m_EffectGroup->CreateFactory(CLASS_EFFECT_TEXTURE);
        static_cast<HoEffectTextureController *>(m_ModelController)->Init(CLASS_EFFECT_CREATE_MESH);
        static_cast<HoEffectTextureController *>(m_ModelController)->SetLive(true);
    }
    else if(stricmp(typeName, "Billboard") == 0)
    {
        m_ModelController = NULL;
        m_WorkTypeName    = CLASS_EFFECT_TEXTURE;
        m_ModelController = m_EffectGroup->CreateFactory(CLASS_EFFECT_TEXTURE);
        static_cast<HoEffectTextureController *>(m_ModelController)->Init(CLASS_EFFECT_BILLBOARD);
        static_cast<HoEffectTextureController *>(m_ModelController)->SetLive(true);
    }
    else if(stricmp(typeName, "BillboardAxial") == 0)
    {
        m_ModelController = NULL;
        m_WorkTypeName    = CLASS_EFFECT_BILLBOARD_AXIAL;
        m_ModelController = m_EffectGroup->CreateFactory(CLASS_EFFECT_BILLBOARD_AXIAL);
    }
    else if(stricmp(typeName, "ParticleSystem") == 0)
    {
        m_ModelController = NULL;
        m_WorkTypeName    = CLASS_EFFECT_PARTICLE_SYSTEM;
        m_ModelController = m_EffectGroup->CreateFactory(CLASS_EFFECT_PARTICLE_SYSTEM);
    }
}

void HoEffectMain::LuaEnd()
{
    m_WorkTypeName = CLASS_EFFECT_NONE;

	if(m_SpecificWorkTypeName == CLASS_EFFECT_NONE)
	{
		if(m_ModelController != NULL)
			m_EffectGroup->AddModelController(m_ModelController);
		m_ModelController = NULL;
	}
}

void HoEffectMain::LuaInitPos(float x, float y, float z)
{
	if(m_WorkTypeName == CLASS_EFFECT_PARENT)
	{
        point3 pos;
		pos.x = x;
		pos.y = y;
		pos.z = z;
		m_EffectGroup->SetCalcTranslate(&pos, NULL);
	}
    else
        m_ModelController->SetTranslate(point3(x, y, z));
}

void HoEffectMain::LuaInitColor(float r, float g, float b, float a)
{
    if(m_WorkTypeName == CLASS_EFFECT_MESH )
        static_cast<HoEffectMeshController *>(m_ModelController)->InitColor(r, g, b, a);
    else if(m_WorkTypeName == CLASS_EFFECT_TEXTURE)
        static_cast<HoEffectTextureController *>(m_ModelController)->InitColor(r, g, b, a);
    else if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
        static_cast<HoEffectParticleController *>(m_ModelController)->InitColor(r, g, b, a);
    else if(m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
        static_cast<HoEffectBillboardAxialController *>(m_ModelController)->InitColor(r, g, b, a);

}

void HoEffectMain::LuaInitMeshName(const char *meshName, const char *boneName)
{
    if(m_WorkTypeName == CLASS_EFFECT_MESH)
    {
        if(boneName == NULL)
            static_cast<HoEffectMeshController *>(m_ModelController)->Init(meshName);
        else
            static_cast<HoEffectMeshController *>(m_ModelController)->Init(meshName, boneName);
    }
}

void HoEffectMain::LuaInitTextureName(const char *textureName)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
        static_cast<HoEffectParticleController *>(m_ModelController)->Init(textureName);
    else if(m_WorkTypeName == CLASS_EFFECT_TEXTURE)
        static_cast<HoEffectTextureController *>(m_ModelController)->Init(textureName);
    else if(m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
        static_cast<HoEffectBillboardAxialController *>(m_ModelController)->Init(textureName);
}

void HoEffectMain::LuaInitMaxFrame(float frame)
{
    if(m_WorkTypeName == CLASS_EFFECT_MESH)
    {
        static_cast<HoEffectMeshController *>(m_ModelController)->InitMaxFrame(frame);
    }
}

void HoEffectMain::LuaInitSize(float x, float y)
{
    if(m_WorkTypeName == CLASS_EFFECT_TEXTURE)
        static_cast<HoEffectTextureController *>(m_ModelController)->InitSize(x, y);
    else if(m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
        static_cast<HoEffectBillboardAxialController *>(m_ModelController)->InitSize(x, y);
    else if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
        static_cast<HoEffectParticleController *>(m_ModelController)->InitSize(x, y);
}

void HoEffectMain::LuaInitSize(float x1, float x2, float y1, float y2)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
        static_cast<HoEffectParticleController *>(m_ModelController)->InitSize(x1, x2, y1, y2);
}


void HoEffectMain::LuaInitLoop(int loop)
{
    if(m_WorkTypeName == CLASS_EFFECT_MESH)
        static_cast<HoEffectMeshController *>(m_ModelController)->InitLoop(loop);
    else if(m_WorkTypeName == CLASS_EFFECT_TEXTURE)
        static_cast<HoEffectTextureController *>(m_ModelController)->InitLoop(loop);
    else if(m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
        static_cast<HoEffectBillboardAxialController *>(m_ModelController)->InitLoop(loop);
    else if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
        static_cast<HoEffectParticleController *>(m_ModelController)->InitLoop(loop);
}

void HoEffectMain::LuaInitEndTime(float time)
{
    if(m_WorkTypeName == CLASS_EFFECT_TEXTURE)
        static_cast<HoEffectTextureController *>(m_ModelController)->InitEndTime(time);
    else if(m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
        static_cast<HoEffectBillboardAxialController *>(m_ModelController)->InitEndTime(time);
    else if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
        static_cast<HoEffectParticleController *>(m_ModelController)->InitEndTime(time, time);
}

void HoEffectMain::LuaInitEndTime(float x1, float x2)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
        static_cast<HoEffectParticleController *>(m_ModelController)->InitEndTime(x1, x2);
}

void HoEffectMain::LuaInitAniTextureName(const char *textureName, int textureCount, float aniDelayTime)
{
    if(m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
        static_cast<HoEffectBillboardAxialController *>(m_ModelController)->Init(textureName, textureCount, aniDelayTime);
    else if(m_WorkTypeName == CLASS_EFFECT_TEXTURE)
        static_cast<HoEffectTextureController *>(m_ModelController)->Init(textureName, textureCount, aniDelayTime);
}

void HoEffectMain::LuaInitStartDelayTime(float delayTime)
{
    if(m_WorkTypeName == CLASS_EFFECT_MESH)
        static_cast<HoEffectMeshController *>(m_ModelController)->InitStartDelayTime(delayTime);
    else if(m_WorkTypeName == CLASS_EFFECT_TEXTURE)
        static_cast<HoEffectTextureController *>(m_ModelController)->InitStartDelayTime(delayTime);
    else if(m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
        static_cast<HoEffectBillboardAxialController *>(m_ModelController)->InitStartDelayTime(delayTime);
}

void HoEffectMain::LuaEventColor(float time, float r, float g, float b, float a)
{
    if(m_WorkTypeName == CLASS_EFFECT_MESH ||
       m_WorkTypeName == CLASS_EFFECT_TEXTURE ||
       m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL ||
       m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
    {
        HoEffectEventColor *eventColor = new HoEffectEventColor;
        eventColor->SetStartTime(HoEffectMinMax<float>(time, time));
        HoEffectMinMax<color4> color;
        color.Max.r = r;
        color.Min.r = r;
        color.Max.g = g;
        color.Min.g = g;
        color.Max.b = b;
        color.Min.b = b;
        color.Max.a = a;
        color.Min.a = a;
        eventColor->Set(color);

        m_ModelController->AddEvent(eventColor);
    }
}

void HoEffectMain::LuaEventSize(float time, float x, float y, float z)
{
    if(m_WorkTypeName == CLASS_EFFECT_MESH ||
       m_WorkTypeName == CLASS_EFFECT_TEXTURE ||
       m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
    {
        HoEffectEventSize *eventSize = new HoEffectEventSize;
        eventSize->SetStartTime(HoEffectMinMax<float>(time, time));
        HoEffectMinMax<point3> size;

        size.Max.x = x;
        size.Min.x = x;
        size.Max.y = y;
        size.Min.y = y;
        size.Max.z = z;
        size.Min.z = z;

        eventSize->Set(size);
        m_ModelController->AddEvent(eventSize);
    }
}

void HoEffectMain::LuaEventFadeColor(float time, float r, float g, float b, float a)
{
    if(m_WorkTypeName == CLASS_EFFECT_MESH ||
       m_WorkTypeName == CLASS_EFFECT_TEXTURE ||
       m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL||
       m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
    {
        HoEffectEventColor *eventColor = new HoEffectEventColor;
        eventColor->SetStartTime(HoEffectMinMax<float>(time, time));
        eventColor->SetFade(true);
        HoEffectMinMax<color4> color;
        color.Max.r = r;
        color.Min.r = r;
        color.Max.g = g;
        color.Min.g = g;
        color.Max.b = b;
        color.Min.b = b;
        color.Max.a = a;
        color.Min.a = a;
        eventColor->Set(color);

        m_ModelController->AddEvent(eventColor);
    }
}


void HoEffectMain::LuaEventFadeSize(float time, float x, float y, float z)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM ||
       m_WorkTypeName == CLASS_EFFECT_TEXTURE ||
       m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
    {
        HoEffectEventSize *eventSize = new HoEffectEventSize;
        eventSize->SetStartTime(HoEffectMinMax<float>(time, time));
        eventSize->SetFade(true);
        HoEffectMinMax<point3> size;

        size.Max.x = x;
        size.Min.x = x;
        size.Max.y = y;
        size.Min.y = y;
        size.Max.z = z;
        size.Min.z = z;

        eventSize->Set(size);
        m_ModelController->AddEvent(eventSize);
    }
}

void HoEffectMain::LuaInitSpawnBoundingBox(float x1, float x2, float y1, float y2, float z1, float z2)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
    {
        static_cast<HoEffectParticleController *>(m_ModelController)->
            InitSpawnBoundingBox(x1, x2, y1, y2, z1, z2);
    }
}

void HoEffectMain::LuaInitSpawnBoundingSphere(float x1, float x2)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
    {
        static_cast<HoEffectParticleController *>(m_ModelController)->
            InitSpawnBoundingSphere(x1, x2);
    }
}

void HoEffectMain::LuaInitSpawnBoundingDoughnut(float x1, float x2, float y1, float y2)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
    {
        static_cast<HoEffectParticleController *>(m_ModelController)->
            InitSpawnBoundingDoughnut(x1, x2, y1, y2);
    }
}

void HoEffectMain::LuaInitBlendType(const char *type)
{
    int blendType;

    if( stricmp(type, "Lamp") == 0)
        blendType = SMMAT_BLEND_LAMP;
    else if( stricmp(type, "Shadow") == 0)
        blendType = SMMAT_BLEND_SHADOW;
    else if( stricmp(type, "Color") == 0)
        blendType = SMMAT_BLEND_COLOR;
    else if( stricmp(type, "AddColor") == 0)
        blendType = SMMAT_BLEND_ADDCOLOR;
    else if( stricmp(type, "Alpha") == 0)
        blendType = SMMAT_BLEND_ALPHA;
    else if( stricmp(type, "InvShadow") == 0)
        blendType = SMMAT_BLEND_INVSHADOW;

    if(m_WorkTypeName == CLASS_EFFECT_TEXTURE)
        static_cast<HoEffectTextureController *>(m_ModelController)->InitBlendType(blendType);
    else if(m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
        static_cast<HoEffectBillboardAxialController *>(m_ModelController)->InitBlendType(blendType);
    else if(m_WorkTypeName == CLASS_EFFECT_MESH)
        static_cast<HoEffectMeshController *>(m_ModelController)->InitBlendType(blendType);
    else if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
        static_cast<HoEffectParticleController *>(m_ModelController)->InitBlendType(blendType);
}

void HoEffectMain::LuaInitVelocityType(const char *typeName)
{
    if(stricmp(typeName, "Random") == 0)
    {
        if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
            static_cast<HoEffectParticleController *>(m_ModelController)->InitVelocityType(SPAWN_VELOCITY_RANDOM);
    }
    else if( stricmp(typeName, "CurPos") == 0 )
    {
        if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
            static_cast<HoEffectParticleController *>(m_ModelController)->InitVelocityType(SPAWN_VELOCITY_CURPOS);
    }
}

void HoEffectMain::LuaInitParticleType(const char *typeName)
{
    if(stricmp(typeName, "BillboardDefault") == 0)
    {
        if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
            static_cast<HoEffectParticleController *>(m_ModelController)->InitParticleType(PARTICLE_BILLBOARD_DEFAULT);
    }
    else if(stricmp(typeName, "BillboardAxial") == 0)
    {
        if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
            static_cast<HoEffectParticleController *>(m_ModelController)->InitParticleType(PARTICLE_BILLBOARD_AXIAL);
    }
}

void HoEffectMain::LuaInitParticleNum(float particleNum)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
    {
        static_cast<HoEffectParticleController *>(m_ModelController)->
            InitParticleNum(particleNum);
    }
}

void HoEffectMain::LuaInitVelocity(float x1, float x2, float y1, float y2, float z1, float z2)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
    {
        static_cast<HoEffectParticleController *>(m_ModelController)->
            InitVelocity(x1, x2, y1, y2, z1, z2);
    }
}

void HoEffectMain::LuaInitEmitRate(float emitRate)
{
    if(m_WorkTypeName == CLASS_EFFECT_PARTICLE_SYSTEM)
    {
        static_cast<HoEffectParticleController *>(m_ModelController)->
            InitEmitRate(emitRate);
    }
}

void HoEffectMain::LuaInitAxialPos(float x1, float y1, float z1, float x2, float y2, float z2)
{
    if(m_WorkTypeName == CLASS_EFFECT_BILLBOARD_AXIAL)
    {
        static_cast<HoEffectBillboardAxialController *>(m_ModelController)->InitPos(x1, y1, z1, x2, y2, z2);
    }
}

