extern int ViewPointLen;

extern int		MapPosiLeft[256];
extern int		MapPosiRight[256];
extern int		MapPosiTop;
extern int		MapPosiBot;

extern int CameraX;
extern int CameraY;
extern int CameraZ;

extern int  CameraAngX;
extern int  CameraAngY;
extern int  CameraAngZ;

extern int MidX;;
extern int MidY;
extern int viewdistZ;
extern int ZDivision;

extern int AddDepthZ;



extern int ccDistZMin;
extern smRGB ccBackColor;
extern DWORD smBackColor;

void SetViewLength();
void SetViewRadian();
int MakeMapTable();

int GetRadian(int Rad);
float smConvZ3D(float z);
void smInitColorZClip(int r, int g, int b);


int SetNormal(POINT3D *p1, POINT3D *p2, POINT3D *p3, POINT3D *normal);
