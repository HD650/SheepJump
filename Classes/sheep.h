#include "cocos2d.h"
#include "alldefine.h"
#include "AppDelegate.h"
#ifndef SheepH
#define SheepH


class Bride;
//�Ǹ���ֵĴ��󣬴��˵����c++��֧��int�Σ�����ĳĳĳ���ȱ��;
//������Ϊinclude��˳�򲻶�����ģ�������һ�����ļ�����������h�ļ���Ȼ�������ļ��������Ǹ����ļ�
//����������һ������Ҳ������֮�µ��࣬����ʵ���ӵ�ʱ���������ӽ����ģ���ʱ��Ϊ�˹�������������������һ�£�������һ��


//ע�⣡��sheep��Ϊ��С������һ�����Լ����������getcontentsize�Ѿ��ǲ���ȷ�Ĵ�С�ˣ�Ҫʹ��getboundingbox��

using namespace cocos2d;
class Sheep :public Sprite
{
public:
	static Sheep* createsheep(float speed);
	virtual void initsheep(float speed);
	~Sheep();
	virtual void remove();
	//��ʼ����ľŹ���
	virtual void inittarget();
	//��ʼ���Ź���ͼƬ
	virtual void initsprite();
	//���ؾŹ���
	void hidetarget();

	//ÿ֡���£�������������ߺͼ��λ��
	void update(float dt);
	//���λ�ã�����ӷ�ײǽ��Ѫ
	virtual void checkpos();
	bool isRightXout();
	bool isBarcontact(Rect bar);
	bool isDownYout();
	//��ǰ������
	virtual void move(float dt);
	//����Ծ����
	virtual void jump();
	//����������������ɱ�������򲻼Ʒ֣�����Ѫ
	virtual void dead();
	//������ץ�ߵĶ���������״̬���ƶ�������Ϊbenncatchedmove
	void beencatched(Bride* who);
	//����ץ��֮����ƶ�����
	void beencatchedmove();
	
	//�������ƣ������¶���ǰӦ��ֹͣ�϶���
	virtual void walkanimate();
	virtual void jumpanimate();
	virtual void deadanimate();

	bool g_target[3][3];//�Ź���1=��0=��
	Sprite* g_targetnode[3][3];//�Ź���ͼƬ
	float g_vx;//����ǰ���ٶȣ���λ����ÿ֡��
	bool g_ismove = true;//�Ƿ�ǰ�������ڿ��ƣ�����ֱ��ײǽ֮��ʬ�岻�Ῠ�����
	bool g_jumped = false;//���Ƿ�������һֻ��ֻ������һ��
	bool g_isdead = false;//���Ƿ��Ѿ�ײǽ���������ǣ�ʬ���x�粻�ӷ�
	bool g_isctached = false;//���Ƿ����ڱ�ץ�ߣ���ϵ���Ƿ�ᱻ��ը����ץ�ߵĵ��򲻻ᱻ��ը
	bool g_cancatch = true;//��ϵ���紵֮�����Ŀ��ѡ����ΪĿ���Ǳ����ģ�����Ҫ��һ�����
	Bride* g_bride=nullptr;//ץ������������ڱ�ץ�ߺ����ͬ��λ��

	Animate* walk_animate;
	Animate* dead_animate;
};

#endif