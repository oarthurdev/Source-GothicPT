#include "sinbaram\\sinlinkheader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "File\File.h"

extern char	szShotCutMessage[10][100];

int tab;
bool TextureBox = false, ViewBox = false, ZoomBox = false;

bool cSettings::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void cSettings::Init()
{
	cImages[0] = CreateTextureMaterial("game\\images\\settings\\setting.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[1] = CreateTextureMaterial("game\\images\\settings\\window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[2] = CreateTextureMaterial("game\\images\\settings\\dividers.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[3] = CreateTextureMaterial("game\\images\\settings\\header.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[4] = CreateTextureMaterial("game\\images\\settings\\header2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[5] = CreateTextureMaterial("game\\images\\settings\\graphics.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[6] = CreateTextureMaterial("game\\images\\settings\\screen.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[7] = CreateTextureMaterial("game\\images\\settings\\general.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[8] = CreateTextureMaterial("game\\images\\settings\\general_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[9] = CreateTextureMaterial("game\\images\\settings\\cancel.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[10] = CreateTextureMaterial("game\\images\\settings\\cancel_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[11] = CreateTextureMaterial("game\\images\\settings\\save.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[12] = CreateTextureMaterial("game\\images\\settings\\save_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[13] = CreateTextureMaterial("game\\images\\settings\\reset.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[14] = CreateTextureMaterial("game\\images\\settings\\reset_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[15] = CreateTextureMaterial("game\\images\\settings\\checkbox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[16] = CreateTextureMaterial("game\\images\\settings\\checkbox_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[17] = CreateTextureMaterial("game\\images\\settings\\largegear.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[18] = CreateTextureMaterial("game\\images\\settings\\combo_box.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[19] = CreateTextureMaterial("game\\images\\settings\\save.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[20] = CreateTextureMaterial("game\\images\\settings\\save_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[21] = CreateTextureMaterial("game\\images\\settings\\reset.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[22] = CreateTextureMaterial("game\\images\\settings\\reset_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[23] = CreateTextureMaterial("game\\images\\settings\\cancel.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[24] = CreateTextureMaterial("game\\images\\settings\\cancel_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[25] = CreateTextureMaterial("game\\images\\settings\\video.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[26] = CreateTextureMaterial("game\\images\\settings\\video_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[27] = CreateTextureMaterial("game\\images\\settings\\audio.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[28] = CreateTextureMaterial("game\\images\\settings\\audio_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[29] = CreateTextureMaterial("game\\images\\settings\\general.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[30] = CreateTextureMaterial("game\\images\\settings\\general_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[31] = CreateTextureMaterial("game\\images\\settings\\combo_box_on.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[32] = CreateTextureMaterial("game\\images\\settings\\combo_box_down1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[33] = CreateTextureMaterial("game\\images\\settings\\combo_box_down2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[34] = CreateTextureMaterial("game\\images\\settings\\combo_box_down3.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[35] = CreateTextureMaterial("game\\images\\settings\\combo_box_down_select_bottom.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[36] = CreateTextureMaterial("game\\images\\settings\\combo_box_down_select.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[37] = CreateTextureMaterial("game\\images\\settings\\backgroundmusic.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[38] = CreateTextureMaterial("game\\images\\settings\\volumebar.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[39] = CreateTextureMaterial("game\\images\\settings\\selector.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[40] = CreateTextureMaterial("game\\images\\settings\\soundeffects.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[41] = CreateTextureMaterial("game\\images\\settings\\camera.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[42] = CreateTextureMaterial("game\\images\\settings\\lootfilter.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[43] = CreateTextureMaterial("game\\images\\settings\\personalization.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ReadTextures();
}

void cSettings::Open()
{
	cOpen = true;
}

void cSettings::Close()
{
	cOpen = false;
}

void cSettings::Draw()
{
	if (cOpen)
	{
		int WinX = (WinSizeX / 2) - 280, WinY = ((WinSizeY - 600) / 2) + 50;

		SetFontTextColor( RGB(255, 255, 255));

		dsDrawTexImage(cImages[1], WinX, WinY, 561, 438, 255);
		dsDrawTexImage(cImages[2], WinX + 8, WinY + 16, 542, 414, 255);
		dsDrawTexImage(cImages[3], WinX, WinY + 6, 545, 33, 255);

		if (Tab == 0 || MouseAction(WinX + 9, WinY + 45, 120, 32))
			dsDrawTexImage(cImages[26], WinX + 9, WinY + 45, 120, 32, 255);
		else
			dsDrawTexImage(cImages[25], WinX + 9, WinY + 45, 120, 32, 255);

		if (Tab == 1 || MouseAction(WinX + 9, WinY + 78, 120, 32))
			dsDrawTexImage(cImages[28], WinX + 9, WinY + 78, 120, 32, 255);
		else
			dsDrawTexImage(cImages[27], WinX + 9, WinY + 78, 120, 32, 255);

		if (Tab == 2 || MouseAction(WinX + 9, WinY + 111, 120, 32))
			dsDrawTexImage(cImages[30], WinX + 9, WinY + 111, 120, 32, 255);
		else
			dsDrawTexImage(cImages[29], WinX + 9, WinY + 111, 120, 32, 255);
		//Tab3
		//if (Tab == 3 || MouseAction(WinX + 9, WinY + 144, 120, 32))
			//dsDrawTexImage(cImages[30], WinX + 9, WinY + 144, 120, 32, 255);
		//else
			//dsDrawTexImage(cImages[29], WinX + 9, WinY + 144, 120, 32, 255);

		if (MouseAction(WinX + 27, WinY + 350, 79, 20))
			dsDrawTexImage(cImages[22], WinX + 27, WinY + 350, 79, 20, 255);
		else
			dsDrawTexImage(cImages[21], WinX + 27, WinY + 350, 79, 20, 255);

		if (MouseAction(WinX + 27, WinY + 376, 79, 20))
			dsDrawTexImage(cImages[20], WinX + 27, WinY + 376, 79, 20, 255);
		else
			dsDrawTexImage(cImages[19], WinX + 27, WinY + 376, 79, 20, 255);

		if (MouseAction(WinX + 27, WinY + 402, 79, 20))
			dsDrawTexImage(cImages[24], WinX + 27, WinY + 402, 79, 20, 255);
		else
			dsDrawTexImage(cImages[23], WinX + 27, WinY + 402, 79, 20, 255);
		if (Tab == 0)
		{
			
			dsDrawTexImage(cImages[4], WinX + 131, WinY + 46, 410, 29, 255);
			dsDrawTexImage(cImages[4], WinX + 131, WinY + 233, 410, 29, 255);
			

			dsDrawTexImage(cImages[5], WinX + 245, WinY + 242, 149, 11, 255);
			dsDrawTexImage(cImages[6], WinX + 250, WinY + 55, 149, 11, 255);

			dsTextLineOut(WinX + 150, WinY + 80, "Display:", 9);
			dsTextLineOut(WinX + 150, WinY + 131, "Ratio:", 7);
			dsTextLineOut(WinX + 303, WinY + 131, "Resolution:", 12);

			if (!bWindowed)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 100, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 100, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 100, "Fullscreen", 11);

			if (bWindowed)
				dsDrawTexImage(cImages[16], WinX + 239, WinY + 100, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 239, WinY + 100, 15, 15, 255);

			dsTextLineOut(WinX + 259, WinY + 100, "Windowed", 9);

			if (bAutoAdjust)
				dsDrawTexImage(cImages[16], WinX + 379, WinY + 100, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 379, WinY + 100, 15, 15, 255);

			dsTextLineOut(WinX + 399, WinY + 100, "Auto Adjust", 12);


			if (bRatio == 0)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 151, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 151, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 151, "4:3", 4);

			if (bRatio == 1)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 171, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 171, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 171, "5:4", 4);

			if (bRatio == 2)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 191, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 191, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 191, "16:9 (widescreen)", 18);

			if (bRatio == 3)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 211, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 211, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 211, "16:10 (widescreen)", 19);

			if (bRatio == 0)
			{
				if (bResolution == 0)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 151, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 151, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 151, "800x600", 8);

				if (bResolution == 1)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 171, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 171, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 171, "1024x768", 9);

				if (bResolution == 2)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 191, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 191, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 191, "1280x960", 9);

				if (bResolution == 3)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 211, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 211, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 211, "1400x1050", 10);
			}
			else if (bRatio == 1)
			{
				if (bResolution == 4)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 151, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 151, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 151, "1280x1024", 10);
			}
			else if (bRatio == 2)
			{
				if (bResolution == 5)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 151, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 151, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 151, "1280x720", 9);

				if (bResolution == 6)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 171, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 171, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 171, "1366x768", 9);

				if (bResolution == 7)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 191, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 191, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 191, "1600x900", 9);

				if (bResolution == 8)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 211, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 211, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 211, "1920x1080", 10);
			}
			else if (bRatio == 3)
			{

				if (bResolution == 9)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 151, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 151, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 151, "1280x800", 9);

				if (bResolution == 10)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 171, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 171, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 171, "1440x900", 9);

				if (bResolution == 11)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 191, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 191, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 191, "1680x1050", 9);

				if (bResolution == 12)
					dsDrawTexImage(cImages[16], WinX + 303, WinY + 211, 15, 15, 255);
				else
					dsDrawTexImage(cImages[15], WinX + 303, WinY + 211, 15, 15, 255);

				dsTextLineOut(WinX + 323, WinY + 211, "1920x1200", 10);
			}


			dsTextLineOut(WinX + 150, WinY + 267, "Texture Quality:", 17);
			dsTextLineOut(WinX + 363, WinY + 267, "Bit Depth:", 11);

			if (bBPP == 32)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 287, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 287, 15, 15, 255);

			dsTextLineOut(WinX + 383, WinY + 287, "32 bit", 7);

			if (bBPP == 16)
				dsDrawTexImage(cImages[16], WinX + 443, WinY + 287, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 443, WinY + 287, 15, 15, 255);

			dsTextLineOut(WinX + 463, WinY + 287, "16 bit", 7);

			dsTextLineOut(WinX + 150, WinY + 327, "Effects:", 7);
			dsTextLineOut(WinX + 363, WinY + 327, "Dynamic Lights:", 16);
			dsTextLineOut(WinX + 150, WinY + 367, "Dynamic Shadows:", 17);

			if (bEffects)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 347, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 347, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 347, "ON", 3);

			if (!bEffects)
				dsDrawTexImage(cImages[16], WinX + 230, WinY + 347, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 230, WinY + 347, 15, 15, 255);

			dsTextLineOut(WinX + 250, WinY + 347, "OFF", 3);

			if (bLights)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 347, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 347, 15, 15, 255);

			dsTextLineOut(WinX + 383, WinY + 347, "ON", 3);

			if (!bLights)
				dsDrawTexImage(cImages[16], WinX + 443, WinY + 347, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 443, WinY + 347, 15, 15, 255);

			dsTextLineOut(WinX + 463, WinY + 347, "OFF", 3);

			if (bShadows)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 387, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 387, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 387, "ON", 3);

			if (!bShadows)
				dsDrawTexImage(cImages[16], WinX + 230, WinY + 387, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 230, WinY + 387, 15, 15, 255);

			dsTextLineOut(WinX + 250, WinY + 387, "OFF", 3);

			if (TextureBox)
			{

				HoDrawTexImage(cImages[32], float(WinX + 150), float(WinY + 287), 86.f, 26.f, 0.f, 0.f, 86., 26.f, 255);
				HoDrawTexImage(cImages[33], float(WinX + 150), float(WinY + 313), 86.f, 24.f, 0.f, 0.f, 86., 24.f, 255);
				HoDrawTexImage(cImages[33], float(WinX + 150), float(WinY + 337), 86.f, 24.f, 0.f, 0.f, 86., 24.f, 255);
				HoDrawTexImage(cImages[33], float(WinX + 150), float(WinY + 361), 86.f, 24.f, 0.f, 0.f, 86., 24.f, 255);
				HoDrawTexImage(cImages[34], float(WinX + 150), float(WinY + 385), 86.f, 25.f, 0.f, 0.f, 86., 25.f, 255);

				if (MouseAction(WinX + 150, WinY + 313, 86, 24))
					HoDrawTexImage(cImages[36], float(WinX + 150), float(WinY + 313), 86.f, 24.f, 0.f, 0.f, 86., 24.f, 255);
				if (MouseAction(WinX + 150, WinY + 337, 86, 24))
					HoDrawTexImage(cImages[36], float(WinX + 150), float(WinY + 337), 86.f, 24.f, 0.f, 0.f, 86., 24.f, 255);
				if (MouseAction(WinX + 150, WinY + 361, 86, 24))
					HoDrawTexImage(cImages[36], float(WinX + 150), float(WinY + 361), 86.f, 24.f, 0.f, 0.f, 86., 24.f, 255);
				if (MouseAction(WinX + 150, WinY + 385, 86, 25))
					HoDrawTexImage(cImages[35], float(WinX + 150), float(WinY + 385), 86.f, 25.f, 0.f, 0.f, 86., 25.f, 255);

				dsTextLineOut(WinX + 178, WinY + 317, "High", 5);
				dsTextLineOut(WinX + 170, WinY + 341, "Medium", 7);
				dsTextLineOut(WinX + 178, WinY + 365, "Low", 4);
				dsTextLineOut(WinX + 170, WinY + 390, "Very Low", 9);
			}
			else
			{

				if (MouseAction(WinX + 150, WinY + 287, 86, 26))
					HoDrawTexImage(cImages[31], float(WinX + 150), float(WinY + 287), 86.f, 26.f, 0.f, 0.f, 86.f, 26.f, 255);
				else
					HoDrawTexImage(cImages[18], float(WinX + 150), float(WinY + 287), 86.f, 26.f, 0.f, 0.f, 86.f, 26.f, 255);

			}

			if (bTexture == 0)
				dsTextLineOut(WinX + 170, WinY + 292, "High", 5);
			else if (bTexture == 1)
				dsTextLineOut(WinX + 162, WinY + 292, "Medium", 7);
			else if (bTexture == 2)
				dsTextLineOut(WinX + 170, WinY + 292, "Low", 4);
			else if (bTexture == 3)
				dsTextLineOut(WinX + 162, WinY + 292, "Very Low", 9);


		}
		else if (Tab == 1)
		{
			dsDrawTexImage(cImages[4], WinX + 131, WinY + 46, 410, 29, 255);
			dsDrawTexImage(cImages[37], WinX + 255, WinY + 55, 149, 11, 255);

			if (bMusic)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 80, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 80, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 80, "Master Music", 13);
			dsTextLineOut(WinX + 150, WinY + 110, "Music Volume:", 14);

			HoDrawTexImage(cImages[38], float(WinX + 150), float(WinY + 140), 187.f, 34.f, 0.f, 0.f, 187.f, 34.f, 255);

			if (bMVol == 0)
				HoDrawTexImage(cImages[39], float(WinX + 148), float(WinY + 137), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bMVol == 1)
				HoDrawTexImage(cImages[39], float(WinX + 169), float(WinY + 137), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bMVol == 2)
				HoDrawTexImage(cImages[39], float(WinX + 190), float(WinY + 137), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bMVol == 3)
				HoDrawTexImage(cImages[39], float(WinX + 211), float(WinY + 137), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bMVol == 4)
				HoDrawTexImage(cImages[39], float(WinX + 232), float(WinY + 137), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bMVol == 5)
				HoDrawTexImage(cImages[39], float(WinX + 253), float(WinY + 137), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bMVol == 6)
				HoDrawTexImage(cImages[39], float(WinX + 274), float(WinY + 137), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bMVol == 7)
				HoDrawTexImage(cImages[39], float(WinX + 295), float(WinY + 137), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bMVol == 8)
				HoDrawTexImage(cImages[39], float(WinX + 316), float(WinY + 137), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);

			if (GetAsyncKeyState(VK_LBUTTON) != 0)
			{
				if (MouseAction(WinX + 148, WinY + 137, 21, 52))
					bMVol = 0;
				if (MouseAction(WinX + 169, WinY + 137, 21, 52))
					bMVol = 1;
				if (MouseAction(WinX + 190, WinY + 137, 21, 52))
					bMVol = 2;
				if (MouseAction(WinX + 211, WinY + 137, 21, 52))
					bMVol = 3;
				if (MouseAction(WinX + 232, WinY + 137, 21, 52))
					bMVol = 4;
				if (MouseAction(WinX + 253, WinY + 137, 21, 52))
					bMVol = 5;
				if (MouseAction(WinX + 274, WinY + 137, 21, 52))
					bMVol = 6;
				if (MouseAction(WinX + 295, WinY + 137, 21, 52))
					bMVol = 7;
				if (MouseAction(WinX + 316, WinY + 137, 21, 52))
					bMVol = 8;
			}

			dsDrawTexImage(cImages[4], WinX + 131, WinY + 197, 410, 29, 255);
			dsDrawTexImage(cImages[40], WinX + 255, WinY + 206, 149, 11, 255);

			if (bSound)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 236, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 236, 15, 15, 255);

			if (bAmbient)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 236, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 236, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 236, "Master Sound", 13);
			dsTextLineOut(WinX + 383, WinY + 236, "Ambient Sounds", 15);
			dsTextLineOut(WinX + 150, WinY + 266, "Sound Volume:", 14);

			HoDrawTexImage(cImages[38], float(WinX + 150), float(WinY + 296), 187.f, 34.f, 0.f, 0.f, 187.f, 34.f, 255);


			if (bSVol == 0)
				HoDrawTexImage(cImages[39], float(WinX + 148), float(WinY + 293), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bSVol == 1)
				HoDrawTexImage(cImages[39], float(WinX + 169), float(WinY + 293), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bSVol == 2)
				HoDrawTexImage(cImages[39], float(WinX + 190), float(WinY + 293), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bSVol == 3)
				HoDrawTexImage(cImages[39], float(WinX + 211), float(WinY + 293), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bSVol == 4)
				HoDrawTexImage(cImages[39], float(WinX + 232), float(WinY + 293), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bSVol == 5)
				HoDrawTexImage(cImages[39], float(WinX + 253), float(WinY + 293), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bSVol == 6)
				HoDrawTexImage(cImages[39], float(WinX + 274), float(WinY + 293), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bSVol == 7)
				HoDrawTexImage(cImages[39], float(WinX + 295), float(WinY + 293), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);
			else if (bSVol == 8)
				HoDrawTexImage(cImages[39], float(WinX + 316), float(WinY + 293), 23.f, 52.f, 0.f, 0.f, 23.f, 52.f, 255);

			if (GetAsyncKeyState(VK_LBUTTON) != 0)
			{
				if (MouseAction(WinX + 148, WinY + 293, 21, 52))
					bSVol = 0;
				if (MouseAction(WinX + 169, WinY + 293, 21, 52))
					bSVol = 1;
				if (MouseAction(WinX + 190, WinY + 293, 21, 52))
					bSVol = 2;
				if (MouseAction(WinX + 211, WinY + 293, 21, 52))
					bSVol = 3;
				if (MouseAction(WinX + 232, WinY + 293, 21, 52))
					bSVol = 4;
				if (MouseAction(WinX + 253, WinY + 293, 21, 52))
					bSVol = 5;
				if (MouseAction(WinX + 274, WinY + 293, 21, 52))
					bSVol = 6;
				if (MouseAction(WinX + 295, WinY + 293, 21, 52))
					bSVol = 7;
				if (MouseAction(WinX + 316, WinY + 293, 21, 52))
					bSVol = 8;
			}
		}
		//Tab 2
		else if (Tab == 2)
		{
			dsDrawTexImage(cImages[4], WinX + 131, WinY + 46, 410, 29, 255);
			dsDrawTexImage(cImages[41], WinX + 255, WinY + 55, 149, 11, 255);


			dsTextLineOut(WinX + 150, WinY + 80, "Camera View Range:", 19);
			dsTextLineOut(WinX + 363, WinY + 80, "Camera Zoom Range:", 19);
			dsTextLineOut(WinX + 150, WinY + 130, "Camera Shake:", 14);
			dsTextLineOut(WinX + 363, WinY + 130, "Inverted Camera:", 17);



			if (bCamShake)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 150, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 150, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 150, "ON", 3);



			if (!bCamShake)
				dsDrawTexImage(cImages[16], WinX + 230, WinY + 150, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 230, WinY + 150, 15, 15, 255);

			dsTextLineOut(WinX + 250, WinY + 150, "OFF", 3);



			if (bCamInv)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 150, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 150, 15, 15, 255);


			dsTextLineOut(WinX + 383, WinY + 150, "ON", 3);

			if (!bCamInv)
				dsDrawTexImage(cImages[16], WinX + 443, WinY + 150, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 443, WinY + 150, 15, 15, 255);

			dsTextLineOut(WinX + 463, WinY + 150, "OFF", 3);

			dsDrawTexImage(cImages[4], WinX + 131, WinY + 173, 410, 29, 255);
			dsDrawTexImage(cImages[42], WinX + 245, WinY + 182, 149, 11, 255);


			if (bFilter)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 202, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 202, 15, 15, 255);

			if (bFilterSpec)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 202, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 202, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 202, "Enable Filter:", 15);
			dsTextLineOut(WinX + 383, WinY + 202, "Enable Spec Filter:", 20);

			if (bHP)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 222, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 222, 15, 15, 255);

			if (bMP)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 242, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 242, 15, 15, 255);

			if (bSP)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 262, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 262, 15, 15, 255);

			if (bGold)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 282, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 282, 15, 15, 255);

			if (bAmulets)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 302, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 302, 15, 15, 255);

			if (bRings)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 322, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 322, 15, 15, 255);

			if (bSheltoms)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 342, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 342, 15, 15, 255);

			if (bForce)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 362, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 362, 15, 15, 255);

			if (bPremiums)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 382, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 382, 15, 15, 255);

			if (bCrystal)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 402, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 402, 15, 15, 255);

			if (bDefItem)
				dsDrawTexImage(cImages[16], WinX + 240, WinY + 222, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 240, WinY + 222, 15, 15, 255);

			if (bOffItem)
				dsDrawTexImage(cImages[16], WinX + 240, WinY + 242, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 240, WinY + 242, 15, 15, 255);

			if (bElse)
				dsDrawTexImage(cImages[16], WinX + 240, WinY + 262, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 240, WinY + 262, 15, 15, 255);


			dsTextLineOut(WinX + 170, WinY + 222, "HP Potions", 11);
			dsTextLineOut(WinX + 170, WinY + 242, "MP Potions", 11);
			dsTextLineOut(WinX + 170, WinY + 262, "SP Potions", 11);
			dsTextLineOut(WinX + 170, WinY + 282, "Gold", 5);
			dsTextLineOut(WinX + 170, WinY + 302, "Amulets", 8);
			dsTextLineOut(WinX + 170, WinY + 322, "Rings", 6);
			dsTextLineOut(WinX + 170, WinY + 342, "Sheltoms", 9);
			dsTextLineOut(WinX + 170, WinY + 362, "Force Orbs", 11);
			dsTextLineOut(WinX + 170, WinY + 382, "Premiums", 9);
			dsTextLineOut(WinX + 170, WinY + 402, "Monster Crystals", 17);

			dsTextLineOut(WinX + 260, WinY + 222, "Defense Items", 14);
			dsTextLineOut(WinX + 260, WinY + 242, "Offense Items", 14);
			dsTextLineOut(WinX + 260, WinY + 262, "Everything Else", 16);


			if (bMS)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 222, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 222, 15, 15, 255);

			if (bFS)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 242, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 242, 15, 15, 255);

			if (bPS)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 262, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 262, 15, 15, 255);

			if (bAS)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 282, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 282, 15, 15, 255);

			if (bKS)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 302, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 302, 15, 15, 255);

			if (bATS)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 322, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 322, 15, 15, 255);

			if (bPRS)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 342, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 342, 15, 15, 255);

			if (bMGS)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 362, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 362, 15, 15, 255);

			if (bASS)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 382, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 382, 15, 15, 255);

			if (bSH)
				dsDrawTexImage(cImages[16], WinX + 363, WinY + 402, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 363, WinY + 402, 15, 15, 255);

			if (bNaked)
				dsDrawTexImage(cImages[16], WinX + 453, WinY + 222, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 453, WinY + 222, 15, 15, 255);

			dsTextLineOut(WinX + 383, WinY + 222, "MS", 2);
			dsTextLineOut(WinX + 383, WinY + 242, "FS", 2);
			dsTextLineOut(WinX + 383, WinY + 262, "PS", 2);
			dsTextLineOut(WinX + 383, WinY + 282, "AS", 2);
			dsTextLineOut(WinX + 383, WinY + 302, "KS", 2);
			dsTextLineOut(WinX + 383, WinY + 322, "ATS", 3);
			dsTextLineOut(WinX + 383, WinY + 342, "PRS", 3);
			dsTextLineOut(WinX + 383, WinY + 362, "MGS", 3);
			dsTextLineOut(WinX + 383, WinY + 382, "ASS", 3);
			dsTextLineOut(WinX + 383, WinY + 402, "SH", 2);
			dsTextLineOut(WinX + 473, WinY + 222, "Naked", 6);

			if (ViewBox)
			{
				HoDrawTexImage(cImages[32], WinX + 150, WinY + 100, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);
				HoDrawTexImage(cImages[33], WinX + 150, WinY + 126, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				HoDrawTexImage(cImages[33], WinX + 150, WinY + 150, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				HoDrawTexImage(cImages[34], WinX + 150, WinY + 174, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);

				if (MouseAction(WinX + 150, WinY + 126, 86, 24))
					HoDrawTexImage(cImages[36], WinX + 150, WinY + 126, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 150, WinY + 150, 86, 24))
					HoDrawTexImage(cImages[36], WinX + 150, WinY + 150, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 150, WinY + 174, 86, 25))
					HoDrawTexImage(cImages[35], WinX + 150, WinY + 174, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);

				dsTextLineOut(WinX + 178, WinY + 128, "Short", 6);
				dsTextLineOut(WinX + 180, WinY + 152, "Far", 4);
				dsTextLineOut(WinX + 180, WinY + 176, "Full", 5);
			}
			else
			{
				if (MouseAction(WinX + 150, WinY + 100, 86, 26))
					HoDrawTexImage(cImages[31], WinX + 150, WinY + 100, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);
				else
					HoDrawTexImage(cImages[18], WinX + 150, WinY + 100, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);
			}


			if (bCamView == 0)
				dsTextLineOut(WinX + 169, WinY + 105, "Short", 6);
			else if (bCamView == 1)
				dsTextLineOut(WinX + 170, WinY + 105, "Far", 4);
			else if (bCamView == 2)
				dsTextLineOut(WinX + 170, WinY + 105, "Full", 5);



			if (ZoomBox)
			{
				HoDrawTexImage(cImages[32], WinX + 363, WinY + 100, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);
				HoDrawTexImage(cImages[33], WinX + 363, WinY + 126, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				HoDrawTexImage(cImages[33], WinX + 363, WinY + 150, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				HoDrawTexImage(cImages[33], WinX + 363, WinY + 174, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				HoDrawTexImage(cImages[34], WinX + 363, WinY + 198, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);

				if (MouseAction(WinX + 363, WinY + 126, 86, 24))
					HoDrawTexImage(cImages[36], WinX + 363, WinY + 126, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 363, WinY + 150, 86, 24))
					HoDrawTexImage(cImages[36], WinX + 363, WinY + 150, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 363, WinY + 174, 86, 24))
					HoDrawTexImage(cImages[36], WinX + 363, WinY + 174, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 363, WinY + 198, 86, 25))
					HoDrawTexImage(cImages[35], WinX + 363, WinY + 198, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);

				dsTextLineOut(WinX + 391, WinY + 128, "Short", 6);
				dsTextLineOut(WinX + 388, WinY + 152, "Regular", 8);
				dsTextLineOut(WinX + 393, WinY + 176, "Far", 4);
				dsTextLineOut(WinX + 385, WinY + 200, "Extra Far", 10);
			}
			else
			{

				if (MouseAction(WinX + 363, WinY + 100, 86, 26))
					HoDrawTexImage(cImages[31], WinX + 363, WinY + 100, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);
				else
					HoDrawTexImage(cImages[18], WinX + 363, WinY + 100, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

			}


			if (bCamRange == 0)
				dsTextLineOut(WinX + 382, WinY + 105, "Short", 6);
			else if (bCamRange == 1)
				dsTextLineOut(WinX + 380, WinY + 105, "Regular", 8);
			else if (bCamRange == 2)
				dsTextLineOut(WinX + 384, WinY + 105, "Far", 4);
			else if (bCamRange == 3)
				dsTextLineOut(WinX + 376, WinY + 105, "Extra Far", 10);
		}
		//Tab3
		/*
		else if (Tab == 3)
		{
			dsDrawTexImage(cImages[4], WinX + 131, WinY + 46, 410, 29, 255);
			dsDrawTexImage(cImages[43], WinX + 255, WinY + 55, 149, 11, 255);

			dsTextLineOut(WinX + 150, WinY + 80, "Exibir Traje", 14);

			if (bTraje)
				dsDrawTexImage(cImages[16], WinX + 150, WinY + 100, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 150, WinY + 100, 15, 15, 255);

			dsTextLineOut(WinX + 170, WinY + 100, "ON", 3);



			if (!bTraje)
				dsDrawTexImage(cImages[16], WinX + 230, WinY + 100, 15, 15, 255);
			else
				dsDrawTexImage(cImages[15], WinX + 230, WinY + 100, 15, 15, 255);

			dsTextLineOut(WinX + 250, WinY + 100, "OFF", 3);
		}
		*/
	}
}

