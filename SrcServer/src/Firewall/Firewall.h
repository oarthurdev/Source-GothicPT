#pragma once
#include <Windows.h>
#include <string>
#include <crtdbg.h>
#include <netfw.h>
#include <objbase.h>
#include <oleauto.h>

class Firewall
{
public:
	enum class Rule
	{
		AllowAccess = 1,
		BlockAccess = 2,
	};

public:
	static Firewall * GetInstance();

	bool AddRule(Firewall::Rule Rule, std::string IP, unsigned short Port);

private:
	Firewall();
	~Firewall();

private:
	static Firewall * m_Instance;
	INetFwPolicy2 * m_Policy;
	HRESULT m_Initialized;
};

