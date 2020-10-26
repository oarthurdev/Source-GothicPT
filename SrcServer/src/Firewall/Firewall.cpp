#include "Firewall.h"
#include <tchar.h>
#include <atlconv.h>

Firewall * Firewall::m_Instance = nullptr;

Firewall * Firewall::GetInstance()
{
	if(!m_Instance)
		m_Instance = new Firewall();
	return m_Instance;
}

bool Firewall::AddRule(Firewall::Rule Rule, std::string IP, unsigned short Port)
{
	long CurrentProfilesBitMask = 0;
	INetFwRules * Rules = nullptr;
	INetFwRule * FirewallRule = nullptr;
	switch(Rule)
	{
	case Firewall::Rule::AllowAccess:
	{

	} break;
	case Firewall::Rule::BlockAccess:
	{
		USES_CONVERSION;
		BSTR RuleRAddress = SysAllocString(A2W(IP.c_str()));
		BSTR RuleLPorts = SysAllocString(A2W(std::to_string(Port).c_str()));
		BSTR RuleName = SysAllocString(L"PT Server Firewall");
		BSTR RuleDesc = SysAllocString(L"Block HTTP Request");
		BSTR RuleGroup = SysAllocString(L"Priston Tale Rules");

		m_Policy->get_Rules(&Rules);
		m_Policy->get_CurrentProfileTypes(&CurrentProfilesBitMask);
		if(FAILED(CoCreateInstance(__uuidof(NetFwRule), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwRule), (void**)&FirewallRule)))
		{
			printf("Rule Creation failed.\n");
			SysFreeString(RuleRAddress);
			SysFreeString(RuleLPorts);
			SysFreeString(RuleGroup);
			SysFreeString(RuleDesc);
			SysFreeString(RuleName);
			return false;
		}
		FirewallRule->put_Name(RuleName);
		FirewallRule->put_Description(RuleDesc);
		FirewallRule->put_Protocol(NET_FW_IP_PROTOCOL_TCP);
		FirewallRule->put_LocalPorts(RuleLPorts);
		FirewallRule->put_RemoteAddresses(RuleRAddress);
		FirewallRule->put_Direction(NET_FW_RULE_DIR_IN);
		FirewallRule->put_Grouping(RuleGroup);
		FirewallRule->put_Profiles(CurrentProfilesBitMask);
		FirewallRule->put_Action(NET_FW_ACTION_BLOCK);
		FirewallRule->put_Enabled(VARIANT_TRUE);
		Rules->Add(FirewallRule);

		SysFreeString(RuleRAddress);
		SysFreeString(RuleLPorts);
		SysFreeString(RuleGroup);
		SysFreeString(RuleDesc);
		SysFreeString(RuleName);
	} break;
	}
	return true;
}

Firewall::Firewall()
{
	m_Initialized = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
	if(m_Initialized != RPC_E_CHANGED_MODE)
	{
		if(FAILED(m_Initialized))
		{
			printf("CoInitializeEx failed: 0x%08lx\n", m_Initialized);
		}
	}
	if(FAILED(CoCreateInstance(__uuidof(NetFwPolicy2), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwPolicy2), (void**)&m_Policy)))
	{
		printf("CoCreateInstance failed.\n");
	}
}

Firewall::~Firewall()
{

}
