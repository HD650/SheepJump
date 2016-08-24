#include "sheeplayer.h"

//zÖáÎ»ÖÃlandµÈ1£¬sheepµÈ10£¬birdµÈ11£¬labelµÈ999

SheepLayer* SheepLayer::createsheeplayer()
{
	auto temp = new SheepLayer; 
	temp->autorelease();
	temp->initsheeplayer();
	return temp;
}

void SheepLayer::initsheeplayer()
{
	Layer::init();
	auto back = Sprite::create("gameback.png");
	back->setAnchorPoint(Vec2(0, 0));
	back->setPosition(Vec2(0, 0));
	this->addChild(back, BackGround);

	g_sheeps = new Vector<Sheep*>();
	g_wolves = new Vector<Sheep*>();
	g_monster = new Vector<Sheep*>();
	g_brides = new Vector<Bride*>();
	g_allcreater = new Vector<Sheep*>();
	
	g_hardness = 1;
	
	this->setAnchorPoint(Vec2(0, 0));
	this->addland();
	
	auto font = TTFConfig(EnglishFont, 30);
	auto lable = Label::createWithTTF(font, String::createWithFormat("Hp:%d,Scores:%d", 5, 0)->getCString());
	//auto lable = LabelTTF::create(String::createWithFormat("Hp:%d,Scores:%d", 5, 0)->getCString(), EnglishFont, 30);
	lable->setColor(Color3B(0, 0, 0));
	lable->setAnchorPoint(Vec2(0, 0));
	lable->setPosition(Vec2(30, Director::getInstance()->getVisibleSize().height - 50));
	g_gamelabel = lable;
	this->addChild(lable,GameUI);

	auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
	//auto wlable = Label::create(valuemap.at("SheepLayer_Begin").asString(), ChineseFont, 35);
	auto chinesefont = TTFConfig(ChineseFont, 35);
	auto wlable = Label::createWithTTF(chinesefont, valuemap.at("SheepLayer_Begin").asString());
	wlable->setColor(Color3B(0, 0, 0));
	wlable->setAnchorPoint(Vec2(0.5, 0.5));
	wlable->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 
		Director::getInstance()->getVisibleSize().height / 3 * 2.2));
	g_wavelabel = wlable;
	this->addChild(wlable,GameUI);
	wlable->runAction(Sequence::create(FadeIn::create(1), DelayTime::create(1), FadeOut::create(1), nullptr));

	initbutton();

	g_adm = new AddManager(this);
}

SheepLayer::~SheepLayer()
{
	
}

void SheepLayer::addland()
{
	auto land = Sprite::create("land.png");
	this->g_land = land;
	land->setAnchorPoint(Vec2(0, 0));
	auto body = PhysicsBody::createBox(Size(9999, land->getContentSize().height));//land³¤ÓÚÆÁÄ»

	body->setDynamic(false);
	body->setGravityEnable(false);
	body->setCategoryBitmask(Collision_Land);
	body->setCollisionBitmask(Collision_Land);
	land->setPhysicsBody(body);
	land->setAnchorPoint(Vec2(0, 0));
	

	auto bar = Sprite::create("bar.png");
	auto barbody = PhysicsBody::createBox(bar->getContentSize());
	barbody->setDynamic(false);
	barbody->setGravityEnable(false);
	barbody->setCategoryBitmask(Collision_Bar);
	barbody->setCollisionBitmask(Collision_Bar);
	bar->setPhysicsBody(barbody);
	bar->setAnchorPoint(Vec2(0, 0));
	g_bar = bar;

	land->setPosition(Vec2(land->getContentSize().width / 2, 
		Director::getInstance()->getVisibleSize().height / 2));//land×ó±ßÍ»³öÆÁÄ»·ÀÖ¹Ñò´íÎóÂäÏÂ
	bar->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 4 * 3,
		Director::getInstance()->getVisibleSize().height / 2 + bar->getContentSize().height / 2 + land->getContentSize().height / 2));

	this->addChild(land,Land);
	this->addChild(bar,Land);
}

void SheepLayer::barshack()
{
	this->g_bar->runAction(Sequence::create(EaseElasticOut::create(ScaleBy::create(0.3, 1.2, 1.1)), DelayTime::create(0.7),
		EaseExponentialIn::create(ScaleTo::create(0.3, 1, 1)), nullptr));

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("beat.mp3");
	}
}

void SheepLayer::barbreak()
{
	auto smokepart = TextureCache::getInstance()->addImage("smoke_particle.png");
	auto smoke = ParticleFire::create();
	smoke->setTexture(smokepart);
	smoke->setEmissionRate(50);
	smoke->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 0));
	smoke->setScaleX(3);
	this->addChild(smoke, GameObjectEffEct);
}

