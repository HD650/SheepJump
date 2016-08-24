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
	//scene�Ĵ���������Ӧ���Զ����Լ��ӽ�����AppDelegate��ߣ���Ϊ��ʼ��ʱ���ܻ���ʵ�Ұָ��
	static GameScene* creategamescene();
	void initgamescene();
	~GameScene();
	
	//�����menu����Ķ���sheeplayer�ϱ���ʾ��menu��menu������scene�ڣ���layer��ֻ�����Ǹ���ͣ��ť��Ҳ���������ٵ�
	void initmenu();
	void destorymenu();
	void showmenu();
	void hidemenu();
	void tomainmenu();
	bool touchtomain(Touch* in,Event* what);
	void restartgame();
	void tohighscores();
	void toconfig();
	
	//����Ѫ����ͬʱ���¼Ʒְ�
	virtual void changehp(bool);
	//���ķ�����ͬʱ���¼Ʒְ�
	virtual void changescores(bool);
	//��Ϸ��ʼ���ڵļ���ʽΪֱ������sheeplayer��update���ɣ�addmanager���ƹ�һ��ʱ��
	virtual void gamebegin();
	//��Ϸ����
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