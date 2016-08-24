#include"techsheeplayer.h"

TechSheepLayer* TechSheepLayer::createtechsheeplayer()
{
	auto temp = new TechSheepLayer();
	temp->autorelease();
	temp->inittechsheeplayer();
	return temp;
}

void TechSheepLayer::inittechsheeplayer()
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

	//auto lable = LabelTTF::create(String::createWithFormat("Hp:%d,Scores:%d", 999, 0)->getCString(), EnglishFont, 30);
	auto font = TTFConfig(EnglishFont, 30);
	auto lable = Label::createWithTTF(font, String::createWithFormat("Hp:%d,Scores:%d", 999, 0)->getCString());
	lable->setColor(Color3B(0, 0, 0));
	lable->setAnchorPoint(Vec2(0, 0));
	lable->setPosition(Vec2(30, Director::getInstance()->getVisibleSize().height - 50));
	g_gamelabel = lable;
	this->addChild(lable, GameUI);

	auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
	auto chinesefont = TTFConfig(ChineseFont, 50);
	auto wlable = Label::createWithTTF(chinesefont, valuemap.at("Tech_Begin").asString());
	//auto wlable = Label::create(valuemap.at("Tech_Begin").asString(), ChineseFont, 50);
	wlable->setColor(Color3B(0, 0, 0));
	wlable->setAnchorPoint(Vec2(0.5, 0.5));
	wlable->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 3 * 2));
	g_wavelabel = wlable;
	this->addChild(wlable, GameUI);
	wlable->runAction(Sequence::create(FadeIn::create(1), DelayTime::create(1), FadeOut::create(1), nullptr));

	g_adm = new AddManager(this);

	step = techstep::Begin;
	auto one = (AppDelegate*)Application::getInstance();
	this->scores = one->g_gamescene->g_scores;
	this->hp = one->g_gamescene->g_hp;
	this->inittextdata();

	this->g_lableback = Sprite::create("techlabelback.png");
	chinesefont = TTFConfig(ChineseFont, 25);
	this->g_lable = Label::createWithTTF(chinesefont, "nothing");
	//this->g_lable = Label::create("nothing", ChineseFont, 25);
	g_lable->setColor(Color3B(0, 0, 0));
	g_lable->setAnchorPoint(Vec2(0.5, 0.5));
	g_lable->setPosition(g_lableback->getContentSize().width / 2, g_lableback->getContentSize().height / 2);
	g_lableback->addChild(g_lable, GameUI);
	g_lableback->setAnchorPoint(Vec2(0.5, 0.5));
	g_lableback->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().width / 4 * 1.5));
	this->addChild(g_lableback, GameUI);
	g_lableback->setVisible(false);
}

void TechSheepLayer::inittextdata()
{
	auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
	for (auto i = valuemap.at("Begin").asValueVector().begin(); i != valuemap.at("Begin").asValueVector().end(); i++)
	{
		data[static_cast<int>(techstep::Begin)].push_back((*i).asString());
	}
	for (auto i = valuemap.at("HDU_Tech").asValueVector().begin(); i != valuemap.at("HDU_Tech").asValueVector().end(); i++)
	{
		data[static_cast<int>(techstep::HDU_Tech)].push_back((*i).asString());
	}
	for (auto i = valuemap.at("Sheep_Jump").asValueVector().begin(); i != valuemap.at("Sheep_Jump").asValueVector().end(); i++)
	{
		data[static_cast<int>(techstep::Sheep_Jump)].push_back((*i).asString());
	}
	for (auto i = valuemap.at("Wolf_Turn").asValueVector().begin(); i != valuemap.at("Wolf_Turn").asValueVector().end(); i++)
	{
		data[static_cast<int>(techstep::Wolf_Turn)].push_back((*i).asString());
	}
	for (auto i = valuemap.at("Wolf_Kill").asValueVector().begin(); i != valuemap.at("Wolf_Kill").asValueVector().end(); i++)
	{
		data[static_cast<int>(techstep::Wolf_Kill)].push_back((*i).asString());
	}
	for (auto i = valuemap.at("Monster_Kill").asValueVector().begin(); i != valuemap.at("Monster_Kill").asValueVector().end(); i++)
	{
		data[static_cast<int>(techstep::Monster_Kill)].push_back((*i).asString());
	}
	for (auto i = valuemap.at("Bird_Catch").asValueVector().begin(); i != valuemap.at("Bird_Catch").asValueVector().end(); i++)
	{
		data[static_cast<int>(techstep::Bird_Catch)].push_back((*i).asString());
	}
	for (auto i = valuemap.at("Wind").asValueVector().begin(); i != valuemap.at("Wind").asValueVector().end(); i++)
	{
		data[static_cast<int>(techstep::Wind)].push_back((*i).asString());
	}
	for (auto i = valuemap.at("Final").asValueVector().begin(); i != valuemap.at("Final").asValueVector().end(); i++)
	{
		data[static_cast<int>(techstep::Final)].push_back((*i).asString());
	}
}

