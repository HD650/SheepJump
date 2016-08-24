#include "techscene.h"

TechScene* TechScene::createtechscene()
{
	auto temp = new TechScene();
	temp->autorelease();
	auto one = (AppDelegate*)Application::getInstance();
	one->g_gamescene = temp;
	temp->retain();
	temp->inittechscene();
	return temp;
}

TechScene::~TechScene()
{
	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Horns.mp3", true);
	}
}

void TechScene::inittechscene()
{
	Scene::initWithPhysics();
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(WorldGravity);

	g_hp = 999;
	g_scores = 0;
	g_gamelayer = GameLayer::creategamelayer();
	g_techsheeplayer = TechSheepLayer::createtechsheeplayer();
	g_sheeplayer = g_techsheeplayer;
	
	this->addChild(g_techsheeplayer, 1);
	this->addChild(g_gamelayer, 2);

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Dark Rock.mp3", true);
	}
}

void TechScene::changescores(bool in)
{
	GameScene::changescores(in);
	g_techsheeplayer->nextquest();
}

void TechScene::changehp(bool in)
{
	GameScene::changehp(in);
	g_techsheeplayer->nextquest();
}

void TechScene::gamebegin()
{
	g_techsheeplayer->showtext();
}