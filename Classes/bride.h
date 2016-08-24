#include "cocos2d.h"
#include "AppDelegate.h"
#include "alldefine.h"

#ifndef brideH
#define brideH
enum GotoWhere
{
	Idel,
	Target,
	Away,
};

using namespace cocos2d;
class Bride :public Sheep//�񾭹�������޸ģ��������Ѿ����ܴ������ˣ���
{
public:
	static Bride* createbride();
	void initbride();
	virtual void remove();
	bool cancatch();
	void catchsheep();
	void update(float dt);
	void beginpredate();
	void idel();
	void flytosheep(float dt);
	void flyaway();
	void checkpos();

	void flyanimate();
	void flyawayanimate();

	GotoWhere gotowhere;
	Sheep* g_target;
	bool g_iscatch = false;
};

#endif
