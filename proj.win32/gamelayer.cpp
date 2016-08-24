#include "gamelayer.h"

GameLayer* GameLayer::creategamelayer()
{
	auto temp = new GameLayer;
	temp->autorelease();
	temp->initgamelayer();
	return temp;
}

void GameLayer::initgamelayer()
{
	Layer::init();
	this->setAnchorPoint(Vec2(0, 0));
	
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		auto temp = Sprite::create("disable.png");
		temp->setAnchorPoint(Vec2(0.5, 0.5));
		//temp->setPosition(Director::getInstance()->getVisibleSize().width / 5 * 1 + ii * temp->getContentSize().width * 2,
			//temp->getContentSize().width * 5 - i * temp->getContentSize().width * 2);
		temp->setPosition(Director::getInstance()->getVisibleSize().width / 4 * (ii + 1),
			Director::getInstance()->getVisibleSize().width / 4 * (3.5 - i - 1));
		temp->retain();
		g_node[i][ii] = temp;
		this->addChild(temp);

		g_touched[i][ii] = false;
		g_nodeshuted[i][ii] = false;
	}

	g_magicbook = MagicBook::createmagicbook();
	g_magicbook->retain();
	this->addChild(g_magicbook);

	auto _listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(GameLayer::ontouchbegin, this);
	_listener->onTouchMoved = CC_CALLBACK_2(GameLayer::ontouchmove, this);
	_listener->onTouchEnded = CC_CALLBACK_2(GameLayer::ontouchend, this);
	this->getEventDispatcher()->addEventListenerWithFixedPriority(_listener, 1);
	_listener->retain();
	this->listener = _listener;

	g_drawnode = DrawNode::create();
	this->addChild(g_drawnode);

	this->streak = MotionStreak::create(0.3f, 0.1f, 25, Color3B(0,0,0), "streak.png");
	this->addChild(streak, GameObjectEffEct);
}

GameLayer::~GameLayer()
{
	this->disable();
	this->g_magicbook->removeFromParent();
	this->g_magicbook->release();
	this->g_magicbook = nullptr;
}

bool GameLayer::ontouchbegin(Touch* in, Event* who)
{
	g_begin = false;

	this->streak->setPosition(in->getLocation());
	this->streak->reset();

	auto loc = in->getLocation();
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		if (g_node[i][ii]->getBoundingBox().containsPoint(loc) && !g_touched[i][ii])
		{

			g_touched[i][ii] = true;
			if (g_nodeshuted[i][ii] == true)
			{
				g_touched[i][ii] = false;
				return true;
			}
		
			g_node[i][ii]->runAction(Sequence::create(ScaleTo::create(0.2, 1.8),ScaleTo::create(0.3, 1),nullptr));
			//g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(180, 0, 0)), nullptr));
			//g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, 0, 180)), nullptr));
			
			g_begin = true;

			Line temp;
			temp.begin = Vec2(g_node[i][ii]->getPosition());
			temp.end = Vec2(g_node[i][ii]->getPosition());
			g_lines.push_back(temp);
		}
	}
	return true;
}

void GameLayer::ontouchmove(Touch* in, Event* who)
{
	auto loc = in->getLocation();

	this->streak->setPosition(loc);

	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		if (g_node[i][ii]->getBoundingBox().containsPoint(loc) && !g_touched[i][ii])
		{
			g_touched[i][ii] = true;//正常设置被触摸
			if (g_nodeshuted[i][ii] == true)
			{
				g_touched[i][ii] = false;
				return;
			}

			if (!g_begin)
			{
				Line temp;
				temp.begin = Vec2(g_node[i][ii]->getPosition());
				temp.end = Vec2(g_node[i][ii]->getPosition());
				g_lines.push_back(temp);

				g_node[i][ii]->runAction(Sequence::create(ScaleTo::create(0.2, 1.8), ScaleTo::create(0.3, 1), nullptr));
			}

			g_begin = true;

			auto last = g_lines.begin();
			for (auto i = g_lines.begin(); i != g_lines.end(); i++)
				last = i;
			(*last).end = Vec2(g_node[i][ii]->getPosition());

			auto dir = (*last).begin - (*last).end;
			dir.normalize();
			if (dir.x < 0)
			{
				if (dir.y < 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, 180, -90)), nullptr));
				else if (dir.y == 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, 180, 0)), nullptr));
				else
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, 180, 90)), nullptr));
			}
			else if (dir.x == 0)
			{
				if (dir.y < 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(-180, 0, 0)), nullptr));
				else if (dir.y == 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, 0, 0)), nullptr));
				else
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(180, 0, 0)), nullptr));
			}
			else
			{
				if (dir.y < 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, -180, 90)), nullptr));
				else if (dir.y == 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, -180, 0)), nullptr));
				else
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, -180, -90)), nullptr));
			}

			Line temp;
			temp.begin = Vec2(g_node[i][ii]->getPosition());
			temp.end = Vec2(g_node[i][ii]->getPosition());
			g_lines.push_back(temp);
		}
	}
}

