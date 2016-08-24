#include "cocos2d.h"
#include "gamelayer.h"
#include "sheeplayer.h"
#include "AppDelegate.h"
#ifndef GameSceneH
#define GameSceneH


using namespace cocos2d;
class GameScene :public Scene
{
public:
	//scene的创建函数中应该自动把自己加进单例AppDelegate里边，因为初始化时可能会访问到野指针
	static GameScene* creategamescene();
	void initgamescene();
	~GameScene();
	
	//这里的menu管理的都是sheeplayer上边显示的menu，menu本体在scene内，而layer内只管理那个暂停按钮，也是用完销毁的
	void initmenu();
	void destorymenu();
	void showmenu();
	void hidemenu();
	void tomainmenu();
	bool touchtomain(Touch* in,Event* what);
	void restartgame();
	void tohighscores();
	void toconfig();
	
	//更改血量，同时更新计分版
	virtual void changehp(bool);
	//更改分数，同时更新计分版
	virtual void changescores(bool);
	//游戏开始现在的加羊方式为直接启动sheeplayer的update即可，addmanager会掌管一切时序
	virtual void gamebegin();
	//游戏结束
	void gameover();
	
	void topause();
	void toresume();

	int g_hp;
	int g_scores;
	bool isgameovered;

	GameLayer* g_gamelayer;
	SheepLayer* g_sheeplayer;
	Menu* g_menu;

	EventListenerTouchOneByOne* m_listener;
};

#endif