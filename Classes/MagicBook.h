#include "cocos2d.h"
#include "AppDelegate.h"
#ifndef MagicBookH
#define MagicBookH


using namespace cocos2d;
class MagicBook :public Sprite
{
public:
	static MagicBook* createmagicbook();
	void initmagicbook();
	~MagicBook();
	//触发法术就返回true，不然false，gamelayer根据这个选择是否播放输入错误动画
	bool magic(bool in[3][3]);
	//吹风，只对陆地物体有效
	void wind();
	void windshack();
	//闪电，杀死最大威胁的怪物，会封锁一个node3秒
	void lightning();
	void lightningshack(float y);
	//变羊术，法印有待修改
	void changesheep();
	void changesheepshack(Vec2 pos);
	//命令鸟，难度较大，要划掉所有格子
	void orderbrid();
	void orderbridshack(Vec2 pos);

	//是否可以释放法印，用于教学关控制
	bool g_ismagic = true;
	bool g_islightning = true;
	bool g_iswind = true;
	bool g_ischangesheep = true;
	bool g_isorderbride = true;

	bool g_wind[3][3];
	bool g_lightning[3][3];
	bool g_changesheep[3][3];
	bool g_orderbrid[3][3];
};

#endif