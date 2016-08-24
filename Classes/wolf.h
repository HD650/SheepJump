#include "cocos2d.h"
#include "AppDelegate.h"
#include"sheep.h"
#ifndef wolfH
#define wolfH


using namespace cocos2d;
class Wolf :public Sheep
{
public:
	static Wolf* createwolf(float speed);
	void initwolf(float speed);
	virtual void initsprite();
	virtual void remove();

	virtual void checkpos();

	void walkanimate();
	void jumpanimate();
	void deadanimate();
};


#endif