void SheepLayer::gameover()
{
	auto one = (AppDelegate*)Application::getInstance();
	this->barbreak();
	this->hidescene();

	int heighscore = UserDefault::getInstance()->getIntegerForKey("heighscore");
	if (heighscore<one->g_gamescene->g_scores)
		UserDefault::getInstance()->setIntegerForKey("heighscore", one->g_gamescene->g_scores);

	auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
	auto chinesefont = TTFConfig(ChineseFont, 50);
	Label* gameover = Label::createWithTTF(chinesefont, valuemap.at("SheepLayer_GameOver").asString());
	//Label* gameover = Label::create(valuemap.at("SheepLayer_GameOver").asString(), ChineseFont, 50);
	gameover->setColor(Color3B(0, 0, 0));
	chinesefont = TTFConfig(ChineseFont, 40);
	Label* undertitle = Label::createWithTTF(chinesefont,valuemap.at("SheepLayer_GameOver_Under").asString() +
		String::createWithFormat("%d", 0)->getCString());
	//Label* undertitle = Label::create(valuemap.at("SheepLayer_GameOver_Under").asString() +
		//String::createWithFormat("%d", 0)->getCString(), ChineseFont, 40);
	this->g_gameover = undertitle;
	this->g_gameover->retain();
	undertitle->setColor(Color3B(0, 0, 0));
	gameover->setAnchorPoint(Vec2(0.5, 0.5));
	undertitle->setAnchorPoint(Vec2(0.5, 0.5));
	gameover->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 3 * 2));
	undertitle->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 3 * 2 - 100));
	
	gameover->runAction(FadeIn::create(1));
	undertitle->runAction(FadeIn::create(1));
	this->g_menubutton->runAction(FadeOut::create(1));
	this->g_gamelabel->runAction(FadeOut::create(1));
	
	this->addChild(gameover, GameUI);
	this->addChild(undertitle, GameUI);
	
	this->schedule(CC_CALLBACK_0(SheepLayer::gameoveraddnum, this), 0.3, "gameoveraddnum");
	this->schedule(CC_CALLBACK_0(SheepLayer::rainsheep, this), 0.3, "rainsheep");
}

void SheepLayer::gameoveraddnum()
{
	auto one = (AppDelegate*)Application::getInstance();
	static int finalscore = one->g_gamescene->g_scores;
	static int nowscore = 0;
	if (nowscore >= finalscore)
	{
		this->unschedule("gameoveraddnum");
	}
	auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
	this->g_gameover->setString(valuemap.at("SheepLayer_GameOver_Under").asString() +
		String::createWithFormat("%d", nowscore)->getCString());
	nowscore++;
}

void SheepLayer::rainsheep()
{
		auto temp = Sheep::createsheep(0);
		temp->g_isdead = true;
		int rand = random<int>(0, 99);
		temp->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*rand / 100,
			Director::getInstance()->getVisibleSize().height + rand));
		temp->getPhysicsBody()->setGravityEnable(true);
		temp->getPhysicsBody()->setRotationEnable(true);
		temp->setRotation(rand);
		temp->hidetarget();
		temp->getPhysicsBody()->setCollisionBitmask(Collision_DeadSheep);
		temp->getPhysicsBody()->applyTorque(DeadTorque);
		temp->g_ismove = false;
		temp->g_isdead = true;
		if (rand <= 50)
		{
			temp->runAction(RepeatForever::create(RotateBy::create(2, 360)));
		}
		else
		{
			temp->runAction(RepeatForever::create(RotateBy::create(2, -360)));
		}
		this->addChild(temp, GameObject);
		temp->retain();
		g_sheeps->pushBack(temp);
		g_allcreater->pushBack(temp);

		auto temp2 = Sheep::createsheep(0);
		temp2->g_isdead = true;
		int rand2 = random<int>(0, 99);
		temp2->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*rand2 / 100,
			Director::getInstance()->getVisibleSize().height + rand2));
		temp2->getPhysicsBody()->setGravityEnable(true);
		temp2->getPhysicsBody()->setRotationEnable(true);
		temp2->setRotation(rand2);
		temp2->hidetarget();
		temp2->getPhysicsBody()->setCollisionBitmask(Collision_DeadSheep);
		temp2->getPhysicsBody()->applyTorque(DeadTorque);
		temp2->g_ismove = false;
		temp2->g_isdead = true;
		if (rand2 <= 50)
		{
			temp2->runAction(RepeatForever::create(RotateBy::create(2, 360)));
		}
		else
		{
			temp2->runAction(RepeatForever::create(RotateBy::create(2, -360)));
		}
		this->addChild(temp2, GameObject);
		temp2->retain();
		g_sheeps->pushBack(temp2);
		g_allcreater->pushBack(temp2);
}

