#include "assert.h"
#include "HoEffectView.h"
HoEffectView::HoEffectView()
{
}

HoEffectView::~HoEffectView()
{

}

#define FLOATS_EM				(FLOATNS+3)
#define SM_DIST_NEARZ			16
#define SMFLOAT_DIST_NEARZ		(SM_DIST_NEARZ<<FLOATNS)

static bool UpdateBillboardDefault(const SBillboardRenderInfo *renderInfo)
{
    int x,y,z;
	int rx , ry, rz;
	int width , height;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

     sColor[ SMC_R ] = int(renderInfo->m_Color.r);
	sColor[ SMC_G ] = int(renderInfo->m_Color.g);
	sColor[ SMC_B ] = int(renderInfo->m_Color.b);
    sColor[ SMC_A ] = int(renderInfo->m_Color.a);

	x = int(renderInfo->m_Pos.x * 256.f);
	y = int(renderInfo->m_Pos.y * 256.f);
	z = int(renderInfo->m_Pos.z * 256.f);

	
	x -= smRender.CameraPosiX;
	y -= smRender.CameraPosiY;
	z -= smRender.CameraPosiZ;

	rx = x * smRender.mCamera._11 +
		 y * smRender.mCamera._21 +
		 z * smRender.mCamera._31 ;

	ry = x * smRender.mCamera._12 +
		 y * smRender.mCamera._22 +
		 z * smRender.mCamera._32 ;

	rz = x * smRender.mCamera._13 +
		 y * smRender.mCamera._23 +
		 z * smRender.mCamera._33 ;

	x = rx>>FLOATS_EM;
	y = ry>>FLOATS_EM;
	z = rz>>FLOATS_EM;

    if ( z<SMFLOAT_DIST_NEARZ )
        return false;
    width  = int(renderInfo->m_Size.x*256.f / 2.f);
    height = int(renderInfo->m_Size.y*256.f / 2.f);

	
    POINT3D angle;
    angle.x = (int)((renderInfo->m_Angle.x/360.f)*4096.f);
    angle.y = (int)((renderInfo->m_Angle.y/360.f)*4096.f);
    angle.z = (int)((renderInfo->m_Angle.z/360.f)*4096.f);

    angle.x = angle.x & ANGCLIP;
    angle.y = angle.y & ANGCLIP;
    angle.z = angle.z & ANGCLIP;

    POINT3D outVertex[4];
    POINT3D inVertex[4];
    memset(outVertex, 0, sizeof(outVertex));
    inVertex[0].x = -width;
    inVertex[0].y = -height;
    inVertex[0].z = 0;

    inVertex[1].x =  width;
    inVertex[1].y = -height;
    inVertex[1].z = 0;

    inVertex[2].x = -width;
    inVertex[2].y = height;
    inVertex[2].z = 0;

    inVertex[3].x = width;
    inVertex[3].y = height;
    inVertex[3].z = 0;

    smMATRIX inRotXMatrix;
    smMATRIX inRotYMatrix;
    smMATRIX inRotZMatrix;

    smMATRIX outMatrix;
    smIdentityMatrix(outMatrix);
    smIdentityMatrix(inRotXMatrix);
    smIdentityMatrix(inRotYMatrix);
    smIdentityMatrix(inRotZMatrix);

    smRotateXMatrix(inRotXMatrix, angle.x);
    smRotateYMatrix(inRotYMatrix, angle.y);
    smRotateZMatrix(inRotZMatrix, angle.z);

    smMatrixMult(outMatrix, inRotXMatrix, inRotYMatrix);
    smMatrixMult(outMatrix, outMatrix, inRotZMatrix);

    int index=0;
    for(index = 0; index < 4; index++)
    {
        outVertex[index].x = inVertex[index].x * outMatrix._11 +
		                     inVertex[index].y * outMatrix._21 +
		                     inVertex[index].z * outMatrix._31 ;
        outVertex[index].x = outVertex[index].x >> FLOATNS;

	    outVertex[index].y = inVertex[index].x * outMatrix._12 +
		                     inVertex[index].y * outMatrix._22 +
		                     inVertex[index].z * outMatrix._32 ;
        outVertex[index].y = outVertex[index].y >> FLOATNS;

	    outVertex[index].z = inVertex[index].x * outMatrix._13 +
		                     inVertex[index].y * outMatrix._23 +
		                     inVertex[index].z * outMatrix._33 ;
        outVertex[index].z = outVertex[index].z >> FLOATNS;
    }

    
	v[0] = smRender.AddRendVertex ( x+outVertex[0].x , y+outVertex[0].y , z+outVertex[0].z, sColor );
	v[1] = smRender.AddRendVertex ( x+outVertex[1].x , y+outVertex[1].y , z+outVertex[1].z, sColor );
	v[2] = smRender.AddRendVertex ( x+outVertex[2].x , y+outVertex[2].y , z+outVertex[2].z, sColor );
	v[3] = smRender.AddRendVertex ( x+outVertex[3].x , y+outVertex[3].y , z+outVertex[3].z, sColor );

	
	rf = &smRender.RendFace[ smRender.nRendFace++ ];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial    = renderInfo->m_MatID;		
	rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
	rf->lpTexLink  = 0;
    
	smRender.AddRendTempTexLink( rf , 0,	0, 1, 1, 1, 0, 0);

	
	rf = &smRender.RendFace[ smRender.nRendFace++ ];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial    = renderInfo->m_MatID;		
	rf->ClipStatus = v[1]->ClipStatus|v[2]->ClipStatus|v[3]->ClipStatus;
	rf->lpTexLink  = 0;
    
	smRender.AddRendTempTexLink( rf , 0, 1, 1, 1, 0, 0, 0);

    return true;
}

