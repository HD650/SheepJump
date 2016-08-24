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
	//���������ͷ���true����Ȼfalse��gamelayer�������ѡ���Ƿ񲥷�������󶯻�
	bool magic(bool in[3][3]);
	//���磬ֻ��½��������Ч
	void wind();
	void windshack();
	//���磬ɱ�������в�Ĺ�������һ��node3��
	void lightning();
	void lightningshack(float y);
	//����������ӡ�д��޸�
	void changesheep();
	void changesheepshack(Vec2 pos);
	//�������ѶȽϴ�Ҫ�������и���
	void orderbrid();
	void orderbridshack(Vec2 pos);

	//�Ƿ�����ͷŷ�ӡ�����ڽ�ѧ�ؿ���
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