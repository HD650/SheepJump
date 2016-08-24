#include "bride.h"

Bride* Bride::createbride()
{
	auto temp = new Bride;
	temp->autorelease();
	temp->initbride();
	return temp;
}

void Bride::initbride()
{
	SheepLayer* temp = ((AppDelegate*)Application::getInstance())->g_gamescene->g_sheeplayer;
	Sprite::initWithFile("bride1.png");
	this->setAnchorPoint(Vec2(0, 0));
	
	auto body=PhysicsBody::createBox(this->getContentSize());
	body->setCategoryBitmask(Collision_DeadSheep);
	body->setGravityEnable(false);
	this->setPhysicsBody(body);

	Vector<SpriteFrame*> animatedata;
	animatedata.pushBack(SpriteFrame::create("bride1.png", Rect(0, 0, 125, 108)));
	animatedata.pushBack(SpriteFrame::create("bride2.png", Rect(0, 0, 125, 108)));
	Animation* animation = Animation::createWithSpriteFrames(animatedata, 1);
	this->walk_animate = Animate::create(animation);
	walk_animate->retain();

	g_target = nullptr;
	g_iscatch = false;
	//auto i = temp->g_allcreater->begin();
	gotowhere = GotoWhere::Idel;
	
	//this->g_target = (*i);

	this->scheduleUpdate();
	this->setScale(0.65);

	this->flyanimate();

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("birde.mp3");
	}
}

void Bride::remove()
{
	auto one = (AppDelegate*)Application::getInstance();
	this->unscheduleAllSelectors();
	this->unscheduleAllCallbacks();
	this->unscheduleUpdate();
	one->g_gamescene->g_sheeplayer->g_brides->eraseObject(this);
	this->removeFromParent();
	this->walk_animate->release();
	this->release();
}

void Bride::update(float dt)
{
	SheepLayer* temp = ((AppDelegate*)Application::getInstance())->g_gamescene->g_sheeplayer;
	if (!g_iscatch)
	{
		g_target = nullptr;
		for (auto i = temp->g_sheeps->begin(); i != temp->g_sheeps->end(); i++)
		{
			if (!(*i)->g_isdead&&!(*i)->g_isctached && (*i)->g_cancatch)
			{
				g_target = (*i);
				break;
			}
		}
		for (auto i = temp->g_wolves->begin(); i != temp->g_wolves->end(); i++)
		{
			if (!(*i)->g_isdead&&!(*i)->g_isctached && (*i)->g_cancatch)
			{
				g_target = (*i);
				break;
			}
		}
		for (auto i = temp->g_monster->begin(); i != temp->g_monster->end(); i++)
		{
			if (!(*i)->g_isdead&&!(*i)->g_isctached&&(*i)->g_cancatch)
			{
				g_target = (*i);
				break;
			}
		}
	}
	
	if (this->gotowhere == GotoWhere::Target)
		this->flytosheep(dt);
	checkpos();
}

void Bride::beginpredate()
{
	this->gotowhere = GotoWhere::Target;
	this->getActionManager()->removeAllActionsFromTarget(this);
	this->unschedule("idel");
}

void Bride::idel()
{
	Vec2 pos = this->getPosition();
	pos.x -= BrideSpeed*0.016;
	this->setPosition(pos);
	if (this->isFlippedX())
		this->setFlipX(false);
}

void Bride::flytosheep(float dt)
{
	if (g_target == nullptr)
	{
		this->flyanimate();
		return;
	}
	Vec2 dis = g_target->getPosition();
	dis.y += g_target->getBoundingBox().size.height / 2;
	Vec2 pos = this->getPosition();
	Vec2 dir = (dis - pos);
	dir.normalize();
	
	if (dir.x > 0 && !this->isFlipX())
	{
		this->setFlipX(true);
	}
	else if (dir.x < 0 && this->isFlipX())
	{
		this->setFlippedX(false);
	}

	this->setPosition(pos + dir*BrideSpeed*1.5*dt);
	if (this->cancatch()&&!(this->g_iscatch))
	{
		this->gotowhere = GotoWhere::Away;
		this->catchsheep();
		this->g_iscatch = true;
		this->flyawayanimate();
	}
}

//已经使用idle代替
void Bride::flyaway( )
{
	Vec2 dis = Vec2(-200, Director::getInstance()->getVisibleSize().height / 4 * 3);
	Vec2 pos = this->getPosition();
	Vec2 dir = (dis - pos);
	dir.normalize();
	
	if (dir.x > 0 && !this->isFlipX())
	{
		this->setFlipX(true);
	}
	else if (dir.x < 0 && this->isFlipX())
	{
		this->setFlippedX(false);
	}

	dir = dir / 50;
	this->setPosition(pos + dir*BrideSpeed);
}

void Bride::checkpos()
{
	if (this->getPosition().x <= -100)
	{
		if (g_iscatch)
		{
			if (g_target != nullptr)
				g_target->remove();
			this->remove();
		}
		else
			this->remove();
	}
}

bool Bride::cancatch()
{
	Vec2 pos = this->getPosition();
	Vec2 dis = g_target->getPosition();
	dis.y += g_target->getBoundingBox().size.height / 2;
	if (pos.distance(dis) <= 2)
	{
		return true;
	}
	return false;
}

void Bride::catchsheep()
{
	g_target->beencatched(this);
}

void Bride::flyanimate()
{
	this->runAction(RepeatForever::create(Spawn::create(this->walk_animate, Sequence::create(EaseExponentialOut::create(MoveBy::create(0.5, Vec2(0, 5))),
		EaseExponentialInOut::create(MoveBy::create(1, Vec2(0, -10))), EaseBackIn::create(MoveBy::create(0.5, Vec2(0, 5))), nullptr), nullptr)));
	this->schedule(CC_CALLBACK_0(Bride::idel, this), "idel");
}

void Bride::flyawayanimate()
{
	this->runAction(RepeatForever::create(Spawn::create(this->walk_animate, Sequence::create(EaseExponentialOut::create(MoveBy::create(0.5, Vec2(0, 5))),
		EaseExponentialInOut::create(MoveBy::create(1, Vec2(0, -10))), EaseBackIn::create(MoveBy::create(0.5, Vec2(0, 5))), nullptr), nullptr)));
	this->schedule(CC_CALLBACK_0(Bride::idel, this), "idel");
}