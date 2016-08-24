#include "gamescene.h"
#include "alldefine.h"

GameScene* GameScene::creategamescene()
{
	auto temp = new GameScene;
	temp->autorelease();
	auto one = (AppDelegate*)Application::getInstance();
	one->g_gamescene = temp;
	temp->retain();
	temp->initgamescene();
	
	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Thin.mp3", true);
	}

	return temp;
}

void GameScene::initgamescene()
{
	Scene::initWithPhysics();
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(WorldGravity);
	this->getPhysicsWorld()->setSpeed(1);

	g_gamelayer = GameLayer::creategamelayer();
	g_sheeplayer = SheepLayer::createsheeplayer();

	g_hp = 5;
	g_scores = 0;
	isgameovered = false;
	
	this->addChild(g_sheeplayer, -1);
	this->addChild(g_gamelayer, 0);
}

GameScene::~GameScene()
{
	//this->g_sheeplayer->removeFromParent();
	//this->g_gamelayer->removeFromParent();	
}

void GameScene::initmenu()
{
	auto game = MenuItemImage::create("game_a.png", "game_b.png", CC_CALLBACK_0(GameScene::restartgame, this));
	auto main = MenuItemImage::create("main_a.png", "main_b.png", CC_CALLBACK_0(GameScene::tomainmenu, this));
	//auto config = MenuItemImage::create("config_a.png", "config_b.png", CC_CALLBACK_0(GameScene::toconfig, this));
	auto back = MenuItemImage::create("back_a.png", "back_b.png", CC_CALLBACK_0(GameScene::hidemenu, this));

	game->setPosition(0, 100);
	main->setPosition(0, 50);
	//config->setPosition(0, 50);
	back->setPosition(0, 0);

	this->g_menu = Menu::create(game, main, back, nullptr);
	g_menu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(g_menu, GameUI);
}

void GameScene::destorymenu()
{
	this->g_menu->removeFromParent();
	g_menu = nullptr;
}

void GameScene::changehp(bool in)
{
	g_hp += in ? 1 : -1;
	g_sheeplayer->freshlable();
	if (g_hp <= 0 && !isgameovered)//防止多次gameover
	{
		isgameovered = true;
		this->gameover();
	}
}

void GameScene::changescores(bool in)
{
	g_scores += in ? 1 : -1;
	g_sheeplayer->freshlable();
}

void GameScene::gamebegin()
{
	this->g_sheeplayer->scheduleUpdate();
}

void GameScene::gameover()
{
	auto one = (AppDelegate*)Application::getInstance();
	this->g_sheeplayer->g_adm->g_shouldadd = false;//死后停止生产羊
	one->g_gamescene->release();//释放上一个gamescene的内存，注意：一定要删除上一个场景的listener
	one->g_gamescene->g_gamelayer->disable();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->onTouchBegan = CC_CALLBACK_2(GameScene::touchtomain, this);
	one->g_gamescene->getEventDispatcher()->addEventListenerWithFixedPriority(m_listener, 1);
	one->g_gamescene->g_sheeplayer->gameover();
}

void GameScene::topause()
{
	this->g_gamelayer->pause();
	this->g_gamelayer->disable();
	this->g_sheeplayer->pause();
	this->g_sheeplayer->pauseallcreators();
}

void GameScene::toresume()
{
	this->g_gamelayer->resume();
	this->g_gamelayer->enable();
	this->g_sheeplayer->resume();
	this->g_sheeplayer->resumeallcreators();
}

void GameScene::tomainmenu()
{
	auto one = (AppDelegate*)Application::getInstance();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, one->g_mainmenu, true));
	one->g_gamescene->release();//释放上一个gamescene的内存，注意：一定要删除上一个场景的listener
	this->_eventDispatcher->removeEventListener(m_listener);
}

bool GameScene::touchtomain(Touch* in, Event* what)
{
	auto one = (AppDelegate*)Application::getInstance();
	one->g_mainmenu->release();
	one->g_mainmenu = MainMenu::createmainmenu();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, one->g_mainmenu, true));
	this->_eventDispatcher->removeEventListener(m_listener);
	return true;
}

void GameScene::restartgame()
{
	auto one = (AppDelegate*)Application::getInstance();
	one->g_gamescene->release();//释放上一个gamescene的内存，注意：一定要删除上一个场景的listener
	one->g_gamescene = GameScene::creategamescene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, one->g_gamescene, false));
	one->g_gamescene->gamebegin();
	this->hidemenu();
}

void GameScene::tohighscores()
{
	//nothing
}

void GameScene::toconfig()
{
	//nothing
}

void GameScene::showmenu()
{
	this->topause();
	this->initmenu();
}

void GameScene::hidemenu()
{
	this->destorymenu();
	this->toresume();
	g_sheeplayer->initbutton();
}