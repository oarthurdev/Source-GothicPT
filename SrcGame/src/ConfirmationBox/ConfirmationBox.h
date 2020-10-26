#pragma once
#include <string>
#include <functional>

class ConfirmationBox
{
public:
	void CheckFlag(bool Flag);
	void Start();

	void SetTitle(std::string Title);
	void SetText(std::string Doc1, std::string Doc2);
	void SetCallback(std::function<void(bool)> Callback);

	const char* GetDoc1() const;
	const char* GetDoc2() const;
private:
	std::string m_Title, m_Doc1, m_Doc2;
	std::function<void(bool)> m_Callback;
};

extern ConfirmationBox _ConfirmationBox;