void TechSheepLayer::addsheep()
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

void TechSheepLayer::addwolf()
{
	g_hardness++;
	auto one = (AppDelegate*)Application::getInstance();
	auto temp = TechWolf::createtechwolf(g_adm->howfast(g_hardness));
	temp->retain();
	temp->setPosition(-temp->getContentSize().width / 3,
		(one->g_gamescene->g_sheeplayer->g_bar->getPosition().y) -
		(one->g_gamescene->g_sheeplayer->g_bar->getContentSize().height / 2));
	g_wolves->pushBack(temp);
	g_allcreater->pushBack(temp);
	this->addChild(temp, GameObject);
}

void TechSheepLayer::addbird()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto temp = TechBride::createtechbride();
	temp->retain();
	temp->setPosition(Director::getInstance()->getVisibleSize().width + temp->getContentSize().width / 2,
		Director::getInstance()->getVisibleSize().height - 150);
	this->g_brides->pushBack(temp);
	this->addChild(temp, GameObjectForward);

}

void TechSheepLayer::addmonster()
{
	g_hardness++;
	auto one = (AppDelegate*)Application::getInstance();
	auto temp = TechMonster::createtechmonster(g_adm->howfast(g_hardness));
	temp->retain();
	temp->setPosition(-temp->getContentSize().width / 3,
		(one->g_gamescene->g_sheeplayer->g_bar->getPosition().y) -
		(one->g_gamescene->g_sheeplayer->g_bar->getContentSize().height / 2));
	g_monster->pushBack(temp);
	g_allcreater->pushBack(temp);
	this->addChild(temp, GameObject);
}

bool TechSheepLayer::isquestfinish(Sheep* who)
{
	auto one = (AppDelegate*)Application::getInstance();
	switch (step)
	{
	case techstep::HDU_Tech:
		return true;

	case techstep::Begin:
		return true;

	case techstep::Sheep_Jump:
		if (one->g_gamescene->g_scores > this->scores)
		{
			this->scores = one->g_gamescene->g_scores;
			this->hp = one->g_gamescene->g_hp;
			return true;
		}

		else
		{
			this->scores = one->g_gamescene->g_scores;
			this->hp = one->g_gamescene->g_hp;

			this->g_wavelabel->setSystemFontSize(Tech_Waring_Label_Font_Size);
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
			this->g_wavelabel->setString(valuemap.at("Sheep_Jump_In").asString());
			this->g_wavelabel->runAction(Sequence::create(FadeIn::create(1), DelayTime::create(1), FadeOut::create(1), nullptr));

			return false;
		}

	case techstep::Wolf_Turn:
		if (one->g_gamescene->g_scores > this->scores&&one->g_gamescene->g_hp == this->hp)
			return true;
		else
		{
			this->scores = one->g_gamescene->g_scores;
			this->hp = one->g_gamescene->g_hp;

			this->g_wavelabel->setSystemFontSize(Tech_Waring_Label_Font_Size);
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
			this->g_wavelabel->setString(valuemap.at("Wolf_Turn_In").asString());
			this->g_wavelabel->runAction(Sequence::create(FadeIn::create(1), DelayTime::create(1), FadeOut::create(1), nullptr));

			return false;
		}

	case techstep::Wolf_Kill:
		if (who->g_isdead)
			return true;
		else
		{
			this->g_wavelabel->setSystemFontSize(Tech_Waring_Label_Font_Size);
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
			this->g_wavelabel->setString(valuemap.at("Wolf_Kill_In").asString());
			this->g_wavelabel->runAction(Sequence::create(FadeIn::create(1), DelayTime::create(1), FadeOut::create(1), nullptr));
			return false;
		}

	case techstep::Monster_Kill:
		if (who->g_isdead)
			return true;
		else
		{
			this->g_wavelabel->setSystemFontSize(Tech_Waring_Label_Font_Size);
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
			this->g_wavelabel->setString(valuemap.at("Monster_Kill_In").asString());
			this->g_wavelabel->runAction(Sequence::create(FadeIn::create(1), DelayTime::create(1), FadeOut::create(1), nullptr));
			return false;
		}

	case techstep::Bird_Catch:
		if (who->g_isctached)
			return true;
		else
		{
			this->g_wavelabel->setSystemFontSize(Tech_Waring_Label_Font_Size);
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
			this->g_wavelabel->setString(valuemap.at("Bird_Catch_In").asString());
			this->g_wavelabel->runAction(Sequence::create(FadeIn::create(1), DelayTime::create(1), FadeOut::create(1), nullptr));
			return false;
		}

	case techstep::Wind:
		if (who->getPosition().y >= Director::getInstance()->getVisibleSize().height / 1.5)
			return true;
		else
		{
			return false;
		}

	case techstep::Final:
		if (!g_isquit)
		{
			this->quit();
			one->g_gamescene->release();
			Director::getInstance()->replaceScene(TransitionPageTurn::create(1, one->g_mainmenu, true));
		}
		this->g_isquit = true;//截断教学循环
		return true;
		break;

	default:
		return false;
		break;
	}

}

