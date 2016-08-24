#include "configscene.h"
#include "AppDelegate.h"

bool ConfigScene::init()
{
	Scene::init();
	auto bg = Sprite::create("menuback.png");
	bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg,BackGround);

	auto on = MenuItemImage::create("BGMon.png", "BGMon.png", CC_CALLBACK_0(ConfigScene::BGMon, this));
	auto off = MenuItemImage::create("BGMoff.png", "BGNoff.png", CC_CALLBACK_0(ConfigScene::BGMoff, this));
	auto back = MenuItemImage::create("configback.png", "configback.png", CC_CALLBACK_0(ConfigScene::backtomain, this));
	auto menu = Menu::create(on, off, back, nullptr);
	on->setPosition(Vec2(-90, 0));
	off->setPosition(Vec2(90, 0));
	back->setPosition(Vec2(0, -90));
	menu->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(menu, GameUI);

	auto font = TTFConfig(TitleFont, 35);
	auto lable = Label::createWithTTF(font, String::createWithFormat("Want Some Music?", 5, 0)->getCString());
	//auto lable = LabelTTF::create(String::createWithFormat("Want Some Music?", 5, 0)->getCString(), TitleFont, 35);
	lable->setColor(Color3B::BLACK);
	lable->setAnchorPoint(Vec2(0.5, 1));
	lable->setPosition(Director::getInstance()->getVisibleSize().width / 2, 
		Director::getInstance()->getVisibleSize().height - 20);
	this->addChild(lable, GameUI);

	return true;
}

void ConfigScene::BGMon()
{
	UserDefault::getInstance()->setBoolForKey("BGM", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Horns.mp3",true);
}

void ConfigScene::BGMoff()
{
	UserDefault::getInstance()->setBoolForKey("BGM", false);
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void ConfigScene::backtomain()
{
	auto one = (AppDelegate*)Application::getInstance();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, one->g_mainmenu, false));
}