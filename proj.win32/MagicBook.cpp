#include "MagicBook.h"

MagicBook* MagicBook::createmagicbook()
{
	auto temp = new MagicBook;
	temp->autorelease();
	temp->initmagicbook();
	return temp;
}

void MagicBook::initmagicbook()
{
	Sprite::init();
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 20 - this->getContentSize().width, 150));

	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		g_wind[i][ii] = false;
		g_lightning[i][ii] = false;
		g_changesheep[i][ii] = false;
		g_orderbrid[i][ii] = false;
	}
	g_wind[2][0] = true;
	g_wind[2][1] = true;
	g_wind[2][2] = true;

	g_lightning[0][1] = true;
	g_lightning[1][0] = true;
	g_lightning[1][1] = true;
	g_lightning[1][2] = true;
	g_lightning[2][1] = true;

	g_changesheep[0][0] = true;
	g_changesheep[0][1] = true;
	g_changesheep[0][2] = true;
	g_changesheep[1][0] = true;
	g_changesheep[2][0] = true;
	g_changesheep[1][2] = true;
	g_changesheep[2][2] = true;
	g_changesheep[2][1] = true;

	g_orderbrid[0][0] = true;
	g_orderbrid[0][1] = true;
	g_orderbrid[0][2] = true;
	g_orderbrid[1][0] = true;
	g_orderbrid[1][1] = true;
	g_orderbrid[1][2] = true;
	g_orderbrid[2][0] = true;
	g_orderbrid[2][1] = true;
	g_orderbrid[2][2] = true;


	g_ismagic = true;
	g_islightning = true;
	g_iswind = true;
	g_ischangesheep = true;
	g_isorderbride = true;
}

MagicBook::~MagicBook()
{
	this->g_ismagic = false;
}

bool MagicBook::magic(bool in[3][3])
{
	if (!g_ismagic)
		return false;
	bool iswind = true;
	bool isligthning = true;
	bool ischangesheep = true;
	bool isorederbrid = true;
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		if (in[i][ii] != g_wind[i][ii])
			iswind = false;
	}
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		if (in[i][ii] != g_lightning[i][ii])
			isligthning = false;
	}
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		if (in[i][ii] != g_changesheep[i][ii])
			ischangesheep = false;
	}
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		if (in[i][ii] != g_orderbrid[i][ii])
			isorederbrid = false;
	}

	if (iswind&&g_iswind)
	{
		this->wind();
		return true;
	}
	if (isligthning&&g_islightning)
	{
		this->lightning();
		return true;
	}
	if (ischangesheep&&g_ischangesheep)
	{
		this->changesheep();
		return true;
	}
	if (isorederbrid&&g_isorderbride)
	{
		this->orderbrid();
		return true;
	}

	return false;
}

void MagicBook::wind()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto sheeps = one->g_gamescene->g_sheeplayer->g_sheeps;
	auto monster = one->g_gamescene->g_sheeplayer->g_monster;
	auto wolf = one->g_gamescene->g_sheeplayer->g_wolves;
	auto bride = one->g_gamescene->g_sheeplayer->g_brides;

	one->g_gamescene->getPhysicsWorld()->setGravity(WorldWindGravity);
	this->scheduleOnce([=](float in)
	{
		one->g_gamescene->getPhysicsWorld()->setGravity(WorldGravity);
	}
	, 1.2, "wind");

	one->g_gamescene->g_gamelayer->shutonenode();
	this->windshack();
}

void MagicBook::windshack()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto windpart = TextureCache::getInstance()->addImage("wind_particle.png");
	auto wind = ParticleRain::create();
	wind->setTexture(windpart);
	wind->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	wind->setGravity(Vec2(0, -98));
	wind->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 0));
	wind->setScaleY(-1);
	wind->setLife(3);
	wind->setDuration(3);

	one->g_gamescene->g_sheeplayer->addChild(wind, GameObjectEffEct);

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("wind.mp3");
	}
}

void MagicBook::lightning()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto sheeps = one->g_gamescene->g_sheeplayer->g_sheeps;
	auto monster = one->g_gamescene->g_sheeplayer->g_monster;
	auto wolf = one->g_gamescene->g_sheeplayer->g_wolves;
	auto all = one->g_gamescene->g_sheeplayer->g_allcreater;

	one->g_gamescene->g_gamelayer->shutonenode();

	if (monster->size() != 0)
	{
		for (auto now = monster->begin(); now != monster->end(); now++)
		{
			if (!(*now)->g_isdead&&!(*now)->g_isctached)
			{
				(*now)->dead();
				lightningshack((*now)->getPosition().x);
				return;
			}
		}

	}
	if (wolf->size() != 0)
	{
		for (auto now = wolf->begin(); now != wolf->end(); now++)
		{
			if (!(*now)->g_isdead&&!(*now)->g_isctached)
			{
				(*now)->dead();
				lightningshack((*now)->getPosition().x);
				return;
			}
		}

	}
	if (sheeps->size() != 0)
	{
		for (auto now = sheeps->begin(); now != sheeps->end(); now++)
		{
			if (!(*now)->g_isdead&&!(*now)->g_isctached)
			{
				(*now)->dead();
				lightningshack((*now)->getPosition().x);
				return;
			}
		}

	}
}