void TechSheepLayer::nextquest(Sheep* in)
{
	if (!isquestfinish(in))
	{
		putquest();
	}
	else
	{
		if (g_isquit)//如果已经截断，就不继续了，只要步调用showtext或者其中的一环，教学循环就不会继续，对点击的监听也会停止
			return;
		int i = step;
		i += 1;
		if (i >= techstep::Final)
			i = techstep::Final;
		step = static_cast<techstep>(i);
		this->showtext();
	}
}

void TechSheepLayer::putquest()
{
	auto one = (AppDelegate*)Application::getInstance();
	switch (step)
	{
	case Begin:
		one->g_gamescene->g_gamelayer->g_magicbook->g_ischangesheep = false;//禁止施法，防止崩溃
		one->g_gamescene->g_gamelayer->g_magicbook->g_islightning = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_isorderbride = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_iswind = false;
		nextquest();
		break;
	case HDU_Tech:
		nextquest();
		break;
	case Sheep_Jump:
		one->g_gamescene->g_gamelayer->g_magicbook->g_ischangesheep = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_islightning = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_isorderbride = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_iswind = false;
		addsheep();
		break;
	case Wolf_Turn:		//BUG变羊之后装死羊，刷出新狼再立即变羊出bug
		one->g_gamescene->g_gamelayer->g_magicbook->g_islightning = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_isorderbride = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_iswind = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_ischangesheep = true;
		addwolf();
		break;
	case Wolf_Kill:
		one->g_gamescene->g_gamelayer->g_magicbook->g_ischangesheep = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_isorderbride = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_iswind = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_islightning = true;
		addwolf();
		break;
	case Monster_Kill:
		one->g_gamescene->g_gamelayer->g_magicbook->g_ischangesheep = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_islightning = true;
		one->g_gamescene->g_gamelayer->g_magicbook->g_isorderbride = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_iswind = false;
		addmonster();
		break;
	case Bird_Catch:
		one->g_gamescene->g_gamelayer->g_magicbook->g_ischangesheep = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_islightning = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_isorderbride = true;
		one->g_gamescene->g_gamelayer->g_magicbook->g_iswind = false;
		if (this->g_sheeps->size() == 0)
		{
			addsheep();
			(*this->g_sheeps->begin())->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
				(one->g_gamescene->g_sheeplayer->g_bar->getPosition().y) -
				(one->g_gamescene->g_sheeplayer->g_bar->getContentSize().height / 2)));
			(*this->g_sheeps->begin())->g_ismove = false;
		}
		addbird();
		break;
	case Wind:
		one->g_gamescene->g_gamelayer->g_magicbook->g_ischangesheep = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_islightning = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_isorderbride = false;
		one->g_gamescene->g_gamelayer->g_magicbook->g_iswind = true;
		if (this->g_sheeps->size() == 0)
		{
			addsheep();
			(*this->g_sheeps->begin())->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
				(one->g_gamescene->g_sheeplayer->g_bar->getPosition().y) -
				(one->g_gamescene->g_sheeplayer->g_bar->getContentSize().height / 2)));
			(*this->g_sheeps->begin())->g_ismove = false;
			(*this->g_sheeps->begin())->schedule(
				[&](float in)
			{
				auto one = (AppDelegate*)Application::getInstance();
				auto pos = (*this->g_sheeps->begin())->getPosition();
				if (pos.y >= Director::getInstance()->getVisibleSize().height / 1.5);
				((TechSheepLayer*)(one->g_gamescene->g_sheeplayer))->nextquest((*this->g_sheeps->begin()));
			},
				"isquestfinsh");
			(*this->g_sheeps->begin())->hidetarget();
			(*this->g_sheeps->begin())->getPhysicsBody()->setGravityEnable(true);
		}
		break;
	case Final:
		break;
	default:
		break;
	}
}

