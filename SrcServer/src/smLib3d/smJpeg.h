



#if !defined(AFX_JPEG_H__2835EF17_2235_11D2_8C8B_006097ADB77E__INCLUDED_)
#define AFX_JPEG_H__2835EF17_2235_11D2_8C8B_006097ADB77E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif 

struct SET
{
	BYTE C[3];
};

struct DQT
{
	BYTE Q[64];
};

struct DHT
{
	BOOL Flag;
	int Num;
	WORD *HUFFCODE;
	BYTE *HUFFSIZE;
	BYTE *HUFFVAL;
	WORD MAXCODE[17];
	WORD MINCODE[17];
	int VALPTR[17];
	int *PT;
};

struct FRAMEHEADER
{
	WORD Y;
	WORD X;
	BYTE Nf;
	BYTE C[3];
	BYTE H[3];
	BYTE V[3];
	BYTE Tq[3];
};

struct SCANHEADER
{
	BYTE Ns;
	BYTE Cs[3];
	BYTE Td[3];
	BYTE Ta[3];
	BYTE Ss;
	BYTE Se;
	BYTE Ah;
	BYTE Al;
};


class CJpeg
{
public:


	void LoadJPG(LPSTR FileName);
	void FindSOI();
	void FindDQT();
	void FindDHT();
	void FindSOF();
	void FindSOS();
	void FindETC();
	void Decode();
	void DecodeMCU(int mx, int my);
	void DecodeDU(int N);
	void IDCT();
	void Zigzag();
	void DecodeAC(int Th);
	void DecodeDC(int Th);
	short Extend(WORD V, BYTE T);
	WORD Receive(BYTE SSSS);
	BYTE hDecode(int Th);
	BYTE NextByte();
	WORD NextBit();
	void ConvertYUV2RGB();




	void SaveJPG(LPSTR FileName, int Width, int Height, BYTE *pp);
	void PutSOI(HFILE hFile);
	void PutDQT(HFILE hFile);
	void PutDHT(HFILE hFile);
	void PutSOF(HFILE hFile, int Width, int Height);
	void PutSOS(HFILE hFile);
	void PutEOI(HFILE hFile);
	void ShotBit(BYTE Bit);
	void ChargeCode(WORD Code, int Size);
	void EncodeDU(short *pos, BOOL Flag, int bWidth);
	void hEncode(int bWidth, int bHeight);
	BYTE GetCategory(short V);
	void Zigzag2();
	void DCT(short *pos, int bWidth, BOOL Flag);

	int GetHeight();
	int GetWidth();

	WORD Ri;
	int m_rWidth;
	int m_rHeight;
	BYTE * pByte;

	int cnt;

	short *Y;
	short *Cb;
	short *Cr;

	SET *MCU;

	BYTE Hmax;
	BYTE Vmax;

	BYTE * m_pData;
	BYTE * m_pBuf;
	int m_Index;
	DQT TbQ[20];
	DHT TbH[20];
	short ZZ[64];
	FRAMEHEADER FrameHeader;
	SCANHEADER ScanHeader;
	short PrevDC[3];


	CJpeg();
	virtual ~CJpeg();

};

#endif 
