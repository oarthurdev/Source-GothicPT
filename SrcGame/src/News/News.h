#pragma once

class rsPLAYINFO;

class News
{
private:
	rsPLAYINFO *player;
public:
	News(rsPLAYINFO *player) : player(player){}
	void welcome(); 
	void title(); 
};