void cSettings::Button()
{
	if (cOpen)
	{
		int WinX = (WinSizeX / 2) - 280, WinY = ((WinSizeY - 600) / 2) + 50;

		if (MouseAction(WinX + 9, WinY + 45, 120, 32))
			Tab = 0;

		if (MouseAction(WinX + 9, WinY + 78, 120, 32))
			Tab = 1;

		if (MouseAction(WinX + 9, WinY + 111, 120, 32))
			Tab = 2;

		//if (MouseAction(WinX + 9, WinY + 144, 120, 32))
			//Tab = 3;

		if (Tab == 0)
		{
			if (MouseAction(WinX + 150, WinY + 100, 15, 15))
				bWindowed = false;

			if (MouseAction(WinX + 239, WinY + 100, 15, 15))
				bWindowed = true;

			if (MouseAction(WinX + 379, WinY + 100, 15, 15))
			{
				if (!bAutoAdjust)
					bAutoAdjust = true;
				else
					bAutoAdjust = false;
			}

			if (MouseAction(WinX + 150, WinY + 151, 15, 15))
				bRatio = 0;
			if (MouseAction(WinX + 150, WinY + 171, 15, 15))
				bRatio = 1;
			if (MouseAction(WinX + 150, WinY + 191, 15, 15))
				bRatio = 2;
			if (MouseAction(WinX + 150, WinY + 211, 15, 15))
				bRatio = 3;

			if (bRatio == 0)
			{
				if (MouseAction(WinX + 303, WinY + 151, 15, 15))
					bResolution = 0;
				if (MouseAction(WinX + 303, WinY + 171, 15, 15))
					bResolution = 1;
				if (MouseAction(WinX + 303, WinY + 191, 15, 15))
					bResolution = 2;
				if (MouseAction(WinX + 303, WinY + 211, 15, 15))
					bResolution = 3;
			}
			else if (bRatio == 1)
			{
				if (MouseAction(WinX + 303, WinY + 151, 15, 15))
					bResolution = 4;
			}
			else if (bRatio == 2)
			{
				if (MouseAction(WinX + 303, WinY + 151, 15, 15))
					bResolution = 5;
				if (MouseAction(WinX + 303, WinY + 171, 15, 15))
					bResolution = 6;
				if (MouseAction(WinX + 303, WinY + 191, 15, 15))
					bResolution = 7;
				if (MouseAction(WinX + 303, WinY + 211, 15, 15))
					bResolution = 8;
			}
			else if (bRatio == 3)
			{
				if (MouseAction(WinX + 303, WinY + 151, 15, 15))
					bResolution = 9;
				if (MouseAction(WinX + 303, WinY + 171, 15, 15))
					bResolution = 10;
				if (MouseAction(WinX + 303, WinY + 191, 15, 15))
					bResolution = 11;
				if (MouseAction(WinX + 303, WinY + 211, 15, 15))
					bResolution = 12;
			}

			if (MouseAction(WinX + 363, WinY + 287, 15, 15))
				bBPP = 32;
			if (MouseAction(WinX + 443, WinY + 287, 15, 15))
				bBPP = 16;

			if (MouseAction(WinX + 150, WinY + 347, 15, 15))
				bEffects = true;
			if (MouseAction(WinX + 230, WinY + 347, 15, 15))
				bEffects = false;

			if (MouseAction(WinX + 363, WinY + 347, 15, 15))
				bLights = true;
			if (MouseAction(WinX + 443, WinY + 347, 15, 15))
				bLights = false;

			if (MouseAction(WinX + 150, WinY + 387, 15, 15))
				bShadows = true;
			if (MouseAction(WinX + 230, WinY + 387, 15, 15))
				bShadows = false;

			if (TextureBox)
			{
				TextureBox = false;
				if (MouseAction(WinX + 150, WinY + 313, 86, 24))
					bTexture = 0;
				if (MouseAction(WinX + 150, WinY + 337, 86, 24))
					bTexture = 1;
				if (MouseAction(WinX + 150, WinY + 361, 86, 24))
					bTexture = 2;
				if (MouseAction(WinX + 150, WinY + 385, 86, 25))
					bTexture = 3;
			}
			else
				if (MouseAction(WinX + 150, WinY + 287, 86, 26))
					TextureBox = true;

		}
		else if (Tab == 1)
		{
			if (MouseAction(WinX + 150, WinY + 80, 15, 15))
			{
				if (!bMusic)
					bMusic = true;
				else
					bMusic = false;
			}

			if (MouseAction(WinX + 150, WinY + 236, 15, 15))
			{
				if (!bSound)
					bSound = true;
				else
					bSound = false;
			}

			if (MouseAction(WinX + 363, WinY + 236, 15, 15))
			{
				if (!bAmbient)
					bAmbient = true;
				else
					bAmbient = false;
			}

		}
		else if (Tab == 2)
		{
			if (ViewBox)
			{
				ViewBox = false;
				if (MouseAction(WinX + 150, WinY + 126, 86, 24))
					bCamView = 0;
				if (MouseAction(WinX + 150, WinY + 150, 86, 24))
					bCamView = 1;
				if (MouseAction(WinX + 150, WinY + 174, 86, 25))
					bCamView = 2;
			}
			else if (MouseAction(WinX + 150, WinY + 100, 86, 26))
				ViewBox = true;

			if (ZoomBox)
			{
				ZoomBox = false;
				if (MouseAction(WinX + 363, WinY + 126, 86, 24))
					bCamRange = 0;
				if (MouseAction(WinX + 363, WinY + 150, 86, 24))
					bCamRange = 1;
				if (MouseAction(WinX + 363, WinY + 174, 86, 24))
					bCamRange = 2;
				if (MouseAction(WinX + 363, WinY + 198, 86, 25))
					bCamRange = 3;
			}
			else if (MouseAction(WinX + 363, WinY + 100, 86, 26))
				ZoomBox = true;

			if (MouseAction(WinX + 150, WinY + 150, 15, 15))
				bCamShake = true;
			if (MouseAction(WinX + 230, WinY + 150, 15, 15))
				bCamShake = false;
			if (MouseAction(WinX + 363, WinY + 150, 15, 15))
				bCamInv = true;
			if (MouseAction(WinX + 443, WinY + 150, 15, 15))
				bCamInv = false;

			if (MouseAction(WinX + 150, WinY + 202, 15, 15))
				if (!bFilter)
					bFilter = true;
				else
					bFilter = false;

			if (MouseAction(WinX + 150, WinY + 222, 15, 15))
				if (!bHP)
					bHP = true;
				else
					bHP = false;

			if (MouseAction(WinX + 150, WinY + 242, 15, 15))
				if (!bMP)
					bMP = true;
				else
					bMP = false;

			if (MouseAction(WinX + 150, WinY + 262, 15, 15))
				if (!bSP)
					bSP = true;
				else
					bSP = false;

			if (MouseAction(WinX + 150, WinY + 282, 15, 15))
				if (!bGold)
					bGold = true;
				else
					bGold = false;

			if (MouseAction(WinX + 150, WinY + 302, 15, 15))
				if (!bAmulets)
					bAmulets = true;
				else
					bAmulets = false;


			if (MouseAction(WinX + 150, WinY + 322, 15, 15))
				if (!bRings)
					bRings = true;
				else
					bRings = false;

			if (MouseAction(WinX + 150, WinY + 342, 15, 15))
				if (!bSheltoms)
					bSheltoms = true;
				else
					bSheltoms = false;

			if (MouseAction(WinX + 150, WinY + 362, 15, 15))
				if (!bForce)
					bForce = true;
				else
					bForce = false;

			if (MouseAction(WinX + 150, WinY + 382, 15, 15))
				if (!bPremiums)
					bPremiums = true;
				else
					bPremiums = false;

			if (MouseAction(WinX + 150, WinY + 402, 15, 15))
				if (!bCrystal)
					bCrystal = true;
				else
					bCrystal = false;

			if (MouseAction(WinX + 240, WinY + 222, 15, 15))
				if (!bDefItem)
					bDefItem = true;
				else
					bDefItem = false;

			if (MouseAction(WinX + 240, WinY + 242, 15, 15))
				if (!bOffItem)
					bOffItem = true;
				else
					bOffItem = false;

			if (MouseAction(WinX + 240, WinY + 262, 15, 15))
				if (!bElse)
					bElse = true;
				else
					bElse = false;

			if (MouseAction(WinX + 363, WinY + 202, 15, 15))
				if (!bFilterSpec)
					bFilterSpec = true;
				else
					bFilterSpec = false;

			if (MouseAction(WinX + 363, WinY + 222, 15, 15))
				if (!bMS)
					bMS = true;
				else
					bMS = false;

			if (MouseAction(WinX + 363, WinY + 242, 15, 15))
				if (!bFS)
					bFS = true;
				else
					bFS = false;


			if (MouseAction(WinX + 363, WinY + 262, 15, 15))
				if (!bPS)
					bPS = true;
				else
					bPS = false;

			if (MouseAction(WinX + 363, WinY + 282, 15, 15))
				if (!bAS)
					bAS = true;
				else
					bAS = false;

			if (MouseAction(WinX + 363, WinY + 302, 15, 15))
				if (!bKS)
					bKS = true;
				else
					bKS = false;

			if (MouseAction(WinX + 363, WinY + 322, 15, 15))
				if (!bATS)
					bATS = true;
				else
					bATS = false;

			if (MouseAction(WinX + 363, WinY + 342, 15, 15))
				if (!bPRS)
					bPRS = true;
				else
					bPRS = false;

			if (MouseAction(WinX + 363, WinY + 362, 15, 15))
				if (!bMGS)
					bMGS = true;
				else
					bMGS = false;

			if (MouseAction(WinX + 363, WinY + 382, 15, 15))
				if (!bASS)
					bASS = true;
				else
					bASS = false;

			if (MouseAction(WinX + 363, WinY + 402, 15, 15))
				if (!bSH)
					bSH = true;
				else
					bSH = false;

			if (MouseAction(WinX + 453, WinY + 222, 15, 15))
				if (!bNaked)
					bNaked = true;
				else
					bNaked = false;
		}
		//Tab3
		else if (Tab == 3)
		{
		if (MouseAction(WinX + 150, WinY + 100, 15, 15))
			bTraje = true;
		if (MouseAction(WinX + 230, WinY + 100, 15, 15))
			bTraje = false;
		}

		if (MouseAction(WinX + 27, WinY + 376, 79, 20))
			Save();
		if (MouseAction(WinX + 27, WinY + 402, 79, 20))
			Close();
	}
}

