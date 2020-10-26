

#include "smLib3d\\smd3d.h"

#pragma comment( lib, "vfw32.lib" )

int OpenVideoFile(char *AVIFile);
void CloseAVIData();
void AVIDrawSurface(LPDIRECT3DTEXTURE9 *lpDDSSource, int frame);
