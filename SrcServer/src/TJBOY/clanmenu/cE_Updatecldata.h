#pragma once

#ifndef __CE_UPDATECLDATA_H__
#define __CE_UPDATECLDATA_H__
class CUpdateCldata
{
public:
	CUpdateCldata();
	virtual ~CUpdateCldata();
public:
	void Updatecldata();
public:
	void Close();
};
#endif

#ifdef CE_UPDATECLDATA_CPP
class CUpdateCldata g_UpdateCldata;
#else
extern class CUpdateCldata g_UpdateCldata;
#endif