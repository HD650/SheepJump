#include "cocos2d.h"
#include "MagicBook.h"
#include "CCMotionStreak.h"
#include "AppDelegate.h"
#ifndef LayerH
#define LayerH


using namespace cocos2d;

struct Line
{
	Vec2 begin = Vec2(0, 0);
	Vec2 end = Vec2(0, 0);
};

class GameLayer:public Layer
{
public:
	static GameLayer* creategamelayer();
	void initgamelayer();
	//析构gamelayer不干，gamelayer在释放内存时，里边的两个层自动析构，达到场景清空的效果
	~GameLayer();

	//单点触摸开始，检查并点亮九宫格，注意g_begin
	bool ontouchbegin(Touch* in, Event* who);
	//触摸继续，追踪坐标
	void ontouchmove(Touch* in, Event* who);
	//触摸结束，追踪最后一次坐标，之后刷新九宫格为全0，然后调用checkpass检查图案是否和某只羊匹配
	void ontouchend(Touch* in, Event* who);
	//闪电和上升气流的惩罚，封锁一个格子3秒
	void shutonenode();
	void refreshshut();
	//九宫格清0，动画也清0
	void freshnode();
	//检查所有场景内羊的九宫格
	void checkpass();
	//隐藏九宫格，并且释放监听器（重要），这样不会干扰到菜单的选取
	void disable();
	//显示九宫格，再次加入监听器
	void enable();
	//画线
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	
	//拖尾效果
	MotionStreak* streak;
	//九宫格图片
	Sprite* g_node[3][3];
	//用户本次输入的九宫格
	bool g_touched[3][3];
	//被封锁的格子，自己有一个计时器，自己刷新，不应和正常格子一起刷新
	bool g_nodeshuted[3][3];
	//底层绘制类
	DrawNode* g_drawnode;
	//管理九宫格连线作图的所有坐标
	std::vector<Line> g_lines;
	//上一个接触的点，用于旋转动画的方向
	Vec2 lastnode;
	//判断是否触摸到九宫格，如果根本没有触摸到九宫格的任何一点，那么不进行checkpass提高性能同时防止访问野指针
	bool g_begin;
	
	//魔法书
	MagicBook* g_magicbook;

private:
	//监听触摸事件的listener，在释放这个层是一定要先移除这个，不然之后的魔法会双倍释放
	EventListenerTouchOneByOne* listener;
};
#endif