static bool GetCameraTest(POINT3D &world)
{
	int rx, ry, rz;

    
	world.x -= smRender.CameraPosiX;
	world.y -= smRender.CameraPosiY;
	world.z -= smRender.CameraPosiZ;

	rx = world.x * smRender.mCamera._11 +
		 world.y * smRender.mCamera._21 +
		 world.z * smRender.mCamera._31 ;

	ry = world.x * smRender.mCamera._12 +
		 world.y * smRender.mCamera._22 +
		 world.z * smRender.mCamera._32 ;

	rz = world.x * smRender.mCamera._13 +
		 world.y * smRender.mCamera._23 +
		 world.z * smRender.mCamera._33 ;

	world.x = rx>>FLOATS_EM;
	world.y = ry>>FLOATS_EM;
	world.z = rz>>FLOATS_EM;

    if ( world.z<SMFLOAT_DIST_NEARZ )
		return false;
	return true;
}

static bool UpdateBillboardAxial(const SBillboardRenderInfo *renderInfo)
{
    POINT3D currentPos;
    POINT3D destPos;

     currentPos.x   = int(renderInfo->m_Pos.x * 256.f);
    currentPos.y   = int(renderInfo->m_Pos.y * 256.f);
    currentPos.z   = int(renderInfo->m_Pos.z * 256.f);

    destPos.x   = int(renderInfo->m_DesPos.x * 256.f);
    destPos.y   = int(renderInfo->m_DesPos.y * 256.f);
    destPos.z   = int(renderInfo->m_DesPos.z * 256.f);

    if(GetCameraTest(currentPos) == FALSE)
			return false;

    if(GetCameraTest(destPos) == FALSE)
			return true;

    smRENDVERTEX *v[4];
    smRENDFACE	 *rf;
    short		sColor[4];

    sColor[ SMC_R ] = int(renderInfo->m_Color.r);
	sColor[ SMC_G ] = int(renderInfo->m_Color.g);
	sColor[ SMC_B ] = int(renderInfo->m_Color.b);
    sColor[ SMC_A ] = int(renderInfo->m_Color.a);

    smTEXRECT texRect;
    texRect.left = 0;
    texRect.top  = 0;
    texRect.right = 1;
    texRect.bottom = 1;

    float dx     = float(destPos.x - currentPos.x); 
    float dy     = float(destPos.y - currentPos.y); 
    float length = (float)sqrt(dx*dx+dy*dy);        

    dx = dx/length*renderInfo->m_Size.x*256.f; 
    dy = dy/length*renderInfo->m_Size.x*256.f;

    D3DVECTOR persp;
    persp.x = -dy;
    persp.y = +dx;
    persp.z = 0;

    if (abs((int)dx) > 1.0f) currentPos.x -= (int)dx;
    if (abs((int)dy) > 1.0f) currentPos.y -= (int)dy;
    v[0] = smRender.AddRendVertex ( int(destPos.x-persp.x), int(destPos.y-persp.y), int(destPos.z), sColor );
    v[1] = smRender.AddRendVertex ( int(destPos.x+persp.x), int(destPos.y+persp.y), int(destPos.z), sColor );
    v[2] = smRender.AddRendVertex ( int(currentPos.x-persp.x), int(currentPos.y-persp.y), int(currentPos.z), sColor );
    v[3] = smRender.AddRendVertex ( int(currentPos.x+persp.x), int(currentPos.y+persp.y), int(currentPos.z), sColor );

    
    rf = &smRender.RendFace[ smRender.nRendFace++ ];
    rf->lpRendVertex[0] = v[0];
    rf->lpRendVertex[1] = v[1];
    rf->lpRendVertex[2] = v[2];
    rf->Matrial    = renderInfo->m_MatID;		
    rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
    rf->lpTexLink  = 0;

    
    smRender.AddRendTempTexLink( rf , 0,	texRect.left , texRect.bottom,
                                texRect.right , texRect.bottom,
                                texRect.left , texRect.top );


    
    rf = &smRender.RendFace[ smRender.nRendFace++ ];
    rf->lpRendVertex[0] = v[1];
    rf->lpRendVertex[1] = v[3];
    rf->lpRendVertex[2] = v[2];
    rf->Matrial    = renderInfo->m_MatID;		
    rf->ClipStatus = v[1]->ClipStatus|v[2]->ClipStatus|v[3]->ClipStatus;
    rf->lpTexLink  = 0;

    
    smRender.AddRendTempTexLink( rf , 0,	texRect.right , texRect.bottom,
                                            texRect.right , texRect.top,
                                            texRect.left  , texRect.top );

    return true;
}

