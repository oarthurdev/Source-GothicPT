

#define BMPsmooth_CPP


#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "BMPsmooth.h"



void convert_32_16_smooth(byte *sRGB_32, byte *dRGB_16)
{
	byte *sorRGBp;
	byte *destRGBp;

	int r[9];
	int g[9];
	int b[9];

	int i, j;
	int x, y, x2, y2;
	for(y = 0, y2 = 0; y < 32; y += 2, y2++)
	{
		for(x = 0, x2 = 0; x < 32; x += 2, x2++)
		{

			int rgbcnt = 0;
			for(j = y - 1; j < y + 2; j++)
			{
				for(i = x - 1; i < x + 2; i++)
				{




					if(i < 0 || i >= 32 || j < 0 || j >= 32)
					{

						r[rgbcnt] = -1;
						g[rgbcnt] = -1;
						b[rgbcnt] = -1;

					}
					else
					{

						sorRGBp = (byte*)sRGB_32;
						sorRGBp += (j * 32 * 3) + (i * 3);


						byte rr = *sorRGBp; sorRGBp++;
						byte gg = *sorRGBp; sorRGBp++;
						byte bb = *sorRGBp; sorRGBp++;

						r[rgbcnt] = (int)rr;
						g[rgbcnt] = (int)gg;
						b[rgbcnt] = (int)bb;
					}

					rgbcnt++;
				}
			}


			float allR = 0, allRcnt = 0;
			float allG = 0, allGcnt = 0;
			float allB = 0, allBcnt = 0;
			for(i = 0; i < 9; i++)
			{
				if(r[i] != -1)
				{
					allR += (float)r[i];  allRcnt++;
				}
				if(g[i] != -1)
				{
					allG += (float)g[i];  allGcnt++;
				}
				if(b[i] != -1)
				{
					allB += (float)b[i];  allBcnt++;
				}
			}

			allR /= (float)allRcnt;
			allG /= (float)allGcnt;
			allB /= (float)allBcnt;

			destRGBp = (byte*)dRGB_16;
			destRGBp += (y2 * 16 * 3) + (x2 * 3);

			*destRGBp = (byte)allR;
			destRGBp++;
			*destRGBp = (byte)allG;
			destRGBp++;
			*destRGBp = (byte)allB;
			destRGBp++;

		}
	}
}


int bmpSAVE(char *loadfname, char *savefname)
{

#pragma pack(2)
	struct
	{
		char    signature[2];
		long    size;
		short   reserved1, reserved2;
		long    offbits;
	}   header;

	struct
	{
		long    size, width, height;
		short   planes, bitcount;
		long    compression, sizecimage;
		long    xpelspermeter, ypelspermeter, clrused, clrimportant;
	}   info;
#pragma pack()


	byte sRGB_32[32 * 32 * 3];
	byte dRGB_16[16 * 16 * 3];


	FILE    *fp;







	fp = fopen(loadfname, "rb");
	if(fp == NULL)
	{
		return 0;
	}
	fread(&header, 1, sizeof(header), fp);
	if(memcmp(header.signature, "BM", 2) != 0)
		return 0;

	fread(&info, 1, sizeof(info), fp);




	fseek(fp, header.offbits, SEEK_SET);

	fread(sRGB_32, 1, sizeof(sRGB_32), fp);


	fclose(fp);


	convert_32_16_smooth(sRGB_32, dRGB_16);



	header.signature[0] = 'B';
	header.signature[1] = 'M';
	header.size = 822;
	header.reserved1 = 0;
	header.reserved2 = 0;
	header.offbits = 54;

	info.size = 40;
	info.width = 16;
	info.height = 16;
	info.planes = 1;
	info.bitcount = 24;
	info.compression = 0;
	info.sizecimage = 768;
	info.xpelspermeter = 3780;
	info.ypelspermeter = 3780;
	info.clrused = 0;
	info.clrimportant = 0;



	fp = fopen(savefname, "wb");
	if(fp == NULL)
	{
		return 0;
	}
	fwrite(&header, 1, sizeof(header), fp);
	fwrite(&info, 1, sizeof(info), fp);
	fwrite(dRGB_16, 1, 16 * 16 * 3, fp);
	fclose(fp);

	return 1;
}