void SheepLayer::update(float dt)
{
	/*cocos2d::log(String::createWithFormat("sheep:%d,wolf:%d,monster:%d,bride:%d,all:%d",
		this->g_sheeps->size(),this->g_wolves->size(),this->g_monster->size(),this->g_brides->size(),
		this->g_allcreater->size())->getCString());*/
	if (g_adm->shouldadd(dt, g_hardness))
	{
		this->add();
	}
}

void SheepLayer::add()
{
	int temp = random<int>(0, 99);
	if (temp <= 50)
	{
		this->addsheep();
		temp = random<int>(0, 99);
		if (temp < 10)
		{
			this->scheduleOnce(CC_CALLBACK_0(SheepLayer::addbride, this), 1, "addbridedely");
		}
	}
	else if (temp <= 80)
	{
		this->addwolf();
		temp = random<int>(0, 99);
		if (temp<33)
			this->scheduleOnce(CC_CALLBACK_0(SheepLayer::addbride, this), 1, "addbridedely");
	}
	else if (temp <= 99)
	{
		this->addmonster();
		temp = random<int>(0, 99);
		if (temp<50)
			this->scheduleOnce(CC_CALLBACK_0(SheepLayer::addbride, this), 1, "addbridedely");
	}
}

void SheepLayer::addsheep()
{
	g_hardness++;
	auto one = (AppDelegate*)Application::getInstance();
	auto temp = Sheep::createsheep(g_adm->howfast(g_hardness));
	temp->retain();
	temp->setPosition(-temp->getContentSize().width / 3,
		(one->g_gamescene->g_sheeplayer->g_bar->getPosition().y) -
		(one->g_gamescene->g_sheeplayer->g_bar->getContentSize().height / 2));
	g_sheeps->pushBack(temp);
	g_allcreater->pushBack(temp);
	this->addChild(temp, GameObject);
}

void SheepLayer::addmonster()
{
	if (g_monster->size() < 1)
	{
		g_hardness++;
		auto one = (AppDelegate*)Application::getInstance();
		auto temp = Monster::createmonster(g_adm->howfast(g_hardness));
		temp->retain();
		temp->setPosition(-temp->getContentSize().width / 3,
			(one->g_gamescene->g_sheeplayer->g_bar->getPosition().y) -
			(one->g_gamescene->g_sheeplayer->g_bar->getContentSize().height / 2));
		g_monster->pushBack(temp);
		g_allcreater->pushBack(temp);
		this->addChild(temp, GameObject);
	}
	else
	this->addsheep();
}

void SheepLayer::addwolf()
{
	if (g_wolves->size() < 2)
	{
		g_hardness++;
		auto one = (AppDelegate*)Application::getInstance();
		auto temp = Wolf::createwolf(g_adm->howfast(g_hardness));
		temp->retain();
		temp->setPosition(-temp->getContentSize().width / 3,
			(one->g_gamescene->g_sheeplayer->g_bar->getPosition().y) -
			(one->g_gamescene->g_sheeplayer->g_bar->getContentSize().height / 2));
		g_wolves->pushBack(temp);
		g_allcreater->pushBack(temp);
		this->addChild(temp, GameObject);
	}
	else
	this->addsheep();
}

void SheepLayer::addbride()
{
	if (g_brides->size() == 0)
	{
		auto one = (AppDelegate*)Application::getInstance();
		auto temp = Bride::createbride();
		temp->retain();
		temp->setPosition(Director::getInstance()->getVisibleSize().width + temp->getContentSize().width / 3,
			Director::getInstance()->getVisibleSize().height - 100);
		this->g_brides->pushBack(temp);
		this->addChild(temp, GameObjectForward);
	}
}

void SheepLayer::pauseallcreators()
{
	for (auto i = this->g_sheeps->begin(); i != this->g_sheeps->end(); i++)
	{
		(*i)->pause();
		(*i)->getPhysicsBody()->setVelocity(Vec2(0, 0));
		(*i)->getPhysicsBody()->setGravityEnable(false);
	}
	for (auto i = this->g_monster->begin(); i != this->g_monster->end(); i++)
	{
		(*i)->pause();
		(*i)->getPhysicsBody()->setVelocity(Vec2(0, 0));
		(*i)->getPhysicsBody()->setGravityEnable(false);
	}
	for (auto i = this->g_wolves->begin(); i != this->g_wolves->end(); i++)
	{
		(*i)->pause();
		(*i)->getPhysicsBody()->setVelocity(Vec2(0, 0));
		(*i)->getPhysicsBody()->setGravityEnable(false);
	}
	for (auto i = this->g_brides->begin(); i != this->g_brides->end(); i++)
	{
		(*i)->pause();
		(*i)->getPhysicsBody()->setVelocity(Vec2(0, 0));
		(*i)->getPhysicsBody()->setGravityEnable(false);
	}
}

