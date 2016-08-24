#include "sheep.h"

Sheep* Sheep::createsheep(float speed)
{
	auto temp = new Sheep;
	temp->autorelease();
	temp->initsheep(speed);
	return temp;
}

void Sheep::initsheep(float speed)
{
	Sprite::initWithFile("sheep1.png");
	this->setAnchorPoint(Vec2(0, 0));
	initsprite();
	inittarget();

	auto body = PhysicsBody::createBox(this->getContentSize());
	body->setRotationEnable(false);
	body->setCategoryBitmask(Collision_Sheep);
	body->setCollisionBitmask(Collision_Sheep);
	body->setGravityEnable(false);//为了防止嵌地抖动，只能无视重力，在起跳后，重新打开重力
	this->setPhysicsBody(body);

	this->g_vx = speed;
	this->g_ismove = true;
	this->g_jumped = false;
	this->g_isdead = false;
	this->g_bride = nullptr;
	this->scheduleUpdate();
	this->setScale(0.7);

	Vector<SpriteFrame*> animatedata;
	animatedata.pushBack(SpriteFrame::create("sheep1.png", Rect(0, 0, 125, 89)));
	animatedata.pushBack(SpriteFrame::create("sheep2.png", Rect(0, 0, 125, 89)));
	Animation* animation = Animation::createWithSpriteFrames(animatedata, 1);
	this->walk_animate = Animate::create(animation);
	walk_animate->retain();
	Vector<SpriteFrame*> animatedata2;
	animatedata2.pushBack(SpriteFrame::create("sheep_dead1.png", Rect(0, 0, 125, 89)));
	animatedata2.pushBack(SpriteFrame::create("sheep_dead2.png", Rect(0, 0, 125, 89)));
	Animation* animation2 = Animation::createWithSpriteFrames(animatedata2, 0.3);
	this->dead_animate = Animate::create(animation2);
	dead_animate->retain();

	this->walkanimate();
	if (UserDefault::getInstance()->getBoolForKey("BGM",true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sheep.mp3");
	}
}

Sheep::~Sheep()
{
	this->unscheduleUpdate();
}

void Sheep::remove()
{
	auto one = (AppDelegate*)Application::getInstance();
	this->removeFromParent();
	one->g_gamescene->g_sheeplayer->g_sheeps->eraseObject(this);
	one->g_gamescene->g_sheeplayer->g_allcreater->eraseObject(this);
	this->dead_animate->release();
	this->walk_animate->release();
	this->release();
}

void Sheep::inittarget()
{
	int x = random<int>(0, 2);
	int y = random<int>(0, 2);
	g_target[x][y] = true;
	g_targetnode[x][y]->setColor(Color3B(255, 255, 255));

	for (int i = 0; i < 2; i++)
	{
		if (random<float>(0, 1) < 0.5)
			x = MAX(0, x - 1);
		else
			x = MIN(x + 1, 2);
		if (random<float>(0, 1) < 0.5)
			y = MAX(0, y - 1);
		else
			y = MIN(y + 1, 2);
		g_target[x][y] = true;
		g_targetnode[x][y]->setColor(Color3B(255, 255, 255));
	}
}

void Sheep::initsprite()
{
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		auto temp = Sprite::create("point.png");
		temp->setAnchorPoint(Vec2(0.5, 0.5));
		temp->setPosition((this->getBoundingBox().size.width / 2 + (ii - 1) * 1.5 * temp->getContentSize().width) - 15,
			(this->getBoundingBox().size.height / 2 + (1 - i) * 1.5 * temp->getContentSize().height) + 7);

		temp->retain();
		g_targetnode[i][ii] = temp;
		this->addChild(temp);
		temp->setColor(Color3B(80, 0, 0));

		g_target[i][ii] = false;
	}
}

void Sheep::hidetarget()
{
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		g_targetnode[i][ii]->runAction(FadeOut::create(0.3));
	}
}

void Sheep::update(float dt)
{
	move(dt);
	checkpos();
}

void Sheep::move(float dt)
{
	if (g_ismove)
	{
		auto pos = this->getPosition();
		pos.x += dt*g_vx;
		this->setPosition(pos);
	}
}

void Sheep::jump()
{
	if (g_isdead)
		return;
	if (g_isctached)
	{
		g_jumped = true;
		return;
	}
	this->getPhysicsBody()->setGravityEnable(true);
	if (!g_jumped)
	{
		this->getPhysicsBody()->applyImpulse(JumpImpulse);
		this->g_vx += 50;
		g_jumped = true;
		
		this->jumpanimate();
	}
}

