
#include "smd3d.h"

#define SMSFACE_MAX		1000


smSTAGE_FACE *smFaceList[SMSFACE_MAX];
int	smFaceListCnt;


int Stage_StepHeight = 10 * fONE;

int smStage_WaterChk;

smSTAGE_FACE *CheckFace = 0;
smSTAGE_FACE *DebugFace = 0;
WORD		DebugFaceMat = 0;


int smGetPlaneProduct(POINT3D *p1, POINT3D *p2, POINT3D *p3, POINT3D *p)
{
	int ux, uy, uz;
	int vx, vy, vz;
	int nx, ny, nz;
	int result;


	ux = (p2->x - p1->x) >> 6;
	uy = (p2->y - p1->y) >> 6;
	uz = (p2->z - p1->z) >> 6;

	vx = (p3->x - p1->x) >> 6;
	vy = (p3->y - p1->y) >> 6;
	vz = (p3->z - p1->z) >> 6;


	nx = (uy*vz - uz*vy) >> 2;
	ny = (uz*vx - ux*vz) >> 2;
	nz = (ux*vy - uy*vx) >> 2;


	result = (nx*((p->x - p1->x) >> 6) + ny*((p->y - p1->y) >> 6) + nz*((p->z - p1->z) >> 6));

	return result;
};


int smGetThroughPlane(POINT3D *p1, POINT3D *p2, POINT3D *p3, POINT3D *sp, POINT3D *ep, POINT3D *cp)
{
	int ux, uy, uz;
	int vx, vy, vz;


	int nx, ny, nz;
	int denominator, t;
	int lx, ly, lz;


	ux = (p2->x - p1->x);
	uy = (p2->y - p1->y);
	uz = (p2->z - p1->z);

	vx = (p3->x - p1->x);
	vy = (p3->y - p1->y);
	vz = (p3->z - p1->z);



	nx = (uy*vz - uz*vy) >> 3;
	ny = (uz*vx - ux*vz) >> 3;
	nz = (ux*vy - uy*vx) >> 3;

	lx = ep->x - sp->x;
	ly = ep->y - sp->y;
	lz = ep->z - sp->z;

	denominator = (nx * lx + ny * ly + nz * lz) >> 3;


	if(denominator != 0)
	{

		t = (((-nx * sp->x + nx * p1->x) +
			(-ny * sp->y + ny * p1->y) +
			(-nz * sp->z + nz * p1->z)) << 3) / denominator;


		if(t >= 0 && t <= 8)
		{
			cp->x = sp->x + ((lx * t) >> 3);
			cp->y = sp->y + ((ly * t) >> 3);
			cp->z = sp->z + ((lz * t) >> 3);

			return TRUE;
		}
	}

	return FALSE;
};



int smGetTriangleImact(POINT3D *p1, POINT3D *p2, POINT3D *p3, POINT3D *sp, POINT3D *ep)
{

	int vx, vy, vz;
	POINT3D cp1, cp2, cp3;
	int c1, c2;

	c1 = smGetPlaneProduct(p1, p2, p3, sp);
	c2 = smGetPlaneProduct(p1, p2, p3, ep);

	if((c1 <= 0 && c2 <= 0) || (c1 > 0 && c2 > 0))
		return FALSE;

	vx = (ep->x - sp->x) << 4;
	vy = (ep->y - sp->y) << 4;
	vz = (ep->z - sp->z) << 4;

	cp1.x = p1->x + vx;
	cp1.y = p1->y + vy;
	cp1.z = p1->z + vz;

	cp2.x = p2->x + vx;
	cp2.y = p2->y + vy;
	cp2.z = p2->z + vz;

	cp3.x = p3->x + vx;
	cp3.y = p3->y + vy;
	cp3.z = p3->z + vz;

	c1 = smGetPlaneProduct(p1, p2, &cp1, sp);
	if(c1 >= 0)  return FALSE;

	c1 = smGetPlaneProduct(p2, p3, &cp2, sp);
	if(c1 >= 0)  return FALSE;

	c1 = smGetPlaneProduct(p3, p1, &cp3, sp);
	if(c1 >= 0)  return FALSE;

	return TRUE;
};

int smGetTriangleOnArea(smSTAGE_VERTEX *sp1, smSTAGE_VERTEX *sp2, smSTAGE_VERTEX *sp3, POINT3D *sp)
{

	POINT3D cp1, cp2, cp3;
	int c1;
	POINT3D p1, p2, p3;

	p1.x = sp1->x;
	p1.y = sp1->y;
	p1.z = sp1->z;
	p2.x = sp2->x;
	p2.y = sp2->y;
	p2.z = sp2->z;
	p3.x = sp3->x;
	p3.y = sp3->y;
	p3.z = sp3->z;

	cp1.x = p1.x;
	cp1.y = p1.y - 32 * fONE;
	cp1.z = p1.z;

	cp2.x = p2.x;
	cp2.y = p2.y - 32 * fONE;
	cp2.z = p2.z;

	cp3.x = p3.x;
	cp3.y = p3.y - 32 * fONE;
	cp3.z = p3.z;

	c1 = smGetPlaneProduct(&p1, &p2, &cp1, sp);
	if(c1 >= 0)  return FALSE;

	c1 = smGetPlaneProduct(&p2, &p3, &cp2, sp);
	if(c1 >= 0)  return FALSE;

	c1 = smGetPlaneProduct(&p3, &p1, &cp3, sp);
	if(c1 >= 0)  return FALSE;

	return TRUE;
};


static int smMakeTLine(POINT3D *Posi, POINT3D *Angle, int dist, int ObjWidth, int ObjHeight, smLINE3D *Lines, POINT3D *ep)
{
	int width;

	int dist2 = dist + fONE * 12;
	int PosiMinY = fONE * 12;
	int PosiMaxY = ObjHeight - (ObjHeight >> 2);

	width = ObjWidth >> 2;

	GetMoveLocation(0, 0, dist, Angle->x, Angle->y, Angle->z);
	ep->x = Posi->x + GeoResult_X;
	ep->y = Posi->y + GeoResult_Y;
	ep->z = Posi->z + GeoResult_Z;

	GetMoveLocation(0, PosiMinY, 0, Angle->x, Angle->y, Angle->z);
	Lines[0].sp.x = Posi->x + GeoResult_X;
	Lines[0].sp.y = Posi->y + GeoResult_Y;
	Lines[0].sp.z = Posi->z + GeoResult_Z;

	GetMoveLocation(0, PosiMinY, dist2, Angle->x, Angle->y, Angle->z);
	Lines[0].ep.x = Posi->x + GeoResult_X;
	Lines[0].ep.y = Posi->y + GeoResult_Y;
	Lines[0].ep.z = Posi->z + GeoResult_Z;

	GetMoveLocation(0, PosiMaxY, 0, Angle->x, Angle->y, Angle->z);
	Lines[1].sp.x = Posi->x + GeoResult_X;
	Lines[1].sp.y = Posi->y + GeoResult_Y;
	Lines[1].sp.z = Posi->z + GeoResult_Z;

	GetMoveLocation(0, PosiMaxY, dist2, Angle->x, Angle->y, Angle->z);
	Lines[1].ep.x = Posi->x + GeoResult_X;
	Lines[1].ep.y = Posi->y + GeoResult_Y;
	Lines[1].ep.z = Posi->z + GeoResult_Z;

	GetMoveLocation(-width, PosiMinY, dist2, Angle->x, Angle->y, Angle->z);
	Lines[2].sp.x = Posi->x + GeoResult_X;
	Lines[2].sp.y = Posi->y + GeoResult_Y;
	Lines[2].sp.z = Posi->z + GeoResult_Z;

	GetMoveLocation(width, PosiMinY, dist2, Angle->x, Angle->y, Angle->z);
	Lines[2].ep.x = Posi->x + GeoResult_X;
	Lines[2].ep.y = Posi->y + GeoResult_Y;
	Lines[2].ep.z = Posi->z + GeoResult_Z;

	GetMoveLocation(-width, PosiMaxY, dist2, Angle->x, Angle->y, Angle->z);
	Lines[3].sp.x = Posi->x + GeoResult_X;
	Lines[3].sp.y = Posi->y + GeoResult_Y;
	Lines[3].sp.z = Posi->z + GeoResult_Z;

	GetMoveLocation(width, PosiMaxY, dist2, Angle->x, Angle->y, Angle->z);
	Lines[3].ep.x = Posi->x + GeoResult_X;
	Lines[3].ep.y = Posi->y + GeoResult_Y;
	Lines[3].ep.z = Posi->z + GeoResult_Z;

	return 4;
}


