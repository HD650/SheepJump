#include "cocos2d.h"
#include "sheep.h"
#include "AppDelegate.h"

#ifndef mainmenuH
#define mainmenuH
using namespace cocos2d;
class MainMenu :public Scene
{
public:
	static MainMenu* createmainmenu();
	void initmainmenu();
	
	void sheeprun();

	void startnewgame();
	void startteacher();
	void seehightscores();
	void startconfigure();
};

#endif