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
	float howfast(float hardness);//�����ѶȲ���һ���ٶȲ�����
	bool shouldadd(float dt,float hardness);//��ʱ���shouldadd�ж��Ƿ�Ӧ�����һֻ��
	virtual void refreshwait();//�����Ѷȸ���shouldwaitʱ����
	virtual bool wavechange(float i);//����wavechange��������wave�ı�ʱ��shouldadd��Ϊfalse���������֮����Ϊtrue
	
	float g_delytime;//����һֻ�����֮����ӳ�ʱ��
	float g_shouldwait;//�������Ӧ�ü������delytime�������֮��Ͳ���һֻ��
	bool g_shouldadd;//�Ƿ�Ҫ�����򣬵�ʱ������ʱ������ڲ���wavechange��������ô�Բ��ò�����������ǿ�������
	float g_hardness;//Ŀǰ�Ѷ�

private:
	SheepLayer* g_sheeplayer;
};

class SheepLayer :public Layer
{
public:
	static SheepLayer* createsheeplayer();
	void initsheeplayer();
	~SheepLayer();
	//������棬����λ�úܿ����Ƿֱ��ʸı�������
	void addland();
	void barshack();
	void barbreak();
	//��Ϸ���������ؽ������֣����ؼƷְ��
	virtual void gameover();
	void gameoveraddnum();
	void rainsheep();
	//�������һֻ���������ע��ֻ����һֻ
	void add();
	void addsheep();
	void addmonster();
	void addwolf();
	void addbride();
	//��ͣ����������������
	void pauseallcreators();
	void resumeallcreators();
	
	//�˵���أ�ʹ��֮��ֱ�����٣���ֹ������bug
	void initbutton();
	void showmenu();
	//��Ϸ����֮��Ĵ���
	void hidescene();
	//���¼Ʒְ棬ֻ���gamescene���ã��Ʒְ������Ҳ����gamescene�е�
	void freshlable();
	//����ص���ȫ�ٻص��������ڲ�����Addmanager��shouldadd�ж��Ƿ�Ҫ��
	void update(float dt);

	//��ϷĿǰ�Ѷȣ�ÿ����һֻ���һ
	float g_hardness;

	Vector<Sheep*>* g_sheeps;
	Vector<Sheep*>* g_monster;
	Vector<Sheep*>* g_wolves;
	Vector<Bride*>* g_brides;
	Vector<Sheep*>* g_allcreater;//������֮�����������
	//�Ʒְ�
	Label* g_gamelabel;
	//wave������
	Label* g_wavelabel;
	//������Ʒְ�
	Label* g_gameover;
	//ǽ
	Sprite* g_bar;
	Sprite* g_land;
	//�˵���ť
	Menu* g_menubutton;

	AddManager* g_adm;
};




#endif