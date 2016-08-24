#include "cocos2d.h"
#include "AppDelegate.h"
#include"sheep.h"
#ifndef monsterH
#define monsterH


using namespace cocos2d;
class Monster :public Sheep
{
public:
	static Monster* createmonster(float speed);
	void initmonster(float speed);
	virtual void remove();
	void dead();

	virtual void checkpos();

	void walkanimate();
	void jumpanimate();
	void deadanimate();
};


#endif