void cSettings::Load()
{
	IniFiles ini(".\\game.ini");

	if (ini.ReadBool("Screen", "Windowed"))
	{
		smConfig.WinMode = true;
		bWindowed = true;
		cWindowed = true;
	}
	else
	{
		smConfig.WinMode = false;
		bWindowed = false;
		cWindowed = false;
	}

	if (ini.ReadBool("Screen", "AutoAdjust"))
	{
		bAutoAdjust = true;
		cAutoAdjust = true;
	}
	else
	{
		bAutoAdjust = false;
		cAutoAdjust = false;
	}

	if (lstrcmp(ini.ReadString("Screen", "Ratio"), "4:3") == 0)
	{
		bRatio = 0;
		cRatio = 0;
	}

	if (lstrcmp(ini.ReadString("Screen", "Ratio"), "5:4") == 0)
	{
		bRatio = 1;
		cRatio = 1;
	}

	if (lstrcmp(ini.ReadString("Screen", "Ratio"), "16:9") == 0)
	{
		bRatio = 2;
		cRatio = 2;
	}

	if (lstrcmp(ini.ReadString("Screen", "Ratio"), "16:10") == 0)
	{
		bRatio = 3;
		cRatio = 3;
	}

	smConfig.ScreenSize.x = ini.ReadInt("Screen", "Width");
	smConfig.ScreenSize.y = ini.ReadInt("Screen", "Height");

	smScreenWidth = smConfig.ScreenSize.x;
	smScreenHeight = smConfig.ScreenSize.y;

	if (bRatio == 0)
	{
		if (smConfig.ScreenSize.x == 800 && smConfig.ScreenSize.x == 600)
		{
			bResolution = 0;
			cResolution = 0;
		}
		else
			if (smConfig.ScreenSize.x == 1024 && smConfig.ScreenSize.x == 768)
			{
				bResolution = 1;
				cResolution = 1;
			}
			else
				if (smConfig.ScreenSize.x == 1280 && smConfig.ScreenSize.x == 960)
				{
					bResolution = 2;
					cResolution = 2;
				}
				else
					if (smConfig.ScreenSize.x == 1400 && smConfig.ScreenSize.x == 1050)
					{
						bResolution = 3;
						cResolution = 3;
					}
	}
	else if (bRatio == 1)
	{
		if (smConfig.ScreenSize.x == 1280 && smConfig.ScreenSize.x == 1024)
		{
			bResolution = 4;
			cResolution = 4;
		}
	}
	else if (bRatio == 2)
	{
		if (smConfig.ScreenSize.x == 1280 && smConfig.ScreenSize.x == 720)
		{
			bResolution = 5;
			cResolution = 5;
		}
		else
			if (smConfig.ScreenSize.x == 1366 && smConfig.ScreenSize.x == 768)
			{
				bResolution = 6;
				cResolution = 6;
			}
			else
				if (smConfig.ScreenSize.x == 1600 && smConfig.ScreenSize.x == 900)
				{
					bResolution = 7;
					cResolution = 7;
				}
				else
					if (smConfig.ScreenSize.x == 1920 && smConfig.ScreenSize.x == 1080)
					{
						bResolution = 8;
						cResolution = 8;
					}
	}
	else if (bRatio == 3)
	{
		if (smConfig.ScreenSize.x == 1280 && smConfig.ScreenSize.x == 800)
		{
			bResolution = 9;
			cResolution = 9;
		}
		else
			if (smConfig.ScreenSize.x == 1440 && smConfig.ScreenSize.x == 900)
			{
				bResolution = 10;
				cResolution = 10;
			}
			else
				if (smConfig.ScreenSize.x == 1680 && smConfig.ScreenSize.x == 1050)
				{
					bResolution = 11;
					cResolution = 11;
				}
				else
					if (smConfig.ScreenSize.x == 1920 && smConfig.ScreenSize.x == 1200)
					{
						bResolution = 12;
						cResolution = 12;
					}
	}

	bTexture = ini.ReadInt("Graphics", "TextureQuality");
	cTexture = bTexture;
	smConfig.TextureQuality = bTexture;
	bBPP = ini.ReadInt("Graphics", "BitDepth");
	cBPP = bBPP;
	smConfig.ScreenColorBit = bBPP;
	if (ini.ReadBool("Graphics", "Effects"))
	{
		bEffects = true;
		cEffects = true;
	}
	else
	{
		bEffects = false;
		cEffects = false;
	}

	if (ini.ReadBool("Graphics", "DynamicLights"))
	{
		bLights = true;
		cLights = true;
	}
	else
	{
		bLights = false;
		cLights = false;
	}


	if (ini.ReadBool("Graphics", "DynamicShadows"))
	{
		bShadows = true;
		cShadows = true;
	}
	else
	{
		bShadows = false;
		cShadows = false;
	}

	if (ini.ReadBool("Audio", "Music"))
	{
		bMusic = true;
		cMusic = true;
	}
	else
	{
		bMusic = false;
		cMusic = false;
	}


	if (ini.ReadBool("Audio", "Sound"))
	{
		bSound = true;
		cSound = true;
	}
	else
	{
		bSound = false;
		cSound = false;
	}


	if (ini.ReadBool("Audio", "Ambient"))
	{
		bAmbient = true;
		cAmbient = true;
	}
	else
	{
		bAmbient = false;
		cAmbient = false;
	}

	if (ini.ReadBool("Camera", "Shake"))
	{
		bCamShake = true;
		cCamShake = true;
		
	}
	else
	{
		bCamShake = false;
		cCamShake = false;
		
	}

	if (ini.ReadBool("Camera", "Inverted"))
	{
		bCamInv = true;
		cCamInv = true;
		
	}
	else
	{
		bCamInv = false;
		cCamInv = false;
		
	}


	if (ini.ReadBool("LootFilter", "HP"))
	{
		bHP = true;
		cHP = true;
	}
	else
	{
		bHP = false;
		cHP = false;
	}

	if (ini.ReadBool("LootFilter", "MP"))
	{
		bMP = true;
		cMP = true;
	}
	else
	{
		bMP = false;
		cMP = false;
	}

	if (ini.ReadBool("LootFilter", "SP"))
	{
		bSP = true;
		cSP = true;
	}
	else
	{
		bSP = false;
		cSP = false;
	}

	if (ini.ReadBool("LootFilter", "Gold"))
	{
		bGold = true;
		cGold = true;
	}
	else
	{
		bGold = false;
		cGold = false;
	}

	if (ini.ReadBool("LootFilter", "Amulets"))
	{
		bAmulets = true;
		cAmulets = true;
	}
	else
	{
		bAmulets = false;
		cAmulets = false;
	}


	if (ini.ReadBool("LootFilter", "Rings"))
	{
		bRings = true;
		cRings = true;
	}
	else
	{
		bRings = false;
		cRings = false;
	}


	if (ini.ReadBool("LootFilter", "Sheltoms"))
	{
		bSheltoms = true;
		cSheltoms = true;
	}
	else
	{
		bSheltoms = false;
		cSheltoms = false;
	}


	if (ini.ReadBool("LootFilter", "Force"))
	{
		bForce = true;
		cForce = true;
	}
	else
	{
		bForce = false;
		cForce = false;
	}

	if (ini.ReadBool("LootFilter", "Premiums"))
	{
		bPremiums = true;
		cPremiums = true;
	}
	else
	{
		bPremiums = false;
		cPremiums = false;
	}

	if (ini.ReadBool("LootFilter", "Crystal"))
	{
		bCrystal = true;
		cCrystal = true;
	}
	else
	{
		bCrystal = false;
		cCrystal = false;
	}

	if (ini.ReadBool("LootFilter", "DefItem"))
	{
		bDefItem = true;
		cDefItem = true;
	}
	else
	{
		bDefItem = false;
		cDefItem = false;
	}

	if (ini.ReadBool("LootFilter", "Else"))
	{
		bOffItem = true;
		cOffItem = true;
	}
	else
	{
		bOffItem = false;
		cOffItem = false;
	}

	if (ini.ReadBool("LootFilter", "Else"))
	{
		bElse = true;
		cElse = true;
	}
	else
	{
		bElse = false;
		cElse = false;
	}
	
	if (ini.ReadBool("LootFilter", "Enabled"))
	{
		bFilter = true;
		cFilter = true;
	}
	else
	{
		bFilter = false;
		cFilter = false;
	}



	if (ini.ReadBool("LootSpecFilter", "MS"))
	{
		bMS = true;
		cMS = true;
	}
	else
	{
		bMS = false;
		cMS = false;
	}

	if (ini.ReadBool("LootSpecFilter", "FS"))
	{
		bFS = true;
		cFS = true;
	}
	else
	{
		bFS = false;
		cFS = false;
	}

	if (ini.ReadBool("LootSpecFilter", "PS"))
	{
		bPS = true;
		cPS = true;
	}
	else
	{
		bPS = false;
		cPS = false;
	}

	if (ini.ReadBool("LootSpecFilter", "AS"))
	{
		bAS = true;
		cAS = true;
	}
	else
	{
		bAS = false;
		cAS = false;
	}

	if (ini.ReadBool("LootSpecFilter", "KS"))
	{
		bKS = true;
		cKS = true;
	}
	else
	{
		bKS = false;
		cKS = false;
	}

	if (ini.ReadBool("LootSpecFilter", "ATS"))
	{
		bATS = true;
		cATS = true;
	}
	else
	{
		bATS = false;
		cATS = false;
	}

	if (ini.ReadBool("LootSpecFilter", "PRS"))
	{
		bPRS = true;
		cPRS = true;
	}
	else
	{
		bPRS = false;
		cPRS = false;
	}

	if (ini.ReadBool("LootSpecFilter", "MGS"))
	{
		bMGS = true;
		cMGS = true;
	}
	else
	{
		bMGS = false;
		cMGS = false;
	}

	if (ini.ReadBool("LootSpecFilter", "ASS"))
	{
		bASS = true;
		cASS = true;
	}
	else
	{
		bASS = false;
		cASS = false;
	}

	if (ini.ReadBool("LootSpecFilter", "SH"))
	{
		bSH = true;
		cSH = true;
	}
	else
	{
		bSH = false;
		cSH = false;
	}

	if (ini.ReadBool("LootSpecFilter", "Naked"))
	{
		bNaked = true;
		cNaked = true;
	}
	else
	{
		bNaked = false;
		cNaked = false;
	}

	if (ini.ReadBool("LootSpecFilter", "Enabled"))
	{
		bFilterSpec = true;
		cFilterSpec = true;
	}
	else
	{
		bFilterSpec = false;
		cFilterSpec = false;
	}
	if (ini.ReadBool("Personalização", "ExibirTraje"))
	{
		bTraje = true;
		cTraje = true;
		
	}

	bMVol = ini.ReadInt("Audio", "MusicVolume");
	cMVol = bMVol;
	bSVol = ini.ReadInt("Audio", "SoundVolume");
	cSVol = bSVol;
	bCamView = ini.ReadInt("Camera", "View");
	cCamView = bCamView;
	bCamRange = ini.ReadInt("Camera", "Range");
	cCamRange = bCamRange;
	bPort = ini.ReadInt("Game", "Port");
	cPort = bPort;
	
	lstrcpy(Server1, ini.ReadString("Game", "IP"));
	lstrcpy(Server2, ini.ReadString("Game", "IP"));
	lstrcpy(Server3, ini.ReadString("Game", "IP"));
}