void TechSheepLayer::showlabel()
{
	auto one = (AppDelegate*)Application::getInstance();
	one->g_gamescene->g_gamelayer->disable();
	p_listener = EventListenerTouchOneByOne::create();
	p_listener->onTouchBegan = CC_CALLBACK_2(TechSheepLayer::buttondown, this);
	this->getEventDispatcher()->addEventListenerWithFixedPriority(p_listener, 1);
	this->pauseallcreators();
	this->g_lableback->setVisible(true);
}

void TechSheepLayer::hidelabel()
{
	this->getEventDispatcher()->removeEventListener(p_listener);
	this->resumeallcreators();
	this->g_lableback->setVisible(false);
	auto one = (AppDelegate*)Application::getInstance();
	if (step == techstep::Begin || step == techstep::HDU_Tech)
		;
	else
		one->g_gamescene->g_gamelayer->enable();
	this->putquest();
}

void TechSheepLayer::showtext(int index)
{
	this->refreshtext();
	this->showlabel();
}

void TechSheepLayer::refreshtext()
{
	string text = data[static_cast<int>(step)].at(0);
	g_lable->setString(text.c_str());
}

bool TechSheepLayer::buttondown(Touch* loc, Event* what)
{
	static int textstep = 0;
	g_lable->runAction(Sequence::create(FadeOut::create(0.1), CallFunc::create([&](){
		if ((textstep + 1) > data[static_cast<int>(step)].size())
		{
			textstep = 0;
			this->hidelabel();
		}
		string text = data[static_cast<int>(step)].at(textstep);
		g_lable->setString(text.c_str());
	}), DelayTime::create(0.1), FadeIn::create(0.1), nullptr));
	textstep++;
	return true;
}

void TechSheepLayer::gameover()
{
	return;
}

void TechSheepLayer::quit()
{
	this->pause();
	this->getEventDispatcher()->removeEventListener(p_listener);
}


TechWolf* TechWolf::createtechwolf(float in)
{
	auto temp = new TechWolf;
	temp->autorelease();
	temp->initwolf(in);
	return temp;
}
void TechWolf::remove()//BUG变羊之后装死羊，刷出新狼再立即变羊出bug
{
	auto one = (AppDelegate*)Application::getInstance();
	if ((!this->g_isdead) && one->g_gamescene->g_sheeplayer->g_sheeps->size() == 0 && !isRightXout())
	{
		Wolf::remove();
	}
	else
	{
		((TechSheepLayer*)one->g_gamescene->g_sheeplayer)->nextquest(this);
		Wolf::remove();
	}
}
void TechWolf::checkpos()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto bar = one->g_gamescene->g_sheeplayer->g_bar->getBoundingBox();
	if (!g_isdead)
	{
		if (isRightXout())
		{
			one->g_gamescene->g_scores -= 4;
			this->remove();
			return;
		}
		if (isBarcontact(bar))
		{
			one->g_gamescene->g_hp -= 1;
			one->g_gamescene->g_sheeplayer->barshack();
			this->dead();
			return;
		}
	}
	else
	{
		if (isDownYout())
		{
			this->remove();
			return;
		}
	}
}
TechMonster* TechMonster::createtechmonster(float in)
{
	auto temp = new TechMonster;
	temp->autorelease();
	temp->initmonster(in);
	return temp;
}
void TechMonster::remove()
{
	auto one = (AppDelegate*)Application::getInstance();
	((TechSheepLayer*)one->g_gamescene->g_sheeplayer)->nextquest(this);
	Monster::remove();
}
void TechMonster::checkpos()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto bar = one->g_gamescene->g_sheeplayer->g_bar->getBoundingBox();
	if (!g_isdead)
	{
		if (isRightXout())
		{
			one->g_gamescene->gameover();
			this->remove();
			return;
		}
		if (isBarcontact(bar))
		{
			one->g_gamescene->gameover();
			one->g_gamescene->g_sheeplayer->barbreak();
			this->dead();
			one->g_gamescene->g_sheeplayer->g_wavelabel->setSystemFontSize(Tech_Waring_Label_Font_Size);
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile("tech_text.plist");
			one->g_gamescene->g_sheeplayer->g_wavelabel->setString(valuemap.at("Monster_Kill_In").asString());
			one->g_gamescene->g_sheeplayer->g_wavelabel->runAction(Sequence::create(FadeIn::create(1), DelayTime::create(1), FadeOut::create(1), nullptr));
			return;
		}
	}
	else
	{
		if (isDownYout())
		{
			this->remove();
			return;
		}
	}
}
TechBride* TechBride::createtechbride()
{
	auto temp = new TechBride;
	temp->initbride();
	temp->autorelease();
	temp->retain();
	return temp;
}
void TechBride::remove()
{
	auto one = (AppDelegate*)Application::getInstance();
	((TechSheepLayer*)one->g_gamescene->g_sheeplayer)->nextquest(this->g_target);
	Bride::remove();
}