static int smMakeXLine(POINT3D *Posi, POINT3D *Angle, int dist, int ObjWidth, int ObjHeight, smLINE3D *Lines, POINT3D *ep)
{
	int width;

	int dist2 = dist + fONE * 12;
	int PosiMinY = fONE * 15;
	int PosiMaxY = ObjHeight - (ObjHeight >> 2);
	int left, right, top, bottom;

	width = ObjWidth >> 2;

	GetMoveLocation(0, 0, dist, Angle->x, Angle->y, Angle->z);
	ep->x = Posi->x + GeoResult_X;
	ep->y = Posi->y + GeoResult_Y;
	ep->z = Posi->z + GeoResult_Z;

	left = -width;
	right = width;
	top = -width;
	bottom = width;

	GetMoveLocation(0, PosiMinY, 0, Angle->x, Angle->y, Angle->z);
	Lines[0].sp.x = Posi->x + GeoResult_X;
	Lines[0].sp.y = Posi->y + GeoResult_Y;
	Lines[0].sp.z = Posi->z + GeoResult_Z;

	GetMoveLocation(0, PosiMinY, dist2, Angle->x, Angle->y, Angle->z);
	Lines[0].ep.x = Posi->x + GeoResult_X;
	Lines[0].ep.y = Posi->y + GeoResult_Y;
	Lines[0].ep.z = Posi->z + GeoResult_Z;

	GetMoveLocation(0, PosiMaxY, 0, Angle->x, Angle->y, Angle->z);
	Lines[1].sp.x = Posi->x + GeoResult_X;
	Lines[1].sp.y = Posi->y + GeoResult_Y;
	Lines[1].sp.z = Posi->z + GeoResult_Z;

	GetMoveLocation(0, PosiMaxY, dist2, Angle->x, Angle->y, Angle->z);
	Lines[1].ep.x = Posi->x + GeoResult_X;
	Lines[1].ep.y = Posi->y + GeoResult_Y;
	Lines[1].ep.z = Posi->z + GeoResult_Z;




	GetMoveLocation(-width, PosiMinY, -width, Angle->x, Angle->y, Angle->z);
	Lines[2].sp.x = ep->x + GeoResult_X;
	Lines[2].sp.y = ep->y + GeoResult_Y;
	Lines[2].sp.z = ep->z + GeoResult_Z;

	GetMoveLocation(width, PosiMinY, width, Angle->x, Angle->y, Angle->z);
	Lines[2].ep.x = ep->x + GeoResult_X;
	Lines[2].ep.y = ep->y + GeoResult_Y;
	Lines[2].ep.z = ep->z + GeoResult_Z;

	GetMoveLocation(-width, PosiMaxY, width, Angle->x, Angle->y, Angle->z);
	Lines[3].sp.x = ep->x + GeoResult_X;
	Lines[3].sp.y = ep->y + GeoResult_Y;
	Lines[3].sp.z = ep->z + GeoResult_Z;

	GetMoveLocation(width, PosiMaxY, -width, Angle->x, Angle->y, Angle->z);
	Lines[3].ep.x = ep->x + GeoResult_X;
	Lines[3].ep.y = ep->y + GeoResult_Y;
	Lines[3].ep.z = ep->z + GeoResult_Z;




	return 6;
}

class smCHAR;

extern smCHAR *CheckOtherPlayPosi(int x, int y, int z);

smSTAGE3D::smSTAGE3D()
{

	VectLight.x = fONE;
	VectLight.y = -fONE;
	VectLight.z = fONE / 2;

	Bright = DEFAULT_BRIGHT;
	Contrast = DEFAULT_CONTRAST;

	Head = FALSE;

	smLight = 0;
	nLight = 0;
	MemMode = 0;


}

smSTAGE3D::smSTAGE3D(int nv, int nf)
{

	VectLight.x = fONE;
	VectLight.y = -fONE;
	VectLight.z = fONE / 2;

	Bright = DEFAULT_BRIGHT;
	Contrast = DEFAULT_CONTRAST;

	Head = FALSE;

	smLight = 0;
	nLight = 0;
	MemMode = 0;


	Init(nv, nf);
}

smSTAGE3D::~smSTAGE3D()
{
	Close();
}


int smSTAGE3D::GetPlaneProduct(smSTAGE_FACE *face, POINT3D *p)
{
	smSTAGE_VERTEX *vp = &Vertex[face->Vertex[0]];


	int result = ((face->VectNormal[0] >> 4) * ((p->x - vp->x) >> 4) +
		(face->VectNormal[1] >> 4) * ((p->y - vp->y) >> 4) +
		(face->VectNormal[2] >> 4) * ((p->z - vp->z) >> 4));

	return result;
};


int smSTAGE3D::GetThroughPlane(smSTAGE_FACE *face, POINT3D *sp, POINT3D *ep)
{


	POINT3D p1, p2, p3, cp, ssp, eep;

	smSTAGE_VERTEX *vp = &Vertex[face->Vertex[0]];
	p1.x = vp->x >> 5;
	p1.y = vp->y >> 5;
	p1.z = vp->z >> 5;

	vp = &Vertex[face->Vertex[1]];
	p2.x = vp->x >> 5;
	p2.y = vp->y >> 5;
	p2.z = vp->z >> 5;

	vp = &Vertex[face->Vertex[2]];
	p3.x = vp->x >> 5;
	p3.y = vp->y >> 5;
	p3.z = vp->z >> 5;

	ssp.x = sp->x >> 5;
	ssp.y = sp->y >> 5;
	ssp.z = sp->z >> 5;

	eep.x = ep->x >> 5;
	eep.y = ep->y >> 5;
	eep.z = ep->z >> 5;

	return smGetThroughPlane(&p1, &p2, &p3, &ssp, &eep, &cp);
};


