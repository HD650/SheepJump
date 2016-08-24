#include "mainmenu.h"

MainMenu* MainMenu::createmainmenu()
{
	auto temp = new MainMenu;
	temp->initmainmenu();
	temp->autorelease();
	auto one = (AppDelegate*)Application::getInstance();
	one->g_mainmenu = temp;
	temp->retain();
	return temp;
}

void MainMenu::initmainmenu()
{
	Scene::init();
	auto back = Sprite::create("menuback.png");
	back->setAnchorPoint(Vec2(0, 0));
	back->setPosition(Vec2(0, 0));
	this->addChild(back);

	auto game=MenuItemImage::create("game_a.png", "game_b.png", CC_CALLBACK_0(MainMenu::startnewgame, this));
	auto tech = MenuItemImage::create("tech_a.png", "tech_b.png", CC_CALLBACK_0(MainMenu::startteacher, this));
	auto config = MenuItemImage::create("config_a.png", "config_b.png", CC_CALLBACK_0(MainMenu::startconfigure, this));
	auto menu = Menu::create(game, tech, config, nullptr);
	game->setPosition(Vec2(0, 120));
	tech->setPosition(Vec2(0, 60));
	config->setPosition(Vec2(0,0));
	menu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/3));
	this->addChild(menu);

	//auto mainlabel = LabelTTF::create("SheepJump!", TitleFont, 60);
	auto font=TTFConfig(TitleFont, 60);
	auto mainlabel = Label::createWithTTF(font, "SheepJump!");

	mainlabel->setAnchorPoint(Vec2(0.5, 1));
	mainlabel->setColor(Color3B(0, 0, 0));
	mainlabel->setPosition(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height - 20);
	this->addChild(mainlabel);
	int hs = UserDefault::getInstance()->getIntegerForKey("heighscore",0);
	//auto heighscore = LabelTTF::create(String::createWithFormat("HightestScore:%d", hs)->getCString(), EnglishFont, 30);
	font = TTFConfig(EnglishFont, 30);
	auto heighscore = Label::createWithTTF(font, String::createWithFormat("HightestScore:%d", hs)->getCString());
	heighscore->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 3 * 1.9));
	heighscore->setColor(Color3B(0, 0, 0));
	this->addChild(heighscore);
	
	this->schedule(CC_CALLBACK_0(MainMenu::sheeprun, this), 0.7, "sheeprun");
	
	if (UserDefault::getInstance()->getBoolForKey("BGM",true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Horns.mp3", true);
	}
}

void MainMenu::sheeprun()
{
	auto temp = Sprite::create("sheep_back1.png");
	temp->setAnchorPoint(Vec2(0, 0));
	temp->setPosition(-temp->getBoundingBox().size.width, 0);
	temp->setScale(0.5);
	temp->schedule([=](float dt)
	{
		auto pos = temp->getPosition();
		pos.x += dt * 100;
		temp->setPosition(pos);
		if (temp->getPosition().x >= Director::getInstance()->getVisibleSize().width + 20)
		{
			temp->removeFromParent();
		}
	}
	, "sheeprun");
	temp->runAction(RepeatForever::create(Sequence::create(EaseExponentialOut::create(RotateBy::create(0.5, 1)),
		EaseExponentialInOut::create(RotateBy::create(1, -3)), EaseBackIn::create(RotateBy::create(0.5, 1)), nullptr)));
	this->addChild(temp, GameObject);

	auto temp2 = Sprite::create("sheep_back1.png");
	temp2->setAnchorPoint(Vec2(0, 0));
	temp2->setPosition(-temp2->getBoundingBox().size.width, Director::getInstance()->getVisibleSize().height - 135);
	temp2->setScale(0.5);
	temp2->schedule([=](float dt)
	{
		auto pos = temp2->getPosition();
		pos.x += dt * 100;
		temp2->setPosition(pos);
		if (temp2->getPosition().x >= Director::getInstance()->getVisibleSize().width + 20)
		{
			temp2->removeFromParent();
		}
	}
	, "sheeprun2");
	temp2->runAction(RepeatForever::create(Sequence::create(EaseExponentialOut::create(RotateBy::create(0.5, 1)),
		EaseExponentialInOut::create(RotateBy::create(1, -3)), EaseBackIn::create(RotateBy::create(0.5, 1)), nullptr)));
	this->addChild(temp2, GameObject);
}

void  MainMenu::startnewgame()
{
	static bool second = false;
	auto one = (AppDelegate*)Application::getInstance();
	one->g_gamescene = GameScene::creategamescene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, one->g_gamescene, false));
	one->g_gamescene->gamebegin();
}

void MainMenu::startteacher()
{
	auto one = (AppDelegate*)Application::getInstance();
	one->g_gamescene = TechScene::createtechscene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, one->g_gamescene, false));
	one->g_gamescene->gamebegin();
}

void MainMenu::startconfigure()
{
	auto temp = ConfigScene::create();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, temp, true));
}