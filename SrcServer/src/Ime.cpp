


#include <windows.h>
#include "Ime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif





ImeClass::ImeClass(){}

ImeClass::~ImeClass()
{
}

void ImeClass::GetInfoPerTime(){}

void ImeClass::GetCompositionString(){}

void ImeClass::GetCompositionStringInfo(){}

void ImeClass::GetCandidateList(){}

void ImeClass::SetCandidateInfo(LPCANDIDATELIST lpCandList){}

void ImeClass::GetImeInfo(){}

void ImeClass::OnButtonChangemode(){}
