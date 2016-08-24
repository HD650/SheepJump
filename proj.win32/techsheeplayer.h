#include "sheeplayer.h"
#include "AppDelegate.h"

#ifndef techsheeplayerH
#define techsheeplayerH

using namespace std;

enum techstep
{
	Begin,
	HDU_Tech,
	Sheep_Jump,
	Wolf_Turn,
	Wolf_Kill,
	Monster_Kill,
	Bird_Catch,
	Wind,
	Final,
};

class TechWolf :public Wolf
{
public:
	static TechWolf* createtechwolf(float);
	virtual void remove()override;
	virtual void checkpos()override;
};
class TechMonster :public Monster
{
public:
	static TechMonster* createtechmonster(float);
	virtual void remove()override;
	virtual void checkpos()override;
};
class TechBride :public Bride
{
public:
	static TechBride* createtechbride();
	virtual void remove()override;
};


class TechSheepLayer :public SheepLayer
{
public:
	static TechSheepLayer* createtechsheeplayer();
	void inittechsheeplayer();
	void inittextdata();

	void addsheep();
	void addwolf();
	void addbird();
	void addmonster();
	//控制状态变化，如果玩家完成了要求的任务，返回true，反之返回false
	bool isquestfinish(Sheep* in = nullptr);
	//内部调用isquestfinish判断任务是否完成，改变状态机
	void nextquest(Sheep* in = nullptr);
	//根据状态机真正部署关卡
	void putquest();
	//展示文字版，隐藏九宫格并加载文字版的监听器
	void showlabel();
	//与showlabel相反
	void hidelabel();
	//暂停场景展示文字，仅仅负责刷新文本并调用showlabel
	void showtext(int index = 0);
	//刷新文字，因为原逻辑在切换段落时有一句的延迟
	void refreshtext();
	void gameover()override;
	//退出场景函数，主要是防止文字版监听器没释放
	void quit();

	//分数和血量仅仅是检测任务的
	int scores;
	int hp;
	//状态机，目前的教学进度
	techstep step;
	//用于断掉教学链条，不然推出场景之后，教学还在后台继续循环，夺取所有点击使得游戏不能继续进行，使用这个从中切断
	bool g_isquit = false;
	//文本台词
	vector<string> data[10];
	
	Sprite* g_lableback;//文本背景
	Label* g_lable;//文本容器

	bool buttondown(Touch* loc = nullptr, Event* what = nullptr);//用户按键之后调用，更换文本，控制换段
	
	EventListenerTouchOneByOne* p_listener;
};

#endif