static bool UpdateCreateMesh(const SBillboardRenderInfo *renderInfo)
{
    int x,y,z;
    int width , height;

    smRENDVERTEX *v[4];
    smRENDFACE	 *rf;
    short		sColor[4];

    sColor[ SMC_R ] = int(renderInfo->m_Color.r);
	sColor[ SMC_G ] = int(renderInfo->m_Color.g);
	sColor[ SMC_B ] = int(renderInfo->m_Color.b);
    sColor[ SMC_A ] = int(renderInfo->m_Color.a);

	x = int(renderInfo->m_Pos.x * 256.f);
	y = int(renderInfo->m_Pos.y * 256.f);
	z = int(renderInfo->m_Pos.z * 256.f);

    POINT3D inVertex[4];
    POINT3D outVertex[4];

    width  = int(renderInfo->m_Size.x*256.f / 2.f);
    height = int(renderInfo->m_Size.y*256.f / 2.f);

    inVertex[0].x   = x-width;
    inVertex[0].y   = y;
    inVertex[0].z   = z+height;

    inVertex[1].x   = x+width;
    inVertex[1].y   = y;
    inVertex[1].z   = z+height;

    inVertex[2].x   = x-width;
    inVertex[2].y   = y;
    inVertex[2].z   = z-height;

    inVertex[3].x   = x+width;
    inVertex[3].y   = y;
	inVertex[3].z   = z-height;
	
	int index = 0;
	
	
		inVertex[0].x   = -width;
		inVertex[0].y   = 0;
		inVertex[0].z   = height;

		inVertex[1].x   = width;
		inVertex[1].y   = 0;
		inVertex[1].z   = height;

		inVertex[2].x   = -width;
		inVertex[2].y   = 9;
		inVertex[2].z   = -height;

		inVertex[3].x   = width;
		inVertex[3].y   = 0;
		inVertex[3].z   = -height;

		POINT3D angle;
		angle.x = (int)(renderInfo->m_Angle.x);
		angle.y = (int)(renderInfo->m_Angle.y);
		angle.z = (int)(renderInfo->m_Angle.z);

		angle.x = angle.x & ANGCLIP;
		angle.y = angle.y & ANGCLIP;
		angle.z = angle.z & ANGCLIP;

		smMATRIX inRotXMatrix;
		smMATRIX inRotYMatrix;
		smMATRIX inRotZMatrix;

		smMATRIX outMatrix;
		smIdentityMatrix(outMatrix);
		smIdentityMatrix(inRotXMatrix);
		smIdentityMatrix(inRotYMatrix);
		smIdentityMatrix(inRotZMatrix);

		smRotateXMatrix(inRotXMatrix, angle.x);
		smRotateYMatrix(inRotYMatrix, angle.y);
		smRotateZMatrix(inRotZMatrix, angle.z);

		smMatrixMult(outMatrix, inRotXMatrix, inRotYMatrix);
		smMatrixMult(outMatrix, outMatrix, inRotZMatrix);

		for(index = 0; index < 4; index++)
		{
			outVertex[index].x = inVertex[index].x * outMatrix._11 +
								 inVertex[index].y * outMatrix._21 +
								 inVertex[index].z * outMatrix._31 ;


			outVertex[index].y = inVertex[index].x * outMatrix._12 +
								 inVertex[index].y * outMatrix._22 +
								 inVertex[index].z * outMatrix._32 ;


			outVertex[index].z = inVertex[index].x * outMatrix._13 +
								 inVertex[index].y * outMatrix._23 +
								 inVertex[index].z * outMatrix._33 ;

			outVertex[index].x = outVertex[index].x/fONE+x;
			outVertex[index].y = outVertex[index].y/fONE+y;
			outVertex[index].z = outVertex[index].z/fONE+z;

		}

		memcpy(inVertex, outVertex, sizeof(inVertex));
	

	
	for(index = 0; index < 4; index++)
    {
        inVertex[index].x -= smRender.CameraPosiX;
        inVertex[index].y -= smRender.CameraPosiY;
        inVertex[index].z -= smRender.CameraPosiZ;
    }

	for(index = 0; index < 4; index++)
    {
        outVertex[index].x = inVertex[index].x*smRender.mCamera._11 +
                             inVertex[index].y*smRender.mCamera._21 +
                             inVertex[index].z*smRender.mCamera._31;

        outVertex[index].y = inVertex[index].x*smRender.mCamera._12 +
                             inVertex[index].y*smRender.mCamera._22 +
                             inVertex[index].z*smRender.mCamera._32;

        outVertex[index].z = inVertex[index].x*smRender.mCamera._13 +
                             inVertex[index].y*smRender.mCamera._23 +
                             inVertex[index].z*smRender.mCamera._33;

        outVertex[index].x = outVertex[index].x >> FLOATS_EM;
        outVertex[index].y = outVertex[index].y >> FLOATS_EM;
        outVertex[index].z = outVertex[index].z >> FLOATS_EM;

		if(outVertex[index].z < SMFLOAT_DIST_NEARZ)
            return false;
    }
	

	
    v[0] = smRender.AddRendVertex ( outVertex[0].x , outVertex[0].y , outVertex[0].z, sColor);
    v[1] = smRender.AddRendVertex ( outVertex[1].x,  outVertex[1].y , outVertex[1].z, sColor);
    v[2] = smRender.AddRendVertex ( outVertex[2].x , outVertex[2].y , outVertex[2].z, sColor);
    v[3] = smRender.AddRendVertex ( outVertex[3].x , outVertex[3].y , outVertex[3].z, sColor);

		
		rf = &smRender.RendFace[ smRender.nRendFace++ ];
		rf->lpRendVertex[0] = v[0];
		rf->lpRendVertex[1] = v[1];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial    = renderInfo->m_MatID;		
		rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
		rf->lpTexLink  = 0;

	    
	    smRender.AddRendTempTexLink( rf , 0,	0, 1, 1, 1, 0, 0);


		
		rf = &smRender.RendFace[ smRender.nRendFace++ ];
		rf->lpRendVertex[0] = v[1];
		rf->lpRendVertex[1] = v[3];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial    = renderInfo->m_MatID;		
		rf->ClipStatus = v[1]->ClipStatus|v[2]->ClipStatus|v[3]->ClipStatus;
		rf->lpTexLink  = 0;

	  
	    smRender.AddRendTempTexLink( rf , 0, 1, 1, 1, 0, 0, 0);
    return true;
}