void cSettings::Save()
{
	cTraje = bTraje;
	cWindowed = bWindowed;
	cAutoAdjust = bAutoAdjust;
	cRatio = bRatio;
	cResolution = bResolution;
	cTexture = bTexture;
	cBPP = bBPP;
	cEffects = bEffects;
	cLights = bLights;
	cShadows = bShadows;
	cMusic = bMusic;
	cMVol = bMVol;
	cSound = bSound;
	cAmbient = bAmbient;
	cSVol = bSVol;
	cCamView = bCamView;
	cCamRange = bCamRange;
	cCamShake = bCamShake;
	cCamInv = bCamInv;
	cFilter = bFilter;
	cFilterSpec = bFilterSpec;
	cHP = bHP;
	cMP = bMP;
	cSP = bSP;
	cGold = bGold;
	cAmulets = bAmulets;
	cRings = bRings;
	cSheltoms = bSheltoms;
	cForce = bForce;
	cPremiums = bPremiums;
	cCrystal = bCrystal;
	cDefItem = bDefItem;
	cOffItem = bOffItem;
	cElse = bElse;
	cMS = bMS;
	cFS = bFS;
	cPS = bPS;
	cAS = bAS;
	cKS = bKS;
	cATS = bATS;
	cPRS = bPRS;
	cMGS = bMGS;
	cASS = bASS;
	cSH = bSH;
	cNaked = bNaked;

	IniFiles ini(".\\game.ini");
	ini.WriteBool("Screen", "Windowed", cWindowed);
	ini.WriteBool("Screen", "AutoAdjust", cAutoAdjust);
	ini.WriteBool("Audio", "Music", bMusic);
	ini.WriteBool("Audio", "Sound", bSound);
	ini.WriteBool("Graphics", "Effects", cEffects);
	ini.WriteBool("Graphics", "DynamicLights", cLights);
	ini.WriteBool("Graphics", "DynamicShadows", cShadows);
	ini.WriteBool("Camera", "Shake", cCamShake);
	ini.WriteBool("Camera", "Inverted", cCamInv);
	ini.WriteBool("LootFilter", "Enabled", cFilter);
	ini.WriteBool("LootFilter", "HP", cHP);
	ini.WriteBool("LootFilter", "MP", cMP);
	ini.WriteBool("LootFilter", "SP", cSP);
	ini.WriteBool("LootFilter", "Gold", cGold);
	ini.WriteBool("LootFilter", "Amulets", cAmulets);
	ini.WriteBool("LootFilter", "Rings", cRings);
	ini.WriteBool("LootFilter", "Sheltoms", cSheltoms);
	ini.WriteBool("LootFilter", "Force", cForce);
	ini.WriteBool("LootFilter", "Premiums", cPremiums);
	ini.WriteBool("LootFilter", "Crystal", cCrystal);
	ini.WriteBool("LootFilter", "DefItem", cDefItem);
	ini.WriteBool("LootFilter", "OffItem", cOffItem);
	ini.WriteBool("LootFilter", "Else", cElse);

	ini.WriteBool("LootSpecFilter", "Enabled", cFilterSpec);
	ini.WriteBool("LootSpecFilter", "MS", cMS);
	ini.WriteBool("LootSpecFilter", "FS", cFS);
	ini.WriteBool("LootSpecFilter", "PS", cPS);
	ini.WriteBool("LootSpecFilter", "AS", cAS);
	ini.WriteBool("LootSpecFilter", "KS", cKS);
	ini.WriteBool("LootSpecFilter", "ATS", cATS);
	ini.WriteBool("LootSpecFilter", "PRS", cPRS);
	ini.WriteBool("LootSpecFilter", "MGS", cMGS);
	ini.WriteBool("LootSpecFilter", "ASS", cASS);
	ini.WriteBool("LootSpecFilter", "SH", cSH);
	ini.WriteBool("LootSpecFilter", "Naked", cNaked);


	if (cRatio == 0)
	{
		if (cResolution == 0)
		{
			smConfig.ScreenSize.x = 800;
			smConfig.ScreenSize.y = 600;
		}
		else if (cResolution == 1)
		{
			smConfig.ScreenSize.x = 1024;
			smConfig.ScreenSize.y = 768;
		}
		else if (cResolution == 2)
		{
			smConfig.ScreenSize.x = 1280;
			smConfig.ScreenSize.y = 960;
		}
		else if (cResolution == 3)
		{
			smConfig.ScreenSize.x = 1400;
			smConfig.ScreenSize.y = 1050;
		}
	}
	else if (cRatio == 1)
	{
		if (cResolution == 4)
		{
			smConfig.ScreenSize.x = 1280;
			smConfig.ScreenSize.y = 1024;
		}
	}
	else if (cRatio == 2)
	{
		if (cResolution == 5)
		{
			smConfig.ScreenSize.x = 1280;
			smConfig.ScreenSize.y = 720;
		}
		else if (cResolution == 6)
		{
			smConfig.ScreenSize.x = 1366;
			smConfig.ScreenSize.y = 768;
		}
		else if (cResolution == 7)
		{
			smConfig.ScreenSize.x = 1600;
			smConfig.ScreenSize.y = 900;
		}
		else if (cResolution == 8)
		{
			smConfig.ScreenSize.x = 1920;
			smConfig.ScreenSize.y = 1080;
		}
	}
	else if (cRatio == 3)
	{
		if (cResolution == 9)
		{
			smConfig.ScreenSize.x = 1280;
			smConfig.ScreenSize.y = 800;
		}
		else if (cResolution == 10)
		{
			smConfig.ScreenSize.x = 1440;
			smConfig.ScreenSize.y = 900;
		}
		else if (cResolution == 11)
		{
			smConfig.ScreenSize.x = 1680;
			smConfig.ScreenSize.y = 1050;
		}
		else if (cResolution == 12)
		{
			smConfig.ScreenSize.x = 1920;
			smConfig.ScreenSize.y = 1200;
		}
	}

	ini.WriteInt("Screen", "Width", smConfig.ScreenSize.x);
	ini.WriteInt("Screen", "Height", smConfig.ScreenSize.y);
	ini.WriteInt("Graphics", "TextureQuality", cTexture);
	ini.WriteInt("Graphics", "BitDepth", cBPP);
	ini.WriteInt("Audio", "MusicVolume", cMVol);
	ini.WriteInt("Audio", "SoundVolume", cSVol);
	ini.WriteInt("Camera", "View", cCamView);
	ini.WriteInt("Camera", "Range", cCamRange);
	Set(cWindowed, smConfig.ScreenSize.x, smConfig.ScreenSize.y);

	SetVolumeBGM(360);
}