int smSTAGE3D::GetTriangleImact(smSTAGE_FACE *face, smLINE3D *pLines, int LineCnt)
{
	int vx, vy, vz;
	POINT3D p1, p2, p3;
	POINT3D cp;
	POINT3D *sp, *ep;
	int c1, c2;
	smSTAGE_VERTEX *vp;
	int cnt;
	int flag, TrueCnt;



	vp = &Vertex[face->Vertex[0]];
	p1.x = vp->x;	p1.y = vp->y;	p1.z = vp->z;
	vp = &Vertex[face->Vertex[1]];
	p2.x = vp->x;	p2.y = vp->y;	p2.z = vp->z;
	vp = &Vertex[face->Vertex[2]];
	p3.x = vp->x;	p3.y = vp->y;	p3.z = vp->z;


	TrueCnt = 0;

	for(cnt = 0; cnt < LineCnt; cnt++)
	{
		sp = &pLines[cnt].sp;
		ep = &pLines[cnt].ep;

		flag = TRUE;

		if(((sp->y < p1.y && sp->y < p2.y && sp->y < p3.y) ||
			(sp->y > p1.y && sp->y > p2.y && sp->y > p3.y)) &&
			((ep->y < p1.y && ep->y < p2.y && ep->y < p3.y) ||
			(ep->y > p1.y && ep->y > p2.y && ep->y > p3.y)))
			flag = FALSE;

		if(flag)
		{

			c1 = GetPlaneProduct(face, sp);
			c2 = GetPlaneProduct(face, ep);
			if((c1 <= 0 && c2 <= 0) || (c1 > 0 && c2 > 0)) flag = FALSE;














			if(c1 <= 0)
			{
				vx = (ep->x - sp->x) << 8;
				vy = (ep->y - sp->y) << 8;
				vz = (ep->z - sp->z) << 8;
			}
			else
			{
				vx = (sp->x - ep->x) << 8;
				vy = (ep->y - ep->y) << 8;
				vz = (ep->z - ep->z) << 8;
			}




			if(flag == TRUE)
			{
				cp.x = p1.x + vx;
				cp.y = p1.y + vy;
				cp.z = p1.z + vz;

				c1 = smGetPlaneProduct(&p1, &p2, &cp, sp);








				if(c1 > 0)  flag = FALSE;

			}

			if(flag == TRUE)
			{
				cp.x = p2.x + vx;
				cp.y = p2.y + vy;
				cp.z = p2.z + vz;
				c1 = smGetPlaneProduct(&p2, &p3, &cp, sp);








				if(c1 > 0)  flag = FALSE;

			}

			if(flag == TRUE)
			{
				cp.x = p3.x + vx;
				cp.y = p3.y + vy;
				cp.z = p3.z + vz;
				c1 = smGetPlaneProduct(&p3, &p1, &cp, sp);








				if(c1 > 0)  flag = FALSE;

			}

			if(flag == TRUE)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}


int smSTAGE3D::CheckNextMove(POINT3D *Posi, POINT3D *Angle, POINT3D *MovePosi, int dist, int ObjWidth, int ObjHeight, int CheckOverLap)
{
	int he, height;


	int cnt;
	smSTAGE_FACE *face;

	POINT3D ep;

	POINT3D zAngle[3];

	smLINE3D Lines[8];


	if(!Head) return NULL;

	CheckFace = 0;
	smStage_WaterChk = CLIP_OUT;

	height = CLIP_OUT;

	zAngle[0].x = Angle->x;
	zAngle[0].y = Angle->y;
	zAngle[0].z = Angle->z;

	zAngle[1].x = Angle->x;
	zAngle[1].y = (Angle->y - 768) & ANGCLIP;
	zAngle[1].z = Angle->z;

	zAngle[2].x = Angle->x;
	zAngle[2].y = (Angle->y + 768) & ANGCLIP;
	zAngle[2].z = Angle->z;

	int hy;
	int heFace;

	int acnt;
	int cnt2;
	int Sucess = 0;
	int Oly = Posi->y;
	int	WaterHeight;
	int	whe;

	hy = (ObjHeight + fONE * 16384);

	acnt = MakeAreaFaceList(Posi->x - fONE * 64 * 1, Posi->z - fONE * 64 * 1, fONE * 64 * 2, fONE * 64 * 2, Posi->y + hy, Posi->y - hy);

	if(!acnt) return NULL;

	int ccnt;
	int LineCnt;

	WaterHeight = CLIP_OUT;

	for(ccnt = 0; ccnt < 3; ccnt++)
	{

		LineCnt = smMakeTLine(Posi, &zAngle[ccnt], dist, ObjWidth, ObjHeight, Lines, &ep);


		for(cnt = 0; cnt < acnt; cnt++)
		{

			face = smFaceList[cnt];

			if(smMaterial[face->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
			{
				he = GetPolyHeight(face, ep.x, ep.z);
				if(he != CLIP_OUT)
				{
					hy = he - ep.y;
					if(hy < Stage_StepHeight)
					{
						if(height < he)
						{
							height = he;
							heFace = cnt;
						}
					}

					CheckFace = face;
				}
			}
			else
			{




				if(smMaterial[face->Vertex[3]].Transparency > 0.1 || smMaterial[face->Vertex[3]].MeshState & sMATS_SCRIPT_ORG_WATER)

				{

					he = GetPolyHeight(face, ep.x, ep.z);
					if(WaterHeight < he) WaterHeight = he;
				}
			}
		}

		if(height != CLIP_OUT)
		{
			smStage_WaterChk = WaterHeight;
			whe = (height + (ObjHeight >> 1)) + 10 * fONE;
			if(WaterHeight != CLIP_OUT && WaterHeight > whe &&
				WaterHeight < whe + 5 * fONE)
			{


				cnt2 = 0;
			}
			else
			{
				for(cnt2 = 0; cnt2 < acnt; cnt2++)
				{
					if(smMaterial[smFaceList[cnt2]->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
					{
						if(GetTriangleImact(smFaceList[cnt2], Lines, LineCnt) == TRUE)
						{
							cnt2 = -1;
							break;
						}
					}
				}
			}

			if(cnt2 > 0)
			{
				if(CheckOverLap)
				{
					if(ccnt > 0 && CheckOtherPlayPosi(ep.x, height, ep.z) == NULL)
					{
						MovePosi->x = ep.x;
						MovePosi->z = ep.z;
						MovePosi->y = height;
						Sucess = TRUE;
						return ccnt + 1;
					}
				}
				else
				{
					MovePosi->x = ep.x;
					MovePosi->z = ep.z;
					MovePosi->y = height;
					Sucess = TRUE;
					return ccnt + 1;
				}
			}
		}

		if(ccnt == 0) dist >>= 1;
	}

	CheckFace = 0;

	return NULL;
}


int smSTAGE3D::GetFloorHeight(int x, int y, int z, int ObjHeight)
{
	int he, height;

	int cnt;
	smSTAGE_FACE *face;

	int hy;
	int acnt;

	hy = (ObjHeight + fONE * 16384);

	acnt = MakeAreaFaceList(x - fONE * 64 * 1, z - fONE * 64 * 1, fONE * 64 * 2, fONE * 64 * 2, y + hy, y - hy);

	if(!acnt) return CLIP_OUT;

	height = CLIP_OUT;

	for(cnt = 0; cnt < acnt; cnt++)
	{

		face = smFaceList[cnt];

		if(smMaterial[face->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
		{

			he = GetPolyHeight(face, x, z);
			if(he != CLIP_OUT)
			{
				hy = he - y;
				if(hy < 10 * fONE)
				{
					if(height < he)
					{
						height = he;
					}
				}
			}
		}
	}

	return height;
}


int smSTAGE3D::GetFloorHeight2(int x, int y, int z, int ObjHeight)
{
	int he, height;

	int cnt;
	smSTAGE_FACE *face;

	int hy;
	int acnt;

	hy = (ObjHeight + fONE * 16384);

	acnt = MakeAreaFaceList(x - fONE * 64 * 1, z - fONE * 64 * 1, fONE * 64 * 2, fONE * 64 * 2, y + hy, y - hy);

	if(!acnt) return CLIP_OUT;

	height = CLIP_OUT;

	for(cnt = 0; cnt < acnt; cnt++)
	{

		face = smFaceList[cnt];

		if(smMaterial[face->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
		{

			he = GetPolyHeight(face, x, z);
			if(he != CLIP_OUT)
			{
				hy = he - y;
				if(hy > 10 * fONE)
				{
					if(height > he)
					{
						height = he;
					}
				}
			}
		}
	}

	return height;
}


int smSTAGE3D::GetEmptyHeight(int x, int y, int z, int ObjHeight)
{
	int he, height;

	int cnt;
	smSTAGE_FACE *face;

	int hy;
	int acnt;
	int fchk;

	fchk = 0;

	hy = (ObjHeight + fONE * 16384);

	acnt = MakeAreaFaceList(x - fONE * 64 * 1, z - fONE * 64 * 1, fONE * 64 * 2, fONE * 64 * 2, y + hy, y - hy);

	if(!acnt) return CLIP_OUT;

	height = CLIP_OUT;

	for(cnt = 0; cnt < acnt; cnt++)
	{

		face = smFaceList[cnt];

		if(smMaterial[face->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
		{

			he = GetPolyHeight(face, x, z);
			if(he != CLIP_OUT)
			{
				if(height < he)
				{
					height = he;
				}
				if(he<y + ObjHeight && he>y)
					fchk++;
			}
		}
	}

	if(fchk == 0) return NULL;

	return height;
}


int smSTAGE3D::CheckFloorFaceHeight(int x, int y, int z, int hSize)
{
	int cnt;
	smSTAGE_FACE *face;

	int	height = 1000000;
	int acnt;
	int he;
	int hy = fONE * 16384;

	acnt = MakeAreaFaceList(x - fONE * 64 * 1, z - fONE * 64 * 1, fONE * 64 * 2, fONE * 64 * 2, y + hy, y - hy);

	if(!acnt) return CLIP_OUT;

	for(cnt = 0; cnt < acnt; cnt++)
	{
		face = smFaceList[cnt];
		if(smMaterial[face->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
		{
			he = abs(GetPolyHeight(face, x, z) - y);
			if(he < height) height = he;
			if(he <= hSize) return 0;
		}
	}

	if(height == 1000000) height = CLIP_OUT;

	return height;
}


int smSTAGE3D::CheckVecImpact(POINT3D *Posi, POINT3D *Angle, int dist)
{
	smLINE3D sLine[1];

	if(!Head) return 0;

	int hy;
	int acnt;
	int cnt2;

	hy = (fONE * 64);

	acnt = MakeAreaFaceList(Posi->x - fONE * 64 * 1, Posi->z - fONE * 64 * 1, fONE * 64 * 2, fONE * 64 * 2, Posi->y + hy, Posi->y - hy);

	if(!acnt) return TRUE;

	memcpy(&sLine[0].sp, Posi, sizeof(POINT3D));
	GetMoveLocation(0, 0, dist, Angle->x, Angle->y, Angle->z);

	sLine[0].ep.x = Posi->x + GeoResult_X;
	sLine[0].ep.y = Posi->y + GeoResult_Y;
	sLine[0].ep.z = Posi->z + GeoResult_Z;

	for(cnt2 = 0; cnt2 < acnt; cnt2++)
	{
		if(smMaterial[smFaceList[cnt2]->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
		{
			if(GetTriangleImact(smFaceList[cnt2], sLine, 1) == TRUE)
			{

				Posi->x = sLine[0].ep.x;
				Posi->y = sLine[0].ep.y;
				Posi->z = sLine[0].ep.z;

				return FALSE;
			}
		}
	}

	Posi->x = sLine[0].ep.x;
	Posi->y = sLine[0].ep.y;
	Posi->z = sLine[0].ep.z;

	return TRUE;
}


int smSTAGE3D::CheckVecImpact2(int sx, int sy, int sz, int ex, int ey, int ez)
{
	smLINE3D sLine[1];

	if(!Head) return 0;

	int hy;
	int acnt;
	int cnt2;

	hy = (fONE * 128);

	acnt = MakeAreaFaceList(sx - fONE * 64 * 1, sz - fONE * 64 * 1, fONE * 64 * 2, fONE * 64 * 2, sy + hy, sy - hy);

	if(!acnt) return TRUE;

	sLine[0].sp.x = sx;
	sLine[0].sp.y = sy;
	sLine[0].sp.z = sz;

	sLine[0].ep.x = ex;
	sLine[0].ep.y = ey;
	sLine[0].ep.z = ez;

	for(cnt2 = 0; cnt2 < acnt; cnt2++)
	{
		if(smMaterial[smFaceList[cnt2]->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
		{
			if(GetTriangleImact(smFaceList[cnt2], sLine, 1) == TRUE)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}



void smSTAGE3D::Init(void)
{
	nLight = 0;
	nTexLink = 0;
	nFace = 0;
	nVertex = 0;

	::ZeroMemory(StageArea, sizeof(StageArea));

	AreaList = NULL;
	Vertex = NULL;
	Face = NULL;
	TexLink = NULL;
	smLight = NULL;
	smMaterialGroup = NULL;
	StageObject = NULL;
	smMaterial = NULL;
	lpwAreaBuff = NULL;
}


int smSTAGE3D::Init(int nv, int nf)
{
	Vertex = new smSTAGE_VERTEX[nv];
	Face = new smSTAGE_FACE[nf];
	TexLink = new smTEXLINK[nf * 4];
	StageObject = new smSTAGE_OBJECT;

	nVertex = 0;
	nFace = 0;
	nTexLink = 0;

	nVertColor = 0;

	SumCount = 0;
	CalcSumCount = 0;

	smMaterialGroup = 0;
	lpwAreaBuff = 0;

	StageMapRect.top = 0;
	StageMapRect.bottom = 0;
	StageMapRect.left = 0;
	StageMapRect.right = 0;

	clearStageArea();

	return TRUE;
}

int smSTAGE3D::Close()
{
	Head = 0;




	if(nLight) delete smLight;

	if(lpwAreaBuff) delete lpwAreaBuff;

	if(nTexLink) delete	TexLink;
	if(nFace)	delete	Face;
	if(nVertex)	delete	Vertex;

	if(StageObject) delete StageObject;
	if(smMaterialGroup) delete smMaterialGroup;


	return TRUE;
}


int smSTAGE3D::AddVertex(int x, int y, int z)
{
	Vertex[nVertex].sum = 0;
	Vertex[nVertex].x = x;
	Vertex[nVertex].y = y;
	Vertex[nVertex].z = z;

	Vertex[nVertex].sDef_Color[SMC_R] = 255;
	Vertex[nVertex].sDef_Color[SMC_G] = 255;
	Vertex[nVertex].sDef_Color[SMC_B] = 255;
	Vertex[nVertex].sDef_Color[SMC_A] = 255;

	if(nVertex == 0)
	{

		StageMapRect.top = z;
		StageMapRect.bottom = z;
		StageMapRect.left = x;
		StageMapRect.right = x;
	}
	else
	{

		if(StageMapRect.top > z)		StageMapRect.top = z;
		if(StageMapRect.bottom < z)	StageMapRect.bottom = z;
		if(StageMapRect.left > x)		StageMapRect.left = x;
		if(StageMapRect.right < x)		StageMapRect.right = x;
	}

	nVertex++;

	return (nVertex - 1);
}


int smSTAGE3D::AddFace(int a, int b, int c, int matrial)
{
	Face[nFace].sum = 0;
	Face[nFace].Vertex[0] = a;
	Face[nFace].Vertex[1] = b;
	Face[nFace].Vertex[2] = c;
	Face[nFace].Vertex[3] = matrial;

	Face[nFace].lpTexLink = 0;

	nFace++;

	return nFace - 1;
}


int smSTAGE3D::SetFaceMaterial(int FaceNum, int MatNum)
{
	Face[FaceNum].Vertex[3] = MatNum;

	return TRUE;
}


int smSTAGE3D::SetVertexColor(DWORD NumVertex, BYTE r, BYTE g, BYTE b, BYTE a)
{

	Vertex[NumVertex].sDef_Color[SMC_R] = r;
	Vertex[NumVertex].sDef_Color[SMC_G] = g;
	Vertex[NumVertex].sDef_Color[SMC_B] = b;
	Vertex[NumVertex].sDef_Color[SMC_A] = a;

	return TRUE;
}


int smSTAGE3D::AddTexLink(int FaceNum, DWORD *hTex, smFTPOINT *t1, smFTPOINT *t2, smFTPOINT *t3)
{
	int cnt;
	smTEXLINK	*tl;


	TexLink[nTexLink].u[0] = t1->u;
	TexLink[nTexLink].v[0] = t1->v;
	TexLink[nTexLink].u[1] = t2->u;
	TexLink[nTexLink].v[1] = t2->v;
	TexLink[nTexLink].u[2] = t3->u;
	TexLink[nTexLink].v[2] = t3->v;
	TexLink[nTexLink].hTexture = hTex;
	TexLink[nTexLink].NextTex = 0;


	if(!Face[FaceNum].lpTexLink)
	{

		Face[FaceNum].lpTexLink = &TexLink[nTexLink];
	}
	else
	{

		tl = Face[FaceNum].lpTexLink;

		for(cnt = 0; cnt < 8; cnt++)
		{
			if(!tl->NextTex)
			{

				tl->NextTex = &TexLink[nTexLink];
				break;
			}
			else
			{

				tl = tl->NextTex;
			}

		}
	}

	nTexLink++;

	return nTexLink - 1;
}




int smSTAGE3D::SetVertexShade(int isSetLight)

{
	int cnt;
	int cnt2;
	POINT3D	p[3];
	POINT3D pn;
	POINT3D *normal;
	POINT3D pLight;
	int	*NormalCnt;
	int gShade;
	int r, g, b;

	memcpy(&pLight, &VectLight, sizeof(POINT3D));

	normal = new POINT3D[nVertex];
	NormalCnt = new int[nVertex];


	for(cnt = 0; cnt < nVertex; cnt++)
	{
		normal[cnt].x = 0;
		normal[cnt].y = 0;
		normal[cnt].z = 0;
		NormalCnt[cnt] = 0;
	}


	for(cnt = 0; cnt < nFace; cnt++)
	{
		for(cnt2 = 0; cnt2 < 3; cnt2++)
		{
			p[cnt2].x = Vertex[Face[cnt].Vertex[cnt2]].x >> FLOATNS;
			p[cnt2].y = Vertex[Face[cnt].Vertex[cnt2]].y >> FLOATNS;
			p[cnt2].z = Vertex[Face[cnt].Vertex[cnt2]].z >> FLOATNS;
		}

		SetNormal(&p[0], &p[1], &p[2], &pn);


		Face[cnt].VectNormal[0] = (short)pn.x;
		Face[cnt].VectNormal[1] = (short)pn.y;
		Face[cnt].VectNormal[2] = (short)pn.z;

		for(cnt2 = 0; cnt2 < 3; cnt2++)
		{
			normal[Face[cnt].Vertex[cnt2]].x += pn.x;
			normal[Face[cnt].Vertex[cnt2]].y += pn.y;
			normal[Face[cnt].Vertex[cnt2]].z += pn.z;
			NormalCnt[Face[cnt].Vertex[cnt2]] ++;
		}
	}



	for(cnt = 0; cnt < nVertex; cnt++)
	{
		if(NormalCnt[cnt] > 0)
		{
			normal[cnt].x /= NormalCnt[cnt];
			normal[cnt].y /= NormalCnt[cnt];
			normal[cnt].z /= NormalCnt[cnt];
		}
		pn.x = normal[cnt].x;
		pn.y = normal[cnt].y;
		pn.z = normal[cnt].z;



		if(isSetLight)
		{
			gShade = ((pn.x * pLight.x) + (pn.y * pLight.y) + (pn.z * pLight.z)) >> FLOATNS;
			gShade /= Contrast;
			gShade += Bright;

			r = Vertex[cnt].sDef_Color[SMC_R];
			g = Vertex[cnt].sDef_Color[SMC_G];
			b = Vertex[cnt].sDef_Color[SMC_B];

			r = (r*gShade) >> 8;
			g = (g*gShade) >> 8;
			b = (b*gShade) >> 8;

			Vertex[cnt].sDef_Color[SMC_R] = r;
			Vertex[cnt].sDef_Color[SMC_G] = g;
			Vertex[cnt].sDef_Color[SMC_B] = b;
			Vertex[cnt].sDef_Color[SMC_A] = 255;
		}

	}

	float transp;

	for(cnt = 0; cnt < nFace; cnt++)
	{

		transp = smMaterial[Face[cnt].Vertex[3]].Transparency;

		if(transp > 0)
		{
			for(cnt2 = 0; cnt2 < 3; cnt2++)
			{
				Vertex[Face[cnt].Vertex[cnt2]].sDef_Color[SMC_A] = 255 - ((BYTE)(transp * 255));
			}
		}
	}


	delete NormalCnt;
	delete normal;

	return TRUE;
}


int smSTAGE3D::AddVertexLightRound(POINT3D *LightPos, int r, int g, int b, int Range)
{
	int cnt;
	int ddist;
	int dist;
	int dr, dg, db;
	int lx, ly, lz;
	int dRange;
	int x, y, z;
	int eLight;

	dRange = ((Range / 256) * 72) >> FLOATNS;
	dRange *= dRange;

	lx = LightPos->x;
	ly = LightPos->y;
	lz = LightPos->z;

	for(cnt = 0; cnt < nVertex; cnt++)
	{
		x = (lx - Vertex[cnt].x) >> FLOATNS;
		y = (ly - Vertex[cnt].y) >> FLOATNS;
		z = (lz - Vertex[cnt].z) >> FLOATNS;

		ddist = x*x + y*y + z*z;

		if(ddist < dRange)
		{


			dist = (int)sqrt((long double)ddist);
			eLight = (Range >> FLOATNS) - dist;

			eLight = fONE - ((eLight << FLOATNS) / dRange);

			dr = (r * eLight) >> FLOATNS;
			dg = (g * eLight) >> FLOATNS;
			db = (b * eLight) >> FLOATNS;

			Vertex[cnt].sDef_Color[SMC_R] += dr;
			Vertex[cnt].sDef_Color[SMC_G] += dg;
			Vertex[cnt].sDef_Color[SMC_B] += db;


			if(Vertex[cnt].sDef_Color[SMC_R] > 360) Vertex[cnt].sDef_Color[SMC_R] = 360;
			if(Vertex[cnt].sDef_Color[SMC_G] > 360) Vertex[cnt].sDef_Color[SMC_G] = 360;
			if(Vertex[cnt].sDef_Color[SMC_B] > 360) Vertex[cnt].sDef_Color[SMC_B] = 360;



		}
	}

	return TRUE;
}


int	smSTAGE3D::InitDynLight(int nl)
{
	nLight = 0;
	smLight = new smLIGHT3D[nl];

	return TRUE;
}


int smSTAGE3D::AddDynLight(int type, POINT3D *LightPos, int r, int g, int b, int Range)
{

	smLight[nLight].type = type;
	smLight[nLight].x = LightPos->x;
	smLight[nLight].y = LightPos->y;
	smLight[nLight].z = LightPos->z;
	smLight[nLight].r = r;
	smLight[nLight].g = g;
	smLight[nLight].b = b;
	smLight[nLight].Range = Range;


	nLight++;

	return TRUE;
}


int smSTAGE3D::CheckFaceIceFoot(POINT3D *Pos, POINT3D *Angle, int CheckHeight)
{
	int num = CheckHeight + (fONE * 16384);
	int acnt = MakeAreaFaceList(Pos->x - (fONE * 64 * 1), Pos->z - (fONE * 64 * 1),
		fONE * 64 * 2, fONE * 64 * 2, Pos->y + num, Pos->y - num);
	if(!acnt)
		return 0;

	smSTAGE_FACE *face;
	int			  faceNum = 0, faceheight = CLIP_OUT;
	for(int cnt = 0; cnt < acnt; cnt++)
	{
		face = smFaceList[cnt];
		num = smMaterial[face->Vertex[3]].MeshState;

		if((num & SMMAT_STAT_CHECK_FACE) && (num & sMATS_SCRIPT_CHECK_ICE))
		{
			num = GetPolyHeight(face, Pos->x, Pos->z);
			if(num != CLIP_OUT)
			{
				if((num - Pos->y) < 10 * fONE)
				{
					if(faceheight < num)
					{
						faceheight = num;
						faceNum = cnt;
					}
				}
			}
		}
	}

	if(faceNum == 0)
		return 0;

	face = smFaceList[faceNum];
	Angle->x = GetRadian2D(0, -1024, face->VectNormal[2], face->VectNormal[1]);
	Angle->z = GetRadian2D(0, -1024, face->VectNormal[0], face->VectNormal[1]);
	Pos->y = faceheight + (1 * fONE);
	return 1;
}







int smSTAGE3D::MakeAreaFaceList(int x, int z, int width, int height, int top, int bottom)
{
	int cnt;
	smSTAGE_FACE *face;
	int CalcSum;
	int wx, wz;
	int lx, lz;
	int num, fnum;

	int cntX, cntZ;
	int sx, sz;
	int y1, y2, y3;

	smFaceListCnt = 0;

	CalcSumCount++;
	CalcSum = CalcSumCount;

	sx = (x >> (FLOATNS + 6)) & 0xFF;
	sz = (z >> (FLOATNS + 6)) & 0xFF;

	wx = sx + (width >> (FLOATNS + 6));
	wz = sz + (height >> (FLOATNS + 6));


	for(cntX = sx; cntX < wx; cntX++)
	{
		for(cntZ = sz; cntZ < wz; cntZ++)
		{
			lx = cntX & 0xFF;
			lz = cntZ & 0xFF;

			if(StageArea[lx][lz])
			{
				num = StageArea[lx][lz][0];

				for(cnt = 1; cnt < num + 1; cnt++)
				{
					fnum = StageArea[lx][lz][cnt];
					face = &Face[fnum];
					if(face->CalcSum != CalcSum)
					{
						face->CalcSum = CalcSum;
						y1 = Vertex[face->Vertex[0]].y;
						y2 = Vertex[face->Vertex[1]].y;
						y3 = Vertex[face->Vertex[2]].y;
						if((y1<top && y1>bottom) || (y2<top && y2>bottom) || (y3<top && y3>bottom))
							smFaceList[smFaceListCnt++] = face;
					}
				}
			}
		}
	}

	CalcSumCount++;

	return smFaceListCnt;
}


int smSTAGE3D::GetPolyHeight(smSTAGE_FACE *face, int x, int z)
{
	smSTAGE_VERTEX		*p[3];
	smSTAGE_VERTEX		*ptop, *pmid, *pbot;

	int cnt;

	int lx, tx, bx;
	int ly, ty, by;
	int   lz, tz, bz;

	int   x1, x2;
	int   y1, y2;
	int	  ye, xe;
	int	  yl;

	p[0] = &Vertex[face->Vertex[0]];
	p[1] = &Vertex[face->Vertex[1]];
	p[2] = &Vertex[face->Vertex[2]];

	ptop = p[0];
	pbot = p[1];
	pmid = p[2];


	for(cnt = 0; cnt < 3; cnt++)
	{
		if(p[cnt]->z < ptop->z) ptop = p[cnt];
	}

	if(ptop == pbot) pbot = pmid;


	for(cnt = 0; cnt < 3; cnt++)
	{
		if(p[cnt]->z > pbot->z && ptop != p[cnt]) pbot = p[cnt];
	}


	for(cnt = 0; cnt < 3; cnt++)
	{
		if(ptop != p[cnt] && pbot != p[cnt])
		{
			pmid = p[cnt];
			break;
		}
	}

	if(z<ptop->z || z>pbot->z)
		return CLIP_OUT;

	lz = pbot->z - ptop->z;
	tz = pmid->z - ptop->z;
	bz = pbot->z - pmid->z;

	if(lz != 0) lx = ((pbot->x - ptop->x) << FLOATNS) / lz;
	else lx = 0;
	if(tz != 0) tx = ((pmid->x - ptop->x) << FLOATNS) / tz;
	else tx = 0;
	if(bz != 0) bx = ((pbot->x - pmid->x) << FLOATNS) / bz;
	else bx = 0;

	x1 = ((lx * (z - ptop->z)) >> FLOATNS) + ptop->x;

	if(z < pmid->z)
	{
		x2 = ((tx * (z - ptop->z)) >> FLOATNS) + ptop->x;
	}
	else
	{
		x2 = ((bx * (z - pmid->z)) >> FLOATNS) + pmid->x;
	}


	if(lz != 0) ly = ((pbot->y - ptop->y) << FLOATNS) / lz;
	else ly = 0;
	if(tz != 0) ty = ((pmid->y - ptop->y) << FLOATNS) / tz;
	else ty = 0;
	if(bz != 0) by = ((pbot->y - pmid->y) << FLOATNS) / bz;
	else by = 0;

	y1 = ((ly * (z - ptop->z)) >> FLOATNS) + ptop->y;

	if(z < pmid->z)
	{
		y2 = ((ty * (z - ptop->z)) >> FLOATNS) + ptop->y;
	}
	else
	{
		y2 = ((by * (z - pmid->z)) >> FLOATNS) + pmid->y;
	}

	if(x1 > x2)
	{
		cnt = x1; x1 = x2; x2 = cnt;
		cnt = y1; y1 = y2; y2 = cnt;
	}

	if(x<x1 || x>x2)
		return CLIP_OUT;


	xe = x2 - x1;
	ye = y2 - y1;

	if(xe != 0) yl = (ye << FLOATNS) / xe;
	else yl = y1;

	return ((yl * (x - x1)) >> FLOATNS) + y1;
}


int smSTAGE3D::GetAreaHeight(int ax, int az, int x, int z)
{
	int he, height;
	int num, fnum;

	int cnt;
	smSTAGE_FACE *face;
	int CalcSum;
	int lx, lz;

	lx = ax & 0xFF;
	lz = az & 0xFF;

	CalcSum = CalcSumCount;
	height = -200 * fONE;

	if(StageArea[lx][lz])
	{
		num = StageArea[lx][lz][0];
		for(cnt = 1; cnt < num + 1; cnt++)
		{
			fnum = StageArea[lx][lz][cnt];
			face = &Face[fnum];
			
			if(face->CalcSum != CalcSum && smMaterial[face->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
			{
				face->CalcSum = CalcSum;
				he = GetPolyHeight(face, x, z);
				if(he != CLIP_OUT && he > height)
					height = he;
			}
		}
	}

	return height;
}


int smSTAGE3D::GetAreaHeight2(int ax, int az, int x, int z)
{
	int he, height;
	int num, fnum;

	int cnt;
	smSTAGE_FACE *face;
	int CalcSum;
	int lx, lz;

	lx = ax & 0xFF;
	lz = az & 0xFF;

	CalcSum = CalcSumCount;
	height = -200 * fONE;

	if(StageArea[lx][lz])
	{
		num = StageArea[lx][lz][0];
		for(cnt = 1; cnt < num + 1; cnt++)
		{
			fnum = StageArea[lx][lz][cnt];
			face = &Face[fnum];



			if(face->CalcSum != CalcSum)
			{
				face->CalcSum = CalcSum;
				he = GetPolyHeight(face, x, z);
				if(he != CLIP_OUT && he > height) height = he;
			}
		}
	}

	return height;
}


int smSTAGE3D::GetHeight(int x, int z)
{
	int lx, lz;
	int height = 0;

	if(!Head) return 0;

	lx = x >> (6 + FLOATNS);
	lz = z >> (6 + FLOATNS);

	height = GetAreaHeight(lx, lz, x, z);

	CalcSumCount++;

	return height;
}


int smSTAGE3D::GetHeight2(int x, int z)
{
	int lx, lz;
	int height = 0;

	if(!Head) return 0;

	lx = x >> (6 + FLOATNS);
	lz = z >> (6 + FLOATNS);

	height = GetAreaHeight2(lx, lz, x, z);

	CalcSumCount++;

	return height;
}


int smSTAGE3D::CheckSolid(int sx, int sy, int sz, int dx, int dy, int dz)
{
	int num, fnum;

	int cnt;
	smSTAGE_FACE *face;
	int CalcSum;
	int lx, lz;

	POINT3D p1, p2, p3, sp, dp;

	sp.x = sx; sp.y = sy; sp.z = sz;
	dp.x = dx; dp.y = dy; dp.z = dz;


	CalcSum = CalcSumCount;

	lx = dx >> (6 + FLOATNS);
	lz = dz >> (6 + FLOATNS);
	lx &= 0xFF;
	lz &= 0xFF;

	if(StageArea[lx][lz])
	{
		num = StageArea[lx][lz][0];

		for(cnt = 1; cnt < num + 1; cnt++)
		{
			fnum = StageArea[lx][lz][cnt];
			face = &Face[fnum];

			if(face->CalcSum != CalcSum && smMaterial[face->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
			{
				face->CalcSum = CalcSum;

				p1.x = Vertex[face->Vertex[0]].x;
				p1.y = Vertex[face->Vertex[0]].y;
				p1.z = Vertex[face->Vertex[0]].z;
				p2.x = Vertex[face->Vertex[1]].x;
				p2.y = Vertex[face->Vertex[1]].y;
				p2.z = Vertex[face->Vertex[1]].z;
				p3.x = Vertex[face->Vertex[2]].x;
				p3.y = Vertex[face->Vertex[2]].y;
				p3.z = Vertex[face->Vertex[2]].z;

				if(smGetTriangleImact(&p1, &p2, &p3, &sp, &dp) == TRUE)
				{
					CalcSumCount++;
					return TRUE;
				}
			}
		}
	}

	lx = sx >> (6 + FLOATNS);
	lz = sz >> (6 + FLOATNS);
	lx &= 0xFF;
	lz &= 0xFF;

	if(StageArea[lx][lz])
	{
		num = StageArea[lx][lz][0];

		for(cnt = 1; cnt < num + 1; cnt++)
		{
			fnum = StageArea[lx][lz][cnt];
			face = &Face[fnum];

			if(face->CalcSum != CalcSum && smMaterial[face->Vertex[3]].MeshState & SMMAT_STAT_CHECK_FACE)
			{
				face->CalcSum = CalcSum;

				p1.x = Vertex[face->Vertex[0]].x;
				p1.y = Vertex[face->Vertex[0]].y;
				p1.z = Vertex[face->Vertex[0]].z;
				p2.x = Vertex[face->Vertex[1]].x;
				p2.y = Vertex[face->Vertex[1]].y;
				p2.z = Vertex[face->Vertex[1]].z;
				p3.x = Vertex[face->Vertex[2]].x;
				p3.y = Vertex[face->Vertex[2]].y;
				p3.z = Vertex[face->Vertex[2]].z;

				if(smGetTriangleImact(&p1, &p2, &p3, &sp, &dp) == TRUE)
				{
					CalcSumCount++;
					return TRUE;
				}
			}
		}
	}

	CalcSumCount++;

	return FALSE;
}


void smSTAGE3D::clearStageArea()
{
	for(int y = 0; y < MAP_SIZE; y++)
	{
		for(int x = 0; x < MAP_SIZE; x++)
		{
			StageArea[x][y] = 0;
		}
	}
}


int smSTAGE3D::getPolyAreas(POINT3D *ip1, POINT3D *ip2, POINT3D *ip3)
{
	POINT3D		p1, p2, p3;
	POINT3D		*p[3];

	int cnt;

	int left, right, top, bottom;
	int cntX, cntY;

	memcpy(&p1, ip1, sizeof(POINT3D));
	memcpy(&p2, ip2, sizeof(POINT3D));
	memcpy(&p3, ip3, sizeof(POINT3D));

	p[0] = &p1;
	p[1] = &p2;
	p[2] = &p3;


	left = p[0]->x; right = p[0]->x;
	top = p[0]->z; bottom = p[0]->z;

	for(cnt = 1; cnt < 3; cnt++)
	{
		if(p[cnt]->x < left)		left = p[cnt]->x;
		if(p[cnt]->x > right)	right = p[cnt]->x;
		if(p[cnt]->z < top)		top = p[cnt]->z;
		if(p[cnt]->z > bottom)	bottom = p[cnt]->z;
	}

	left >>= 6; right >>= 6;
	top >>= 6; bottom >>= 6;
	right++; bottom++;
	AreaListCnt = 0;

	for(cntX = left; cntX < right; cntX++)
	{
		for(cntY = top; cntY < bottom; cntY++)
		{
			AreaList[AreaListCnt].x = cntX & 0xFF;
			AreaList[AreaListCnt].y = cntY & 0xFF;
			AreaListCnt++;
		}
	}

	return TRUE;
}


int smSTAGE3D::SetupPolyAreas()
{
	POINT3D p[3];
	int cnt, cnt2;
	int num;


	clearStageArea();


	AreaList = new POINT[4096];

	for(cnt = 0; cnt < nFace; cnt++)
	{
		for(cnt2 = 0; cnt2 < 3; cnt2++)
		{
			p[cnt2].x = Vertex[Face[cnt].Vertex[cnt2]].x >> FLOATNS;
			p[cnt2].y = Vertex[Face[cnt].Vertex[cnt2]].y >> FLOATNS;
			p[cnt2].z = Vertex[Face[cnt].Vertex[cnt2]].z >> FLOATNS;
		}

		getPolyAreas(&p[0], &p[1], &p[2]);


		if(AreaListCnt > 0)
		{
			for(cnt2 = 0; cnt2 < AreaListCnt; cnt2++)
			{
				StageArea[AreaList[cnt2].x][AreaList[cnt2].y]++;
			}
		}
	}
	delete AreaList;


	int wbCnt;

	wbCnt = 0;


	for(cnt2 = 0; cnt2 < MAP_SIZE; cnt2++)
	{
		for(cnt = 0; cnt < MAP_SIZE; cnt++)
		{
			num = (int)StageArea[cnt][cnt2];

			if(num > 0)
			{
				wbCnt += num + 1;
			}
		}
	}

	wAreaSize = wbCnt;


	lpwAreaBuff = new DWORD[wbCnt];

	wbCnt = 0;


	for(cnt2 = 0; cnt2 < MAP_SIZE; cnt2++)
	{
		for(cnt = 0; cnt < MAP_SIZE; cnt++)
		{
			num = (int)StageArea[cnt][cnt2];
			if(num > 0)
			{
				StageArea[cnt][cnt2] = &lpwAreaBuff[wbCnt];
				StageArea[cnt][cnt2][0] = 0;
				wbCnt += num + 1;
			}
		}
	}



	AreaList = new POINT[4096];


	for(cnt = 0; cnt < nFace; cnt++)
	{
		for(cnt2 = 0; cnt2 < 3; cnt2++)
		{
			p[cnt2].x = Vertex[Face[cnt].Vertex[cnt2]].x >> FLOATNS;
			p[cnt2].y = Vertex[Face[cnt].Vertex[cnt2]].y >> FLOATNS;
			p[cnt2].z = Vertex[Face[cnt].Vertex[cnt2]].z >> FLOATNS;
		}

		getPolyAreas(&p[0], &p[1], &p[2]);

		if(AreaListCnt > 0)
		{
			for(cnt2 = 0; cnt2 < AreaListCnt; cnt2++)
			{
				StageArea[AreaList[cnt2].x][AreaList[cnt2].y][0]++;
				num = StageArea[AreaList[cnt2].x][AreaList[cnt2].y][0];
				StageArea[AreaList[cnt2].x][AreaList[cnt2].y][num] = cnt;
			}
		}
	}
	delete AreaList;

	return TRUE;

}


int smSTAGE3D::RenderGeom()
{
	int cnt;
	int x1, x2;
	int t;

	int num;
	int fnum;

	smSTAGE_FACE *face;
	int clipW, clipH;
	smRENDFACE *rendface;

	int k = 0;

	if(smMaterialGroup)
		smRender.SetMaterialGroup(smMaterialGroup);


	smRender.InitStageMesh(Vertex, SumCount);

	for(int h = MapPosiTop; h < MapPosiBot; h++)
	{
		x1 = MapPosiLeft[h & 0xFF];
		x2 = MapPosiRight[h & 0xFF];
		if(x1 > x2)
		{
			t = x1; x1 = x2; x2 = t;
		}
		clipH = h & 0xFF;

		for(int w = x1; w < x2; w++)
		{
			clipW = w & 0xFF;
			if(StageArea[clipW][clipH])
			{
				num = StageArea[clipW][clipH][0];

				for(cnt = 1; cnt < num + 1; cnt++)
				{
					fnum = StageArea[clipW][clipH][cnt];
					face = &Face[fnum];

					if(face->sum != SumCount)
					{
						rendface = smRender.AddStageFace(face);
					}
					k++;
				}
			}
		}
	}

	smRender.ClipRendFace();
	smRender.GeomVertex2D();

	return TRUE;
}

#define STAGE_RECT_LIMIT (30 * 64 * fONE)
#define STAGE_RECT_LIMIT2 (320 * 64 * fONE)

int smSTAGE3D::DrawStage(int x, int y, int z, int angX, int angY, int angZ, smEMATRIX *eRotMatrix)
{
	if(!Head)
		return 0;

	SumCount++;


	if(z < (StageMapRect.top - STAGE_RECT_LIMIT)) return FALSE;
	if(z > (StageMapRect.bottom + STAGE_RECT_LIMIT)) return FALSE;
	if(x < (StageMapRect.left - STAGE_RECT_LIMIT)) return FALSE;
	if(x > (StageMapRect.right + STAGE_RECT_LIMIT)) return FALSE;


	CameraX = x >> FLOATNS;
	CameraY = y >> FLOATNS;
	CameraZ = z >> FLOATNS;

	CameraY -= 1500;
	if(CameraY < 400) CameraY = 400;

	CameraAngX = GetRadian(angX);
	CameraAngY = GetRadian(angY);
	CameraAngZ = GetRadian(angZ);



	if(CameraAngX > ANGLE_90)
		CameraAngX = ANGLE_360 - CameraAngX;


	SetViewLength();
	SetViewRadian();

	if(MakeMapTable())
	{

		if(eRotMatrix)
			smRender.SetCameraPosi(x, y, z, eRotMatrix);
		else
			smRender.SetCameraPosi(x, y, z, angX, angY, angZ);

		CameraAngX = GetRadian(angX);
		CameraAngY = GetRadian(angY);
		CameraAngZ = GetRadian(angZ);



		RenderGeom();

		smRender.RenderD3D();

		StageObject->Draw(x, y, z, angX, angY, angZ);
	}
	return FALSE;
}

int smSTAGE3D::DrawStage2(int x, int y, int z, int angX, int angY, int angZ, smEMATRIX *eRotMatrix)
{
	if(!Head) return 0;

	SumCount++;


	if(z < (StageMapRect.top - STAGE_RECT_LIMIT)) return FALSE;
	if(z > (StageMapRect.bottom + STAGE_RECT_LIMIT)) return FALSE;
	if(x < (StageMapRect.left - STAGE_RECT_LIMIT)) return FALSE;
	if(x > (StageMapRect.right + STAGE_RECT_LIMIT)) return FALSE;

	if(z < (StageMapRect.bottom - STAGE_RECT_LIMIT2))
		return FALSE;
	if(z > (StageMapRect.top + STAGE_RECT_LIMIT2))
		return FALSE;
	if(x < (StageMapRect.right - STAGE_RECT_LIMIT2))
		return FALSE;
	if(x > (StageMapRect.left + STAGE_RECT_LIMIT2))
		return FALSE;



	CameraX = x >> FLOATNS;
	CameraY = y >> FLOATNS;
	CameraZ = z >> FLOATNS;

	CameraY -= 1500;
	if(CameraY < 400) CameraY = 400;

	CameraAngX = GetRadian(angX);
	CameraAngY = GetRadian(angY);
	CameraAngZ = GetRadian(angZ);



	if(CameraAngX > ANGLE_90)
		CameraAngX = ANGLE_360 - CameraAngX;


	SetViewLength();
	SetViewRadian();

	if(MakeMapTable())
	{

		if(eRotMatrix)
			smRender.SetCameraPosi(x, y, z, eRotMatrix);
		else
			smRender.SetCameraPosi(x, y, z, angX, angY, angZ);

		CameraAngX = GetRadian(angX);
		CameraAngY = GetRadian(angY);
		CameraAngZ = GetRadian(angZ);


		RenderGeom();

		smRender.RenderD3D();

		return TRUE;
	}
	return FALSE;
}



int smSTAGE3D::DrawOpeningStage(int x, int y, int z, int angX, int angY, int angZ, int FrameStep)
{
	if(!Head)
		return 0;

	SumCount++;


	if(z < (StageMapRect.top - STAGE_RECT_LIMIT)) return FALSE;
	if(z > (StageMapRect.bottom + STAGE_RECT_LIMIT)) return FALSE;
	if(x < (StageMapRect.left - STAGE_RECT_LIMIT)) return FALSE;
	if(x > (StageMapRect.right + STAGE_RECT_LIMIT)) return FALSE;


	CameraX = x >> FLOATNS;
	CameraY = y >> FLOATNS;
	CameraZ = z >> FLOATNS;

	CameraY -= 1500;
	if(CameraY < 400) CameraY = 400;

	CameraAngX = GetRadian(angX);
	CameraAngY = GetRadian(angY);
	CameraAngZ = GetRadian(angZ);

	if(CameraAngX > ANGLE_90)
		CameraAngX = ANGLE_360 - CameraAngX;

	SetViewLength();
	SetViewRadian();

	if(MakeMapTable())
	{
		smRender.SetCameraPosi(x, y, z, angX, angY, angZ);

		CameraAngX = GetRadian(angX);
		CameraAngY = GetRadian(angY);
		CameraAngZ = GetRadian(angZ);

		RenderGeom();

		smRender.RenderD3D();

		StageObject->DrawOpening(x, y, z, angX, angY, angZ, FrameStep);
	}

	return FALSE;
}


static char *szSMDFileHeader = "SMD Stage data Ver 0.72";


int	smSTAGE3D::SaveFile(char *szFile)
{

	HANDLE	hFile;
	DWORD	dwAcess;
	int		cnt, cnt2, slen;
	int		pFile;


	smDFILE_HEADER	FileHeader;

	strcpy_s(FileHeader.szHeader, szSMDFileHeader);

	Head = FALSE;


	if(smMaterialGroup)
		FileHeader.MatCounter = smMaterialGroup->MaterialCount;
	else
		FileHeader.MatCounter = 0;



	pFile = sizeof(smDFILE_HEADER);

	FileHeader.MatFilePoint = pFile;


	if(smMaterialGroup)
		pFile += smMaterialGroup->GetSaveSize();

	FileHeader.First_ObjInfoPoint = pFile;


	hFile = CreateFile(szFile, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;


	WriteFile(hFile, &FileHeader, sizeof(smDFILE_HEADER), &dwAcess, NULL);


	WriteFile(hFile, &Head, sizeof(smSTAGE3D), &dwAcess, NULL);


	if(smMaterialGroup) smMaterialGroup->SaveFile(hFile);


	WriteFile(hFile, Vertex, sizeof(smSTAGE_VERTEX)* nVertex, &dwAcess, NULL);
	WriteFile(hFile, Face, sizeof(smSTAGE_FACE)* nFace, &dwAcess, NULL);
	WriteFile(hFile, TexLink, sizeof(smTEXLINK)	* nTexLink, &dwAcess, NULL);
	if(nLight > 0)
		WriteFile(hFile, smLight, sizeof(smLIGHT3D)	* nLight, &dwAcess, NULL);


	for(cnt2 = 0; cnt2 < MAP_SIZE; cnt2++)
	{
		for(cnt = 0; cnt < MAP_SIZE; cnt++)
		{
			if(StageArea[cnt][cnt2])
			{
				slen = (StageArea[cnt][cnt2][0] + 1);
				WriteFile(hFile, &slen, sizeof(int), &dwAcess, NULL);
				WriteFile(hFile, StageArea[cnt][cnt2], slen * sizeof(WORD), &dwAcess, NULL);
			}
		}
	}


	CloseHandle(hFile);

	return TRUE;
}


int	smSTAGE3D::LoadFile(char *szFile)
{
	DWORD	dwAcess;
	int		slen;

	smDFILE_HEADER	FileHeader;

	HANDLE hFile = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(!hFile)
	{
		//LOG(LOG_ERROR, "Cannot open StageFile(%s)", szFile);
		return FALSE;
	}


	int size = ReadFile(hFile, &FileHeader, sizeof(smDFILE_HEADER), &dwAcess, NULL);


	if(lstrcmp(FileHeader.szHeader, szSMDFileHeader) != 0)
	{
		//LOG(LOG_ERROR, "Wrong StageFile Header (%s)", szFile);
		CloseHandle(hFile);
		return FALSE;
	}


	ReadFile(hFile, &Head, sizeof(smSTAGE3D), &dwAcess, NULL);
	smTEXLINK *lpOldTexLink = TexLink;




	if(FileHeader.MatCounter)
	{
		smMaterialGroup = new smMATERIAL_GROUP;
		smMaterialGroup->LoadFile(hFile);
		smMaterial = smMaterialGroup->smMaterial;
	}


	Vertex = new smSTAGE_VERTEX[nVertex];
	ReadFile(hFile, Vertex, sizeof(smSTAGE_VERTEX) * nVertex, &dwAcess, NULL);

	Face = new smSTAGE_FACE[nFace];
	ReadFile(hFile, Face, sizeof(smSTAGE_FACE) * nFace, &dwAcess, NULL);

	TexLink = new smTEXLINK[nTexLink];
	ReadFile(hFile, TexLink, sizeof(smTEXLINK) * nTexLink, &dwAcess, NULL);

	if(nLight > 0)
	{
		smLight = new smLIGHT3D[nLight];
		ReadFile(hFile, smLight, sizeof(smLIGHT3D) * nLight, &dwAcess, NULL);
	}



	int SubTexLink = TexLink - lpOldTexLink;

	for(int cnt = 0; cnt < nTexLink; cnt++)
	{
		if(TexLink[cnt].NextTex)
		{
			SubTexLink = TexLink[cnt].NextTex - lpOldTexLink;
			TexLink[cnt].NextTex = TexLink + SubTexLink;
		}
	}
	for(int cnt = 0; cnt < nFace; cnt++)
	{
		if(Face[cnt].lpTexLink)
		{
			SubTexLink = Face[cnt].lpTexLink - lpOldTexLink;
			Face[cnt].lpTexLink = TexLink + SubTexLink;
		}
	}

	StageObject = new smSTAGE_OBJECT;



	lpwAreaBuff = new DWORD[wAreaSize];

	int wbCnt = 0;


	for(int cnt2 = 0; cnt2 < MAP_SIZE; cnt2++)
	{
		for(int cnt = 0; cnt < MAP_SIZE; cnt++)
		{
			if(StageArea[cnt][cnt2])
			{
				ReadFile(hFile, &slen, sizeof(int), &dwAcess, NULL);
				StageArea[cnt][cnt2] = &lpwAreaBuff[wbCnt];
				ReadFile(hFile, StageArea[cnt][cnt2], slen * sizeof(DWORD), &dwAcess, NULL);
				wbCnt += slen;
			}
		}
	}


	CloseHandle(hFile);

	CalcSumCount++;

	return TRUE;
}

