#include "cocos2d.h"
#include "sheep.h"
#include "monster.h"
#include "wolf.h"
#include "bride.h"
#include "alldefine.h"
#include "AppDelegate.h"
#ifndef SheepLayerH
#define SheepLayerH


using namespace cocos2d;

class SheepLayer;

class AddManager
{
public:
	AddManager(SheepLayer* in);
	float howfast(float hardness);//根据难度产生一个速度并返回
	bool shouldadd(float dt,float hardness);//用时间和shouldadd判断是否应该添加一只羊
	virtual void refreshwait();//根据难度更新shouldwait时间间隔
	virtual bool wavechange(float i);//管理wavechange动画，当wave改变时，shouldadd置为false，动画完毕之后，置为true
	
	float g_delytime;//自上一只羊产生之后的延迟时间
	float g_shouldwait;//羊产生的应该间隔，当delytime大于这个之后就产生一只羊
	bool g_shouldadd;//是否要产生羊，当时间满足时，如果在播放wavechange动画，那么仍不该产生羊，这个就是控制它的
	float g_hardness;//目前难度

private:
	SheepLayer* g_sheeplayer;
};

class SheepLayer :public Layer
{
public:
	static SheepLayer* createsheeplayer();
	void initsheeplayer();
	~SheepLayer();
	//加入地面，土地位置很可能是分辨率改变后的难题
	void addland();
	void barshack();
	void barbreak();
	//游戏结束，加载结束文字，隐藏计分版等
	virtual void gameover();
	void gameoveraddnum();
	void rainsheep();
	//随机加入一只随机种类羊，注意只加入一只
	void add();
	void addsheep();
	void addmonster();
	void addwolf();
	void addbride();
	//暂停，再启动所有生物
	void pauseallcreators();
	void resumeallcreators();
	
	//菜单相关，使用之后直接销毁，防止监听器bug
	void initbutton();
	void showmenu();
	//游戏结束之后的处理
	void hidescene();
	//更新计分版，只会从gamescene调用，计分版的内容也是在gamescene中的
	void freshlable();
	//加羊回调，全速回调，但是内部调用Addmanager的shouldadd判断是否要加
	void update(float dt);

	//游戏目前难度，每出现一只羊加一
	float g_hardness;

	Vector<Sheep*>* g_sheeps;
	Vector<Sheep*>* g_monster;
	Vector<Sheep*>* g_wolves;
	Vector<Bride*>* g_brides;
	Vector<Sheep*>* g_allcreater;//除了鸟之外的所有生物
	//计分版
	Label* g_gamelabel;
	//wave计数版
	Label* g_wavelabel;
	//死亡后计分版
	Label* g_gameover;
	//墙
	Sprite* g_bar;
	Sprite* g_land;
	//菜单按钮
	Menu* g_menubutton;

	AddManager* g_adm;
};




#endif