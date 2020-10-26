#pragma once

class rsPLAYINFO;

class News
{
private:
	rsPLAYINFO *player;
public:
	News(rsPLAYINFO *player) : player(player){}
	void welcome(); // Mensagem de boas vindas
	void title(); // Trocar Title da janela do game
};