void SheepLayer::resumeallcreators()
{
	for (auto i = this->g_sheeps->begin(); i != this->g_sheeps->end(); i++)
	{
		(*i)->resume();
		(*i)->getPhysicsBody()->setGravityEnable(true);
	}
	for (auto i = this->g_monster->begin(); i != this->g_monster->end(); i++)
	{
		(*i)->resume();
		(*i)->getPhysicsBody()->setGravityEnable(true);
	}
	for (auto i = this->g_wolves->begin(); i != this->g_wolves->end(); i++)
	{
		(*i)->resume();
		(*i)->getPhysicsBody()->setGravityEnable(true);
	}
	for (auto i = this->g_brides->begin(); i != this->g_brides->end(); i++)
	{
		(*i)->resume();
	}
}

void SheepLayer::initbutton()
{
	this->g_menubutton = Menu::create(MenuItemImage::create("menu_a.png", "menu_b.png",
		CC_CALLBACK_0(SheepLayer::showmenu, this)), nullptr);
	this->g_menubutton->setAnchorPoint(Vec2(0.5, 0.5));
	g_menubutton->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 40,
		Director::getInstance()->getVisibleSize().height - 25));
	this->addChild(g_menubutton, GameUI);
}

void SheepLayer::showmenu()
{
	auto one = (AppDelegate*)Application::getInstance();
	this->g_menubutton->removeFromParent();
	one->g_gamescene->showmenu();	
}

void SheepLayer::hidescene()
{
	this->g_bar->runAction(FadeOut::create(0.5));
	this->g_land->runAction(FadeOut::create(0.5));
	for (auto i = this->g_allcreater->begin(); i != this->g_allcreater->end(); i++)
	{
		(*i)->runAction(FadeOut::create(0.5));
	}
	for (auto i = this->g_sheeps->begin(); i != this->g_sheeps->end(); i++)
	{
		(*i)->hidetarget();
	}
	for (auto i = this->g_wolves->begin(); i != this->g_wolves->end(); i++)
	{
		(*i)->hidetarget();
	}
}

void SheepLayer::freshlable()
{
	auto one = (AppDelegate*)Application::getInstance();
	this->g_gamelabel->setString(String::createWithFormat("Hp:%d,Scores:%d", one->g_gamescene->g_hp
		, one->g_gamescene->g_scores)->getCString());
}



//addmanager
AddManager::AddManager(SheepLayer* in)
{
	g_shouldadd = true;
	g_sheeplayer = in;
	g_delytime = 0;
	g_hardness = 0;
	refreshwait();
}

void AddManager::refreshwait()
{
	if (g_hardness <= Wave1)
	{
		g_shouldwait = 5;
	}
	else if (g_hardness <= Wave2)
	{
		if (this->wavechange(3.5))
			g_shouldwait = 3.5;
	}
	else if (g_hardness <= Wave3)
	{
		if (this->wavechange(2.5))
			g_shouldwait = 2.5;
	}
	else if (g_hardness <= Wave4)
	{
		if (this->wavechange(2))
			g_shouldwait = 2;
	}
	else if (g_hardness <= Wave5)
	{
		if (this->wavechange(1.6))
			g_shouldwait = 1.6;
	}
	else
	{
		if (this->wavechange(1.5))
			g_shouldwait = 1.5;
	}
}

bool AddManager::shouldadd(float dt,float hardness)
{
	g_hardness = hardness;
	g_delytime += dt;
	refreshwait();
	if (!g_shouldadd)
	{
		return false;
	}
	if ((g_delytime) > g_shouldwait)
	{
		g_delytime = 0;
		return true;
	}
	else
		return false;
}

float AddManager::howfast(float hardness)
{
	if (hardness <= Wave1)
	{
		return 40;
	}
	else if (hardness <= Wave2)
	{
		return 40;
	}
	else if (hardness <= Wave3)
	{
		return 50;
	}
	else if (hardness <= Wave4)
	{
		return 55;
	}
	else if (hardness <= Wave5)
	{
		return 60;
	}
	else
	{
		return 62;
	}
}

bool AddManager::wavechange(float i)
{
	if (g_shouldwait != i)
	{
		g_shouldadd = false;
		if (g_sheeplayer->g_allcreater->size() > 0)
		{
			return false;
		}
		auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
		g_sheeplayer->g_wavelabel->setString(valuemap.at("SheepLayer_Wave").asString());
		g_sheeplayer->g_wavelabel->runAction(Sequence::create(FadeIn::create(1), 
			DelayTime::create(1),FadeOut::create(1), DelayTime::create(1), 
			CallFuncN::create([this](Node* in){g_shouldadd = true; }), nullptr));
		return true;
	}
}