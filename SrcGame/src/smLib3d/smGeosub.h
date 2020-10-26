
extern int	GeoResult_X;
extern int	GeoResult_Y;
extern int	GeoResult_Z;





bool PointInTri(float a1, float a2, float a3, float b1, float b2, float b3, float mouseX, float mouseY);


void GetMoveLocation(int x, int y, int z, int AngX, int AngY, int AngZ);

void GetTraceAngle(POINT3D *posi, POINT3D *angle, int tx, int ty, int tz);
int CheckLocateBox(int sx, int sz, int tx, int tz, int size);
int GetSubAngle(int a1, int a2);
void GetRadian3D(int x1, int y, int y1, int x2, int y_, int y2);
int GetRadian2D(int x1, int y1, int x2, int y2);
int GetDistance(int x1, int y, int y1, int x2, int y_, int y2);


int MakeTraceMatrix(eCAMERA_TRACE *lpeTrace, int sx, int sy, int sz, int tx, int ty, int tz);