void MagicBook::lightningshack(float x)
{
	auto one = (AppDelegate*)Application::getInstance();
	one->g_gamescene->g_sheeplayer->runAction(Sequence::create(MoveBy::create(0.05, Vec2(-15, -15)), MoveBy::create(0.05, Vec2(30, 15)),
		MoveBy::create(0.05, Vec2(-30, 0)), MoveBy::create(0.05, Vec2(15, 0)), nullptr));

	auto light = Sprite::create("lighting.png");
	light->setScale(0.2);
	light->setAnchorPoint(Vec2(0, 0));
	light->runAction(Sequence::create(MoveBy::create(0.5, Vec2(0, -(Director::getInstance()->getVisibleSize().height + 100))),
		FadeOut::create(0.3), nullptr));
	light->setPosition(Vec2(x, Director::getInstance()->getVisibleSize().height));
	auto width = light->getContentSize().width;
	this->scheduleOnce([=](float in){light->removeFromParent(); }, 0.2, "removelight");

	one->g_gamescene->g_sheeplayer->addChild(light, GameObjectEffEct);


	auto starpart = TextureCache::getInstance()->addImage("light_particle.png");
	auto star = ParticleMeteor::create();
	star->setTexture(starpart);
	star->setEmitterMode(ParticleSystem::Mode::RADIUS);
	star->setPosition(Vec2(x, Director::getInstance()->getVisibleSize().height));
	star->runAction(MoveBy::create(0.2, Vec2(width, -(Director::getInstance()->getVisibleSize().height + 100))));
	this->scheduleOnce([=](float in){star->removeFromParent(); }, 5, "removestar");

	one->g_gamescene->g_sheeplayer->addChild(star, GameObjectEffEct);

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("lighting.mp3");
	}
}

void MagicBook::changesheep()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto sheeps = one->g_gamescene->g_sheeplayer->g_sheeps;
	auto monster = one->g_gamescene->g_sheeplayer->g_monster;
	auto wolf = one->g_gamescene->g_sheeplayer->g_wolves;
	auto all = one->g_gamescene->g_sheeplayer->g_allcreater;

	for (auto now = wolf->begin(); now != wolf->end(); now++)
	{
		if (!(*now)->g_isdead)
		{
			float tempv = (*now)->g_vx;
			float tempx = (*now)->getPosition().x;
			float tempy = (*now)->getPosition().y;
			bool isgravity = (*now)->getPhysicsBody()->isGravityEnabled();
			(*now)->hidetarget();
			(*now)->remove();

			auto temp = Sheep::createsheep(tempv);

			temp->retain();
			temp->setPosition(tempx, tempy);
			temp->getPhysicsBody()->setGravityEnable(isgravity);
			sheeps->pushBack(temp);
			all->pushBack(temp);
			one->g_gamescene->g_sheeplayer->addChild(temp, 1);

			this->changesheepshack(Vec2(tempx, tempy));
			return;
		}
	}
}

void MagicBook::changesheepshack(Vec2 pos)
{
	auto one = (AppDelegate*)Application::getInstance();
	auto smokepart = TextureCache::getInstance()->addImage("smoke_particle.png");
	auto smoke = ParticleGalaxy::create();
	smoke->setTexture(smokepart);
	smoke->setEndSize(0.5);
	smoke->setScale(1.5);
	smoke->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	smoke->setGravity(Vec2(0, 98));
	smoke->setPosition(pos);
	smoke->setLife(2);
	smoke->setDuration(1);
	one->g_gamescene->g_sheeplayer->addChild(smoke, GameObjectEffEct);

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("change.mp3");
	}
}

void MagicBook::orderbrid()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto brid = one->g_gamescene->g_sheeplayer->g_brides;
	for (auto i = brid->begin(); i != brid->end(); i++)
	{
		(*i)->beginpredate();
		this->orderbridshack((*i)->getPosition());
	}
}

void MagicBook::orderbridshack(Vec2 pos)
{
	/*auto one = (AppDelegate*)Application::getInstance();
	auto smokepart = TextureCache::getInstance()->addImage("smoke_particle.png");
	auto smoke = ParticleSun::create();
	smoke->setTexture(smokepart);
	//smoke->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	//smoke->setGravity(Vec2(0, 98));
	smoke->setPosition(pos);
	smoke->setLife(2);
	smoke->setDuration(1);
	one->g_gamescene->g_sheeplayer->addChild(smoke, GameObjectEffEct);*/
	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("birde_fly.mp3");
	}
}