
#ifndef _ASSAUTIL_HEADER_

#define _ASSAUTIL_HEADER_

char *FindFile(char *fileName);


void InitAssaRes();
void CloseAssaRes();
void LoadAssaRes();

void *AssaSearchRes(char *resName, int blendType);


#include <list>
using namespace std;


class cASSATrace
{
public:
	list<POINT3D> TraceList;
private:
	unsigned int Length;

public:
	cASSATrace()
	{
		Length = 50;
	}

	~cASSATrace()
	{

	}


	void SetLength(int length)
	{
		Length = length;
	}


	void AddData(POINT3D *pos)
	{

		POINT3D curPos;
		curPos.x = pos->x;
		curPos.y = pos->y;
		curPos.z = pos->z;

		int t = (int)TraceList.size();
		if(TraceList.size() < Length)
			TraceList.push_front(curPos);
		else
		{
			if(!TraceList.empty())
			{
				std::list<POINT3D>::iterator i;
				i = TraceList.end();
				--i;
				TraceList.erase(i);
				TraceList.push_front(curPos);
			}
		}
	}

};

bool	AssaAddFace2D(smFACE2D *face, int ZPosiFlag = FALSE, int angle = 0);
bool	AssaAddFace2DLine(smFACE2D *face, POINT3D *localDestPos, BOOL centerFlag = FALSE);
bool	AssaAddFaceWorld(smFACE2D *face, POINT3D *inAngle = NULL);
bool	AssaAddFaceTrace(smFACE2D *face, cASSATrace *assaTrace);

bool    AssaSearchObjPos(smCHAR *character, smOBJ3D *obj, POINT3D *outObjPos);
bool	AssaSearchObjPos(smCHAR *character, smOBJ3D *obj, POINT3D *outObjPos, int length);
bool    AssaSearchWeaponPos(smCHAR *character, POINT3D *outWeaponPos, float u = 0.0f);

int AssaTestEffectImage();
#endif