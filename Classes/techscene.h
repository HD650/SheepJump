#include "cocos2d.h"
#include "gamescene.h"
#include"techsheeplayer.h"

#ifndef TechSceneH
#define TechSceneH

class TechScene :public GameScene
{
public:
	static TechScene* createtechscene();
	~TechScene();
	void inittechscene();

	//更改血量，同时更新计分版，同时通知教学层，任务可能有更新
	virtual void changehp(bool);
	//更改分数，同时更新计分版，同时通知教学层，任务可能有更新
	virtual void changescores(bool);
	virtual void gamebegin()override;
	TechSheepLayer* g_techsheeplayer;
};

#endif