bool HoEffectView::UpdateBillboard(const SBillboardRenderInfo *renderInfo, int iX, int iY, int iZ, int aX, int aY, int aZ)
{
    if(renderInfo == NULL)
        return false;
    smRender.Init();
    smRender.SetMaterialGroup(smMaterialGroup);
    smRender.SetCameraPosi(iX, iY, iZ, aX, aY, aZ);
    smMaterialGroup->smMaterial[renderInfo->m_MatID].TwoSide = TRUE;

    smMaterial[renderInfo->m_MatID].BlendType = renderInfo->m_iBlendType;
    if(renderInfo->m_Type == BILLBOARD_DEFAULT)
        UpdateBillboardDefault(renderInfo);
    else if(renderInfo->m_Type == BILLBOARD_AXIAL)
        UpdateBillboardAxial(renderInfo);
    else if(renderInfo->m_Type == CREATE_MESH)
        UpdateCreateMesh(renderInfo);

    smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
    smRender.ClipRendFace();
    smRender.GeomVertex2D(FALSE);
	smRender.RenderD3D();


    return true;
}

bool HoEffectView::UpdateLineList(const SLineListRenderInfo *renderInfo, int iX, int iY, int iZ, int aX, int aY, int aZ)
{
	if(renderInfo == NULL)
		return false;
	if(renderInfo->m_pList == NULL)
		return false;

	assert(renderInfo);
	smRender.Init();
    smRender.SetMaterialGroup(smMaterialGroup);
    smRender.SetCameraPosi(iX, iY, iZ, aX, aY, aZ);
    smMaterialGroup->smMaterial[renderInfo->m_MatID].TwoSide = TRUE;
	smMaterial[renderInfo->m_MatID].BlendType = renderInfo->m_iBlendType;
	
	if(renderInfo->m_pList->size() < 2)
		return false;
	
	POINT3D destPos;
	POINT3D currentPos;
	
	std::list<point3>::iterator iter;
	iter = renderInfo->m_pList->begin();
    destPos.x = (int)iter->x * 256;
    destPos.y = (int)iter->y * 256;
    destPos.z = (int)iter->z * 256;

    int texSizeCount = 0;
    int test = renderInfo->m_pList->size();
    float cellSize = 1.f/(renderInfo->m_pList->size()-1);
    ++iter;
	POINT3D OldVertex[2];
    memset(OldVertex, 0, sizeof(OldVertex));
	
	for (; iter != renderInfo->m_pList->end();iter++)
    {
		currentPos.x = (int)iter->x * 256;
        currentPos.y = (int)iter->y * 256;
        currentPos.z = (int)iter->z * 256;
			
		if(GetCameraTest(currentPos) == FALSE)
			return false;
		if(GetCameraTest(destPos) == FALSE)
			return true;
        
		smRENDVERTEX *v[4];
	    smRENDFACE	 *rf;

	    short		sColor[4];

		sColor[ SMC_R ] = int(renderInfo->m_Color.r);
		sColor[ SMC_G ] = int(renderInfo->m_Color.g);
		sColor[ SMC_B ] = int(renderInfo->m_Color.b);
		sColor[ SMC_A ] = int(renderInfo->m_Color.a);

        smTEXRECT texRect;
        texRect.left   = 0;
        texRect.top    = (float)texSizeCount*cellSize;
        texRect.right  = 1;
        texRect.bottom = (float)(texSizeCount+1)*cellSize;
		
		float dx     = float(destPos.x - currentPos.x); 
		float dy     = float(destPos.y - currentPos.y); 
		float length = (float)sqrt(dx*dx+dy*dy);        

        if(length == 0)
            length = 1;

        dx = dx/length*renderInfo->m_Size.x*256.f;; 
		dy = dy/length*renderInfo->m_Size.x*256.f;;

        D3DVECTOR persp;
        persp.x = -dy;
		persp.y = +dx;
        persp.z = 0;
		
		if(texSizeCount == 0)
		{
			v[0] = smRender.AddRendVertex ( int(destPos.x-persp.x), int(destPos.y-persp.y), int(destPos.z), sColor );
			v[1] = smRender.AddRendVertex ( int(destPos.x+persp.x), int(destPos.y+persp.y), int(destPos.z), sColor );
		}
		else
		{
			v[0] = smRender.AddRendVertex ( OldVertex[0].x, OldVertex[0].y, OldVertex[0].z, sColor );
            v[1] = smRender.AddRendVertex ( OldVertex[1].x, OldVertex[1].y, OldVertex[1].z, sColor );
		}
        
		OldVertex[0].x = int(currentPos.x-persp.x);
        OldVertex[0].y = int(currentPos.y-persp.y);
        OldVertex[0].z = int(currentPos.z);

        OldVertex[1].x = int(currentPos.x+persp.x);
        OldVertex[1].y = int(currentPos.y+persp.y);
        OldVertex[1].z = int(currentPos.z);

        destPos.x = int(iter->x)*256;
        destPos.y = int(iter->y)*256;
        destPos.z = int(iter->z)*256;

        v[2] = smRender.AddRendVertex ( int(currentPos.x-persp.x), int(currentPos.y-persp.y), int(currentPos.z), sColor );
        v[3] = smRender.AddRendVertex ( int(currentPos.x+persp.x), int(currentPos.y+persp.y), int(currentPos.z), sColor );

        
        rf = &smRender.RendFace[ smRender.nRendFace++ ];
        rf->lpRendVertex[0] = v[0];
        rf->lpRendVertex[1] = v[1];
        rf->lpRendVertex[2] = v[2];
		rf->Matrial    = renderInfo->m_MatID;		
        rf->ClipStatus = v[0]->ClipStatus|v[1]->ClipStatus|v[2]->ClipStatus;
        rf->lpTexLink  = 0;

        
        smRender.AddRendTempTexLink( rf , 0,	texRect.left , texRect.top,
                            texRect.right , texRect.top,
                            texRect.left , texRect.bottom );


        
        rf = &smRender.RendFace[ smRender.nRendFace++ ];
        rf->lpRendVertex[0] = v[1];
        rf->lpRendVertex[1] = v[3];
        rf->lpRendVertex[2] = v[2];
        rf->Matrial    = renderInfo->m_MatID;		
        rf->ClipStatus = v[1]->ClipStatus|v[2]->ClipStatus|v[3]->ClipStatus;
        rf->lpTexLink  = 0;

        
        smRender.AddRendTempTexLink( rf , 0, texRect.right , texRect.top,
                                                texRect.right , texRect.bottom,
                                                texRect.left  , texRect.bottom );

        texSizeCount++;
	}

	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
    smRender.ClipRendFace();
    smRender.GeomVertex2D(FALSE);
	smRender.RenderD3D();

	return true;
}