void GameLayer::ontouchend(Touch* in, Event* who)
{
	auto loc = in->getLocation();

	this->streak->setPosition(loc);

	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		if (g_node[i][ii]->getBoundingBox().containsPoint(loc) && !g_touched[i][ii])
		{
			g_touched[i][ii] = true;
			if (g_nodeshuted[i][ii] == true)
			{
				g_touched[i][ii] = false;
				return;
			}
			
			g_begin = true;

			auto last = g_lines.begin();
			for (auto i = g_lines.begin(); i != g_lines.end(); i++)
				last = i;
			(*last).end = Vec2(g_node[i][ii]->getPosition());

			auto dir = (*last).begin - (*last).end;
			dir.normalize();
			if (dir.x < 0)
			{
				if (dir.y < 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, 180, -90)), nullptr));
				else if (dir.y == 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, 180, 0)), nullptr));
				else
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, 180, 90)), nullptr));
			}
			else if (dir.x == 0)
			{
				if (dir.y < 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(-180, 0, 0)), nullptr));
				else if (dir.y == 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, 0, 0)), nullptr));
				else
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(180, 0, 0)), nullptr));
			}
			else
			{
				if (dir.y < 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, -180, 90)), nullptr));
				else if (dir.y == 0)
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, -180, 0)), nullptr));
				else
					g_node[i][ii]->runAction(Sequence::create(RotateBy::create(0.5, Vec3(0, -180, -90)), nullptr));
			}

			Line temp;
			temp.begin = Vec2(g_node[i][ii]->getPosition());
			temp.end = Vec2(g_node[i][ii]->getPosition());
			g_lines.push_back(temp);
		}
	}
	
	if (!g_begin)
		return;
	checkpass();
	freshnode();
}

void GameLayer::shutonenode()
{
	auto x = random<int>(0, 2);
	auto y = random<int>(0, 2);
	this->g_nodeshuted[x][y] = true;
	this->g_node[x][y]->runAction(Spawn::create(RotateTo::create(0.5, Vec3(90, 90, 0)), Sequence::create(DelayTime::create(0.25), CallFunc::create([=](){this->g_node[x][y]->setColor(Color3B(255, 0, 0)); }), nullptr), nullptr));
	
	this->scheduleOnce(CC_CALLBACK_0(GameLayer::refreshshut, this), 3,"refreshshut");
}

void GameLayer::refreshshut()
{
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		if (g_nodeshuted[i][ii] == true)
		{
			g_nodeshuted[i][ii] = false;
			g_node[i][ii]->runAction(RotateTo::create(0.5, Vec3(0, 0, 0)));
		}
	}
}

void GameLayer::freshnode()
{
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		if (g_touched[i][ii])
		{
			if (!g_nodeshuted[i][ii])
			{
				g_node[i][ii]->runAction(ScaleTo::create(0.5, 1));
				g_node[i][ii]->runAction(Sequence::create(RotateTo::create(0.5, Vec3(0, 0, 0)), nullptr));
			}
		}
		g_touched[i][ii] = false;
	}

	g_drawnode->clear();
	g_lines.clear();
}

void GameLayer::checkpass()
{
		auto one = (AppDelegate*)Application::getInstance();
		if (one->g_gamescene->g_sheeplayer->g_allcreater->size()==0)
			return;
		auto sheep = one->g_gamescene->g_sheeplayer->g_sheeps;
		auto wolf = one->g_gamescene->g_sheeplayer->g_wolves;
		for (auto now = sheep->begin(); now != sheep->end(); now++)
		{
			bool isjump = true;
			for (int i = 0; i < 3; i++)
			for (int ii = 0; ii < 3; ii++)
			{
				if (g_touched[i][ii] != (*now)->g_target[i][ii])
				{
					isjump = false;
				}
			}
			if (isjump)
			{
				(*now)->jump();
				return;
			}
		}
		
		for (auto now = wolf->begin(); now != wolf->end(); now++)
		{
			bool isjump = true;
			for (int i = 0; i < 3; i++)
			for (int ii = 0; ii < 3; ii++)
			{
				if (g_touched[i][ii] != (*now)->g_target[i][ii])
				{
					isjump = false;
				}
			}
			if (isjump)
			{
				(*now)->jump();
				return;
			}
		}
	
	auto isvail=g_magicbook->magic(g_touched);
}

void GameLayer::disable()
{
	if (this == nullptr)
		return;

	this->getEventDispatcher()->removeEventListener(this->listener);
	this->g_drawnode->clear();
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		this->g_node[i][ii]->runAction(FadeOut::create(0.5));
	}
}

void GameLayer::enable()
{
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		this->g_node[i][ii]->runAction(FadeIn::create(0.5));
	}
	auto _listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(GameLayer::ontouchbegin, this);
	_listener->onTouchMoved = CC_CALLBACK_2(GameLayer::ontouchmove, this);
	_listener->onTouchEnded = CC_CALLBACK_2(GameLayer::ontouchend, this);
	this->listener->release();
	this->listener = _listener;
	_listener->retain();
	this->getEventDispatcher()->addEventListenerWithFixedPriority(_listener, 1);
}

void GameLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	Layer::draw(renderer,transform,flags);
	for (auto i = g_lines.begin(); i != g_lines.end(); i++)
	{
		g_drawnode->drawSegment((*i).begin, (*i).end, 2.5, Color4F(0, 0, 0,999));
	}
}
