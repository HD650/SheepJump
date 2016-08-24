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

	//����Ѫ����ͬʱ���¼Ʒְ棬ͬʱ֪ͨ��ѧ�㣬��������и���
	virtual void changehp(bool);
	//���ķ�����ͬʱ���¼Ʒְ棬ͬʱ֪ͨ��ѧ�㣬��������и���
	virtual void changescores(bool);
	virtual void gamebegin()override;
	TechSheepLayer* g_techsheeplayer;
};

#endif