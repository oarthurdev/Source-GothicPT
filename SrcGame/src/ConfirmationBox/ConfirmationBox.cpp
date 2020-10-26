#include "ConfirmationBox.h"
#include "SinBaram\\sinLinkHeader.h"

ConfirmationBox _ConfirmationBox;

void ConfirmationBox::CheckFlag(bool Flag)
{
	if (m_Callback)
		m_Callback(Flag);
}

void ConfirmationBox::Start()
{
	cMessageBox.ShowMessage3(MESSAGE_CONFIRMATION_BOX, const_cast<char*>(m_Title.c_str()));
}

void ConfirmationBox::SetTitle(std::string Title)
{
	m_Title = Title;
}

void ConfirmationBox::SetText(std::string Doc1, std::string Doc2)
{
	m_Doc1.clear();
	m_Doc2.clear();

	m_Doc1 = Doc1;
	m_Doc2 = Doc2;
}

void ConfirmationBox::SetCallback(std::function<void(bool)> Callback)
{
	m_Callback = Callback;
}

const char * ConfirmationBox::GetDoc1() const
{
	return m_Doc1.c_str();
}

const char * ConfirmationBox::GetDoc2() const
{
	return m_Doc2.c_str();
}
