#include "cocos2d.h"
#include "alldefine.h"

#ifndef configsceneH
#define configsceneH
using namespace cocos2d;

class ConfigScene :public Scene
{
public:
	CREATE_FUNC(ConfigScene);
	virtual bool init()override;

	void BGMon();
	void BGMoff();
	void backtomain();
};

#endif