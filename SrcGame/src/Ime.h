#ifndef __IME_CONTROL_INCLUDE__
#define __IME_CONTROL_INCLUDE__

#include <imm.h>
#include "strclass.h"

class ImeClass
{

public:
	HWND	m_hWnd;
	HIMC	m_hIMC;

	BOOL	bCandList;
	int		nCandState;
	int		nStartListIdx;
	int		nCandListCount;

	void	GetCompositionString();
	void	GetCompositionStringInfo();
	void	GetCandidateList();
	void	GetImeInfo();
	void	SetCandidateInfo(LPCANDIDATELIST lpCandList);
	void	OnButtonChangemode();

	CStrClass	m_szTitle;
	CStrClass	m_szConvMode;
	CStrClass	m_szHalfMode;
	CStrClass	m_szCOMPOSTR;
	CStrClass	m_szCandList[10];

	CStrClass	m_szResultReadStr;
	CStrClass	m_szCompReadStr;

	ImeClass();
	virtual ~ImeClass();

	void	GetInfoPerTime();

	void	SetHWND(HWND hWnd)
	{
		m_hWnd = hWnd;
	};




	int		nTX1;

















	int		CUR_ON;
	BOOL	bMove;

	POINT	P_MOUSE;

	int		nCurrCompLen;
	int		nPrevCompLen;
};

#endif 