void cSettings::Set(int Windowed, int iWidth, int iHeight)
{

	WinSizeX = iWidth;
	WinSizeY = iHeight;
	smScreenWidth = iWidth;
    smScreenHeight = iHeight;
	MidX = WinSizeX / 2;
	MidY = WinSizeY / 2;

	viewdistZ = ((WinSizeY / 3) * 4);

	SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);

	if (Windowed)
	{
		RECT rc = { 0, 0, iWidth, iHeight };

		UINT uWindowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
		AdjustWindowRect(&rc, uWindowStyle, FALSE);

		int w = rc.right - rc.left;
		int h = rc.bottom - rc.top;

		SetWindowLongA(hwnd, GWL_STYLE, uWindowStyle);
		SetWindowPos(hwnd,
			NULL,
			((GetSystemMetrics(SM_CXSCREEN) >> 1) - (w >> 1)),
			((GetSystemMetrics(SM_CYSCREEN) >> 1) - (h >> 1)),
			w,
			h,
			SWP_NOZORDER);

		UpdateWindow(hwnd);
	}
	else
	{
		SetWindowPos(hwnd,
			NULL,
			0,
			0,
			GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN),
			SWP_DRAWFRAME | SWP_NOZORDER);

		SetWindowLongA(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	}

	if (d3ddev)
	{
		d3dpp.BackBufferWidth = WinSizeX;
		d3dpp.BackBufferHeight = WinSizeY;
		OnLostDevice();
		d3ddev->Reset(&d3dpp);
		InitRender();
		OnResetDevice();
	}

}

void cSettings::Reset()
{
	bTraje = false;
	bWindowed = true;
	bAutoAdjust = true;
	bRatio = 0;
	bResolution = 0;
	bTexture = 0;
	bBPP = 32;
	bEffects = true;
	bLights = false;
	bShadows = true;
	bMusic = false;
	bMVol = 0;
	bSound = false;
	bAmbient = false;
	bSVol = 0;
	bCamView = 0;
	bCamRange = 0;
	bCamShake = false;
	bCamInv = false;
	bFilter = true;
	bFilterSpec = true;
	bHP = true;
	bMP = true;
	bSP = true;
	bGold = true;
	bAmulets = true;
	bRings = true;
	bSheltoms = true;
	bForce = true;
	bPremiums = true;
	bCrystal = true;
	bDefItem = true;
	bOffItem = true;
	bElse = true;
	bMS = true;
	bFS = true;
	bPS = true;
	bAS = true;
	bKS = true;
	bATS = true;
	bPRS = true;
	bMGS = true;
	bASS = true;
	bSH = true;
	bNaked = true;
}
