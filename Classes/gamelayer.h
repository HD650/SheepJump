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
	//����gamelayer���ɣ�gamelayer���ͷ��ڴ�ʱ����ߵ��������Զ��������ﵽ������յ�Ч��
	~GameLayer();

	//���㴥����ʼ����鲢�����Ź���ע��g_begin
	bool ontouchbegin(Touch* in, Event* who);
	//����������׷������
	void ontouchmove(Touch* in, Event* who);
	//����������׷�����һ�����֮꣬��ˢ�¾Ź���Ϊȫ0��Ȼ�����checkpass���ͼ���Ƿ��ĳֻ��ƥ��
	void ontouchend(Touch* in, Event* who);
	//��������������ĳͷ�������һ������3��
	void shutonenode();
	void refreshshut();
	//�Ź�����0������Ҳ��0
	void freshnode();
	//������г�������ľŹ���
	void checkpass();
	//���ؾŹ��񣬲����ͷż���������Ҫ��������������ŵ��˵���ѡȡ
	void disable();
	//��ʾ�Ź����ٴμ��������
	void enable();
	//����
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	
	//��βЧ��
	MotionStreak* streak;
	//�Ź���ͼƬ
	Sprite* g_node[3][3];
	//�û���������ľŹ���
	bool g_touched[3][3];
	//�������ĸ��ӣ��Լ���һ����ʱ�����Լ�ˢ�£���Ӧ����������һ��ˢ��
	bool g_nodeshuted[3][3];
	//�ײ������
	DrawNode* g_drawnode;
	//����Ź���������ͼ����������
	std::vector<Line> g_lines;
	//��һ���Ӵ��ĵ㣬������ת�����ķ���
	Vec2 lastnode;
	//�ж��Ƿ������Ź����������û�д������Ź�����κ�һ�㣬��ô������checkpass�������ͬʱ��ֹ����Ұָ��
	bool g_begin;
	
	//ħ����
	MagicBook* g_magicbook;

private:
	//���������¼���listener�����ͷ��������һ��Ҫ���Ƴ��������Ȼ֮���ħ����˫���ͷ�
	EventListenerTouchOneByOne* listener;
};
#endif