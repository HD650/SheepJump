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
	//����״̬�仯�������������Ҫ������񣬷���true����֮����false
	bool isquestfinish(Sheep* in = nullptr);
	//�ڲ�����isquestfinish�ж������Ƿ���ɣ��ı�״̬��
	void nextquest(Sheep* in = nullptr);
	//����״̬����������ؿ�
	void putquest();
	//չʾ���ְ棬���ؾŹ��񲢼������ְ�ļ�����
	void showlabel();
	//��showlabel�෴
	void hidelabel();
	//��ͣ����չʾ���֣���������ˢ���ı�������showlabel
	void showtext(int index = 0);
	//ˢ�����֣���Ϊԭ�߼����л�����ʱ��һ����ӳ�
	void refreshtext();
	void gameover()override;
	//�˳�������������Ҫ�Ƿ�ֹ���ְ������û�ͷ�
	void quit();

	//������Ѫ�������Ǽ�������
	int scores;
	int hp;
	//״̬����Ŀǰ�Ľ�ѧ����
	techstep step;
	//���ڶϵ���ѧ��������Ȼ�Ƴ�����֮�󣬽�ѧ���ں�̨����ѭ������ȡ���е��ʹ����Ϸ���ܼ������У�ʹ����������ж�
	bool g_isquit = false;
	//�ı�̨��
	vector<string> data[10];
	
	Sprite* g_lableback;//�ı�����
	Label* g_lable;//�ı�����

	bool buttondown(Touch* loc = nullptr, Event* what = nullptr);//�û�����֮����ã������ı������ƻ���
	
	EventListenerTouchOneByOne* p_listener;
};

#endif
