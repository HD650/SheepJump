#include "cocos2d.h"
#include "alldefine.h"
#include "AppDelegate.h"
#ifndef SheepH
#define SheepH


class Bride;
//那个奇怪的错误，大概说的是c++不支持int形，还有某某某后边缺少;
//都是因为include的顺序不对引起的，尽量在一个总文件中引入所有h文件，然后所有文件都引入那个总文件
//这样做错误一般会变成找不到多层之下的类，但其实连接的时候是能连接进来的，这时候为了过编译器，就先行声明一下，像这里一样


//注意！！sheep因为缩小了整整一倍，自己与其子类的getcontentsize已经是不正确的大小了，要使用getboundingbox！

using namespace cocos2d;
class Sheep :public Sprite
{
public:
	static Sheep* createsheep(float speed);
	virtual void initsheep(float speed);
	~Sheep();
	virtual void remove();
	//初始化羊的九宫格
	virtual void inittarget();
	//初始化九宫格图片
	virtual void initsprite();
	//隐藏九宫格
	void hidetarget();

	//每帧更新，控制羊横向行走和检查位置
	void update(float dt);
	//检查位置，出界加分撞墙扣血
	virtual void checkpos();
	bool isRightXout();
	bool isBarcontact(Rect bar);
	bool isDownYout();
	//羊前进控制
	virtual void move(float dt);
	//羊跳跃控制
	virtual void jump();
	//播放死亡动画，并杀死羊，死羊不计分，不扣血
	virtual void dead();
	//被鸟类抓走的动作，更新状态，移动函数变为benncatchedmove
	void beencatched(Bride* who);
	//被鸟抓走之后的移动函数
	void beencatchedmove();
	
	//动画控制，播放新动画前应该停止老动画
	virtual void walkanimate();
	virtual void jumpanimate();
	virtual void deadanimate();

	bool g_target[3][3];//九宫格，1=亮0=灭
	Sprite* g_targetnode[3][3];//九宫格图片
	float g_vx;//样的前进速度（单位像素每帧）
	bool g_ismove = true;//是否前进，用于控制，而且直接撞墙之后尸体不会卡在里边
	bool g_jumped = false;//羊是否跳过，一只羊只允许跳一次
	bool g_isdead = false;//杨是否已经撞墙死亡，如是，尸体出x界不加分
	bool g_isctached = false;//羊是否正在被抓走，关系到是否会被雷炸，被抓走的的羊不会被雷炸
	bool g_cancatch = true;//关系到风吹之后，鸟的目标选择，因为目标是遍历的，所以要这一项控制
	Bride* g_bride=nullptr;//抓到本羊的鸟，用于被抓走后和鸟同步位置

	Animate* walk_animate;
	Animate* dead_animate;
};

#endif