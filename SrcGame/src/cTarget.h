#pragma once

class cTARGET
{
public:

	void Init();
	void DrawTarget();
	void Draw(smCHAR* lpEachPlayer);
	void Text(smCHAR* lpEachPlayer);
	bool LButtonDown();
	bool MouseIn();
	bool StopMotion();

	enum MAT
	{
		BACKGROUND,
		TARGETBG,
		TARGETCLAN,
		TARGETHP,
		TYPEDEMON,
		TYPEMECHANIC,
		TYPEMUTANT,
		TYPENORMAL,
		TYPENPC,
		TYPEPLAYER,
		TYPEUNDEAD,
		MORE,
		MORE_,
		DROPTOP,
		DROPMID,
		DROPBOT,
		MAX_MAT,
	};

	int BaseX, BaseY;

	int Mat[MAX_MAT];

	bool DropDownFlag;
	DWORD TargetSerial;
	void OpenDropDown();
	std::map<int, char*> vOptions;
	void handleOption(int code);
};

extern cTARGET cTarget;