#include "sinbaram\sinLinkHeader.h"

SHOP List;
SHOP_ITEM selectitem;

void Shop::RecvItemToServer(SHOP* Shop)
{
	char Dir[1024];
	CopyMemory(&List, Shop, sizeof(SHOP));

	for (int cnt = 0; cnt < 1000; cnt++)
	{
		switch (List.item[cnt].SubTag)
		{
		case 1:
			wsprintf(Dir, "image\\sinimage\\items\\Accessory\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 2:
			wsprintf(Dir, "image\\sinimage\\items\\Accessory\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 3:
			wsprintf(Dir, "image\\sinimage\\items\\Accessory\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 4:
			wsprintf(Dir, "image\\sinimage\\items\\Accessory\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 5:
			wsprintf(Dir, "image\\sinimage\\items\\Premium\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 6:
			wsprintf(Dir, "image\\sinimage\\items\\Premium\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 7:
			wsprintf(Dir, "image\\sinimage\\items\\Premium\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 8:
			wsprintf(Dir, "image\\sinimage\\items\\Premium\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 9:
			wsprintf(Dir, "image\\sinimage\\items\\Defense\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 10:
			wsprintf(Dir, "image\\sinimage\\items\\Defense\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 11:
			wsprintf(Dir, "image\\sinimage\\items\\Defense\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 12:
			wsprintf(Dir, "image\\sinimage\\items\\Accessory\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 13:
			wsprintf(Dir, "image\\sinimage\\items\\Defense\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 14:
			wsprintf(Dir, "image\\sinimage\\items\\Defense\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 15:
			wsprintf(Dir, "image\\sinimage\\items\\Defense\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 16:
			wsprintf(Dir, "image\\sinimage\\items\\Accessory\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 17:
			wsprintf(Dir, "image\\sinimage\\items\\Weapon\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 18:
			wsprintf(Dir, "image\\sinimage\\items\\Weapon\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 19:
			wsprintf(Dir, "image\\sinimage\\items\\Weapon\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 20:
			wsprintf(Dir, "image\\sinimage\\items\\Weapon\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 21:
			wsprintf(Dir, "image\\sinimage\\items\\Weapon\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 22:
			wsprintf(Dir, "image\\sinimage\\items\\Weapon\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 23:
			wsprintf(Dir, "image\\sinimage\\items\\Weapon\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		case 24:
			wsprintf(Dir, "image\\sinimage\\items\\Weapon\\it%s.bmp", List.item[cnt].itCode);
			List.item[cnt].Image = LoadDibSurfaceOffscreen(Dir);
			break;
		}
	}
}

void Shop::PlusCoin(int Coin)
{
	Coin += Coin;
}

void Shop::MinusCoin(int Coin)
{
	Coin -= Coin;
}


void Shop::SendItemToServer(SHOP_ITEM item)
{
	if (sinChar->Weight[0] + 200 >= sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return;
	}
	else
	{
		selectitem = item;
		cMessageBox.ShowMessage3(MESSAGE_COIN_SHOP, "Deseja comprar?");
	}

}


void Shop::RecvCoinToServer(SHOP_COIN* Shop)
{
	Coin = Shop->Coin;
}

bool Shop::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void Shop::Open()
{
	fOpen = true;
}

void Shop::Init()
{
	Image[0] = CreateTextureMaterial("game\\images\\CoinShop\\background.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[1] = CreateTextureMaterial("game\\images\\CoinShop\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[2] = CreateTextureMaterial("game\\images\\CoinShop\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[3] = CreateTextureMaterial("game\\images\\shop\\btncredits.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[4] = CreateTextureMaterial("game\\images\\shop\\btncredits_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Image[5] = CreateTextureMaterial("game\\images\\CoinShop\\cat\\acessories.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[6] = CreateTextureMaterial("game\\images\\CoinShop\\cat\\acessories_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	//Weapons
	Image[7] = CreateTextureMaterial("game\\images\\CoinShop\\tabs\\weapons.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[8] = CreateTextureMaterial("game\\images\\CoinShop\\tabs\\weapons_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	//Defense
	Image[9] = CreateTextureMaterial("game\\images\\CoinShop\\tabs\\defense.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[10] = CreateTextureMaterial("game\\images\\CoinShop\\tabs\\defense_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	//Acessorios
	Image[11] = CreateTextureMaterial("game\\images\\CoinShop\\tabs\\accessories.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[12] = CreateTextureMaterial("game\\images\\CoinShop\\tabs\\accessories_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	//Premium
	Image[13] = CreateTextureMaterial("game\\images\\CoinShop\\tabs\\premium.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[14] = CreateTextureMaterial("game\\images\\CoinShop\\tabs\\premium_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Image[15] = CreateTextureMaterial("game\\images\\shop\\line.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[16] = CreateTextureMaterial("game\\images\\shop\\line2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[17] = CreateTextureMaterial("game\\images\\shop\\cat\\amulets.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[18] = CreateTextureMaterial("game\\images\\shop\\cat\\amulets_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[19] = CreateTextureMaterial("game\\images\\shop\\cat\\rings.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[20] = CreateTextureMaterial("game\\images\\shop\\cat\\rings_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[21] = CreateTextureMaterial("game\\images\\shop\\cat\\sheltons.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[22] = CreateTextureMaterial("game\\images\\shop\\cat\\sheltons_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[23] = CreateTextureMaterial("game\\images\\shop\\cat\\force.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[24] = CreateTextureMaterial("game\\images\\shop\\cat\\force_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[25] = CreateTextureMaterial("game\\images\\shop\\winitem.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[26] = CreateTextureMaterial("game\\images\\shop\\coin.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//Comprar
	Image[27] = CreateTextureMaterial("game\\images\\CoinShop\\btnbuy.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[28] = CreateTextureMaterial("game\\images\\CoinShop\\btnbuy_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Image[29] = CreateTextureMaterial("game\\images\\shop\\line3.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[30] = CreateTextureMaterial("game\\images\\shop\\cat\\hunting.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[31] = CreateTextureMaterial("game\\images\\shop\\cat\\hunting_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[32] = CreateTextureMaterial("game\\images\\shop\\cat\\mixing.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[33] = CreateTextureMaterial("game\\images\\shop\\cat\\mixing_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[34] = CreateTextureMaterial("game\\images\\shop\\cat\\aging.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[35] = CreateTextureMaterial("game\\images\\shop\\cat\\aging_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[36] = CreateTextureMaterial("game\\images\\shop\\cat\\pets.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[37] = CreateTextureMaterial("game\\images\\shop\\cat\\pets_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[38] = CreateTextureMaterial("game\\images\\shop\\cat\\Crystal.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[39] = CreateTextureMaterial("game\\images\\shop\\cat\\Crystal_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[40] = CreateTextureMaterial("game\\images\\shop\\cat\\PackageUp.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[41] = CreateTextureMaterial("game\\images\\shop\\cat\\PackageUp_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[42] = CreateTextureMaterial("game\\images\\shop\\cat\\Costume.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[43] = CreateTextureMaterial("game\\images\\shop\\cat\\Costume_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//ScrollBar
	Image[44] = CreateTextureMaterial("game\\images\\CoinShop\\scrollbar.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//ScrollBar Icon
	Image[45] = CreateTextureMaterial("game\\images\\CoinShop\\scrollbar_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Image[46] = CreateTextureMaterial("game\\images\\shop\\cat\\Armor.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[47] = CreateTextureMaterial("game\\images\\shop\\cat\\Armor_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[48] = CreateTextureMaterial("game\\images\\shop\\cat\\Robes.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[49] = CreateTextureMaterial("game\\images\\shop\\cat\\Robes_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[50] = CreateTextureMaterial("game\\images\\shop\\cat\\Armlets.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[51] = CreateTextureMaterial("game\\images\\shop\\cat\\Armlets_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[52] = CreateTextureMaterial("game\\images\\shop\\cat\\Gloves.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[53] = CreateTextureMaterial("game\\images\\shop\\cat\\Gloves_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[54] = CreateTextureMaterial("game\\images\\shop\\cat\\Boots.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[55] = CreateTextureMaterial("game\\images\\shop\\cat\\Boots_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[56] = CreateTextureMaterial("game\\images\\shop\\cat\\Shields.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[57] = CreateTextureMaterial("game\\images\\shop\\cat\\Shields_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[58] = CreateTextureMaterial("game\\images\\shop\\cat\\Orbs.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[59] = CreateTextureMaterial("game\\images\\shop\\cat\\Orbs_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//Machado
	Image[60] = CreateTextureMaterial("game\\images\\CoinShop\\categories\\Axes.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[61] = CreateTextureMaterial("game\\images\\CoinShop\\categories\\Axes_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Image[62] = CreateTextureMaterial("game\\images\\shop\\cat\\Claws.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[63] = CreateTextureMaterial("game\\images\\shop\\cat\\Claws_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[64] = CreateTextureMaterial("game\\images\\shop\\cat\\Maces.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[65] = CreateTextureMaterial("game\\images\\shop\\cat\\Maces_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[66] = CreateTextureMaterial("game\\images\\shop\\cat\\Wands.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[67] = CreateTextureMaterial("game\\images\\shop\\cat\\Wands_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[68] = CreateTextureMaterial("game\\images\\shop\\cat\\Scythes.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[69] = CreateTextureMaterial("game\\images\\shop\\cat\\Scythes_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[70] = CreateTextureMaterial("game\\images\\shop\\cat\\Bows.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[71] = CreateTextureMaterial("game\\images\\shop\\cat\\Bows_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[72] = CreateTextureMaterial("game\\images\\shop\\cat\\Swords.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[73] = CreateTextureMaterial("game\\images\\shop\\cat\\Swords_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[74] = CreateTextureMaterial("game\\images\\shop\\cat\\Javelin.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[75] = CreateTextureMaterial("game\\images\\shop\\cat\\Javelin_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[76] = CreateTextureMaterial("game\\images\\shop\\drop.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[77] = CreateTextureMaterial("game\\images\\shop\\dropon.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[78] = CreateTextureMaterial("game\\images\\shop\\drop_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[79] = CreateTextureMaterial("game\\images\\shop\\dropbg.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[80] = CreateTextureMaterial("game\\images\\shop\\dropdown.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[81] = CreateTextureMaterial("game\\images\\shop\\cat\\vip.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[82] = CreateTextureMaterial("game\\images\\shop\\cat\\vip_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[83] = CreateTextureMaterial("game\\images\\shop\\star.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[84] = CreateTextureMaterial("game\\images\\CoinShop\\left.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Image[85] = CreateTextureMaterial("game\\images\\CoinShop\\left_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//item
	Image[86] = CreateTextureMaterial("game\\images\\CoinShop\\itWA138.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ReadTextures();
}

void DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}


void Shop::Draw()
{
	char szBuff[10] = { 0 };
	int WinX = 40, WinY = 70, cnt2 = 0;

	if (fOpen)
	{
		DrawImage(Image[0], WinX, WinY, 560, 450);
		//wsprintf(szBuff, "%d", Coin);
		wsprintf(szBuff, "Olá %s!", lpCurPlayer->smCharInfo.szName);
		DrawFontText(WinX + 23, WinY + 350, szBuff, RGB(255, 255, 255), false);

		wsprintf(szBuff, "%d", Coin);
		DrawFontText(WinX + 23, WinY + 370, szBuff, RGB(255, 255, 255), false);

		//Fechar
		if (MouseAction(WinX + 23, WinY + 325, 93, 23))
			DrawImage(Image[2], WinX + 23, WinY + 325, 93, 23);
		else
			DrawImage(Image[1], WinX + 23, WinY + 325, 93, 23);
		//Arma
		if (MouseAction(WinX + 23, WinY + 55, 159, 29) || Tag == 2)
			DrawImage(Image[8], WinX + 23, WinY + 55, 159, 29);
		else
			DrawImage(Image[7], WinX + 23, WinY + 55, 159, 29);
		//Defesa
		if (MouseAction(WinX + 23, WinY + 84, 159, 29) || Tag == 3)
			DrawImage(Image[10], WinX + 23, WinY + 84, 159, 29);
		else
			DrawImage(Image[9], WinX + 23, WinY + 84, 159, 29);
		//Acessorios
		if (MouseAction(WinX +23, WinY + 113, 159, 29) || Tag == 4)
			DrawImage(Image[12], WinX + 23, WinY + 113, 159, 29);
		else
			DrawImage(Image[11], WinX + 23, WinY + 113, 159, 29);
		//Premium
		if (MouseAction(WinX + 23, WinY + 142, 159, 29) || Tag == 5)
			DrawImage(Image[14], WinX + 23, WinY + 142, 159, 29);
		else
			DrawImage(Image[13], WinX + 23, WinY + 142, 159, 29);		

		if (Tag == 2)
		{
			if (MouseAction(WinX + 191, WinY + 55, 12, 12))
				DrawImage(Image[85], WinX + 191, WinY + 55, 12, 12);
			else
				DrawImage(Image[84], WinX + 191, WinY + 55, 12, 12);

			//Machado(1º item)
			if (MouseAction(WinX + 194, WinY + 55, 74, 14) || SubTag == 17)
				DrawImage(Image[61], WinX + 194, WinY + 55, 74, 14);
			else
				DrawImage(Image[60], WinX + 194, WinY + 55, 74, 14);
		}

		if (SubTag)
		{
			WinX = 250;
			//DrawImage(Image[25], WinX, WinY, 316, 362);
			float Percent = (float)Scroll;
			Percent = (Percent * 100) / (float)GetScroll();
			Percent = (330 * Percent) / 100;
			DrawImage(Image[44], WinX + 310, WinY + 90, 6, 330);//scrollbar
			DrawImage(Image[45], WinX + 310, WinY + 90 + Percent, 8, 11);//icon-scrollbar

			if (MouseAction(WinX + 310, WinY + 90, 8, 330) && GetAsyncKeyState(VK_LBUTTON) != 0)
			{
				float p = (((int)pRealCursorPos.y - (WinY + 18)) * 100) / 330;
				Scroll = (GetScroll() * p) / 100;
			}

			for (int cnt = 0; cnt < 70; cnt++)
			{
				if (List.item[cnt].SubTag && List.item[cnt].SubTag == SubTag)
				{
					int SlotY = cnt2 * 100 - Scroll * 10;
					if (strstr(List.item[cnt].itCode, "VIP"))
					{
						if (List.item[cnt].spec == 0)
							wsprintf(szBuff, "%d", List.item[cnt].Coin);
						if (List.item[cnt].spec == 1)
							wsprintf(szBuff, "%d", List.item[cnt].Coin * 2);
						else if (List.item[cnt].spec == 2)
							wsprintf(szBuff, "%d", List.item[cnt].Coin * 3);
					}
					else
						wsprintf(szBuff, "%d", List.item[cnt].Coin);
					//Nome Item
					if (WinY + 48 + SlotY < 370 && WinY + 102 + SlotY > WinY + 47)
						DrawFontText(WinX + 98, WinY + 102 + SlotY, List.item[cnt].Name, RGB(255, 255, 255), true);
					//Valor do item
					if (WinY + 52 + SlotY < 370 && WinY + 96 + SlotY > WinY + 48)
						DrawFontText(WinX + 256 - strlen(szBuff) * 3, WinY + 96 + SlotY, szBuff, RGB(255, 255, 255), false);
					//Icone Coins
					if (WinY + 53 + SlotY < 370 && WinY + 98 + SlotY > WinY + 48)
						DrawImage(Image[26], WinX + 221, WinY + 99 + SlotY, 23, 14);
					//Botao Comprar
					if (WinY + 100 + SlotY < 370 && WinY + 115 + SlotY > WinY + 48)
					{
						if (MouseAction(WinX + 100, WinY + 115 + SlotY, 75, 26))
							DrawImage(Image[28], WinX + 222, WinY + 115 + SlotY, 75, 26);
						else
							DrawImage(Image[27], WinX + 222, WinY + 115 + SlotY, 75, 26);
					}

					if (WinY + 56 + SlotY < 370 && WinY + 56 + SlotY > WinY + 48)
					{
						if (strstr(List.item[cnt].itCode, "VIP"))
						{
							DrawImage(Image[83], WinX + 22, WinY + 43 + SlotY, 65, 75);
						}
						else
						{
							if (SubTag >= 1)
								DrawSprite(WinX + 22, WinY + 43 + SlotY, List.item[cnt].Image, 0, 0, List.item[cnt].w, List.item[cnt].h);
							else
								DrawSprite(WinX + 34, WinY + 56 + SlotY, List.item[cnt].Image, 0, 0, List.item[cnt].w, List.item[cnt].h);
							if (strstr(List.item[cnt].itCode, "FO1"))
								cInvenTory.DrawForceOrbEffect(WinX + 34, WinY + 56 + SlotY);
						}
					}

					if (WinY + 145 + SlotY < 370 && WinY + 145 + SlotY > WinY + 48)
						DrawImage(Image[29], WinX + 16, WinY + 145 + SlotY, 275, 2);

					if (!List.item[cnt].combobox)
					{
						if (WinY + 73 + SlotY < 370 && WinY + 73 + SlotY > WinY + 48)
						{
							if (MouseAction(WinX + 89, WinY + 73 + SlotY, 110, 26))
								DrawImage(Image[77], WinX + 89, WinY + 73 + SlotY, 111, 27);
							else
								DrawImage(Image[76], WinX + 89, WinY + 73 + SlotY, 111, 27);
						}

						if (WinY + 78 + SlotY < 370 && WinY + 78 + SlotY > WinY + 48)
						{
							
							if (List.item[cnt].spec == 1)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Lutador", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 2)
								DrawFontText(WinX + 100, WinY + 78 + SlotY, "Mecanico", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 3)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Arqueira", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 4)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Pike", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 5)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Atalanta", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 6)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Cavaleiro", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 7)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Mago", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 8)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Sacerdotisa", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 9)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Assassina", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 10)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Xamã", RGB(93, 90, 85), false);
							else
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Sem Spec", RGB(93, 90, 85), false);
							//}
						}
					}

					cnt2++;
				}
			}

			cnt2 = 0;

			for (int cnt = 0; cnt < 70; cnt++)
			{
				if (List.item[cnt].SubTag && List.item[cnt].SubTag == SubTag)
				{
					int SlotY = cnt2 * 100 - Scroll * 10;

					if (List.item[cnt].combobox)
					{
						if (strstr(List.item[cnt].itCode, "VIP"))
						{
							if (WinY + 73 + SlotY < 370 && WinY + 73 + SlotY > WinY + 48)
								DrawImage(Image[78], WinX + 89, WinY + 73 + SlotY, 111, 27);
							if (WinY + 99 + SlotY < 370 && WinY + 99 + SlotY > WinY + 48)
								DrawImage(Image[79], WinX + 89, WinY + 99 + SlotY, 111, 27);
							if (WinY + 125 + SlotY < 370 && WinY + 125 + SlotY > WinY + 48)
								DrawImage(Image[80], WinX + 89, WinY + 125 + SlotY, 111, 27);
						}
						else
						{
							if (WinY + 73 + SlotY < 370 && WinY + 73 + SlotY > WinY + 48)
								DrawImage(Image[78], WinX + 89, WinY + 73 + SlotY, 111, 27);
							if (WinY + 99 + SlotY < 370 && WinY + 99 + SlotY > WinY + 48)
								DrawImage(Image[79], WinX + 89, WinY + 99 + SlotY, 111, 27);
							if (WinY + 125 + SlotY < 370 && WinY + 125 + SlotY > WinY + 48)
								DrawImage(Image[79], WinX + 89, WinY + 125 + SlotY, 111, 27);
							if (WinY + 151 + SlotY < 370 && WinY + 151 + SlotY > WinY + 48)
								DrawImage(Image[79], WinX + 89, WinY + 151 + SlotY, 111, 27);
							if (WinY + 177 + SlotY < 370 && WinY + 177 + SlotY > WinY + 48)
								DrawImage(Image[79], WinX + 89, WinY + 177 + SlotY, 111, 27);
							if (WinY + 203 + SlotY < 370 && WinY + 203 + SlotY > WinY + 48)
								DrawImage(Image[79], WinX + 89, WinY + 203 + SlotY, 111, 27);
							if (WinY + 229 + SlotY < 370 && WinY + 229 + SlotY > WinY + 48)
								DrawImage(Image[79], WinX + 89, WinY + 229 + SlotY, 111, 27);
							if (WinY + 255 + SlotY < 370 && WinY + 255 + SlotY > WinY + 48)
								DrawImage(Image[79], WinX + 89, WinY + 255 + SlotY, 111, 27);
							if (WinY + 281 + SlotY < 370 && WinY + 281 + SlotY > WinY + 48)
								DrawImage(Image[80], WinX + 89, WinY + 281 + SlotY, 111, 27);
						}

						if (WinY + 78 + SlotY < 370 && WinY + 78 + SlotY > WinY + 48)
						{
							
							if (List.item[cnt].spec == 1)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Fighter", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 2)
								DrawFontText(WinX + 100, WinY + 78 + SlotY, "Mechanician", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 3)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Archer", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 4)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Pikeman", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 5)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Atalanta", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 6)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Knight", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 7)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Magician", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 8)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Priestess", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 9)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Assassin", RGB(93, 90, 85), false);
							else if (List.item[cnt].spec == 10)
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Shaman", RGB(93, 90, 85), false);
							else
								DrawFontText(WinX + 110, WinY + 78 + SlotY, "Sem Spec", RGB(93, 90, 85), false);
							//}

						}

						SIZE size;
						if (strstr(List.item[cnt].itCode, "VIP"))
						{
							if (WinY + 98 + SlotY < 370 && WinY + 98 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("1 Day", 6, &size);
								if (MouseAction(WinX + 115, WinY + 98 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 98 + SlotY, "1 Day", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 98 + SlotY, "1 Day", RGB(93, 90, 85), false);
							}

							if (WinY + 118 + SlotY < 370 && WinY + 118 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("7 Days", 7, &size);
								if (MouseAction(WinX + 115, WinY + 116 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 116 + SlotY, "7 Days", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 116 + SlotY, "7 Days", RGB(93, 90, 85), false);
							}

							if (WinY + 137 + SlotY < 370 && WinY + 137 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("30 Days", 8, &size);
								if (MouseAction(WinX + 115, WinY + 135 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 135 + SlotY, "30 Days", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 135 + SlotY, "30 Days", RGB(93, 90, 85), false);
							}
						}
						else
						{
							if (WinY + 98 + SlotY < 370 && WinY + 98 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Fighter", 8, &size);
								if (MouseAction(WinX + 115, WinY + 98 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 98 + SlotY, "Fighter", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 98 + SlotY, "Fighter", RGB(93, 90, 85), false);
							}

							if (WinY + 118 + SlotY < 370 && WinY + 118 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Mechanician", 12, &size);
								if (MouseAction(WinX + 105, WinY + 118 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 105, WinY + 118 + SlotY, "Mechanician", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 105, WinY + 118 + SlotY, "Mechanician", RGB(93, 90, 85), false);
							}

							if (WinY + 138 + SlotY < 370 && WinY + 138 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Archer", 7, &size);
								if (MouseAction(WinX + 115, WinY + 138 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 138 + SlotY, "Archer", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 138 + SlotY, "Archer", RGB(93, 90, 85), false);
							}

							if (WinY + 158 + SlotY < 370 && WinY + 158 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Pikeman", 8, &size);
								if (MouseAction(WinX + 115, WinY + 158 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 158 + SlotY, "Pikeman", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 158 + SlotY, "Pikeman", RGB(93, 90, 85), false);
							}

							if (WinY + 178 + SlotY < 370 && WinY + 178 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Atalanta", 9, &size);
								if (MouseAction(WinX + 115, WinY + 178 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 178 + SlotY, "Atalanta", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 178 + SlotY, "Atalanta", RGB(93, 90, 85), false);
							}

							if (WinY + 198 + SlotY < 370 && WinY + 198 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Knight", 7, &size);
								if (MouseAction(WinX + 115, WinY + 198 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 198 + SlotY, "Knight", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 198 + SlotY, "Knight", RGB(93, 90, 85), false);
							}

							if (WinY + 218 + SlotY < 370 && WinY + 218 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Magician", 9, &size);
								if (MouseAction(WinX + 115, WinY + 218 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 218 + SlotY, "Magician", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 218 + SlotY, "Magician", RGB(93, 90, 85), false);
							}

							if (WinY + 238 + SlotY < 370 && WinY + 238 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Priestess", 10, &size);
								if (MouseAction(WinX + 115, WinY + 238 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 238 + SlotY, "Priestess", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 238 + SlotY, "Priestess", RGB(93, 90, 85), false);
							}


							if (WinY + 258 + SlotY < 370 && WinY + 258 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Assassin", 9, &size);
								if (MouseAction(WinX + 115, WinY + 258 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 258 + SlotY, "Assassin", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 258 + SlotY, "Assassin", RGB(93, 90, 85), false);
							}


							if (WinY + 278 + SlotY < 370 && WinY + 278 + SlotY > WinY + 48)
							{
								GetFontTextExtentPoint("Shaman", 7, &size);
								if (MouseAction(WinX + 115, WinY + 278 + SlotY, size.cx, size.cy))
									DrawFontText(WinX + 115, WinY + 278 + SlotY, "Shaman", RGB(174, 143, 2), false);
								else
									DrawFontText(WinX + 115, WinY + 278 + SlotY, "Shaman", RGB(93, 90, 85), false);
							}


						}
					}

					cnt2++;
				}
			}
		}
	}
}

void Shop::Close()
{
	fOpen = false;
}

void Shop::Button()
{
	if (fOpen)
	{
		int WinX = 40, WinY = 70, cnt2 = 0;
		//Arma
		if (MouseAction(WinX + 23, WinY + 55, 159, 29) && Tag != 2)
			Tag = 2;
		//Defesa
		if (MouseAction(WinX + 23, WinY + 55, 159, 29) && Tag != 1)
			SubTag = 2;
		//Acessorio
		if (MouseAction(WinX + 23, WinY + 84, 159, 29) && Tag != 3)
			SubTag = 3;
		//Premium
		if (MouseAction(WinX + 23, WinY + 113, 159, 29) && Tag != 4)
			SubTag = 4;

		if (Tag == 2)
		{
			if (MouseAction(WinX + 214, WinY + 43, 79, 26) && SubTag != 17)
			{
				SubTag = 17;
				Scroll = 0;
			}

			if (MouseAction(WinX + 214, WinY + 73, 79, 26) && SubTag != 18)
			{
				SubTag = 18;
				Scroll = 0;
			}

			if (MouseAction(WinX + 214, WinY + 104, 79, 26) && SubTag != 19)
			{
				SubTag = 19;
				Scroll = 0;
			}

			if (MouseAction(WinX + 214, WinY + 135, 79, 26) && SubTag != 20)
			{
				SubTag = 20;
				Scroll = 0;
			}

			if (MouseAction(WinX + 214, WinY + 166, 79, 26) && SubTag != 21)
			{
				SubTag = 21;
				Scroll = 0;
			}

			if (MouseAction(WinX + 214, WinY + 197, 79, 26) && SubTag != 22)
			{
				SubTag = 22;
				Scroll = 0;
			}

			if (MouseAction(WinX + 214, WinY + 228, 79, 26) && SubTag != 23)
			{
				SubTag = 23;
				Scroll = 0;
			}

			if (MouseAction(WinX + 214, WinY + 259, 79, 26) && SubTag != 24)
			{
				SubTag = 24;
				Scroll = 0;
			}
		}


		if (SubTag)
		{
			WinX = 450;
			for (int cnt = 0; cnt < 70; cnt++)
			{

				if (List.item[cnt].SubTag && List.item[cnt].SubTag == SubTag)
				{
					int SlotY = cnt2 * 100 - Scroll * 10;

					if (List.item[cnt].combobox)
					{
						SIZE size;
						if (strstr(List.item[cnt].itCode, "VIP"))
						{
							GetFontTextExtentPoint("1 Day", 6, &size);
							if (MouseAction(WinX + 115, WinY + 98 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 0;
							GetFontTextExtentPoint("7 Days", 7, &size);
							if (MouseAction(WinX + 115, WinY + 116 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 1;
							GetFontTextExtentPoint("30 Days", 8, &size);
							if (MouseAction(WinX + 115, WinY + 135 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 2;
							List.item[cnt].combobox = false;
						}
						else
						{
							GetFontTextExtentPoint("Fighter", 8, &size);
							if (MouseAction(WinX + 115, WinY + 98 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 1;
							GetFontTextExtentPoint("Mechanician", 12, &size);
							if (MouseAction(WinX + 105, WinY + 118 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 2;
							GetFontTextExtentPoint("Archer", 7, &size);
							if (MouseAction(WinX + 115, WinY + 138 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 3;
							GetFontTextExtentPoint("Pikeman", 8, &size);
							if (MouseAction(WinX + 115, WinY + 158 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 4;
							GetFontTextExtentPoint("Atalanta", 9, &size);
							if (MouseAction(WinX + 115, WinY + 178 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 5;
							GetFontTextExtentPoint("Knight", 7, &size);
							if (MouseAction(WinX + 115, WinY + 198 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 6;
							GetFontTextExtentPoint("Magician", 9, &size);
							if (MouseAction(WinX + 115, WinY + 218 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 7;
							GetFontTextExtentPoint("Priestess", 10, &size);
							if (MouseAction(WinX + 115, WinY + 238 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 8;
							GetFontTextExtentPoint("Assassin", 9, &size);
							if (MouseAction(WinX + 115, WinY + 258 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 9;
							GetFontTextExtentPoint("Shaman", 7, &size);
							if (MouseAction(WinX + 115, WinY + 278 + SlotY, size.cx, size.cy))
								List.item[cnt].spec = 10;

							List.item[cnt].combobox = false;
						}
					}

					if (WinY + 73 + SlotY < 370 && WinY + 73 + SlotY > WinY + 48)
					{
						if (MouseAction(WinX + 89, WinY + 73 + SlotY, 110, 26))
						{
							if (!List.item[cnt].combobox)
								List.item[cnt].combobox = true;
						}
					}

					if (WinY + 75 + SlotY < 370 && WinY + 75 + SlotY > WinY + 48)
					{
						if (MouseAction(WinX + 222, WinY + 75 + SlotY, 52, 20))
							SendItemToServer(List.item[cnt]);
					}
					cnt2++;
				}
			}
		}
		//Botao Fechar
		if (MouseAction(WinX + 23, WinY + 325, 93, 23))
			Close();
	}
}

int Shop::GetSlot()
{
	int cnt2 = 0;
	for (int cnt = 0; cnt < 70; cnt++)
	{
		if (List.item[cnt].SubTag && List.item[cnt].SubTag == SubTag)
		{
			cnt2++;
		}
	}

	return cnt2;
}

int Shop::GetScroll()
{
	int SlotY = 0, result = 0, WinY = 70;
	do
	{
		SlotY = (GetSlot() * 100 + 100) - result * 10;
		result++;
	} while (WinY + 56 + SlotY > 370);

	return result;
}

void Shop::ButtonScroll(short Dist)
{
	int WinY = 70;
	int SlotY = (GetSlot() * 100 + 100) - Scroll * 10;
	if (fOpen)
	{
		if (SubTag)
		{
			if (Dist > 0)
			{
				if (Scroll)
					Scroll--;
			}
			else if (Dist < 0 && WinY + 56 + SlotY > 370)
			{
				Scroll++;
			}
		}
	}
}