bool HoEffectView::UpdateMesh(const SMeshRenderInfo *renderInfo, int iX, int iY, int iZ, int aX, int aY, int aZ)
{
    if(renderInfo == NULL)
        return false;
    assert(renderInfo);
    assert(renderInfo->m_Pat);
    renderInfo->m_Pat->Frame = renderInfo->m_iCurrentFrame;
    if(renderInfo->m_Pat->smMaterialGroup)
    {
        int matCount = renderInfo->m_Pat->smMaterialGroup->MaterialCount;
        for(int i = 0; i < matCount; i++)
            renderInfo->m_Pat->smMaterialGroup->smMaterial[i].BlendType = renderInfo->m_iBlendType;
    }

    POINT3D pos;
    POINT3D angle;

    POINT3D cameraPos;
    POINT3D cameraAngle;
	
	pos.x = (int)(renderInfo->m_Pos.x * 256.f);
    pos.y = (int)(renderInfo->m_Pos.y * 256.f);
    pos.z = (int)(renderInfo->m_Pos.z * 256.f);
	
	angle.x = int(renderInfo->m_Angle.x);
    angle.y = int(renderInfo->m_Angle.y);
    angle.z = int(renderInfo->m_Angle.z);
	
	cameraPos.x = iX;
    cameraPos.y = iY;
    cameraPos.z = iZ;

    cameraAngle.x = aX;
    cameraAngle.y = aY;
    cameraAngle.z = aZ;

    int oldR, oldG, oldB, oldA;
    oldR = smRender.Color_R;
    oldG = smRender.Color_G;
    oldB = smRender.Color_B;
    oldA = smRender.Color_A;
	
    smRender.Color_R = (int)(renderInfo->m_Color.r - 255.f);
    smRender.Color_G = (int)(renderInfo->m_Color.g - 255.f);
    smRender.Color_B = (int)(renderInfo->m_Color.b - 255.f);
    smRender.Color_A = (int)(renderInfo->m_Color.a - 255.f);
    
    renderInfo->m_Pat->SetPosi(&pos, &angle);
    renderInfo->m_Pat->RenderD3D(&cameraPos, &cameraAngle);

    smRender.Color_R = oldR;
    smRender.Color_G = oldG;
    smRender.Color_B = oldB;
    smRender.Color_A = oldA;

    return true;
}