void Sheep::checkpos()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto bar = one->g_gamescene->g_sheeplayer->g_bar->getBoundingBox();
	if (!g_isdead)
	{
		if (isRightXout())
		{
			one->g_gamescene->changescores(true);
			this->remove();
			return;
		}
		if (isBarcontact(bar))
		{
			one->g_gamescene->changehp(false);
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

bool Sheep::isBarcontact(Rect bar)
{
	if (this->getBoundingBox().containsPoint(Vec2(bar.origin.x - 1, bar.origin.y + bar.size.height / 2)))
		return true;
	if (this->getBoundingBox().containsPoint(Vec2(bar.origin.x, bar.origin.y + bar.size.height)))
		return true;
	if (this->getBoundingBox().containsPoint(bar.origin + bar.size))
		return true;
	return false;
}

bool Sheep::isRightXout()
{
	if (this->getPosition().x >= Director::getInstance()->getVisibleSize().width + this->getBoundingBox().size.width / 2)
		return true;
	return false;
}

bool Sheep::isDownYout()
{
	if (this->getPosition().y < 0 - this->getBoundingBox().size.height)
		return true;
	return false;
}

void Sheep::dead()
{
	this->getPhysicsBody()->setGravityEnable(true);
	this->getPhysicsBody()->setRotationEnable(true);
	auto ver = this->getPhysicsBody()->getVelocity();
	ver.y = 0;
	this->getPhysicsBody()->setVelocity(ver);
	this->getPhysicsBody()->setCollisionBitmask(Collision_DeadSheep);
	this->getPhysicsBody()->applyImpulse(DeadJumpImpulse);
	this->getPhysicsBody()->setAngularVelocity(DeadTorque);
	this->g_ismove = false;
	this->g_isdead = true;

	this->deadanimate();
}

void Sheep::beencatched(Bride* who)
{
	this->deadanimate();

	this->unscheduleUpdate();
	this->schedule(CC_CALLBACK_0(Sheep::beencatchedmove, this), "beencatchedmove");
	this->getPhysicsBody()->setGravityEnable(false);
	this->getPhysicsBody()->setCategoryBitmask(Collision_DeadSheep);
	this->g_bride = who;
	this->g_isctached = true;
}

void Sheep::beencatchedmove()
{
	auto pos=g_bride->getPosition();
	pos.y -= this->getBoundingBox().size.height / 2;
	this->setPosition(pos);
}

void Sheep::walkanimate()
{
	auto temp = RepeatForever::create(Spawn::create(this->walk_animate, Sequence::create(EaseExponentialOut::create(RotateBy::create(0.5, 1)),
		EaseExponentialInOut::create(RotateBy::create(1, -2)), EaseBackIn::create(RotateBy::create(0.5, 1)), nullptr), nullptr));
	temp->setTag(Walk_Animate);
	this->runAction(temp);
}

void Sheep::jumpanimate()
{
	this->getActionManager()->removeActionByTag(Walk_Animate,this);
	this->setSpriteFrame(SpriteFrame::create("sheep1.png", Rect(0, 0, 125, 89)));
	/*this->runAction(Sequence::create(EaseElasticOut::create(RotateBy::create(1, Vec3(-10, 0, 0))),
		EaseExponentialIn::create(RotateTo::create(0.5, Vec3(0, 0, 0))), nullptr));*/
	this->runAction(Sequence::create(EaseElasticOut::create(ScaleBy::create(0.3, 0.8, 1.2)), DelayTime::create(0.7),
		EaseExponentialIn::create(ScaleTo::create(0.3, 0.7, 0.7)), nullptr));

	auto pos = this->getPosition();
	pos.y -= this->getBoundingBox().size.height / 2;
	auto smokepart = TextureCache::getInstance()->addImage("jump_paticle.png");
	auto smoke = ParticleMeteor::create();
	smoke->setColor(Color3B::BLACK);
	smoke->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	smoke->setEndSize(0.5);
	smoke->setScale(2);
	smoke->setScaleY(0.5);
	smoke->setGravity(Vec2(-10, 10));
	smoke->setEmissionRate(50);
	smoke->setDuration(0.5);
	smoke->setLife(0.5);
	smoke->setAngle(270);
	smoke->setPosition(pos);
	this->getParent()->addChild(smoke, GameObjectEffEct);

	this->scheduleOnce([this](float in){if (!this->g_isdead){ this->walkanimate(); } }, 0.4, "returntowalk");

	this->hidetarget();

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.mp3");
	}
}

void Sheep::deadanimate()
{
	this->getActionManager()->removeAllActionsFromTarget(this);
	this->setScale(0.7);

	auto temp = RepeatForever::create(this->dead_animate);
	temp->setTag(Dead_Aninate);
	this->runAction(temp);

	this->hidetarget();

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sheep_dead.mp3");
	}
}